#ifndef WIDGET_H
#define WIDGET_H
#include <QtNetwork>
#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QTcpSocket *tcpSocket;
    QString message;  //存放从服务器接收到的字符串
    quint16 blockSize;  //存放文件的大小信息
private slots:
    void newConnect(); //连接服务器
    void readMessage();  //接收数据
    void displayError(QAbstractSocket::SocketError);  //显示错误
    void on_pushButton_clicked();
};

#endif // WIDGET_H
