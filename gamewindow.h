#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QTime>
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "betwidget.h"
#include "areyousurewidget.h"
#include "gameoverwidget.h"
#include <QSound>

namespace Ui {
class GameWindow;
}

/*  @class  GameWindow
    @brief  Core window on which game is played
*/
class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

    void paintEvent(QPaintEvent *e);

    void delay(unsigned int milliseconds);

public slots:
    void deal_new_hand();

    void dealer_hit();
    void player_hit();

    void action_hit();
    void action_stand();
    void double_down();

    void outcome();

    void openCheckWindow();
    void closeCheckWindow();
    void openGameOverWindow();
    void showInfo();

    void start_new_game();

signals:
    void broke();

private:
    Deck* current_deck;
    QPushButton* hit;
    QPushButton* stand;
    QPushButton* doubledown;
    QWidget* hit_stand;
    QLabel* winner;
    QStackedWidget* action_pool;
    bool game_state;

    QPushButton* infobutton;
    QLabel* tips;

    QStackedWidget* bet_area;
    BetWidget* bet_widget;
    gameoverwidget* end_widget;
    areyousurewidget* check_window;

    // dealers variables
    Hand* dealers_hand;
    QHBoxLayout* dealer_layout;
    QWidget* dealer;
    QLabel* dealer_count;
    QLabel* dealer_count_space;
    QStackedWidget* dealer_space;

    // players variables
    Hand* players_hand;
    QHBoxLayout* player_layout;
    QWidget* player;
    QLabel* player_count;

    QSound* cardslide;
    QSound* chipsbet;
    QSound* winning;

    Ui::GameWindow *ui;
};

#endif // GAMEWINDOW_H
