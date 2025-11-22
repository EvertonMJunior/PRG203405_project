#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QList>

class Penguin;
class FishingLine;
class AnimalGenerator;
class AcquaticAnimal;
class Fish;
class Jellyfish;

class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GameScene(QObject* parent = nullptr);
    ~GameScene() override;
    
    void startGame();
    void stopGame();
    void resetGame();

signals:
    void gameWon();
    void gameLost();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

private slots:
    void gameLoop();
    void onFishSpawned(Fish* fish);
    void onJellyfishSpawned(Jellyfish* jellyfish);
    void startGenerator();

private:
    void setupScene();
    void checkCollisions();
    void checkFishCollision();
    void checkJellyfishCollision();
    void removeOffscreenAnimals();
    
    Penguin* penguin;
    FishingLine* fishingLine;
    AnimalGenerator* animalGenerator;
    QTimer* gameLoopTimer;
    QTimer* startDelayTimer;
    
    QList<Fish*> fishes;
    QList<Jellyfish*> jellyfishes;
    
    static constexpr qreal SCENE_WIDTH = 1000.0;
    static constexpr qreal SCENE_HEIGHT = 720.0;
    static constexpr qreal PENGUIN_X = 640.0;
    static constexpr qreal PENGUIN_Y = 130.0;
};

#endif // GAMESCENE_H

