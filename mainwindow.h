#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>

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
        * @brief ~MainWindow() eh o destrutor da classe
    */
    ~MainWindow();

public slots:
    /**
        * @brief Conecta com o servidor.
    */
    void tcpConnect();
    /**
        * @brief Inicia o timer que chama a funcao generateData().
    */
    void putData();
    /**
        * @brief Eh a função para parar o timer.
    */
    void stopInsert();
    /**
        * @brief Cria novos dados a serem inseridos no servidor.
    */
    void generateData();
    /**
        * @brief Faz com que o produtor se desconecte do servidor.
    */
    void tcpDisconnect();

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
