#include "widget.h"
#include "ui_widget.h"
#include <QtDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 测试打印ffmpeg信息
    qDebug() << avcodec_configuration();
    unsigned version = avcodec_version();
    QString ch = QString::number(version, 10);
    qDebug() << "version:" << version;
}

Widget::~Widget()
{
    delete ui;
}
