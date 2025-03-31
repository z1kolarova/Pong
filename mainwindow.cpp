#include "ball.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QScreen>
#include <iostream>

static int ballDiameter = 15;
static int platformWidth = 15;
static int platformHeight = 100;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowState(Qt::WindowFullScreen);
    ui->setupUi(this);

    QScreen *screen = QGuiApplication::primaryScreen();
    QSize screenSize = screen->size();
    setFixedSize(screenSize);

    int screenHeight = screenSize.height();
    int screenWidth = screenSize.width();

    platformHeight = screenHeight / 6;
    ui->lblHumanScore->move(screenWidth / 2 - 55, screenHeight / 12);
    ui->lblColon->move(screenWidth / 2, screenHeight / 12);
    ui->lblAIScore->move(screenWidth / 2 + 10, screenHeight / 12);

    on_actionNewGame_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNewGame_triggered()
{
    isRunning = true;
    ball = BallPtr(new Ball(this));
    connect(this, &MainWindow::draw, ball.get(), &Ball::draw);
    connect(ball.get(), &Ball::ballTouchedHorizontalEdge, this, &MainWindow::checkIfScored);
    connect(ball.get(), &Ball::ballPlacedToCenter, this, &MainWindow::on_actionPause_triggered);

    humanPlayer = PPPtr(new PlayerPlatform(this, 0, rect().height() / 2, platformWidth, platformHeight));
    connect(this, &MainWindow::draw, humanPlayer.get(), &PlayerPlatform::draw);
    connect(this, &MainWindow::moveHumanPlatform, humanPlayer.get(), &PlayerPlatform::respondToMouseMovement);
    aiPlayer = PPPtr(new PlayerPlatform(this, this->rect().width()-platformWidth, rect().height() / 2, platformWidth, platformHeight));
    connect(this, &MainWindow::draw, aiPlayer.get(), &PlayerPlatform::draw);
    connect(ball.get(), &Ball::ballGoingDirection, aiPlayer.get(), &PlayerPlatform::respondToBallMovement);
    connect(ball.get(), &Ball::ballPlacedToCenter, aiPlayer.get(), &PlayerPlatform::teleportToCenter);
    connect(ball.get(), &Ball::ballPlacedToCenter, humanPlayer.get(), &PlayerPlatform::teleportToCenter);

    on_actionPause_triggered();

    aiScore = 0;
    humanScore = 0;
    ui->lblAIScore->setText("0");
    ui->lblHumanScore->setText("0");
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int mouseY = event->pos().y();
    if(mouseY > 0 && mouseY < rect().height())
        emit moveHumanPlatform(mouseY);
}

void MainWindow::on_actionPause_triggered()
{
    isRunning = !isRunning;
    if(isRunning)
    {
        ball.get()->start(10);
        aiPlayer.get()->start(10);
        humanPlayer.get()->start(10);
    }
    else
    {
        humanPlayer.get()->stop();
        aiPlayer.get()->stop();
        ball.get()->stop();
    }
}

void MainWindow::checkIfScored(int x, int y)
{
    bool aisChance = x <= 0; //pokud je míček na straně s 0, skóruje počítač
    int platformY = aisChance ? humanPlayer.get()->y : aiPlayer.get()->y;

    if (y >= platformY && y <= platformY + platformHeight)
        return;
    if (y + ballDiameter >= platformY && y + ballDiameter <= platformY + platformHeight)
        return;

    if(aisChance)
        aiScored();
    else
        humanScored();

    ball.get()->resetToCenter();
}

void MainWindow::aiScored()
{
    aiScore++;
    ui->lblAIScore->setText(std::to_string(aiScore).c_str());
}

void MainWindow::humanScored()
{
    humanScore++;
    ui->lblHumanScore->setText(std::to_string(humanScore).c_str());
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.fillRect(rect(), QBrush(QColor(Qt::darkGray)));

    painter.setPen(Qt::black);
    painter.setBrush(QBrush(QColor(Qt::white)));

    emit draw(painter);
}

