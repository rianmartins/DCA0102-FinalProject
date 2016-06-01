#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(plotGraph()));

    isConnected = false;

    connect(ui->pushButtonConnect,SIGNAL(clicked(bool)),this, SLOT(tcpConnect()));
    connect(ui->pushButtonPlot,SIGNAL(clicked(bool)),this, SLOT(plotGraph()));
    connect(ui->listWidgetConnections,SIGNAL(itemSelectionChanged()),ui->widget,SLOT(clean()));
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

    float mv = -20;
    QVector<QDateTime> date;
    QVector<float> tempo;
    QVector<float> val;
    uint t;

    if(socket->isOpen()){
        socket->write(data);
        socket->waitForBytesWritten(3000);
        socket->waitForReadyRead(3000);
        qDebug() << "bytes available: " << socket->bytesAvailable();
        while(socket->bytesAvailable()){
            str = socket->readLine().replace("\n","").replace("\r","");
            list = str.split(" ");
            if(list.size() == 2){
                datetime = datetime.fromString(list.at(0),Qt::ISODate);
                date.push_back(datetime);
                str = list.at(1);

                float v1 = str.toFloat();
                val.push_back(v1);
                t = datetime.toTime_t() - date.at(0).toTime_t();
                float t1 = (float) t;
                tempo.push_back(t1);

                ui->widget->setValues(datetime,v1);
            }
            mv = ui->widget->getMaxValue();
            QString maxValue = QString::number(mv);
            ui->labelMax->setText("Value: " + maxValue);
            float minT, maxT;
            if(date.length()<=10)
                minT = 0;
            else
                minT = tempo.at(tempo.length()-11);
            maxT = tempo.at(tempo.length()-1);
            QString minTime = QString::number(minT);
            QString maxTime = QString::number(maxT);
            ui->labelTimeMin->setText("Time: " + minTime);
            ui->labelTimeMax->setText("Time: " + maxTime);
        }
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
    getData(selectedIP);
    if(!timer->isActive())
        timer->start(3000);
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
