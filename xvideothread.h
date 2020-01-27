#ifndef XVIDEOTHREAD_H
#define XVIDEOTHREAD_H

#include <QThread>

class XVideoThread : public QThread
{
public:
    XVideoThread();
    virtual ~XVideoThread();

    static XVideoThread *Get()//创建单例模式
    {
        static XVideoThread vt;
        return &vt;
    }


    void run(); // 线程的运行

    bool isexit = false;
};

#endif // XVIDEOTHREAD_H
