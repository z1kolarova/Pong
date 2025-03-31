#include "ball.h"

#include <iostream>

Ball::Ball(QWidget *p)
{
    parent = p;
    resetToCenter();
    start(10);
}

void Ball::resetToCenter()
{
    QRect rct = parent->rect();
    x = rct.width() / 2;
    y = rct.height() / 2;
    kx = rand() % 4 + 3;
    ky = rand() % 10 + 3;
    emit ballPlacedToCenter();
}

void Ball::draw(QPainter &painter)
{
    painter.drawEllipse(x, y, 15, 15);
}

void Ball::timerEvent(QTimerEvent *)
{
    QRect rct = parent->rect();

    if(x<=0 || x>=rct.width())
    {
        int zmena = rand() % 20;
        emit ballTouchedHorizontalEdge(x, y);
        kx = (kx + zmena) % 10 + 3;
        if(x > rct.width())
            kx *= -1;
        //std::cout << "kx: " << kx << " ";
        ky = (ky + zmena) % 10 + 3;
        //std::cout << "ky: " << ky << " ";
    }
    if(y<=0 || y>=rct.height())
    {
        emit ballTouchedVerticalEdge(x, y);
        ky *= -1;
    }

    emit ballGoingDirection(x, y, kx, ky);

    x += kx;
    y += ky;

    //std::cout << "x: " << x << std::endl;
    //std::cout << "y: " << y << std::endl;
    parent->update();
}
