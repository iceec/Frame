#include "Work_Task.h"
#include "Work_Flow.h"
#include "Socket_Handle.h"
using namespace Yu::thread;
using namespace Yu::socket;
using namespace Yu::utility;
using namespace Yu::plugin;

using std::string;
void Work_Task::run()
{
    Socket temp(m_sockfd);
    Meg_Head info;
    std::memset((void *)&info, 0, sizeof(Meg_Head));

    int len = temp.recv((char *)&info, sizeof(info));
    if (len == 0)
    {
        LOGGERDEBUG("%d is close\n", m_sockfd);
        temp.close();
        m_close = true;
        return;
    }
    else if (len < 0)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            LOGGERDEBUG("socket recv would block :conn=%d errno =%d errmsg =%s\n", m_sockfd, errno, strerror(errno));
        else if (errno == EINTR)
            LOGGERDEBUG("socket recv interrupted :conn=%d errno =%d errmsg =%s\n", m_sockfd, errno, strerror(errno));
        else
            LOGGERERROR("socketconnect abort :conn=%d errno =%d errmsg =%s\n", m_sockfd, errno, strerror(errno));

        temp.close();
        m_close = true;
        return;
    }
    else if (len != sizeof(Meg_Head))
    {
        LOGGERERROR("%d socket client meg_head wrong\n", m_sockfd);
        temp.close();
        m_close = true;
        return;
    }
    else if (info.len > Yu::thread::MAXRECV)
    {
        LOGGERERROR("%d socket client meg.len too large is %u\n", m_sockfd, info.len);
        temp.close();
        m_close = true;
        return;
    }
    char buf[Yu::thread::MAXRECV]{0};
    len = temp.recv(buf, info.len);
    if (len != info.len)
    {
        LOGGERERROR("%d socket recv len wrong len is %d\n", m_sockfd, len);
        temp.close();
        m_close = true;
        return;
    }
    LOGGERINFO("%d socket recv len is %d\n", m_sockfd, len);
    string out;
    single<WorkFlow>::instance()->run((int)info.id, buf, out);
    if(out.size())
        temp.send(&out[0],out.size());
    // std::this_thread::sleep_for(std::chrono::seconds(10));
    return;
}

// 这里每一个县城dest都要操作红黑书 所以得家所
void Work_Task::destory()
{
    if (m_close)
        single<Socket_Handle>::instance()->detach(m_sockfd);
    else
        single<Socket_Handle>::instance()->mod(m_sockfd);
    delete this;
}
