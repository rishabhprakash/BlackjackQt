#ifndef HAND_H
#define HAND_H

#include <QWidget>
#include "card.h"
#include "deck.h"
#include <QVector>
#include <QHBoxLayout>

namespace Ui {
class Hand;
}

/*  @class  Hand
    @brief  Represents hand of cards held by dealer/player during a game. Stores Card pointers in a QVector
*/
class Hand : public QWidget
{
    Q_OBJECT

public:
    explicit Hand(QWidget *parent = 0);
    ~Hand();

    bool is_blackjack;


    int get_total() { return total_count; }
    void tally_total();
    bool reduce();

    size_t size() const { return cards_in_hand.size(); }
    Card& operator[] (int position) { return *(cards_in_hand[position]); }

public slots:
    void drawCard(Deck* current_deck);
    void clear();

    bool checkForBust();
    bool checkForBlackJack();

signals:
    void isBust();
    void isBlackJack();

private:
    QVector<Card*> cards_in_hand;
    int total_count;

    Ui::Hand *ui;
};

#endif // HAND_H
