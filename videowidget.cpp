#include "videowidget.h"
#include "xffmpeg.h"
#include <QtDebug>
#include <QPainter>
#include "xvideothread.h"

VideoWidget::VideoWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    startTimer(20); // 触发定时刷新
    XVideoThread::Get()->start();

//    if (XFFmpeg::GetInstance()->Open("/Users/hengfeng/Desktop/testvideo.mp4")) {
//        printf("open success!\n");
//        startTimer(20); // 触发定时刷新
//        XVideoThread::Get()->start();
//    }
//    else {
//        printf("open failed!%s\n",XFFmpeg::GetInstance()->GetError().c_str());
//    }
}

VideoWidget::~VideoWidget()
{
    XVideoThread::Get()->isexit = true;
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    //绘制
        static QImage *image = nullptr;

        if (image == nullptr)
        {
            uchar *buf = new uchar[width()*height() * 4];//存放解码后的视频空间
            image = new QImage(buf, width(), height(), QImage::Format_ARGB32); // 窗口大小
            qDebug() << "w=" << width() << ", h=" << height();
        }

        AVPacket pkt = XFFmpeg::GetInstance()->Read();//读取视频帧
        if (pkt.stream_index != XFFmpeg::GetInstance()->videoStream)
        {//不为视频帧,释放pkt的空间
            av_packet_unref(&pkt);
            return;
        }
        if (pkt.size == 0) return;

        AVFrame *yuv = XFFmpeg::GetInstance()->Decode(&pkt);//解码读取到的视频帧
        av_packet_unref(&pkt);//解码成后也需要释放空间
        if (yuv == NULL) return;

        //将解码后的视频帧转化为RGB
        XFFmpeg::GetInstance()->ToRGB(yuv, (char *)image->bits(),width(),height());


        QPainter painter;//hua
        painter.begin(this);
        painter.drawImage(QPoint(0, 0), *image);//绘制FFMpeg解码后的视频
        painter.end();//

}

void VideoWidget::timerEvent(QTimerEvent *event)
{
    this->update(); // 触发刷新
}
