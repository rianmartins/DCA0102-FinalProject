#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QVector>
#include <QDateTime>
#include <vector>

using namespace std;


class Graph : public QWidget
{
    Q_OBJECT
public:
    /**
        *@brief Graph eh a classe criada para tratar do plot do grafico.
        *@param parent eh um ponteiro para Qwidget que indica onde o graph serah desenhada
    */
    explicit Graph(QWidget *parent = 0);
    /**
        *@brief No setValues estamos setando os valores obtidos no produtor de dados em vetores da classe Qvector para poder plotar o grafico.
    */
    void setValues(QDateTime t1, float v1);
    /**
        *@brief getMaxValue() retorna o valor maximo que está sendo exibido no grafico.
    */
    float getMaxValue();

protected:
    /**
        *@brief Onde acontece o desenho do grafico.
    */
    void paintEvent(QPaintEvent *e);

public slots:
    /**
        *@brief Clean limpa a tela de plot.
    */
    void clean();

private:
    /**
        *@brief date eh o vetor que guarda as datas geradas pelo produtor de dados.
    */
    vector<QDateTime> date;
    /**
        *@brief time eh o vetor que guarda apenas o segundo em que o dado foi gerado.
    */
    vector<float> time;
    /**
        *@brief value eh o vetor que guarda os valores gerados pelo produtor de dados.
    */
    vector<float> value;
    /**
        *@brief max guarda o maior valor encontrado no vetor value.
    */
    float max;

    /**
        *@brief time1 eh o vetor que guarda os ultimos 10 elementos do vetor time.
    */
    vector<float> time1;
    /**
        *@brief value1 eh o vetor que guarda os ultimos 10 elementos do vetor value.
    */
    vector<float> value1;
};

#endif // GRAPH_H
