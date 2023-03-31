#include "Window.h"

Window::Window(QObject* parent): QObject(parent){
    scene=new QGraphicsScene();
    scene->setSceneRect(0,0,1200,900);
}

void Window::displayMenu()
{
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Chess Game - MZ"));
    QFont titleFont("arial",80);
    titleText->setFont(titleFont);
    int txPos = 600 - titleText->boundingRect().width()/2;
    int tyPos = 100;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the quit button
    Button* multiplayerButton = new Button(QString("Play Multiplayer"));
    int mbxPos = 600 - multiplayerButton->boundingRect().width()/2;
    int mbyPos = 275;
    multiplayerButton->setPos(mbxPos,mbyPos);
    connect(multiplayerButton,&Button::clicked,this,&Window::multiplayer);
    scene->addItem(multiplayerButton);


    // create the play button
    Button* singleplayerButton = new Button(QString("Play Singleplayer"));
    int spxPos = 600 - singleplayerButton->boundingRect().width()/2;
    int spyPos = 350;
    singleplayerButton->setPos(spxPos,spyPos);
    connect(singleplayerButton,&Button::clicked,this,&Window::singleplayer);
    scene->addItem(singleplayerButton);

    // create the quit button
    Button* computerButton = new Button(QString("Play against computer"));
    int cxPos = 600 - computerButton->boundingRect().width()/2;
    int cyPos = 425;
    computerButton->setPos(cxPos,cyPos);
    connect(computerButton,&Button::clicked,this,&Window::computer);
    scene->addItem(computerButton);

    // create the quit button
    Button* settingsButton = new Button(QString("Settings"));
    int sxPos = 600 - settingsButton->boundingRect().width()/2;
    int syPos = 500;
    settingsButton->setPos(sxPos,syPos);
    connect(settingsButton,&Button::clicked,this,&Window::settings);
    scene->addItem(settingsButton);

    // create the quit button
    Button* loadButton = new Button(QString("Load Game"));
    int lxPos = 600 - loadButton->boundingRect().width()/2;
    int lyPos = 575;
    loadButton->setPos(lxPos,lyPos);
    connect(loadButton,&Button::clicked,this,&Window::loading);
    scene->addItem(loadButton);

    // create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos = 600 - quitButton->boundingRect().width()/2;
    int qyPos = 650;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,&Button::clicked,this,&Window::close);
    scene->addItem(quitButton);
}
void Window::displayChessboard(std::map<std::string,Square*> board){
    for(auto it=board.begin();it!=board.end();it++){
        scene->addItem((it->second));
    }
}

void Window::displayPieces(std::list<Piece*> pieces)
{
    for(auto it=pieces.begin();it!=pieces.end();it++){
        scene->addItem(*it);
    }
}

void Window::addPiece(Piece* piece)
{
    scene->addItem(piece);
}
void Window::actualizeView(std::map<std::string,Square*> board,std::list<Piece*> pieces)
{
    try {
        scene->clear();
        displayChessboard(board);
        displayPieces(pieces);
    } catch (std::exception& e) {
        // Handle the exception
        qDebug() << "Exception caught: " << e.what();
    } catch (...) {
        // Handle any other type of exception
        qDebug() << "Unknown exception caught";
    }

}
void Window::deletePiece(Piece* piece)
{
    scene->removeItem(piece);
}
void Window::clearScene()
{
    scene->clear();
}
