#ifndef XAUDIOPLAY_H
#define XAUDIOPLAY_H


class XAudioPlay
{
public:
    XAudioPlay* Get();
    virtual bool Start() = 0;
    virtual void Play(bool isPlay) = 0;
    virtual bool Write(const char* data, int datasize) = 0; // 将音频写入
    virtual void Stop() = 0; // 停止
    virtual int GetFree() = 0; // 获取剩余空间
    XAudioPlay();
    virtual ~XAudioPlay();

    int sampleRate = 48000;
    int sampleSize = 16;
    int channel = 2;
};

#endif // XAUDIOPLAY_H
