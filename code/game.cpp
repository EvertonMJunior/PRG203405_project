#include "game.h"
#include "animalgenerator.h"
#include <algorithm>

Game *Game::instance = nullptr;

Game::Game()
    : status(Status::Waiting), fish_caught(0), remaining_lives(3),
      current_fish_rate(2.0), current_jelly_rate(4.0),
      animal_generator(nullptr) {}

Game *Game::getInstance() {
  if (instance == nullptr) {
    instance = new Game();
  }
  return instance;
}

Status Game::getStatus() const { return status; }

void Game::setStatus(Status newStatus) {
  if (status != newStatus) {
    status = newStatus;
    emit statusChanged(status);
  }
}

int Game::getFishCaught() const { return fish_caught; }

void Game::incrementFishCaught() {
  fish_caught++;
  emit fishCaughtChanged(fish_caught);

  if (fish_caught >= 20) { // has won?
    setStatus(Status::Won);
  }

  if (fish_caught % 5 == 0 && animal_generator != nullptr) {
    current_fish_rate = std::max(0.5, current_fish_rate - 0.5);
    current_jelly_rate = std::max(1.0, current_jelly_rate - 0.5);
    animal_generator->setGenerationRate(current_fish_rate, current_jelly_rate);
  }
}

int Game::getRemainingLives() const { return remaining_lives; }

void Game::decrementLives() {
  if (remaining_lives > 0) {
    remaining_lives--;
    emit livesChanged(remaining_lives);

    if (remaining_lives == 0) { // has lost?
      setStatus(Status::Lost);
    }
  }
}

void Game::reset() {
  fish_caught = 0;
  remaining_lives = 3;
  current_fish_rate = 2.0;
  current_jelly_rate = 4.0;
  status = Status::Waiting;

  animal_generator->setGenerationRate(current_fish_rate, current_jelly_rate);

  emit fishCaughtChanged(fish_caught);
  emit livesChanged(remaining_lives);
  emit statusChanged(status);
}

void Game::setAnimalGenerator(AnimalGenerator *generator) {
  animal_generator = generator;
}

double Game::getCurrentFishRate() const { return current_fish_rate; }

double Game::getCurrentJellyRate() const { return current_jelly_rate; }
