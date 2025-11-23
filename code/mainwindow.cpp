#include "mainwindow.h"
#include "gamescene.h"
#include "game.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFontDatabase>
#include <QFont>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , stackedWidget(nullptr)
    , homeScreen(nullptr)
    , playButton(nullptr)
    , gameScreen(nullptr)
    , gameView(nullptr)
    , gameScene(nullptr)
    , livesLabel(nullptr)
    , fishCounterLabel(nullptr)
    , wonScreen(nullptr)
    , playAgainWonButton(nullptr)
    , lostScreen(nullptr)
    , playAgainLostButton(nullptr)
    , customFontId(-1)
{
    setWindowTitle("Pinguim O Pescador");
    setFixedSize(1000, 720);
    
    loadCustomFont();
    setupUI();
    
    connect(Game::getInstance(), &Game::livesChanged, this, &MainWindow::updateLivesDisplay);
    connect(Game::getInstance(), &Game::fishCaughtChanged, this, &MainWindow::updateFishCounter);
}

MainWindow::~MainWindow()
{
}

void MainWindow::loadCustomFont()
{
    customFontId = QFontDatabase::addApplicationFont(":/assets/BUMBASTIKA.TTF");
}

void MainWindow::setupUI()
{
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);
    
    createHomeScreen();
    createGameScreen();
    createWonScreen();
    createLostScreen();
    
    stackedWidget->setCurrentIndex(HOME);
}

void MainWindow::createHomeScreen()
{
    homeScreen = new QWidget();
    
    QPalette palette;
    palette.setColor(QPalette::Window, QColor("#0074D9"));
    homeScreen->setAutoFillBackground(true);
    homeScreen->setPalette(palette);
    
    QVBoxLayout* layout = new QVBoxLayout(homeScreen);
    layout->setAlignment(Qt::AlignCenter);
    
    QLabel* titleLabel = new QLabel("PINGUIM\nO PESCADOR");
    titleLabel->setAlignment(Qt::AlignCenter);
    
    QFont titleFont;
    if (customFontId != -1) {
        QString family = QFontDatabase::applicationFontFamilies(customFontId).at(0);
        titleFont = QFont(family, 48, QFont::Bold);
    } else {
        titleFont = QFont("Arial", 48, QFont::Bold);
    }
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: white; text-shadow: 3px 3px 6px rgba(0,0,0,0.5);");
    layout->addWidget(titleLabel);
    
    QLabel* penguinLabel = new QLabel();
    QPixmap penguinPixmap(":/assets/penguin_launchscreen.png");
    penguinLabel->setPixmap(penguinPixmap.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    penguinLabel->setAlignment(Qt::AlignCenter);
    penguinLabel->setStyleSheet(
        "margin-left: 110px;"
        );
    layout->addWidget(penguinLabel);
    
    playButton = new QPushButton("JOGAR");
    QFont buttonFont;
    if (customFontId != -1) {
        QString family = QFontDatabase::applicationFontFamilies(customFontId).at(0);
        buttonFont = QFont(family, 24, QFont::Bold);
    } else {
        buttonFont = QFont("Arial", 24, QFont::Bold);
    }
    playButton->setFont(buttonFont);
    playButton->setFixedSize(300, 80);
    playButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #FFA500;"
        "   color: white;"
        "   border: 4px solid white;"
        "   border-radius: 15px;"
        "   padding: 10px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #FFB733;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #FF8C00;"
        "}"
    );
    connect(playButton, &QPushButton::clicked, this, &MainWindow::onPlayButtonClicked);
    layout->addWidget(playButton, 0, Qt::AlignCenter);
    
    stackedWidget->addWidget(homeScreen);
}

void MainWindow::createGameScreen()
{
    gameScreen = new QWidget();
    
    QVBoxLayout* mainLayout = new QVBoxLayout(gameScreen);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    
    gameScene = new GameScene();
    gameView = new QGraphicsView(gameScene);
    gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView->setFixedSize(1000, 720);
    gameView->setSceneRect(0, 0, 1000, 720);
    gameView->setMouseTracking(true);
    
    connect(gameScene, &GameScene::gameWon, this, &MainWindow::onGameWon);
    connect(gameScene, &GameScene::gameLost, this, &MainWindow::onGameLost);
    
    mainLayout->addWidget(gameView);
    
    QWidget* hudWidget = new QWidget(gameScreen);
    hudWidget->setGeometry(0, 0, 1000, 100);
    hudWidget->setStyleSheet("background: transparent;");
    
    QHBoxLayout* hudLayout = new QHBoxLayout(hudWidget);
    hudLayout->setContentsMargins(20, 20, 20, 20);

    QHBoxLayout* livesLayout = new QHBoxLayout();
    for (int i = 0; i < 3; i++) {
        QLabel* lifeIcon = new QLabel();
        QPixmap wormPixmap(":/assets/worm.png");
        lifeIcon->setPixmap(wormPixmap.scaled(35, 35, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        livesLayout->addWidget(lifeIcon);
        lifeIcons.append(lifeIcon);
    }
    hudLayout->addLayout(livesLayout);
    
    hudLayout->addStretch();

    QHBoxLayout* counterLayout = new QHBoxLayout();
    QLabel* fishIcon = new QLabel();
    QPixmap fishPixmap(":/assets/fish_ltr.png");
    fishIcon->setPixmap(fishPixmap.scaled(50, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    counterLayout->addWidget(fishIcon);
    
    fishCounterLabel = new QLabel("0/20");
    QFont counterFont;
    if (customFontId != -1) {
        QString family = QFontDatabase::applicationFontFamilies(customFontId).at(0);
        counterFont = QFont(family, 36, QFont::Bold);
    } else {
        counterFont = QFont("Arial", 36, QFont::Bold);
    }
    fishCounterLabel->setFont(counterFont);
    fishCounterLabel->setStyleSheet("color: white; text-shadow: 2px 2px 4px rgba(0,0,0,0.8);");
    counterLayout->addWidget(fishCounterLabel);
    
    hudLayout->addLayout(counterLayout);
    
    stackedWidget->addWidget(gameScreen);
}

void MainWindow::createWonScreen()
{
    wonScreen = new QWidget();
    
    QPalette palette;
    palette.setColor(QPalette::Window, QColor("#00AA00"));
    wonScreen->setAutoFillBackground(true);
    wonScreen->setPalette(palette);
    
    QVBoxLayout* layout = new QVBoxLayout(wonScreen);
    layout->setAlignment(Qt::AlignCenter);
   
    QLabel* messageLabel = new QLabel("VOCE GANHOU");
    messageLabel->setAlignment(Qt::AlignCenter);
    
    QFont messageFont;
    if (customFontId != -1) {
        QString family = QFontDatabase::applicationFontFamilies(customFontId).at(0);
        messageFont = QFont(family, 24, QFont::Bold);
    } else {
        messageFont = QFont("Arial", 24, QFont::Bold);
    }
    messageLabel->setFont(messageFont);
    messageLabel->setStyleSheet("color: white; text-shadow: 3px 3px 6px rgba(0,0,0,0.5);");
    layout->addWidget(messageLabel);
    
    QLabel* penguinLabel = new QLabel();
    QPixmap penguinPixmap(":/assets/penguin_launchscreen.png");
    penguinLabel->setPixmap(penguinPixmap.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    penguinLabel->setAlignment(Qt::AlignCenter);
    penguinLabel->setStyleSheet(
        "margin-left: 90px;"
        );
    layout->addWidget(penguinLabel);

    playAgainWonButton = new QPushButton("JOGAR NOVAMENTE");
    QFont buttonFont;
    if (customFontId != -1) {
        QString family = QFontDatabase::applicationFontFamilies(customFontId).at(0);
        buttonFont = QFont(family, 14, QFont::Bold);
    } else {
        buttonFont = QFont("Arial", 14, QFont::Bold);
    }
    playAgainWonButton->setFont(buttonFont);
    playAgainWonButton->setFixedSize(400, 80);
    playAgainWonButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #FFA500;"
        "   color: white;"
        "   border: 4px solid white;"
        "   border-radius: 15px;"
        "   padding: 10px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #FFB733;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #FF8C00;"
        "}"
    );
    connect(playAgainWonButton, &QPushButton::clicked, this, &MainWindow::onPlayAgainButtonClicked);
    layout->addWidget(playAgainWonButton, 0, Qt::AlignCenter);
    
    stackedWidget->addWidget(wonScreen);
}

void MainWindow::createLostScreen()
{
    lostScreen = new QWidget();
    
    QPalette palette;
    palette.setColor(QPalette::Window, QColor("#CC0000"));
    lostScreen->setAutoFillBackground(true);
    lostScreen->setPalette(palette);
    
    QVBoxLayout* layout = new QVBoxLayout(lostScreen);
    layout->setAlignment(Qt::AlignCenter);
   
    QLabel* messageLabel = new QLabel("VOCE PERDEU");
    messageLabel->setAlignment(Qt::AlignCenter);
    
    QFont messageFont;
    if (customFontId != -1) {
        QString family = QFontDatabase::applicationFontFamilies(customFontId).at(0);
        messageFont = QFont(family, 24, QFont::Bold);
    } else {
        messageFont = QFont("Arial", 24, QFont::Bold);
    }
    messageLabel->setFont(messageFont);
    messageLabel->setStyleSheet("color: white; text-shadow: 3px 3px 6px rgba(0,0,0,0.5);");
    layout->addWidget(messageLabel);
    

    QLabel* penguinLabel = new QLabel();
    QPixmap penguinPixmap(":/assets/penguin_launchscreen.png");
    penguinLabel->setPixmap(penguinPixmap.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    penguinLabel->setAlignment(Qt::AlignCenter);
    penguinLabel->setStyleSheet(
        "margin-left: 90px;"
        );
    layout->addWidget(penguinLabel);
 
    playAgainLostButton = new QPushButton("JOGAR NOVAMENTE");
    QFont buttonFont;
    if (customFontId != -1) {
        QString family = QFontDatabase::applicationFontFamilies(customFontId).at(0);
        buttonFont = QFont(family, 14, QFont::Bold);
    } else {
        buttonFont = QFont("Arial", 14, QFont::Bold);
    }
    playAgainLostButton->setFont(buttonFont);
    playAgainLostButton->setFixedSize(400, 80);
    playAgainLostButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #FFA500;"
        "   color: white;"
        "   border: 4px solid white;"
        "   border-radius: 15px;"
        "   padding: 10px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #FFB733;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #FF8C00;"
        "}"
    );
    connect(playAgainLostButton, &QPushButton::clicked, this, &MainWindow::onPlayAgainButtonClicked);
    layout->addWidget(playAgainLostButton, 0, Qt::AlignCenter);
    
    stackedWidget->addWidget(lostScreen);
}

void MainWindow::onPlayButtonClicked()
{
    stackedWidget->setCurrentIndex(GAME);
    gameScene->startGame();
    updateLivesDisplay(3);
    updateFishCounter(0);
}

void MainWindow::onPlayAgainButtonClicked()
{
    stackedWidget->setCurrentIndex(HOME);
    gameScene->resetGame();
}

void MainWindow::onGameWon()
{
    stackedWidget->setCurrentIndex(WON);
}

void MainWindow::onGameLost()
{
    stackedWidget->setCurrentIndex(LOST);
}

void MainWindow::updateLivesDisplay(int lives)
{
    for (int i = 0; i < lifeIcons.size(); i++) {
        if (i < lives) {
            lifeIcons[i]->setVisible(true);
        } else {
            lifeIcons[i]->setVisible(false);
        }
    }
}

void MainWindow::updateFishCounter(int fishCaught)
{
    fishCounterLabel->setText(QString("%1/20").arg(fishCaught));
}
