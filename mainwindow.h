#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTcpSocket>
#include <QMainWindow>
#include <QDateTime>
#include <QTimer>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
        * @brief MainWindow eh o construtor da classe principal
        * @param parent eh um ponteiro para QWidget que indica
            * onde a MainWindow sera desenhada
    */
    explicit MainWindow(QWidget *parent = 0);
    /**
        *@brief ~MainWindow() eh o destrutor da classe
    */
    ~MainWindow();
    /**
        *@brief getData() serve para pegar os dados gerados de determinado ip.
        *@param ip é um parametro da classe Qstring para informar o ip desejado na consulta.
    */
    void getData(QString ip);
    /**
        *@brief A função setConnections exibe os ips conectados com o servidor no listViewer para pode plotar o gráfico.
    */
    void setConnections();

public slots:
    /**
        *@brief TcpConnect, conecta com o servidor.
    */
    void tcpConnect();
    /**
        *@brief Na função plotGraph, os dados que foram guardados a partir do produtor de dados para determinado ip é plotado em um gráfico com seus ultimos 10 valores.
    */
    void plotGraph();

private:
    Ui::MainWindow *ui;
    /**
        *@brief Socket de conexao com o servidor.
    */
    QTcpSocket *socket;
    /**
        *@brief isConnected verifica se o cliente esta conectado com o servidor.
    */
    bool isConnected;
    /**
        *@brief timer garante que a funcao plotGraph() continue verificando se há novos valores a serem plotados.
    */
    QTimer *timer;
};

#endif // MAINWINDOW_H
