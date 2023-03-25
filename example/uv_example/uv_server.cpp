#include "uv_server.hpp"
#include "../../header.h"
#include "common_uv.h"
#include "message_progress.hpp"
#include "uv.h"
#include <ratio>
#include <thread>

CUVServer::CUVServer() {}

CUVServer::~CUVServer() {}

CUVServer *CUVServer::get_instance() {
  static std::once_flag _flag;
  static CUVServer _instance;
  std::call_once(_flag, [&]() {
    _instance.init();
    LOG(INFO) << "do init cuvserver";
  });
  return &_instance;
}

bool CUVServer::init() {
  m_pLoopHandle = uv_loop_new();
  if (!m_pLoopHandle) {
    return false;
  }
  this->active_idle();
  return true;
}

bool CUVServer::push_event(EventBase *event) {
  while (!eventInputQueue.try_enqueue(event)) {
    LOG(INFO) << "add event";
  }
  return true;
}

bool CUVServer::pop_event(EventBase *event) {
  return eventInputQueue.try_dequeue(event);
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
  }

  // 新 socket 用于和客户端通信
  uv_tcp_t *client = new uv_tcp_t;
  uv_tcp_init(CUVServer::get_instance()->get_loop_handle(), client);

  // 绑定到新的 TCP 连接上
  if (uv_accept(server, (uv_stream_t *)client) == 0) {
    LOG(INFO) << "Accepted a new client.\n";

    // TODO: 在这里进行业务逻辑处理
    // uv_read_start((uv_stream_t *)client, on_alloc_buffer, on_read_data);

  } else {
    // 关闭新连接的套接字
    uv_close((uv_handle_t *)client, common_close_cb);
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

int CUVServer::progress_input_event(uint32_t per_count) {
  int count = 0;
  EventBase *base;
  while (count < per_count && eventInputQueue.try_dequeue(base)) {
    count++;
    switch (base->m_wType) {
    case EVENT_LISTEN: {
      LOG(INFO) << "new listen event coming";
      EventListen *event = (EventListen *)base;
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
