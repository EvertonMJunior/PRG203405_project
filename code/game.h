#ifndef GAME_H
#define GAME_H

#include <QObject>

class AnimalGenerator;

enum class Status {
    Waiting,
    Playing,
    Won,
    Lost
};

enum class Direction {
    LeftToRight,
    RightToLeft
};

enum class Side {
    Left,
    Right
};

class Game : public QObject
{
    Q_OBJECT

public:
    static Game* getInstance();
    
    Status getStatus() const;
    void setStatus(Status status);
    
    int getFishCaught() const;
    void incrementFishCaught();
    
    int getRemainingLives() const;
    void decrementLives();
    
    void reset();
    
    void setAnimalGenerator(AnimalGenerator* generator);
    
    double getCurrentFishRate() const;
    double getCurrentJellyRate() const;

signals:
    void fishCaughtChanged(int count);
    void livesChanged(int lives);
    void statusChanged(Status status);

private:
    Game();
    ~Game() override = default;
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    
    static Game* instance;
    
    Status status;
    int fish_caught;
    int remaining_lives;
    double current_fish_rate;
    double current_jelly_rate;
    AnimalGenerator* animal_generator;
};

#endif // GAME_H

