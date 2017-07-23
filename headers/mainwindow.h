#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "gamewindow.h"
#include "ruleswindow.h"

namespace Ui {
class MainWindow;
}

/*  @class  MainWindow
    @brief  Window launched on startup of game
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void startNewGame();
    void openRulesWindow();
    void openGitHub();

private:
    QPushButton* rules_button;
    QPushButton* new_game;
    QPushButton* github_link;

    GameWindow* current_game;
    RulesWindow* rules;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
