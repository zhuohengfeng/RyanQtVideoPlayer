#include "widget.h"
#include "xffmpeg.h"
#include <QApplication>

int main(int argc, char *argv[])
{

//    for (;;) {
//        AVPacket pkt = XFFmpeg::GetInstance()->Read();
//        if (pkt.size <= 0) {
//            break;
//        }
//        if (pkt.stream_index != XFFmpeg::GetInstance()->videoStream) {
//            continue;
//        }

//        printf("pts = %lld \n", pkt.pts);
//        AVFrame *yuv = XFFmpeg::GetInstance()->Decode(&pkt);
//        if (yuv) {
//            char rgb[1920*1080*4];
//            XFFmpeg::GetInstance()->ToRGB(yuv, rgb, 1920, 1080);
//            printf("[D] === %d \n", sizeof(rgb));
//        }
//        av_packet_unref(&pkt);
//    }


    // 启动UI应用
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
