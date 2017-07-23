#ifndef RULESWINDOW_H
#define RULESWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class RulesWindow;
}

/*  @class  RulesWindow
    @brief  Window displaying rules of the game
*/
class RulesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RulesWindow(QWidget *parent = 0);
    ~RulesWindow();

    // buttons presenting user with options
    QPushButton* return_to_main;
    QPushButton* start_new_game;

private:
    Ui::RulesWindow *ui;
};

#endif // RULESWINDOW_H
