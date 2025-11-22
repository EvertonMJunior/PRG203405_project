#ifndef ANIMALGENERATOR_H
#define ANIMALGENERATOR_H

#include <QObject>
#include <QTimer>

class Fish;
class Jellyfish;

class AnimalGenerator : public QObject
{
    Q_OBJECT

public:
    explicit AnimalGenerator(QObject* parent = nullptr);
    ~AnimalGenerator() override;
    
    void setGenerationRate(double fishRate, double jellyRate);
    void start();
    void stop();
    
    double getFishRate() const;
    double getJellyRate() const;

signals:
    void fishSpawned(Fish* fish);
    void jellyfishSpawned(Jellyfish* jellyfish);

private slots:
    void spawnFish();
    void spawnJellyfish();

private:
    QTimer* fishTimer;
    QTimer* jellyfishTimer;
    double fish_generation_rate;
    double jelly_generation_rate;
};

#endif // ANIMALGENERATOR_H

