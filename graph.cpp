#include "graph.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QDebug>

Graph::Graph(QWidget *parent) : QWidget(parent)
{
    startTimer(20);
}

void Graph::setValues(QDateTime t1, float v1)
{
    date.push_back(t1);
    value.push_back(v1);
    qDebug() << "t1: " << t1;
    uint t = t1.toTime_t()/date.at(0).toTime_t();
    qDebug() << "t: " << t;
    qDebug() << "t1.toTime_t : " << t1.toTime_t();
    qDebug() << "date.at(0).toTime_t : " << date.at(0).toTime_t();
    float timeGraph = (float) t;
    qDebug() << "time graph" << timeGraph;
    time.push_back(timeGraph);
    qDebug() << "values were set";
    qDebug() << value.size();
}

void Graph::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QBrush brush;
    QPen pen;

    pen.setColor(QColor("black"));
    brush.setStyle(Qt::SolidPattern);
    brush.setColor("white");
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(0,0,width()-1,height()-1);

    QPointF p1(0,height()/2), p2(width()-1,height()/2);
    painter.drawLine(p1,p2);
    pen.setColor("blue");
    painter.setPen(pen);

    //qDebug() << "value.size: " << value.size();
    for(int i = 0; i < value.size(); i++){
        float v = value.at(i)/height();
        float t = time.at(i);
        painter.drawPoint(t,v);
        if(i>0)
            painter.drawLine(time.at(i-1),value.at(i-1),i,v);
        //qDebug() << time.at(i) << " , " << value.at(i);
    }
}

void Graph::timerEvent(QTimerEvent *e)
{
    repaint();
}
