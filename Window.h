#ifndef WINDOW_H
#define WINDOW_H
#include "Button.h"
#include <QGraphicsScene>
#include "Square.h"
#include "Pieces.h"
#include <QWidget>
#include "Pieces.h"
#include <QtCore/QException>
#include <QGraphicsWidget>
#include <QButtonGroup>

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
    void deletePieces(std::list<Piece*> pieces);
    void clearScene();
    void displayMultiplayer();
    void displayCreateServer();
    void displayJoinServer();
    void displaySettings();
    QString loadingWindow();
    QGraphicsScene *scene;

signals:
    void multiplayer();
    void createServer();
    void joinServer();
    void singleplayer();
    void loading();
    void nextMove();
    void previousMove();
    void settings();
    void baseTimeChanged();
    void addingTimeChanged();
    void computer();
    void close();
    void playersRating();
};

class ChoosingPanel : public QGraphicsWidget
{
public:
    ChoosingPanel(QGraphicsItem* parent = nullptr);

    int getSelectedDuration() const;

private:
    QButtonGroup* durationGroup;
};
#endif // WINDOW_H
