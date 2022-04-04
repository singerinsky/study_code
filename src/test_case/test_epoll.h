#ifndef __TEST_EPOLL_H__
#define __TEST_EPOLL_H__
#include "../header.h"
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "sys/epoll.h"
#include <sys/socket.h>
#include "fcntl.h"
#include "../util/concurrentqueue.h"
#include "../util/class_sample.h"
#include <fstream>

constexpr int _epoll_size_ = 100;

enum{
    eFD_LISTEN,
    eFD_CLIENT,
    eFD_LOCALFILE,
};


#define BUFF_SIZE 10240
struct EpollDataStruct
{
    int  fd_type;
    int  fd;
    void *data;
    char recv_buff[BUFF_SIZE];
    char* read_flag = recv_buff;
    char send_buff[BUFF_SIZE];
    char* write_flag = send_buff;
    EpollDataStruct()
    {
        fd_type = 0;
        fd = 0;
        data = nullptr;
    }
};


class epoll_ctrl
{
    public:
    bool add_fd_to_epoll(EpollDataStruct* p_data)
    {
        epoll_event event;
        event.events = EPOLLIN;
        int rst = epoll_ctl(fd_epoll_ctl,EPOLL_CTL_ADD,p_data->fd,&event);
        return rst == 0;
    }

    int fd_epoll_ctl;
};

epoll_ctrl g_epoll_ctrl;

int create_sock()
{
    int opt = 1;
    socklen_t l = sizeof(opt);
    int new_fd = socket(AF_INET,SOCK_STREAM,0);
    setsockopt(new_fd, SOL_SOCKET, SO_REUSEADDR, &opt, l);
    if(new_fd == -1)
    {
        LOG(ERROR)<<"create new socket error, error no :"<<errno;
        return -1;
    }
    return new_fd;
}

int bind_socket(int fd)
{
    struct sockaddr_in bind_addr;
    memset(&bind_addr, 0, sizeof(sockaddr_in));
    bind_addr.sin_family = AF_INET;
    bind_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind_addr.sin_port = htons(5688);

    int rst = bind(fd,(const sockaddr*)&bind_addr,sizeof(sockaddr));
    if(rst == -1){
        LOG(ERROR)<<"bind socket failed! errno is "<<errno;
        return -1;
    }
    LOG(INFO)<<"bind socket success!";
    return rst; 
}

int listen_sock(int fd)
{
    int rst = listen(fd,128);
    if(rst == -1)
    {
        LOG(INFO)<<"listen socket failed!";
    }
    return 0;
}

EpollDataStruct* init_client_sock(int fd)
{
    int flag = 1;
    
    if(0 != setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&flag,sizeof(int)))
    {
        LOG(INFO)<<"set socket "<<fd<<"reuseaddr failed!";
        return nullptr;
    }
    EpollDataStruct* client_sock = new EpollDataStruct();
    client_sock->fd = fd;
    client_sock->fd_type = eFD_CLIENT;
    client_sock->data = nullptr;
    return client_sock;
}

bool add_client_fd_to_epoll(int epoll_fd,EpollDataStruct* pclient)
{
    epoll_event event;
    event.data.ptr = (void*)pclient;
    event.events = EPOLLIN;
    int rst = epoll_ctl(epoll_fd,EPOLL_CTL_ADD,pclient->fd,&event);
    if(rst != 0)
    {
        LOG(INFO)<<"add client fd to epoll failed! errno:"<<errno;
        return false;
    }
    return true;
}


void start_epoll_server()
{
    SampleClass* p_data = new SampleClass();
    EpollDataStruct* epoll_data_ptr = new EpollDataStruct();
    epoll_data_ptr->fd_type = eFD_LISTEN;
    epoll_data_ptr->data = (void*)p_data;
    int epoll_fd =  epoll_create(_epoll_size_);
    LOG(INFO)<<"create epoll fd "<<epoll_fd;
    ASSERT_TRUE(epoll_fd != 0);

    g_epoll_ctrl.fd_epoll_ctl = epoll_fd;
    int new_fd = create_sock();
    ASSERT_TRUE(new_fd != -1);
    int rst = bind_socket(new_fd);
    listen_sock(new_fd);
    epoll_data_ptr->fd = new_fd;
    epoll_event event;
    event.events = EPOLLIN;
    event.data.ptr = (void*)epoll_data_ptr;
    int add_rst = epoll_ctl(epoll_fd,EPOLL_CTL_ADD,new_fd,&event);
    if(add_rst == -1)
    {
        LOG(ERROR)<<"add fd to epoll failed! errno :"<<errno;
    }

    while(true)
    {
        epoll_event event_list[200];
        int event_rst = epoll_wait(epoll_fd,event_list , 200, 5000);
        if(event_rst == 0)
        {
            usleep(1000*1000);
            LOG(INFO)<<"epoll wait back with event size 0";
        }else if(event_rst == -1)
        {
            LOG(ERROR)<<"epoll wait back with error ,errno:"<<errno;
            break;
        }else{
            LOG(INFO)<<"epoll get "<<event_rst<<" event";
            for (int i = 0 ;i <event_rst;i++)
            {
                epoll_event* pevent = &event_list[i];
                if (pevent->events & EPOLLIN)
                {
                    if (pevent->data.ptr != nullptr)
                    {
                        EpollDataStruct *data_ptr = (EpollDataStruct *)pevent->data.ptr;
                        if (data_ptr->fd_type == eFD_LISTEN)
                        {
                            LOG(INFO) << "epoll event listen sock"<<data_ptr->fd<<" accept new connection!";
                            sockaddr client_addr;
                            socklen_t sock_len = sizeof(client_addr);
                            int client_fd = accept4(data_ptr->fd,&client_addr,&sock_len,SOCK_NONBLOCK);
                            if(client_fd == -1)
                            {
                                LOG(INFO)<<"accept fd failed! errno:"<<errno;
                                continue;
                            }
                            EpollDataStruct* pclient = nullptr;
                            pclient = init_client_sock(client_fd);
                            if(pclient == nullptr)
                            {
                                continue;
                            }
                            add_client_fd_to_epoll(epoll_fd,pclient);
                        }else if(data_ptr->fd_type == eFD_CLIENT)
                        {
                            do
                            {
                                int data_free_size = BUFF_SIZE - (data_ptr->read_flag - data_ptr->recv_buff);
                                if(data_free_size == 0)
                                {
                                    LOG(ERROR)<<"read buff  full!";
                                    //TODO decode and process!
                                    continue;
                                }
                                int recv_size = recv(data_ptr->fd, data_ptr->read_flag, data_free_size, 0);
                                if (recv_size == 0)
                                {
                                    LOG(INFO) << "client disconnection";
                                    //TODO ondisconnection
                                    close(data_ptr->fd);
                                    delete data_ptr;
                                    break;
                                }
                                else
                                {
                                    if (recv_size > 0)
                                    {
                                        data_ptr->read_flag += recv_size;
                                        LOG(INFO) << "client recv msg size " << recv_size;
                                        LOG(INFO) << "client recv msg " << data_ptr->recv_buff;
                                    }
                                    else
                                    {
                                    //    LOG(INFO)<<"data read finish!";
                                    //    break;
                                        continue;
                                    }
                                }

                            } while (true);
                        }else if(data_ptr->fd_type == eFD_LOCALFILE)
                        {
                            LOG(INFO)<<"start reading localfile from disk!";
                        }
                    }
                    else
                    {
                        LOG(INFO) << "do other socket staff!";
                    }
                }
            }
        }

    }

}

TEST(Net_Test,test_epoll_create)
{
    LOG(INFO)<<"start test_epoll_create";
    std::thread net_thread(start_epoll_server);
    //net_thread.detach();
    net_thread.join();
    LOG(INFO)<<"continue other test.....";
}

TEST(Net_Test,test_byteorder)
{
    int value32 = 0x12345678;
    short value16 = 0x1234;
    int64_t value64 = 0x1234567812345678;
    int net_value32 =  htonl(value32);
    LOG(INFO)<<"host value 32:"<<value32<<" net value 32:"<<net_value32;
    int net_value16 =  htonl(value16);
    LOG(INFO)<<"host value 16:"<<value16<<" net value 16:"<<net_value16;

    SampleClass test_class;
    for(int index = 0; index< 100;index++)
        test_class.ModifyTest();
    test_class.DumpValue();
}



#endif // __TEST_EPOLL_H__
