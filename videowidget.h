#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QObject>
#include <QOpenGLWidget>

class VideoWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);
    virtual ~VideoWidget();

    void paintEvent(QPaintEvent *event);//窗口的重新绘制
    void timerEvent(QTimerEvent *event);//定时器

};

#endif // VIDEOWIDGET_H
