#include "Saver.h";
#include <typeinfo>;
//std::list<Piece*> Piece::allFigures{};


void Saver::save()
{
    QFile saveFile(savingPath);
    if (saveFile.open(QIODevice::WriteOnly))
    {
        std::cout<<"Saving file";
        saveFile.write(QJsonDocument(wholeGame).toJson());
        saveFile.close();
    }
}

void Saver::pieceToJson(Piece* piece)
{
    QJsonObject jsonPiece;
    jsonPiece.insert("pieceName",typeid(*piece).name());
    jsonPiece.insert("isWhite",piece->getIsWhite());
    singleMove.insert(QString::fromStdString(piece->actualPosition),jsonPiece);
}
void Saver::piecesToJson()
{
    clearJson(&singleMove);
    for(auto it=Piece::allFigures.begin();it!=Piece::allFigures.end();it++)
    {
    pieceToJson(*(it));
    wholeGame.insert(QString::number(move_number),singleMove);
    }
    wholeGame.insert(QString::number(move_number),singleMove);
    move_number+=1;

}

void Saver::clearJson(QJsonObject* listToClear)
{
    while(listToClear->length()>0)
       listToClear->remove(listToClear->keys().first());
}

void Saver::singlePieceChange(Piece *piece, std::string changedTo)
{
    QJsonObject movedPiece;
    movedPiece.insert("from",QString::fromStdString(piece->actualPosition));
    movedPiece.insert("pieceName",typeid(*piece).name());
    movedPiece.insert("isWhite",piece->getIsWhite());
    movedPiece.insert("changeTo",QString::fromStdString(changedTo));
    wholeGame.insert(QString::number(move_number),movedPiece);
    move_number+=1;
}
