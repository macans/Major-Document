#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadSize = 4 * 1024;
    totalBytes = 0;
    bytesWritten = 0;
    bytesToWrite = 0;
    tcpClient = new QTcpSocket(this);
    //当连接服务器成功时，发出connected()信号，我们开始传送文件
    connect(tcpClient,SIGNAL(connected()),this,SLOT(startTransfer()));
    //当有数据发送成功时，我们更新进度条
    connect(tcpClient,SIGNAL(bytesWritten(qint64)),this,
           SLOT(updateClientProgress(qint64)));
    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,
           SLOT(displayError(QAbstractSocket::SocketError)));
    //开始使”发送“按钮不可用
    ui->hostEdit->setText("58.49.235.178");
    ui->portEdit->setText("6666");
    ui->sendButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this);
        if(!fileName.isEmpty())
        {
           ui->sendButton->setEnabled(true);
           ui->clientLabel->setText(tr("open success").arg(fileName));
        }
}

void MainWindow::on_sendButton_clicked()
{
    ui->sendButton->setEnabled(false);
    bytesWritten = 0;
    //初始化已发送字节为0
    ui->clientLabel->setText(tr("connecting..."));
    tcpClient->connectToHost(ui->hostEdit->text(), ui->portEdit->text().toInt());//连接
}

void MainWindow::startTransfer(){
        localFile = new QFile(fileName);
       if(!localFile->open(QFile::ReadOnly))
       {
          qDebug() << "open file error!";
          return;
       }

       //文件总大小
       totalBytes = localFile->size();

       QDataStream sendOut(&outBlock,QIODevice::ReadWrite);
       //sendOut.setVersion(QDataStream::Qt_5_4);
       QString currentFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/') - 1);
       //QByteArray name = currentFileName.toLocal8Bit().toBase64();
       //依次写入总大小信息空间，文件名大小信息空间，文件名
       //sendOut << "66666" << currentFileName.toUtf8();
       outBlock = "{\"user_id\":66666, \"filename\":\"" + currentFileName.toLocal8Bit().toBase64()
               + "\", \"contact_id\":12345, \"kind\":\"audio\", \"u\":\"send\"}";
       //这里的总大小是文件名大小等信息和实际文件大小的总和
       totalBytes += outBlock.size();

       sendOut.device()->seek(0);
       //返回outBolock的开始，用实际的大小信息代替两个qint64(0)空间
      // sendOut<<totalBytes<<qint64((outBlock.size() - sizeof(qint64)*2));

       //发送完头数据后剩余数据的大小
       bytesToWrite = totalBytes - tcpClient->write(outBlock);

       ui->clientLabel->setText(tr("connected"));
       outBlock.resize(0);
}

void MainWindow::updateClientProgress(qint64 numBytes){
        //已经发送数据的大小
        bytesWritten += (int)numBytes;

        if(bytesToWrite > 0) //如果已经发送了数据
        {
       //每次发送loadSize大小的数据，这里设置为4KB，如果剩余的数据不足4KB，
       //就发送剩余数据的大小
           outBlock = localFile->read(qMin(bytesToWrite,loadSize));

           //发送完一次数据后还剩余数据的大小
           bytesToWrite -= (int)tcpClient->write(outBlock);

           //清空发送缓冲区
           outBlock.resize(0);

        } else {
           localFile->close(); //如果没有发送任何数据，则关闭文件
        }

        //更新进度条
        ui->clientBar->setMaximum(totalBytes);
        ui->clientBar->setValue(bytesWritten);

        if(bytesWritten == totalBytes) //发送完毕
        {
         ui->clientLabel->setText(tr("send file 1% success")
    .arg(fileName));
           localFile->close();
           tcpClient->close();
        }
}

void MainWindow::displayError(QAbstractSocket::SocketError){
    qDebug() << tcpClient->errorString();
        tcpClient->close();
        ui->clientBar->reset();
        ui->clientLabel->setText(tr("client ready"));
        ui->sendButton->setEnabled(true);
}
