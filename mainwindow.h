#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ball.h>
#include <playerplatform.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void draw(QPainter &painter);
    void moveHumanPlatform(int y);

private slots:
    void on_actionNewGame_triggered();
    void on_actionPause_triggered();
    void checkIfScored(int x, int y);
    void aiScored();
    void humanScored();

private:
    Ui::MainWindow *ui;
    BallPtr ball;
    PPPtr aiPlayer;
    PPPtr humanPlayer;

    bool isRunning;
    int aiScore;
    int humanScore;

protected:
    virtual void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event) override;
};
#endif // MAINWINDOW_H
