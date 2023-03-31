#ifndef WINDOW_H
#define WINDOW_H
#include "Button.h"
#include <QGraphicsScene>
#include "Square.h"
#include "Pieces.h"
#include <QWidget>
#include "Pieces.h"

class Window : public QObject
{
    Q_OBJECT
public:
    Window(QObject* parent = 0);
    void displayMenu();
    void displayChessboard(std::map<std::string,Square*> board);
    void displayPieces(std::list<Piece*> pieces);
    void actualizeView(std::map<std::string,Square*> board,std::list<Piece*> pieces);
    void addPiece(Piece* piece);
    void deletePiece(Piece* piece);
    void clearScene();
    QGraphicsScene *scene;

signals:
    void multiplayer();
    void singleplayer();
    void loading();
    void settings();
    void computer();
    void close();
    void playersRating();
};

#endif // WINDOW_H
