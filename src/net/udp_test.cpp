#include "udp_test.h"
#include "kcp/ikcp.h"
#include "../header.h"

UdpServer g_server;
UdpClient g_client;

int UdpServer::ServerSendMsg(const char* buf, int len, ikcpcb* kcp,
                             void* user)
{

    return 0;
}

int UdpClient::ClientSendMsg(const char* buf, int len, ikcpcb* kcp,
                             void* user)
{
    return 0;
}
void BuildUdpServer()
{
    ikcpcb* server_kcpcb = ikcp_create(0, &g_server);
    g_server.SetKcpCb(server_kcpcb);
    server_kcpcb->output = &UdpServer::ServerSendMsg;
    ikcp_release(server_kcpcb);
}

void BuildUdpClient() {}

TEST(UDP_TEST, UnitOne)
{
    BuildUdpServer();
}
