#include "widget.h"
#include "ui_widget.h"
#include <QtDebug>
#include <QFile>

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
