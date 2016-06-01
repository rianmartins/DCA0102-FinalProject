#include "graph.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QDebug>

Graph::Graph(QWidget *parent) : QWidget(parent)
{
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
    repaint();
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

    pen.setColor("red");
    painter.setPen(pen);

    if(value.size()>33){
        float nMax = -20;

        time1.clear();
        value1.clear();

        for(uint i = time.size()-10; i < time.size(); i++){
            time1.push_back(time[i]);
            value1.push_back(value[i]);
        }

        for(int i = 9; i >= 0; i--){
            if(value1.at(i) > nMax)
                nMax = value1.at(i);
            time1[i] = time1.at(i)-time1.at(0);
        }
        max = nMax;

        for(uint i = 0; i < value1.size(); i++){
            float v = height() - (value1.at(i)/max)*height();
            float t = time1.at(i)/time1.at(time1.size()-1) * width();
            painter.drawPoint(t,v);
            if(i>0)
                painter.drawLine(time1.at(i-1)/time1.at(time1.size()-1) * width(), height() - (value1.at(i-1)/max)*height(),t,v);
        }
    }
    else{
        float t0, v0, t, v;
        if(time.size()>0)
        {
            t0 = 0;
            v0 = height() - (value.at(0)/max)*height();

            for(uint i = 1; i < value.size(); i++){
                t = time.at(i)/30 * width();
                v = height() - (value.at(i)/max)*height();

                if(t>0)
                    painter.drawLine(QPointF(t0,v0),QPointF(t,v));

                t0 = t;
                v0 = v;
            }
        }
    }
}

float Graph::getMaxValue()
{
    if(value.size()<10)
    {
        return max;
    }
    else
    {
        float nmax = 0;
        for(uint i = 0; i < value1.size(); i++){
            if(value1.at(i) > nmax)
                nmax = value1.at(i);
        }
        return nmax;
    }

}
