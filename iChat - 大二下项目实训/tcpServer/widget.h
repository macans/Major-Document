#ifndef WIDGET_H
#define WIDGET_H
#include <QtNetWork>
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
    QTcpServer *tcpServer;
private slots:
    void sendMessage();
};

#endif // WIDGET_H
