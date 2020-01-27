#include "xaudioplay.h"
#include <QIODevice>
#include <QMutex>

class CXAudioPlay : public XAudioPlay {

public:
//    QAudioOutput *output = NULL;
    QIODevice *io = nullptr;
    QMutex mutext;

    bool Start() {
        return true;
    }

    void Play(bool isPlay) {

    }

    bool Write(const char* data, int datasize) {
        return true;
    }

    void Stop() {
        mutext.lock();
//        if (output) {
//            output->stop();
//            delete output;
//            output = nullptr;
//            io = nullptr;
//        }
        mutext.unlock();
    }

    int GetFree() {
        return 0;
    }

private:


};


XAudioPlay::XAudioPlay()
{

}

XAudioPlay::~XAudioPlay()
{

}

XAudioPlay *XAudioPlay::Get()
{
    static CXAudioPlay ap;
    return &ap;
}
