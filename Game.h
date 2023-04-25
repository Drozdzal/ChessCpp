#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QMouseEvent>
#include "Pieces.h"
#include "Chessboard.h"
#include "Saver.h"
#include "Loader.h"
#include "Window.h"
#include "LanServer.h"
#include "GameMode.h"
#include "LanClient.h"
#include <QAbstractButton>
#include <QMessageBox>

class Game: public QGraphicsView{
    Q_OBJECT
private:
    Window* window;
    MyServer* server;
    MyClient* client;
    Piece* pieceToMove=nullptr;
    Board* chessboard;
    Saver saver;
    Loader loader;
    GameMode* gameMode;
    bool whiteTurn=true;
public:
    Game(QWidget* parent=NULL);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent* event);
    bool isMovePossible(int X,int Y);
    void actualizeView();
    void backToPrimaryPosition();
    bool inPlayingMode=false;
    int timeRemaining=600;
    int timeAdding=20;
public slots:
    void multiplayer();
    void createServer();
    void joinServer();
    void singleplayer();
    void loading();
    void nextMove();
    void previousMove();
    void settings();
    void baseTimeChanged(QAbstractButton *button);
    void addingTimeChanged(QAbstractButton *button);
    void showMainMenu();
    void clickedSurrender();
    void computer();
    void close();
    void quitGame();
};

#endif // GAME_H
