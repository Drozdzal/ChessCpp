#ifndef PIECES_H
#define PIECES_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

class Piece: public QObject,public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Piece(QGraphicsItem * parent=0);
};


#endif // PIECES_H
