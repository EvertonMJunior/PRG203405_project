#include "gamescene.h"
#include "penguin.h"
#include "fishingline.h"
#include "animalgenerator.h"
#include "fish.h"
#include "jellyfish.h"
#include "game.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>

GameScene::GameScene(QObject* parent)
    : QGraphicsScene(parent)
    , penguin(nullptr)
    , fishingLine(nullptr)
    , animalGenerator(nullptr)
    , gameLoopTimer(nullptr)
    , startDelayTimer(nullptr)
{
    setSceneRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    setupScene();
}

GameScene::~GameScene()
{
    stopGame();
  
    qDeleteAll(fishes);
    qDeleteAll(jellyfishes);
}

void GameScene::setupScene()
{
    QPixmap bgPixmap(":/assets/game_background.png");
    QPixmap scaledBg = bgPixmap.scaled(SCENE_WIDTH, SCENE_HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem* background = new QGraphicsPixmapItem(scaledBg);
    background->setZValue(-1);
    addItem(background);
 
    penguin = new Penguin();
    penguin->setPos(PENGUIN_X - penguin->boundingRect().width() / 2, PENGUIN_Y);
    penguin->setZValue(10);
    addItem(penguin);
 
    fishingLine = new FishingLine(PENGUIN_X-115, PENGUIN_Y+22);
    fishingLine->setZValue(5);
    addItem(fishingLine);
 
    animalGenerator = new AnimalGenerator(this);
    Game::getInstance()->setAnimalGenerator(animalGenerator);
    
    connect(animalGenerator, &AnimalGenerator::fishSpawned, this, &GameScene::onFishSpawned);
    connect(animalGenerator, &AnimalGenerator::jellyfishSpawned, this, &GameScene::onJellyfishSpawned);
    
    gameLoopTimer = new QTimer(this);
    connect(gameLoopTimer, &QTimer::timeout, this, &GameScene::gameLoop);
    
    startDelayTimer = new QTimer(this);
    startDelayTimer->setSingleShot(true);
    connect(startDelayTimer, &QTimer::timeout, this, &GameScene::startGenerator);
}

void GameScene::startGame()
{
    Game::getInstance()->reset();
    Game::getInstance()->setStatus(Status::Playing);
    
    for (Fish* fish : fishes) {
        removeItem(fish);
        delete fish;
    }
    fishes.clear();
    
    for (Jellyfish* jelly : jellyfishes) {
        removeItem(jelly);
        delete jelly;
    }
    jellyfishes.clear();
    
    gameLoopTimer->start(16); // ~60 FPS
    
    startDelayTimer->start(1000);
}

void GameScene::stopGame()
{
    if (gameLoopTimer) {
        gameLoopTimer->stop();
    }
    if (startDelayTimer) {
        startDelayTimer->stop();
    }
    if (animalGenerator) {
        animalGenerator->stop();
    }
}

void GameScene::resetGame()
{
    stopGame();
   
    for (Fish* fish : fishes) {
        removeItem(fish);
        delete fish;
    }
    fishes.clear();
    
    for (Jellyfish* jelly : jellyfishes) {
        removeItem(jelly);
        delete jelly;
    }
    jellyfishes.clear();
    
    Game::getInstance()->reset();
}

void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (Game::getInstance()->getStatus() == Status::Playing) {
        fishingLine->setY(event->scenePos().y());
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void GameScene::gameLoop()
{
    Status currentStatus = Game::getInstance()->getStatus();
    
    if (currentStatus != Status::Playing) {
        if (currentStatus == Status::Won) {
            stopGame();
            emit gameWon();
        } else if (currentStatus == Status::Lost) {
            stopGame();
            emit gameLost();
        }
        return;
    }
    
    for (Fish* fish : fishes) {
        fish->updatePosition();
    }
    
    for (Jellyfish* jelly : jellyfishes) {
        jelly->updatePosition();
    }
    
    checkCollisions();
   
    removeOffscreenAnimals();
}

void GameScene::onFishSpawned(Fish* fish)
{
    fishes.append(fish);
    addItem(fish);
    fish->setZValue(2);
}

void GameScene::onJellyfishSpawned(Jellyfish* jellyfish)
{
    jellyfishes.append(jellyfish);
    addItem(jellyfish);
    jellyfish->setZValue(3);
}

void GameScene::startGenerator()
{
    animalGenerator->start();
}

void GameScene::checkCollisions()
{
    checkFishCollision();
    checkJellyfishCollision();
}

void GameScene::checkFishCollision()
{
    QRectF tipRect = fishingLine->getTipRect();
    
    for (int i = fishes.size() - 1; i >= 0; --i) {
        Fish* fish = fishes[i];
        QRectF fishRect = fish->sceneBoundingRect();
        
        if (tipRect.intersects(fishRect)) {
           
            Game::getInstance()->incrementFishCaught();
            
            removeItem(fish);
            fishes.removeAt(i);
            delete fish;
        }
    }
}

void GameScene::checkJellyfishCollision()
{
    QPainterPath linePath = fishingLine->getLinePath();
    QRectF tipRect = fishingLine->getTipRect();
    
    for (Jellyfish* jelly : jellyfishes) {
        QRectF jellyRect = jelly->sceneBoundingRect();
        
        if (linePath.intersects(jellyRect) || tipRect.intersects(jellyRect)) {
            penguin->shock();
            Game::getInstance()->decrementLives();
            
            QTimer::singleShot(200, [this]() {
                if (penguin) {
                    penguin->clearShockEffect();
                }
            });
            
            removeItem(jelly);
            jellyfishes.removeOne(jelly);
            delete jelly;
            break; // Somente um choque por frame
        }
    }
}

void GameScene::removeOffscreenAnimals()
{
    for (int i = fishes.size() - 1; i >= 0; --i) {
        Fish* fish = fishes[i];
        if (fish->isOffscreen(SCENE_WIDTH)) {
            removeItem(fish);
            fishes.removeAt(i);
            delete fish;
        }
    }
    
    for (int i = jellyfishes.size() - 1; i >= 0; --i) {
        Jellyfish* jelly = jellyfishes[i];
        if (jelly->isOffscreen(SCENE_WIDTH)) {
            removeItem(jelly);
            jellyfishes.removeAt(i);
            delete jelly;
        }
    }
}

