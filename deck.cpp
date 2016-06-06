#include "deck.h"
#include "ui_deck.h"

/* Constructor for Deck object */
Deck::Deck(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Deck)
{
    ui->setupUi(this);

    // initialize Deck object with pathways to 52 card images
    deck = new QString[52];

    // Clubs
    deck[0] = ":/Clubs 1.png";
    deck[1] = ":/Clubs 2.png";
    deck[2] = ":/Clubs 3.png";
    deck[3] = ":/Clubs 4.png";
    deck[4] = ":/Clubs 5.png";
    deck[5] = ":/Clubs 6.png";
    deck[6] = ":/Clubs 7.png";
    deck[7] = ":/Clubs 8.png";
    deck[8] = ":/Clubs 9.png";
    deck[9] = ":/Clubs 10.png";
    deck[10] = ":/Clubs 11.png";
    deck[11] = ":/Clubs 12.png";
    deck[12] = ":/Clubs 13.png";

    // Diamonds
    deck[13] = ":/Diamonds 1.png";
    deck[14] = ":/Diamonds 2.png";
    deck[15] = ":/Diamonds 3.png";
    deck[16] = ":/Diamonds 4.png";
    deck[17] = ":/Diamonds 5.png";
    deck[18] = ":/Diamonds 6.png";
    deck[19] = ":/Diamonds 7.png";
    deck[20] = ":/Diamonds 8.png";
    deck[21] = ":/Diamonds 9.png";
    deck[22] = ":/Diamonds 10.png";
    deck[23] = ":/Diamonds 11.png";
    deck[24] = ":/Diamonds 12.png";
    deck[25] = ":/Diamonds 13.png";

    // Hearts
    deck[26] = ":/Hearts 1.png";
    deck[27] = ":/Hearts 2.png";
    deck[28] = ":/Hearts 3.png";
    deck[29] = ":/Hearts 4.png";
    deck[30] = ":/Hearts 5.png";
    deck[31] = ":/Hearts 6.png";
    deck[32] = ":/Hearts 7.png";
    deck[33] = ":/Hearts 8.png";
    deck[34] = ":/Hearts 9.png";
    deck[35] = ":/Hearts 10.png";
    deck[36] = ":/Hearts 11.png";
    deck[37] = ":/Hearts 12.png";
    deck[38] = ":/Hearts 13.png";

    // Spades
    deck[39] = ":/Spades 1.png";
    deck[40] = ":/Spades 2.png";
    deck[41] = ":/Spades 3.png";
    deck[42] = ":/Spades 4.png";
    deck[43] = ":/Spades 5.png";
    deck[44] = ":/Spades 6.png";
    deck[45] = ":/Spades 7.png";
    deck[46] = ":/Spades 8.png";
    deck[47] = ":/Spades 9.png";
    deck[48] = ":/Spades 10.png";
    deck[49] = ":/Spades 11.png";
    deck[50] = ":/Spades 12.png";
    deck[51] = ":/Spades 13.png";
}

/* Destructor for Deck object */
Deck::~Deck()
{
    delete [] deck; // call delete on array
    delete ui;
}
