#pragma once

namespace Yu::thread{

    class Task{
        public:
        virtual void run()=0;
        virtual void destory()=0;
        Task()=default;
        virtual ~Task()=default;
    };

    class EchoTask:public Task{
        public:
            virtual void run()override;
            virtual void destory()override;
            EchoTask();
            EchoTask(int fd);
            ~EchoTask()=default;
        private:
           int  m_sockfd;
           bool is_close;

    };
}