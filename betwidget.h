#ifndef BETWIDGET_H
#define BETWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QSound>

namespace Ui {
class BetWidget;
}

/*  @class  BetWidget
    @brief  Core widget that handles betting before hand is dealt/manages players bankroll (money)
*/
class BetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BetWidget(QWidget *parent = 0);
    ~BetWidget();

    void paintEvent(QPaintEvent *e);

    int get_bet() const { return bet_total; }
    void setHeaderText(const QString& title);

    // used by GameWindow object for connect functions. Encapsulate/write members to access?
    QPushButton* place_bet;
    QPushButton* leave_table;
    int bet_total;
    int balance_total;
    bool min_bet;
    bool doublesafe;

    void double_down();

public slots:

    // functions to adjust bet amount
    void subtract_10();
    void add_10();
    void add_20();
    void add_50();
    void add_100();
    void add_500();
    void add_1000();

private:
    QLabel* header;
    QPushButton** buttons;

    QLabel* bet_amount;
    QLabel* balance_amount;

    QPushButton* increment;
    QPushButton* decrement;

    QSound* chippick;

    Ui::BetWidget *ui;
};

#endif // BETWIDGET_H
