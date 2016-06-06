#ifndef GAMEOVERWIDGET_H
#define GAMEOVERWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class gameoverwidget;
}

/*  @class  gameoverwidget
    @brief  Widget which notifies player when they are out of money.
            Presents them with the choice to continue (buy in $1000), or quit the game
*/
class gameoverwidget : public QWidget
{
    Q_OBJECT

public:
    explicit gameoverwidget(QWidget *parent = 0);
    ~gameoverwidget();

    // buttons presenting two options
    QPushButton* restart;
    QPushButton* end;

private:
    QLabel* notif; // label notifying player "You are all out of money!"

    Ui::gameoverwidget *ui;
};

#endif // GAMEOVERWIDGET_H
