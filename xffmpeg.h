#ifndef XFFMPEG_H
#define XFFMPEG_H

#include <iostream>
#include <QMutex>

// 引入ffmpeg头文件
extern "C"
{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
    #include <libavformat/version.h>
    #include <libavutil/mathematics.h>
}

class XFFmpeg
{

public:
    static XFFmpeg* GetInstance() { // 单例模式
        static XFFmpeg ff;
        return &ff;
    }
    virtual ~XFFmpeg();

    std::string GetError(); // 获取错误信息
    uint totalMs = 0; // 总时长
    uint videoStream = 0; // 视频流
    bool Open(const char* path); //打开视频
    void Close(); // 关闭文件
    AVPacket Read(); //读取视频的每一帧，返回每帧后需要清理空间
    AVFrame* Decode(const AVPacket* pkt); // 读取到每一帧数据后需要对其进行解码
    bool ToRGB(const AVFrame* yuv, char *out, int outwidth, int outheight);

protected:
    char errorbuff[1024];//打开时发生的错误信息
    AVFormatContext* ic = nullptr; // 接封装上下文
    QMutex mutex; // 互斥锁
    AVFrame* yuv = nullptr; // 解码后的视频帧数据(yuv)
    SwsContext* cCtx = nullptr; // 转码器上下文

    XFFmpeg();
};

#endif // XFFMPEG_H
