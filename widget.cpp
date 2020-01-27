#include "widget.h"
#include "ui_widget.h"
#include <QtDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include "xffmpeg.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 设置窗口大小
    this->setFixedSize(640, 480);
    this->setWindowTitle("Qt播放器");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::open()
{
    qDebug() << "open";
    QString name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择视频文件"));
    if (name.isEmpty()) {
        return;
    }
    this->setWindowTitle(name);
    if (!XFFmpeg::GetInstance()->Open(name.toLocal8Bit())) {
        QMessageBox::information(this, "error", "file open failed!");
    }


}
