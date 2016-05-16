#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QVector>
#include <QDateTime>


class Graph : public QWidget
{
    Q_OBJECT
public:
    explicit Graph(QWidget *parent = 0);
    void setValues(QDateTime t1, float v1);
    void clean();

protected:
    void paintEvent(QPaintEvent *e);
    void timerEvent(QTimerEvent *e);

private:
    QVector<QDateTime> date;
    QVector<float> time;
    QVector<float> value;
    float max;
};

#endif // GRAPH_H
