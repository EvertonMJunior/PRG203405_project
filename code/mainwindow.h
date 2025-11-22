#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QLabel>
#include <QGraphicsView>

class GameScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onPlayButtonClicked();
    void onPlayAgainButtonClicked();
    void onGameWon();
    void onGameLost();
    void updateLivesDisplay(int lives);
    void updateFishCounter(int fishCaught);

private:
    void setupUI();
    void createHomeScreen();
    void createGameScreen();
    void createWonScreen();
    void createLostScreen();
    void loadCustomFont();
    
    QStackedWidget* stackedWidget;
    
    QWidget* homeScreen;
    QPushButton* playButton;
    
    QWidget* gameScreen;
    QGraphicsView* gameView;
    GameScene* gameScene;
    QLabel* livesLabel;
    QLabel* fishCounterLabel;
    QList<QLabel*> lifeIcons;
  
    QWidget* wonScreen;
    QPushButton* playAgainWonButton;
  
    QWidget* lostScreen;
    QPushButton* playAgainLostButton;
    
    int customFontId;
    
    enum ScreenIndex {
        HOME = 0,
        GAME = 1,
        WON = 2,
        LOST = 3
    };
};
#endif // MAINWINDOW_H
