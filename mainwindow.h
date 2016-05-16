#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTcpSocket>
#include <QMainWindow>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

typedef struct{
  QDateTime theTime; // hora da medida
  float measurement; // medida
} Entry;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void getData(QString ip);
    void setConnections();

public slots:
    void tcpConnect();
    void plotGraph();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    bool isConnected;
};

#endif // MAINWINDOW_H
