#ifndef PIECES_H
#define PIECES_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsSceneMouseEvent>

class Piece: public QObject,public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Piece(QGraphicsItem * parent=0);

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    bool getIsWhite();
    void setIsPicked(bool picked_state);
    bool getIsPicked();

private:
    bool isWhite=true;
    bool isPicked=false;

};


#endif // PIECES_H
