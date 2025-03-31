#include "playerplatform.h"
#include <iostream>

PlayerPlatform::PlayerPlatform(QWidget *p, int x, int y, int width, int height)
{
    parent = p;

    QRect rct = parent->rect();
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    kx = 0;
    ky = 7; //rand() % 10;

    start(10);
}

void PlayerPlatform::changeMovement(int speed, bool up = true)
{
    ky = speed;
    if (up)
        ky *= -1;
}

void PlayerPlatform::respondToBallMovement(int x, int y, int kx, int ky)
{
    int platformCenter = this->y + height / 2;
    if((this->y + ky <= parent->height() - this->height) && (y > platformCenter - height * 0.45 || y < platformCenter +  height * 0.45))
        this->ky = ky;
    else
        this->ky = 0;
}

void PlayerPlatform::respondToMouseMovement(int y)
{
    int platformCenter = this->y + height / 2;
    if(platformCenter < y && this->y + height < parent->height()) //posun dolů
        ky = (y - platformCenter) / 1;
    else if (platformCenter > y && this->y > 0) //posun nahoru
        ky = (-1) * (platformCenter - y) / 1;
}

void PlayerPlatform::teleportToCenter()
{
    y = (parent->height() / 2) - (height / 2);
}

void PlayerPlatform::draw(QPainter &painter)
{
    painter.drawRect(x, y, width, height);
}

void PlayerPlatform::timerEvent(QTimerEvent *)
{
    QRect rct = parent->rect();

    //if(x<0 || x>rct.width()) kx *= -1;
    if(y + ky < 0 || y + height + ky > rct.height()) ky = 0; //*= -1;

    //x += kx;
    y += ky;
    parent->update();
    ky = 0;
}
