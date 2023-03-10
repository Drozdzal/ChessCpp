#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
// #include "HexBoard.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    // constructors
    Game(QWidget* parent=NULL);

    // public methods

    void displayStart();

    // public attributes
    QGraphicsScene* scene;
    // HexBoard* hexBoard; TODO
    QString whosTurn;
public slots:
    void start();
};

#endif // GAME_H
