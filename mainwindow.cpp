#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"
#include <QDateTime>
#include <QVector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    isConnected = false;

    connect(ui->pushButtonConnect,SIGNAL(clicked(bool)),this, SLOT(tcpConnect()));
    connect(ui->pushButtonPlot,SIGNAL(clicked(bool)),this, SLOT(plotGraph()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getData(QString ip)
{
    QString ch = "get " + ip + "\r\n";
    const char *data = ch.toStdString().c_str();
    QString str;
    QStringList list;
    QDateTime datetime;
    if(socket->isOpen()){
        socket->write(data);
        socket->waitForBytesWritten(3000);
        socket->waitForReadyRead(3000);
        qDebug() << socket->bytesAvailable();
        while(socket->bytesAvailable()){
            str = socket->readLine().replace("\n","").replace("\r","");
            list = str.split(" ");
            if(list.size() == 2){
                datetime.fromString(list.at(0),Qt::ISODate);
                str = list.at(1);
                float v1 = str.toFloat();
                qDebug() << "call set value";
                ui->widget->setValues(datetime,v1);
                qDebug() << "set value called";
            }
        }
        ui->widget->repaint();
    }
}

void MainWindow::tcpConnect(){
    QString ip = ui->lineEditIP->text();
    socket->connectToHost(ip,1234);
    if(socket->waitForConnected(3000)){
        ui->statusBar->showMessage("Connected...\n");
        isConnected = true;
    }
    else{
        ui->statusBar->showMessage("Disconnected\n");
    }

    setConnections();
}

void MainWindow::plotGraph()
{
    QString selectedIP;
    selectedIP = ui->listWidgetConnections->currentItem()->text();
    qDebug() << selectedIP;
    getData(selectedIP);
}

void MainWindow::setConnections()
{
    QString str;
    QDateTime datetime;
    if(socket->isOpen()){
        socket->write("list");
        socket->waitForBytesWritten(3000);
        socket->waitForReadyRead(3000);
        qDebug() << socket->bytesAvailable();
        while(socket->bytesAvailable()){
            str = socket->readLine().replace("\n","").replace("\r","");
            ui->listWidgetConnections->addItem(str);
        }
    }
}
