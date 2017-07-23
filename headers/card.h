#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QLabel>


namespace Ui {
class Card;
}

/*  @class  Card
    @brief  Representation of card object, contains data members face (QLabel), rank (QString) and count (int)
*/
class Card : public QWidget
{
    Q_OBJECT

public:
    explicit Card(QWidget* parent = 0);
    explicit Card(QWidget *parent = 0, QString card_path = "");
    ~Card();

    int getCount() const;
    QString getRank() const;
    bool isAce() const;
    void setCountifAce();
    QLabel* getFace() const;

    void flip();
    bool card_state() const { return isFlipped; }

private:
    QLabel* face;
    QString rank;
    int count;

    QString face_path;
    bool isFlipped;

    Ui::Card *ui;
};

#endif // CARD_H
