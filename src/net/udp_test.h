#ifndef A619AC1B_ACB2_43DF_8C81_3702D1C5FAA2
#define A619AC1B_ACB2_43DF_8C81_3702D1C5FAA2
#include "kcp/ikcp.h"

class UdpServer
{
public:
    ikcpcb* GetKcpCb()
    {
        return m_pKcpCB;
    }

    void SetKcpCb(ikcpcb* pkcp)
    {
        m_pKcpCB = pkcp;
    }
    static int ServerSendMsg(const char* buf, int len,
                             ikcpcb* kcp, void* user);
private:
    ikcpcb* m_pKcpCB;
};


class UdpClient
{
    ikcpcb* GetKcpCb()
    {
        return m_pKcpCB;
    }

    void SetKcpCb(ikcpcb* pkcp)
    {
        m_pKcpCB = pkcp;
    }
    static int ClientSendMsg(const char* buf, int len,
                             ikcpcb* kcp, void* user);
private:
    ikcpcb* m_pKcpCB;
};

void BuildUdpServer();
void BuildUdpClient();

#endif /* A619AC1B_ACB2_43DF_8C81_3702D1C5FAA2 */
