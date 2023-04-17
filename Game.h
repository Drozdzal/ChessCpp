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

class Game: public QGraphicsView{
    Q_OBJECT
public:
    // constructors
    Game(QWidget* parent=NULL);

    // public methods


    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent* event);
    bool isMovePossible(int X,int Y);
    void actualizeView();
    void backToPrimaryPosition();
    // public attributes
    Window* window;
    MyServer* server;
    MyClient* client;
    Piece* pieceToMove=nullptr;
    Board* chessboard;
    Saver saver;
    Loader loader;
    GameMode* gameMode; // TUTAJ PAMIETAC O MOZLIWYM PROBLEMIE w innych niz singleplayer;
    bool inPlayingMode=false;

public slots:
    void multiplayer();
    void createServer();
    void joinServer();
    void singleplayer();
    void loading();
    void nextMove();
    void previousMove();
    void settings();
    void computer();
    void close();
    void quitGame();
private:
    bool whiteTurn=true;


};

#endif // GAME_H
