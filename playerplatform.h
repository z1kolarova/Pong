#ifndef PLAYERPLATFORM_H
#define PLAYERPLATFORM_H


#include <QTimer>
#include <QWidget>
#include <QPainter>

#include <memory>

class PlayerPlatform : public QTimer
{
    Q_OBJECT

public:
    PlayerPlatform(QWidget *p, int x, int y, int width, int height);
    int width = 15;
    int height = 50;
    int x = 0;
    int y = 0;

public slots:
    void draw(QPainter &painter);
    void changeMovement(int speed, bool up);
    void respondToBallMovement(int x, int y, int kx, int ky);
    void respondToMouseMovement(int y);
    void teleportToCenter();

protected:
    QWidget *parent = NULL;
    float kx = 0;
    float ky = 1;

    virtual void timerEvent(QTimerEvent *);
};

typedef std::shared_ptr<PlayerPlatform> PPPtr;

#endif // PLAYERPLATFORM_H
