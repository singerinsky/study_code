#ifndef _UV_SERVER_H_
#define _UV_SERVER_H_

#include "../../src/util/concurrentqueue.h"
#include "message_progress.hpp"
#include "net_service.h"
#include "object_pool.h"
#include "uv.h"
#include "uv_net_client.h"
#include <cstdint>
#include <unordered_map>
class CUVServer {
  SINGLETON_FUN_DEF(CUVServer)

public:
  bool Init();

  void start();

  void pause(uint32_t ms);

  void active_idle();

  static void while_idle(uv_idle_t *idle_t);

  uv_loop_t *get_loop_handle() { return m_pLoopHandle; }

  static void on_connection(uv_stream_t *server, int status);

  bool push_request(RequestBase *event);

  bool pop_event(EventBase *event);

  int progress_input_event(uint32_t per_count);

protected:
  uv_tcp_t *attach_net_service(NetServiceBase *pNetService);

  uv_tcp_t *attach_net_connection(NetServiceBase *pNetService);

  bool add_hanle(uint32_t dwConnID, uv_handle_t *pHandle);

  void remove_handle(uint32_t dwConnID);

  bool add_client(uint32_t dwID, CUvNetClient *);

  CUvNetClient *get_client(uint32_t dwID);

  void remove_client(uint32_t dwID);

private:
  uv_loop_t *m_pLoopHandle = nullptr;

  uv_idle_t *idle_t = nullptr;

  moodycamel::ConcurrentQueue<RequestBase *> m_requestInputQueue;
  moodycamel::ConcurrentQueue<EventBase *> m_eventOutputQueue;

  std::unordered_map<uint32_t, uv_handle_t *> m_allHandle;
  std::unordered_map<uint32_t, CUvNetClient *> m_allClientMap;
};
#endif