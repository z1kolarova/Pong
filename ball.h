#ifndef BALL_H
#define BALL_H


#include <QTimer>
#include <QWidget>
#include <QPainter>

#include <memory>

class Ball : public QTimer
{
    Q_OBJECT

public:
    Ball(QWidget *p);
    void resetToCenter();

signals:
    void ballTouchedHorizontalEdge(int x, int y);
    void ballTouchedVerticalEdge(int x, int y);
    void ballGoingDirection(int x, int y, int kx, int ky);
    void ballPlacedToCenter();

public slots:
    void draw(QPainter &painter);

protected:
    QWidget *parent = NULL;
    int x = 0;
    int y = 0;
    int kx = 1;
    int ky = 1;

    virtual void timerEvent(QTimerEvent *);
};

typedef std::shared_ptr<Ball> BallPtr;

#endif // BALL_H
