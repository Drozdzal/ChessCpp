#include "Window.h"
#include "QFileDialog"
#include "QPushButton"
#include "QWidget"
#include <QGraphicsLinearLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGraphicsProxyWidget>
#include <QVBoxLayout>
#include <QLabel>

QButtonGroup *Window::getAddingTime() const
{
    return addingTime;
}

void Window::setStartingTime(QButtonGroup *newStartingTime)
{
    startingTime = newStartingTime;
}

QButtonGroup *Window::getStartingTime() const
{
    return startingTime;
}

Window::Window(QObject* parent): QObject(parent){
    scene=new QGraphicsScene();
    scene->setSceneRect(0,0,1200,900);
}




void Window::displayMenu()
{
    scene->clear();
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
    try{
    for(auto it=board.begin();it!=board.end();it++){
        scene->addItem((it->second));
    }
    }
    catch (QException& e) {
        // Handle the exception
        qDebug() << "Caught exception: " << e.what();
    }
}

void Window::displayMultiplayer()
{
    scene->clear();
    Button* createButton = new Button(QString("Create Game"));
    int mbxPos = 600 - createButton->boundingRect().width()/2;
    int mbyPos = 275;
    createButton->setPos(mbxPos,mbyPos);
    connect(createButton,&Button::clicked,this,&Window::createServer);
    scene->addItem(createButton);


    // create the play button
    Button* joinButton = new Button(QString("Join online game"));
    int spxPos = 600 - joinButton->boundingRect().width()/2;
    int spyPos = 350;
    joinButton->setPos(spxPos,spyPos);
    connect(joinButton,&Button::clicked,this,&Window::joinServer);
    scene->addItem(joinButton);

    // create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int cxPos = 600 - quitButton->boundingRect().width()/2;
    int cyPos = 425;
    quitButton->setPos(cxPos,cyPos);
    connect(quitButton,&Button::clicked,this,&Window::close);
    scene->addItem(quitButton);
}

void Window::displayCreateServer(){

}

void Window::displayJoinServer(){

}
void Window::displayPieces(std::list<Piece*> pieces)
{
    for(auto it=Piece::allFigures.begin();it!=Piece::allFigures.end();it++){
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

QString Window::loadingWindow()
{
    QString folderPath = ":/bazowy"; // replace with your desired folder path

    Button* nextMoveButton = new Button("Next Move");
            connect(nextMoveButton, &Button::clicked, this, &Window::nextMove);

            scene->addItem(nextMoveButton);
            nextMoveButton->setPos(scene->width() - nextMoveButton->boundingRect().width() - 100, 300); // Position on the right side

    Button* previousMoveButton = new Button("Previous Move");
                    connect(previousMoveButton, &Button::clicked, this, &Window::previousMove);

                    scene->addItem(previousMoveButton);
                    previousMoveButton->setPos(scene->width() - previousMoveButton->boundingRect().width() - 100, 500); // Position on the right side

       // Open a file dialog to allow the player to choose a file
    QString filePath = QFileDialog::getOpenFileName(nullptr, tr("Choose a file"), folderPath);
    return filePath;
    // Open a file dialog to allow the player to choose a file
}
void Window::deletePiece(Piece* piece)
{
    scene->removeItem(piece);
}
void Window::deletePieces(std::list<Piece*> pieces)
{
    for(auto it=Piece::allFigures.begin();it!=Piece::allFigures.end();it++){
        scene->removeItem(*it);
    }

}
void Window::clearScene()
{
    scene->clear();

}

void Window::displaySettings()
{
    scene->clear();

    QWidget* widget = new QWidget();
    QLabel* label = new QLabel("Starting Time:", widget);
    QVBoxLayout* mainLayout = new QVBoxLayout(widget);
    // Create a QButtonGroup and add some buttons to it
    startingTime = new QButtonGroup(widget);
    QPushButton* lowTime = new QPushButton("30 mins", widget);
    QPushButton* mediumTime = new QPushButton("10 mins", widget);
    QPushButton* highTime = new QPushButton("5 mins", widget);
    startingTime->addButton(lowTime);
    startingTime->addButton(mediumTime);
    startingTime->addButton(highTime);

    QHBoxLayout* layout = new QHBoxLayout(widget);
    layout->addWidget(lowTime);
    layout->addWidget(mediumTime);
    layout->addWidget(highTime);
    mainLayout->addLayout(layout);
    // Create a QGraphicsProxyWidget to hold the widget and add it to the scene

    connect(startingTime, &QButtonGroup::buttonClicked, this, &Window::baseTimeChanged);
    addingTime = new QButtonGroup(widget);
    QPushButton* lowAdding = new QPushButton("30 sec", widget);
    QPushButton* mediumAdding = new QPushButton("20 sec", widget);
    QPushButton* highAdding = new QPushButton("10 sec", widget);
    addingTime->addButton(lowAdding);
    addingTime->addButton(mediumAdding);
    addingTime->addButton(highAdding);
    connect(addingTime, &QButtonGroup::buttonClicked, this, &Window::addingTimeChanged);
    // Create a QButtonGroup and add some buttons to it
    QHBoxLayout* layout2 = new QHBoxLayout();
    layout2->addWidget(lowAdding);
    layout2->addWidget(mediumAdding);
    layout2->addWidget(highAdding);



    // Create a QGraphicsProxyWidget to hold the widget and add it to the scene

    mainLayout->addSpacing(100);
    mainLayout->addLayout(layout2);
    widget->setLayout(mainLayout);
    QGraphicsProxyWidget* proxyWidget = new QGraphicsProxyWidget();
    proxyWidget->setWidget(widget);


    Button* mainMenu = new Button(QString("Back to Main Menu"));
    int xPos = 600 - mainMenu->boundingRect().width()/2;
    int yPos = 275;
    mainMenu->setPos(xPos,yPos);
    connect(mainMenu,&Button::clicked,this,&Window::showMainMenu);
    scene->addItem(mainMenu);
    scene->addItem(proxyWidget);


}

void Window::addSurrenderButton()
{
    Button* surrenderButton = new Button(QString("Surrender"));
    int xPos = 950 - surrenderButton->boundingRect().width()/2;
    int yPos = 300;
    surrenderButton->setPos(xPos,yPos);
    connect(surrenderButton,&Button::clicked,this,&Window::surrenderButton);
    scene->addItem(surrenderButton);
}

