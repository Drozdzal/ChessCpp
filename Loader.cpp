#include "Loader.h"
#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QStringList>
#include "Pieces.h"
//#include "Game.h"

//extern Game * game;


void Loader::readJson(QString path){
    QFile desiredJson;
    desiredJson.setFileName(path);
    desiredJson.open(QIODevice::ReadOnly | QIODevice::Text);
    loadedGame = desiredJson.readAll();
    qDebug()<<loadedGame;
    desiredJson.close();

}

void Loader::createPieces(Board* board,QJsonObject obiekcik)
{
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
            //game->window->addPiece(piece);
            board->setPieceOnSquare(piece, square);
        }

        if(obiekcik.value((*it)).toObject().value("pieceName").toString() == "class Rook")
        {
            Rook* piece = new Rook(obiekcik.value((*it)).toObject().value("isWhite").toBool());
            std::string square = "00";
            square[0]=((*it)[0]).toLatin1();
            square[1]=((*it)[1]).toLatin1();
            //game->window->addPiece(piece);
            board->setPieceOnSquare(piece, square);
        }
        if(obiekcik.value((*it)).toObject().value("pieceName").toString() == "class Queen")
        {
            Queen* piece = new Queen(obiekcik.value((*it)).toObject().value("isWhite").toBool());
            std::string square = "00";
            //Przyjemna konwersja na zwyklego chara
            square[0]=((*it)[0]).toLatin1();
            square[1]=((*it)[1]).toLatin1();
            //game->window->addPiece(piece);
            board->setPieceOnSquare(piece, square);
        }
        if(obiekcik.value((*it)).toObject().value("pieceName").toString() == "class Knight")
        {
            Knight* piece = new Knight(obiekcik.value((*it)).toObject().value("isWhite").toBool());
            std::string square = "00";
            square[0]=((*it)[0]).toLatin1();
            square[1]=((*it)[1]).toLatin1();
            //game->window->addPiece(piece);
            board->setPieceOnSquare(piece, square);
        }
        if(obiekcik.value((*it)).toObject().value("pieceName").toString() == "class Bishop")
        {
            Bishop* piece = new Bishop(obiekcik.value((*it)).toObject().value("isWhite").toBool());
            std::string square = "00";
            square[0]=((*it)[0]).toLatin1();
            square[1]=((*it)[1]).toLatin1();
            //game->window->addPiece(piece);
            board->setPieceOnSquare(piece, square);
        }
        if(obiekcik.value((*it)).toObject().value("pieceName").toString() == "class King")
        {
            King* piece = new King(obiekcik.value((*it)).toObject().value("isWhite").toBool());
            std::string square = "00";
            square[0]=((*it)[0]).toLatin1();
            square[1]=((*it)[1]).toLatin1();
            //game->window->addPiece(piece);
            board->setPieceOnSquare(piece, square);
        }
    }
}
void Loader::firstMoveFromJson(Board* board){
//qWarning()<< loadedGame;
QJsonDocument d = QJsonDocument::fromJson(loadedGame.toUtf8());
QJsonObject set = d.object();
QJsonValue value = set.value(QString::number(actual_move));
QJsonObject obiekcik = value.toObject();
createPieces(board,obiekcik);


}
void Loader::moveForward(Board* board){
    actual_move+=1;
    std::list<Piece*>().swap(Piece::allFigures);
    QJsonDocument d = QJsonDocument::fromJson(loadedGame.toUtf8());
    QJsonObject set = d.object();
    QJsonValue value = set.value(QString::number(actual_move));
    QJsonObject obiekcik = value.toObject();
    QStringList pola = obiekcik.keys();
    createPieces(board,obiekcik);

}
void Loader::moveBackward(Board* board){
    actual_move-=1;
    std::list<Piece*>().swap(Piece::allFigures);
    QJsonDocument d = QJsonDocument::fromJson(loadedGame.toUtf8());
    QJsonObject set = d.object();
    QJsonValue value = set.value(QString::number(actual_move));
    QJsonObject obiekcik = value.toObject();
    QStringList pola = obiekcik.keys();
    createPieces(board,obiekcik);
}


