#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    totalBytes = 0;
    bytesReceived = 0;
    fileNameSize = 0;
    tcpServer = new QTcpServer(this);
    connect(tcpServer,SIGNAL(newConnection()),this,
    SLOT(acceptConnection()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::acceptConnection()  //接受连接
{
    tcpServerConnection = tcpServer->nextPendingConnection();
    tcpServerConnection->write("hello");
connect(tcpServerConnection,SIGNAL(readyRead()),this,
    SLOT(updateServerProgress()));
    connect(tcpServerConnection,
SIGNAL(error(QAbstractSocket::SocketError)),this,
           SLOT(displayError(QAbstractSocket::SocketError)));
    //tcpServer->
    ui->serverStatusLabel->setText(tr("accept connection"));
    tcpServer->close();
}
void MainWindow::updateServerProgress()  //更新进度条，接收数据
{
   QDataStream in(tcpServerConnection);
   in.setVersion(QDataStream::Qt_5_4);
   if(bytesReceived <= sizeof(qint64)*2)
   { //如果接收到的数据小于16个字节，那么是刚开始接收数据，我们保存到//来的头文件信息
       if((tcpServerConnection->bytesAvailable() >= sizeof(qint64)*2)
           && (fileNameSize == 0))
       { //接收数据总大小信息和文件名大小信息
           in >> totalBytes >> fileNameSize;
           bytesReceived += sizeof(qint64) * 2;
       }
       if((tcpServerConnection->bytesAvailable() >= fileNameSize)
           && (fileNameSize != 0))
       {  //接收文件名，并建立文件
           in >> fileName;
           ui->serverStatusLabel->setText(tr("receive file %1 ...")
                                           .arg(fileName));
           bytesReceived += fileNameSize;
           localFile= new QFile(fileName);
           if(!localFile->open(QFile::WriteOnly))
           {
                qDebug() << "open file error!";
                return;
           }
       }
       else return;
   }
   if(bytesReceived < totalBytes)
   {  //如果接收的数据小于总数据，那么写入文件
      bytesReceived += tcpServerConnection->bytesAvailable();
      inBlock= tcpServerConnection->readAll();
      localFile->write(inBlock);
      inBlock.resize(0);
   }
//更新进度条
   ui->serverProgressBar->setMaximum(totalBytes);
   ui->serverProgressBar->setValue(bytesReceived);

   if(bytesReceived == totalBytes)
   { //接收数据完成时
    tcpServerConnection->close();
    localFile->close();
    ui->startButton->setEnabled(true);
ui->serverStatusLabel->setText(tr("receive file 1% success")
                        .arg(fileName));
   }
}

void MainWindow::displayError(QAbstractSocket::SocketError p) //错误处理
{
    qDebug() << tcpServerConnection->errorString();
    tcpServerConnection->close();
    ui->serverProgressBar->reset();
    ui->serverStatusLabel->setText(tr("server ready"));
    ui->startButton->setEnabled(true);
}
void MainWindow::on_startButton_clicked()
{
    ui->startButton->setEnabled(false);
    bytesReceived =0;
    if(!tcpServer->listen(QHostAddress::Any, 6666))
    {
       qDebug() << tcpServer->errorString();
       close();
       return;
    }
    ui->serverStatusLabel->setText(tr("listen"));
}
