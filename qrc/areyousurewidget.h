#ifndef AREYOUSUREWIDGET_H
#define AREYOUSUREWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class areyousurewidget;
}

/*  @class   areyousurewidget
    @brief   Widget which confirms with user if/when they choose to quit the game
*/
class areyousurewidget : public QWidget
{
    Q_OBJECT

public:
    explicit areyousurewidget(QWidget *parent = 0);
    ~areyousurewidget();

    // yes and no buttons
    QPushButton* yes;
    QPushButton* no;

private:
    QLabel* sure; // label asking user "Are you sure?"

    Ui::areyousurewidget *ui;
};

#endif // AREYOUSUREWIDGET_H
