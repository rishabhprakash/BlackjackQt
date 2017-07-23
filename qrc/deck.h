#ifndef DECK_H
#define DECK_H

#include <QWidget>
#include "card.h"

namespace Ui {
class Deck;
}

/*  @class  Deck
    @brief  Represents deck of cards, encapsulates array of file pathways (QStrings) to images of all 52 cards in a deck
*/
class Deck : public QWidget
{
    Q_OBJECT

friend class Hand;

public:
    explicit Deck(QWidget *parent = 0);
    ~Deck();

    QString& operator[] (int position) { return deck[position]; }

private:
    QString* deck;
    Ui::Deck *ui;
};

#endif // DECK_H
