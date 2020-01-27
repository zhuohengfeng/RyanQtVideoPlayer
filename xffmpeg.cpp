#include "xffmpeg.h"
#include <QtDebug>


// 避免计算时分母为0时的特判情况
static double r2d(AVRational r)
{
    return r.den == 0 ? 0 : (double)r.num / (double)r.den;
}


XFFmpeg::XFFmpeg()
{
    errorbuff[0] = '\0';
    av_register_all();
}

XFFmpeg::~XFFmpeg()
{

}

bool XFFmpeg::Open(const char *path)
{
    this->Close(); // 打开先前关闭清理
    this->mutex.lock(); // 锁
    int res = avformat_open_input(&this->ic, path , nullptr, nullptr);
    if (res != 0) {
        this->mutex.unlock();
        av_strerror(res, errorbuff, sizeof(errorbuff));
        printf("open %s failed :%s \n", path, errorbuff);
        return false;
    }

    // 解码器
    for (uint i = 0; i < ic->nb_streams; i++) {
        AVCodecContext *enc = ic->streams[i]->codec;
        if (enc->codec_type == AVMEDIA_TYPE_VIDEO) {
            this->videoStream = i;
            this->fps = r2d(ic->streams[i]->avg_frame_rate); // 获取视频的fps = 30
            qDebug() << "FPS: " << this->fps;

            AVCodec* codec = avcodec_find_decoder(enc->codec_id);
            if (!codec) {
                mutex.unlock();
                printf("video code not find\n");
                return false;
            }
            int err = avcodec_open2(enc, codec, nullptr);
            if (err != 0) {
                mutex.unlock();
                char buf[1024] = {0};
                av_strerror(err, buf, sizeof(buf));
                printf(buf);
                return false;
            }
            printf("open codec success\n");
        }
    }

    // 获取视频的总时长
    this->totalMs = ic->duration / (AV_TIME_BASE);
    printf("file totalSec is %d 分 -%d 秒\n", totalMs/ 60, totalMs % 60);//以分秒计时

    this->mutex.unlock();
    return true;
}

void XFFmpeg::Close()
{
    this->mutex.lock();
    if (ic) {
        avformat_close_input(&ic);
    }
    if (yuv) {
        av_frame_free(&yuv);
    }
    if (cCtx) {
        sws_freeContext(cCtx);
        cCtx = nullptr;
    }
    this->mutex.unlock();
}

/**
 * @brief 读取原始数据
 * @return
 */
AVPacket XFFmpeg::Read()
{
    AVPacket pkt;
    memset(&pkt, 0, sizeof(AVPacket));
    this->mutex.lock();
    if (!this->ic) {
        this->mutex.unlock();
        return pkt;
    }
    int err = av_read_frame(ic, &pkt); // 读取视频帧
    if (err != 0) {
        av_strerror(err, errorbuff, sizeof(errorbuff));
    }
    this->mutex.unlock();
    return pkt;
}

AVFrame *XFFmpeg::Decode(const AVPacket *pkt)
{
    this->mutex.lock();
    if (!this->ic) {
        this->mutex.unlock();
        return nullptr;
    }
    if (!this->yuv) {
        this->yuv = av_frame_alloc();
    }
    int re = avcodec_send_packet(ic->streams[pkt->stream_index]->codec, pkt);
    if (re != 0) {
        this->mutex.unlock();
        return nullptr;
    }
    re = avcodec_receive_frame(ic->streams[pkt->stream_index]->codec, yuv);
    if (re != 0) {
        this->mutex.unlock();
        return nullptr;
    }
    this->mutex.unlock();
    return this->yuv;
}

bool XFFmpeg::ToRGB(const AVFrame *yuv, char *out, int outwidth, int outheight)
{
    this->mutex.lock();
    if (!ic) {
        //未打开视频文件
        mutex.unlock();
        return false;
    }

    AVCodecContext* videoCtx = ic->streams[this->videoStream]->codec;
    this->cCtx = sws_getCachedContext(cCtx, videoCtx->width, videoCtx->height,
                                      videoCtx->pix_fmt, outwidth, outheight,
                                      AV_PIX_FMT_BGRA, SWS_BICUBIC,
                                      nullptr, nullptr, nullptr);
    if (!cCtx) {
        mutex.unlock();
        return false;
    }

    uint8_t *data[AV_NUM_DATA_POINTERS] = {0};
    data[0] = (uint8_t*) out; // 第一位输出RGB
    int linesize[AV_NUM_DATA_POINTERS] = {0};

    linesize[0] = outwidth * 4;
    int h = sws_scale(cCtx, yuv->data, //当前处理区域的每个通道数据指针
            yuv->linesize,//每个通道行字节数
            0, videoCtx->height,//原视频帧的高度
            data,//输出的每个通道数据指针
            linesize//每个通道行字节数
            );//开始转码

    if (h > 0)
    {
        printf("(%d)", h);

    }

    this->mutex.unlock();
    return true;
}

std::string XFFmpeg::GetError()
{
    this->mutex.lock();
    std::string re = this->errorbuff;
    this->mutex.unlock();
    return re;
}
