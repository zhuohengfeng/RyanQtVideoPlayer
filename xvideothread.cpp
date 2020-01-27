#include "xvideothread.h"
#include "xffmpeg.h"

XVideoThread::XVideoThread()
{

}

XVideoThread::~XVideoThread()
{

}

void XVideoThread::run()
{
    while (!isexit) {
        AVPacket pkt = XFFmpeg::GetInstance()->Read();
        if (pkt.size <= 0) { // 未打开视频
            msleep(10);
            continue;
        }
        if (pkt.stream_index != XFFmpeg::GetInstance()->videoStream) {
            av_packet_unref(&pkt);
            continue;
        }
        XFFmpeg::GetInstance()->Decode(&pkt);
        if (XFFmpeg::GetInstance()->fps > 0) { // 控制解码进度
            msleep(1000 / XFFmpeg::GetInstance()->fps);
        }
    }
}






