#include "test_zeromq.h"
#include "../header.h"
#include <thread>

bool luncher_zmq_tcp_server()
{
    void* context = zmq_ctx_new();
    void* responder = zmq_socket(context,ZMQ_REP);
    int rc = zmq_bind(responder,"tcp://*:5555");
    while(1)
    {
        char buffer[10];
        zmq_recv(responder,buffer,10,0);
        LOG(INFO)<<"Server received message "<<buffer;
        sleep(1);
        zmq_send(responder,"Hello World",strlen("Hello World"),0);
    }
    return true;
}

bool luncher_zmq_tcp_client()
{
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:5555");

    int request_nbr;
    for (request_nbr = 0; request_nbr != 10; request_nbr++) {
        char buffer [10];
        printf ("Client Sending Hello %d…\n", request_nbr);
        zmq_send (requester, "Hello", 5, 0);
        zmq_recv (requester, buffer, 10, 0);
        printf ("Client Received World %d\n", request_nbr);
        sleep(1);
    }
    zmq_close (requester);
    zmq_ctx_destroy (context);
    return true;
}

TEST(Test_ZMQ,test_001)
{
    auto server_handle = std::async(std::launch::async,luncher_zmq_tcp_server);

    auto client_handle = std::async(std::launch::deferred,luncher_zmq_tcp_client);
    
    ASSERT_EQ(true,client_handle.get());
}

TEST(Test_ZMQ,test_002)
{
    LOG(INFO)<<sizeof(zmq_msg_t);
}
