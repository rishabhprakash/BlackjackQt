#include "card.h"
#include "ui_card.h"
#include <QDebug>

/* Constructor for Card QWidget object

  @param card_path      QString storing filepath to image of its face
 */
Card::Card(QWidget *parent, QString card_path) :
    ui(new Ui::Card)
{
    // store path to image of face in QString member
    face_path = card_path;
    isFlipped = false; // bool storing state of card (hidden or revealed)

    ui->setupUi(this);

    // method to extract rank and count from filepath
    unsigned int index_1 = 0, index_2 = 0;
    for(unsigned int i = 0, size = card_path.length(); i < size; ++i)
    {
        QChar current_i = card_path[i];
        if (current_i == ' ') // find index of space character
        {
            for (unsigned int j = i; j < size; ++j) // find index of period character
            {
                QChar current_j = card_path[j];
                if (current_j == '.')
                {
                    ++i;
                    // extract these indexes
                    index_1 = i;
                    index_2 = j;
                    goto jump;
                }
            }
        }
    }


    jump: QString denom = card_path.mid(index_1, index_2 - index_1); // significant substring
    // intialize members dependently
    if (denom == "1")
    {
        rank = "Ace";
        count = 11;
    }
    else if (denom == "2")
    {
        rank = "Two";
        count = 2;
    }
    else if (denom == "3")
    {
        rank = "Three";
        count = 3;
    }
    else if (denom == "4")
    {
        rank = "Four";
        count = 4;
    }
    else if (denom == "5")
    {
        rank = "Five";
        count = 5;
    }
    else if (denom == "6")
    {
        rank = "Six";
        count = 6;
    }
    else if (denom == "7")
    {
        rank = "Seven";
        count = 7;
    }
    else if (denom == "8")
    {
        rank = "Eight";
        count = 8;
    }
    else if (denom == "9")
    {
        rank = "Nine";
        count = 9;
    }
    else if (denom == "10")
    {
        rank = "Ten";
        count = 10;
    }else if (denom == "11")
    {
        rank = "Jack";
        count = 10;
    }
    else if (denom == "12")
    {
        rank = "Queen";
        count = 10;
    }
    else if (denom == "13")
    {
        rank = "King";
        count = 10;
    }

    QPixmap current(card_path); // Pixmap for face image on screen

    face = new QLabel; // initialize face member with the Pixmap
    face->setPixmap(current);
    face->setMinimumSize(143, 200);
    face->setMaximumSize(143, 200);
    face->setScaledContents(true);
}

/* Destructor for Card class object */
Card::~Card()
{
    delete face;
    delete ui;
}

/*  @function   getCount
    @brief      Returns copy of integer count member of the card object
*/
int Card::getCount() const
{
    return count;
}

/*  @function   getRank
    @brief      Returns copy of QString rank member of the card object
*/
QString Card::getRank() const
{
    return rank;
}

/*  @function   getFace
    @brief      Returns pointer to QLabel face member of the card object
*/
QLabel* Card::getFace() const
{
    return face;
}

/*  @function   isAce
    @brief      Returns boolean true if card is Ace
*/
bool Card::isAce() const
{
    if (getRank() == "Ace") return true;
    else return false;
}

/*  @function   setCountifAce
    @brief      switches count of Ace card to 1 (if it was previously 11)
*/
void Card::setCountifAce()
{
    if (isAce() && count == 11) count = 1;
}

/*  @function   flip
    @brief      Alternates card between two states, revealed and hidden
*/
void Card::flip()
{
    if (isFlipped == false)
    {
        delete face;
        QPixmap current(":/_Back.png"); // Pixmap for image of back of the card on screen

        face = new QLabel; // initialize face member with the Pixmap
        face->setPixmap(current);
        face->setMinimumSize(143, 200);
        face->setMaximumSize(143, 200);
        face->setScaledContents(true);


        isFlipped = true;
    }
    else
    {
        delete face;
        QPixmap current(face_path); // Pixmap for face image on screen

        face = new QLabel; // initialize face member with the Pixmap
        face->setPixmap(current);
        face->setMinimumSize(143, 200);
        face->setMaximumSize(143, 200);
        face->setScaledContents(true);

        isFlipped = false;
    }

}

