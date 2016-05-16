#include "graph.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QDebug>

Graph::Graph(QWidget *parent) : QWidget(parent)
{
    startTimer(20);
    max = -20;
}

void Graph::setValues(QDateTime t1, float v1)
{
    if(v1 > max)
        max = v1;
    date.push_back(t1);
    value.push_back(v1);
    uint t = t1.toTime_t() - date.at(0).toTime_t();
    float timeGraph = (float) t;
    time.push_back(timeGraph);
}

void Graph::clean()
{
    date.clear();
    time.clear();
    value.clear();
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

    pen.setColor("blue");
    painter.setPen(pen);

    for(int i = 0; i < value.size(); i++){
        float v = height() - (value.at(i)/max)*height();
        float t = time.at(i)/time.at(time.length()-1) * width();
        painter.drawPoint(t,v);
        if(i>0)
            painter.drawLine(time.at(i-1)/time.at(time.length()-1) * width(), height() - (value.at(i-1)/max)*height(),t,v);
    }
}

void Graph::timerEvent(QTimerEvent *e)
{
    repaint();
}
