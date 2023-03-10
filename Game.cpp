#include "Game.h"
#include "Square.h"
#include "Button.h"
#include <QGraphicsTextItem>
#include "Pieces.h"

Game::Game(QWidget *parent){
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,768);
    setScene(scene);
}

void Game::start(){
    // test code TODO remove
    int asci_val=66;
    bool color=false;
    QList<Square*> squares;
    for(int row=1;row<=8;row+=1)
    {
        for(int column=1;column<=8;column+=1)
        {
            Square* square = new Square();
            square->setPosition(75*row,75*column);
            square->setColor(color);
            asci_val+=1;
            color=!(color);
            squares.append(square);
            scene->addItem(square);
        }
        color=!(color);
    }
    Piece* piece = new Piece();
    piece->setPos(20,40);
    scene->addItem(piece);
}


void Game::displayStart(){
    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Chess Game - MZ"));
    QFont titleFont("arial",80);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 100;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the quit button
    Button* multiplayerButton = new Button(QString("Play Multiplayer"));
    int mbxPos = this->width()/2 - multiplayerButton->boundingRect().width()/2;
    int mbyPos = 275;
    multiplayerButton->setPos(mbxPos,mbyPos);
    connect(multiplayerButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(multiplayerButton);


    // create the play button
    Button* singleplayerButton = new Button(QString("Play Singleplayer"));
    int spxPos = this->width()/2 - singleplayerButton->boundingRect().width()/2;
    int spyPos = 350;
    singleplayerButton->setPos(spxPos,spyPos);
    connect(singleplayerButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(singleplayerButton);

    // create the quit button
    Button* computerButton = new Button(QString("Play against computer"));
    int cxPos = this->width()/2 - computerButton->boundingRect().width()/2;
    int cyPos = 425;
    computerButton->setPos(cxPos,cyPos);
    connect(computerButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(computerButton);

    // create the quit button
    Button* settingsButton = new Button(QString("Settings"));
    int sxPos = this->width()/2 - settingsButton->boundingRect().width()/2;
    int syPos = 500;
    settingsButton->setPos(sxPos,syPos);
    connect(settingsButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(settingsButton);

    // create the quit button
    Button* loadButton = new Button(QString("Load Game"));
    int lxPos = this->width()/2 - loadButton->boundingRect().width()/2;
    int lyPos = 575;
    loadButton->setPos(lxPos,lyPos);
    connect(loadButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(loadButton);

    // create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 650;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);


}
