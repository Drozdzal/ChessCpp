#ifndef PIECES_H
#define PIECES_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QVector2D>

class Piece: public QObject,public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Piece(QGraphicsItem * parent=0);

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    bool getIsWhite();
    void setIsPicked(bool picked_state);
    bool getIsPicked();
    bool isMovePossible(int destRow,int destColumn);
    bool checkPawnMoves(int destRow,int destColumn);
    bool checkKingMoves(int destRow,int destColumn);
    bool checkRookMoves(int destRow,int destColumn);
    bool checkBishopMoves(int destRow,int destColumn);
    bool checkKnightMoves(int destRow,int destColumn);
    void createWhitePiece();
    int row;
    int column;

private:
    bool isWhite=true;
    bool isPicked=false;
    bool firstMove=true;

};


#endif // PIECES_H
