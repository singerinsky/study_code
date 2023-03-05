#include "../header.h"
#include "uv.h"
#include <gtest/gtest.h>

#define ARRAY_SIZE(_ARRAY_) (sizeof(_ARRAY_)/sizeof((_ARRAY_)[0]))

void function_timer_once_callback(uv_timer_t* handle)
{
    LOG(INFO) << "function_timer_once_callback";
}

void function_timer_repeat_callback(uv_timer_t* handle)
{
    LOG(INFO) << "function_timer_repeat_callback";
}

void function_timer_never_callback(uv_timer_t* handle)
{
    LOG(INFO) << "function_timer_never_callback";
}
void alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf)
{
    buf->base = (char*)malloc(suggested_size);
    buf->len = suggested_size;
}
void new_connection(uv_stream_t* server, int status)
{
    LOG(INFO) << "new connection " << status;
    LOG(INFO) << "fd:" << server->u.fd;
    // uv_close((uv_handle_t*)server, nullptr);
    uv_tcp_t* client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(uv_default_loop(), client);
    if (uv_accept(server, (uv_stream_t*)client) == 0)
    {
        uv_read_start((uv_stream_t*)client, alloc_buffer, nullptr);
    }
    else
    {
        uv_close((uv_handle_t*)client, NULL);
    }
}

void add_tcp_event(uv_loop_t* loop, int port)
{
    uv_tcp_t* tcp_handle_t = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", port, &addr);


    uv_tcp_init(loop, tcp_handle_t);
    auto rst = uv_tcp_bind(tcp_handle_t, (const struct sockaddr*)&addr, 0);
    LOG(INFO) << "bind rst:" << rst;
    int r = uv_listen((uv_stream_t* ) tcp_handle_t, 10, new_connection); //listen
}

TEST(TestUv, test001)
{
    uv_timer_t once_timers[10];
    uv_timer_t* once;
    uv_timer_t repeat, never;
    unsigned int i;
    int r;

    uint64_t start_time = uv_now(uv_default_loop());

    /* Let 10 timers time out in 500 ms total. */
    for (i = 0; i < ARRAY_SIZE(once_timers); i++)
    {
        once = once_timers + i;
        r = uv_timer_init(uv_default_loop(), once);

        r = uv_timer_start(once, function_timer_once_callback, i * 50, 0);

    }

    /* The 11th timer is a repeating timer that runs 4 times */
    // r = uv_timer_init(uv_default_loop(), &repeat);

    // r = uv_timer_start(&repeat, function_timer_repeat_callback, 100, 100);


    /* The 12th timer should not do anything. */
    r = uv_timer_init(uv_default_loop(), &never);

    r = uv_timer_start(&never, function_timer_never_callback, 100, 100);

    r = uv_timer_stop(&never);

    uv_unref((uv_handle_t*)&never);

    add_tcp_event(uv_default_loop(), 9090);

    int count = 0;
    //while (true)
    {
        int rst = uv_run(uv_default_loop(), UV_RUN_DEFAULT);
        LOG(INFO) << " after call uv_run()" << rst << " count:" << count;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }


    //printf("repeat_cb_called %d\n", repeat_cb_called);


    ASSERT_TRUE(500 <= uv_now(uv_default_loop()) - start_time);

}