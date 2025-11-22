#include "animalgenerator.h"
#include "fish.h"
#include "jellyfish.h"

AnimalGenerator::AnimalGenerator(QObject* parent)
    : QObject(parent)
    , fish_generation_rate(2.0)
    , jelly_generation_rate(4.0)
{
    fishTimer = new QTimer(this);
    jellyfishTimer = new QTimer(this);
    
    connect(fishTimer, &QTimer::timeout, this, &AnimalGenerator::spawnFish);
    connect(jellyfishTimer, &QTimer::timeout, this, &AnimalGenerator::spawnJellyfish);
    
    fishTimer->setInterval(static_cast<int>(fish_generation_rate * 1000));
    jellyfishTimer->setInterval(static_cast<int>(jelly_generation_rate * 1000));
}

AnimalGenerator::~AnimalGenerator()
{
    stop();
}

void AnimalGenerator::setGenerationRate(double fishRate, double jellyRate)
{
    fish_generation_rate = fishRate;
    jelly_generation_rate = jellyRate;
    
    fishTimer->setInterval(static_cast<int>(fish_generation_rate * 1000));
    jellyfishTimer->setInterval(static_cast<int>(jelly_generation_rate * 1000));
}

void AnimalGenerator::start()
{
    fishTimer->start();
    jellyfishTimer->start();
}

void AnimalGenerator::stop()
{
    fishTimer->stop();
    jellyfishTimer->stop();
}

double AnimalGenerator::getFishRate() const
{
    return fish_generation_rate;
}

double AnimalGenerator::getJellyRate() const
{
    return jelly_generation_rate;
}

void AnimalGenerator::spawnFish()
{
    Fish* fish = new Fish();
    emit fishSpawned(fish);
}

void AnimalGenerator::spawnJellyfish()
{
    Jellyfish* jellyfish = new Jellyfish();
    emit jellyfishSpawned(jellyfish);
}

