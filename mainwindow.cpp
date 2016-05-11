#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(generateData()));
}

void MainWindow::tcpConnect(){
    QString ip = ui->lineEditIP->text();
    socket->connectToHost(ip,1234);
    if(socket->waitForConnected(3000)){
        ui->textBrowserActivity->setText("IP: " + ip);
        ui->textBrowserActivity->append("Connected...\n");
    }
    else{
        ui->textBrowserActivity->setText("Disconnected\n");
    }
}

void MainWindow::putData()
{
    tcpConnect();
    if(socket->isOpen()){
        timer->start(2000);
    }
}

void MainWindow::generateData()
{
    int min, max, intValue;
    min = ui->lineEditFaixaMin->text().toInt();
    max = ui->lineEditFaixaMax->text().toInt();
    intValue = ui->horizontalSliderIntervalo->value();

    QDateTime datetime;
    QString str;
    datetime = QDateTime::currentDateTime();
    str = "set "
        + datetime.toString(Qt::ISODate)
        + " "
        + QString::number(min + qrand()%(max-min)) + "\r\n";

    ui->textBrowserActivity->append(str);
    socket->write(str.toStdString().c_str());
    socket->waitForBytesWritten(3000);

    timer->setInterval(intValue*1000);
}

void MainWindow::tcpDisconnect()
{
    timer->stop();
    socket->abort();
    ui->textBrowserActivity->append("Disconnected.");
}

void MainWindow::stopInsert()
{
    timer->stop();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete socket;
}
