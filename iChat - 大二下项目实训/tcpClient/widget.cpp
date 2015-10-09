#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
             this,SLOT(displayError(QAbstractSocket::SocketError)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::newConnect()
{
    blockSize = 0; //初始化其为0
    tcpSocket->abort(); //取消已有的连接
    tcpSocket->connectToHost(ui->hostLineEdit->text(),
                             ui->portLineEdit->text().toInt());
    tcpSocket->write("hello");
    //连接到主机，这里从界面获取主机地址和端口号
}

void Widget::readMessage()
{
   while(tcpSocket->bytesAvailable() > 0){
        QByteArray data;
        data.resize(tcpSocket->bytesAvailable());
        tcpSocket->read(data.data(), data.size());
        QString msg = data.data();
        ui->messageLabel->setText(msg);
   }
    //显示接收到的数据
}

void Widget::displayError(QAbstractSocket::SocketError)
{
    qDebug() << tcpSocket->errorString(); //输出错误信息
}

void Widget::on_pushButton_clicked() //连接按钮
{
    newConnect(); //请求连接
}

