#include "uv_server.hpp"
#include "../../header.h"
#include "common_uv.h"
#include "message_progress.hpp"
#include "uv.h"
#include "uv_net_client.h"
#include <ratio>
#include <thread>
#include <utility>

static void client_alloc_cb(uv_handle_t *handle, size_t suggested_size,
                            uv_buf_t *buf) {
  CUvNetClient *pClient = (CUvNetClient *)handle->data;
  buf->base = pClient->getBufferHeadForUVWrite();
  buf->len = pClient->getBufferSizeForUVWrite();
  LOG(INFO) << "call alloc_cb" << buf->base
            << "  suggested_size:" << suggested_size;
}

void client_close_cb(uv_handle_t *close_handle_t) {
  CUvNetClient *pClient = (CUvNetClient *)close_handle_t->data;
  LOG(INFO) << close_handle_t
            << "disconnection from client_close_cb id:" << pClient->GetID();
  NetClientPool::GetInstance()->ReleaseObject(pClient->GetID());
}

void client_recv_cb(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf) {
  if (nread < 0) {
    if (!uv_is_closing((uv_handle_t *)stream)) {
      uv_close((uv_handle_t *)stream, client_close_cb);
    }
    LOG(INFO) << "disconnection";
    // handle the data read error
  } else if (nread == 0) {
    // do nothing
    LOG(INFO) << "read data event coming";
  } else {
    // handle the read data
    LOG(INFO) << "read data event coming";
    CUvNetClient *pClient = (CUvNetClient *)stream->data;
    pClient->moveReadBufferHead(nread);
    pClient->parseReadBuffer();
  }
}

SINGLETON_FUN_BODY(CUVServer)

bool CUVServer::Init() {
  m_pLoopHandle = uv_loop_new();
  if (!m_pLoopHandle) {
    return false;
  }
  this->active_idle();
  return true;
}

bool CUVServer::push_request(RequestBase *request) {
  while (!m_requestInputQueue.try_enqueue(request)) {
    LOG(INFO) << "add event";
  }
  return true;
}

bool CUVServer::pop_event(EventBase *event) {
  return m_eventOutputQueue.try_dequeue(event);
}

void CUVServer::pause(uint32_t ms) {
  chrono::duration<int, std::milli> tSleepTime(ms);
  this_thread::sleep_for(tSleepTime);
}

void CUVServer::active_idle() {
  LOG(INFO) << "no active event ,enter idle";
  this->idle_t = new uv_idle_t();
  uv_idle_init(this->m_pLoopHandle, idle_t);
}

void CUVServer::while_idle(uv_idle_t *idle_t) {
  chrono::duration<int, std::milli> tSleepTime(100);
  LOG(INFO) << "proces idle function";
  this_thread::sleep_for(tSleepTime);
}

void CUVServer::on_connection(uv_stream_t *server, int status) {
  if (status < 0) {
    LOG(ERROR) << "New connection error " << uv_strerror(status);
    return;
  } else if (status == 0) {
    // 新 socket 用于和客户端通信
    uv_tcp_t *client = new uv_tcp_t;
    uv_tcp_init(CUVServer::GetInstance()->get_loop_handle(), client);

    // 绑定到新的 TCP 连接上
    if (uv_accept(server, (uv_stream_t *)client) == 0) {
      LOG(INFO) << "Accepted a new client.\n";
      init_tcp_connection(client);

      // TODO 加入到管理器

      // TODO: 在这里进行业务逻辑处理
      uv_read_start((uv_stream_t *)client, client_alloc_cb, client_recv_cb);
    } else {
      LOG(ERROR) << "accept client error";
    }
  } else {
    LOG(INFO) << "on_connection error!";
  }
}

uv_tcp_t *CUVServer::attach_net_service(NetServiceBase *pNetService) {
  struct sockaddr_in addr;
  uv_ip4_addr(pNetService->GetIPString(), pNetService->GetPort(), &addr);

  uv_tcp_t *pServiceHandle = new uv_tcp_t;
  pServiceHandle->data = pNetService;
  uv_tcp_init(this->get_loop_handle(), pServiceHandle);
  uv_tcp_bind(pServiceHandle, (const struct sockaddr *)&addr, 0);

  int r = uv_listen((uv_stream_t *)pServiceHandle, SOMAXCONN,
                    &CUVServer::on_connection);
  if (r != 0) {
    LOG(ERROR) << "init service net failed!";
    uv_close((uv_handle_t *)pServiceHandle, common_close_cb);
    return nullptr;
  }
  return pServiceHandle;
}

bool CUVServer::add_hanle(uint32_t dwConnID, uv_handle_t *pHandle) {
  auto p = make_pair(dwConnID, pHandle);
  return m_allHandle.insert(p).second;
}

void CUVServer::remove_handle(uint32_t dwConnID) {
  m_allHandle.erase(dwConnID);
}

int CUVServer::progress_input_event(uint32_t per_count) {
  int count = 0;
  RequestBase *base;
  while (count < per_count && m_requestInputQueue.try_dequeue(base)) {
    count++;
    switch (base->m_wType) {
    case REQUEST_LISTEN: {
      LOG(INFO) << "new listen event coming";
      RequestListen *event = (RequestListen *)base;
      auto handle = attach_net_service(event->m_pNetService);
      if (handle == nullptr) {
        // TODO send error event!
      }
    } break;
    default:
      LOG(WARNING) << "Unknown event type: " << base->m_wType;
      ;
    }

    delete base;
  }
  // LOG(INFO) << "this round process event:" << count;
  return per_count;
}

void CUVServer::start() {
  if (m_pLoopHandle) {
    int rst = 0;
    while (true) {
      auto process_num = progress_input_event(100);
      rst = uv_run(m_pLoopHandle, UV_RUN_ONCE);
      // LOG(INFO) << "running uv server,after one round,rst:" << rst;
    }
  }
}
