#ifndef SAVER_H
#define SAVER_H
#include "iostream"
#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include "Pieces.h"

class Saver{
public:
    void save();
    void pieceToJson(Piece* piece);
    void piecesToJson();
    void singlePieceChange(Piece* piece, std::string secondaryPlace);
    void clearJson(QJsonObject* listToClear);
    int move_number=0;
private:
    enum SaveFormat {
            Json, Binary
        };
    QString savingPath=QString("D:/mgr/cpp/Chess/rozgrywki/rozgrywka.json");
    QJsonObject wholeGame;
    QJsonObject singleMove;

};

#endif
