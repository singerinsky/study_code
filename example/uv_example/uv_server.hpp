#ifndef _UV_SERVER_H_
#define _UV_SERVER_H_

#include "../../header.h"
#include "../util/concurrentqueue.h"
#include "message_progress.hpp"
#include "net_service.h"
#include "uv.h"

class CUVServer {
protected:
  CUVServer();

  ~CUVServer();
  CUVServer(const CUVServer &) = delete;
  CUVServer(CUVServer &&) = delete;
  CUVServer &operator=(const CUVServer &) = delete;
  CUVServer &operator=(CUVServer &&) = delete;

public:
  bool init();

  void start();

  void pause(uint32_t ms);

  void active_idle();

  static CUVServer *get_instance();

  static void while_idle(uv_idle_t *idle_t);

  uv_loop_t *get_loop_handle() { return m_pLoopHandle; }

  static void on_connection(uv_stream_t *server, int status);

  bool push_event(EventBase *event);

  bool pop_event(EventBase *event);

  int progress_input_event(uint32_t per_count);

protected:
  uv_tcp_t *attach_net_service(NetServiceBase *pNetService);

  uv_tcp_t *attach_net_connection(NetServiceBase *pNetService);

private:
  uv_loop_t *m_pLoopHandle = nullptr;

  uv_idle_t *idle_t = nullptr;

  moodycamel::ConcurrentQueue<EventBase *> eventInputQueue;
  moodycamel::ConcurrentQueue<EventBase *> eventOutputQueue;
};
#endif