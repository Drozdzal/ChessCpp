#include "Loader.h"
#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QStringList>
#include "Pieces.h"
#include "Game.h"
extern Game * game;


void Loader::readJson(QString path){
    QFile desiredJson;
    desiredJson.setFileName(path);
    desiredJson.open(QIODevice::ReadOnly | QIODevice::Text);
    loadedGame = desiredJson.readAll();
    desiredJson.close();

}
void Loader::firstMoveFromJson(){
//qWarning()<< loadedGame;
QJsonDocument d = QJsonDocument::fromJson(loadedGame.toUtf8());
QJsonObject set = d.object();
QJsonValue value = set.value(QString("0"));
//qWarning()<<value;
QJsonObject obiekcik = value.toObject();
QStringList pola = obiekcik.keys();
for(auto it=pola.begin();it!=pola.end();it++)
{
    qWarning()<<(*it);
    qWarning()<<obiekcik.value((*it)).toObject().value("isWhite").toBool() <<"\n";
    qWarning()<<obiekcik.value((*it)).toObject().value("pieceName").toString() <<"\n";

    if(obiekcik.value((*it)).toObject().value("pieceName").toString() == "class Pawn")
    {
        Pawn* piece = new Pawn(obiekcik.value((*it)).toObject().value("isWhite").toBool());
        std::string square = "00";
        square[0]=((*it)[0]).toLatin1();
        square[1]=((*it)[1]).toLatin1();
        game->scene->addItem(piece);
        game->chessboard.setPieceOnSquare(piece, square);
    }

    if(obiekcik.value((*it)).toObject().value("pieceName").toString() == "class Rook")
    {
        Rook* piece = new Rook(obiekcik.value((*it)).toObject().value("isWhite").toBool());
        std::string square = "00";
        square[0]=((*it)[0]).toLatin1();
        square[1]=((*it)[1]).toLatin1();
        game->scene->addItem(piece);
        game->chessboard.setPieceOnSquare(piece, square);
    }
    if(obiekcik.value((*it)).toObject().value("pieceName").toString() == "class Queen")
    {
        Queen* piece = new Queen(obiekcik.value((*it)).toObject().value("isWhite").toBool());
        std::string square = "00";
        //Przyjemna konwersja na zwyklego chara
        square[0]=((*it)[0]).toLatin1();
        square[1]=((*it)[1]).toLatin1();
        game->scene->addItem(piece);
        game->chessboard.setPieceOnSquare(piece, square);
    }
    if(obiekcik.value((*it)).toObject().value("pieceName").toString() == "class Knight")
    {
        Knight* piece = new Knight(obiekcik.value((*it)).toObject().value("isWhite").toBool());
        std::string square = "00";
        square[0]=((*it)[0]).toLatin1();
        square[1]=((*it)[1]).toLatin1();
        game->scene->addItem(piece);
        game->chessboard.setPieceOnSquare(piece, square);
    }
    if(obiekcik.value((*it)).toObject().value("pieceName").toString() == "class Bishop")
    {
        Bishop* piece = new Bishop(obiekcik.value((*it)).toObject().value("isWhite").toBool());
        std::string square = "00";
        square[0]=((*it)[0]).toLatin1();
        square[1]=((*it)[1]).toLatin1();
        game->scene->addItem(piece);
        game->chessboard.setPieceOnSquare(piece, square);
    }
    if(obiekcik.value((*it)).toObject().value("pieceName").toString() == "class King")
    {
        King* piece = new King(obiekcik.value((*it)).toObject().value("isWhite").toBool());
        std::string square = "00";
        square[0]=((*it)[0]).toLatin1();
        square[1]=((*it)[1]).toLatin1();
        game->scene->addItem(piece);
        game->chessboard.setPieceOnSquare(piece, square);
    }
}





}
void Loader::moveForward(){

}
void Loader::moveBackward(){

}

//void readJson()
//   {
//      QString val;
//      QFile file;
//      file.setFileName("test.json");
//      file.open(QIODevice::ReadOnly | QIODevice::Text);
//      val = file.readAll();
//      file.close();
//      qWarning() << val;
//      QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
//      QJsonObject sett2 = d.object();
//      QJsonValue value = sett2.value(QString("appName"));
//      qWarning() << value;
//      QJsonObject item = value.toObject();
//      qWarning() << tr("QJsonObject of description: ") << item;

//      /* in case of string value get value and convert into string*/
//      qWarning() << tr("QJsonObject[appName] of description: ") << item["description"];
//      QJsonValue subobj = item["description"];
//      qWarning() << subobj.toString();

//      /* in case of array get array and convert into string*/
//      qWarning() << tr("QJsonObject[appName] of value: ") << item["imp"];
//      QJsonArray test = item["imp"].toArray();
//      qWarning() << test[1].toString();
//   }
