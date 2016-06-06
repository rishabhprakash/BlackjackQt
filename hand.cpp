#include "hand.h"
#include "ui_hand.h"

#include <chrono>
#include <random>

/* Constructor for Hand class object */
Hand::Hand(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hand),
    total_count(0),
    is_blackjack(false),
    cards_in_hand({})
{
    ui->setupUi(this);
}

/* Destructor for Hand class object */
Hand::~Hand()
{
    // call delete on each Card stored in QVector
    for(size_t i  = 0, size = cards_in_hand.size(); i < size; ++i)
    {
        delete cards_in_hand[i];
    }
    delete ui;
}

/*  @function   drawCard
    @brief      Add's a Card object to QVector member via a randomized selection from parameter Deck object
*/
void Hand::drawCard(Deck* current_deck)
{
    // initialize seed for random integer generator
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    // generates integer from a uniform distribution
    std::uniform_int_distribution<int> distribution(0,51);
    int random_pos = distribution(generator);

    // construct new card object with QString stored at index of Deck equal to random integer generated above
    Card* new_card = new Card(this, (*current_deck)[random_pos]);
    cards_in_hand.push_back(new_card);

    // tally new total count of hand and check for Blackjack
    this->tally_total();
    if ((cards_in_hand.size() == 2) && (total_count == 21)) is_blackjack = true;
    else is_blackjack = false;

    // check for bust, in turn reduce total count if count above 21 and Aces in hand (reduce their count from 11 to 1)
    checkForBust();
}

/*  @function   tally_total
    @brief      Updates total count of Hand
*/
void Hand::tally_total()
{
    int new_total = 0;

    // run through hand and tally up total count
    for(size_t i = 0, size = cards_in_hand.size(); i < size; ++i)
    {
        new_total += cards_in_hand[i]->getCount();
    }
    total_count = new_total;
}

/*  @function   reduce
    @brief      Reduces total count of Hand if it is above 21 and Hand contains Aces
                (as their count can alternatively be reduced to 1 in such a situation)

    @returns    boolean true if hand reducable (and could be reduced), false if not
*/
bool Hand::reduce()
{
    // base condition
    while (total_count > 21)
    {
        // find first Ace in Hand object
        for(size_t i = 0, size = cards_in_hand.size(); i < size; ++i)
        {
            if (cards_in_hand[i]->getCount() == 11 && cards_in_hand[i]->isAce())
            {
                // reduce Aces count, break out of for loop
                cards_in_hand[i]->setCountifAce();
                break;
            }
            // else, if the Hand's last Card has been reached, it is not an Ace and the total count is still
            // above 21, then return false (not able to reduce hand below 21 - bust)
            else if ((i == size - 1) && (cards_in_hand[i]->getCount() != 11) && (total_count > 21)) return false;
        }
        // tally the total again, if it is still above 21, iterate again
        this->tally_total();
    }
    // if successfully exit loop, implies reduction of hand was possible, return true
    return true;
}

/*  @function   checkForBust
    @brief      Checks if Hand has gone bust/can not be reduced

    @returns    Boolean true if Hand's total count could not be reduced below 21, false otherwise
*/
bool Hand::checkForBust()
{
    if (this->reduce()) return false;
    else
    {
        // emit signal isBust()
        emit isBust();
        return true;
    }
}

/*  @function   checkForBlackJack
    @brief      Checks if a hand is a Blackjack/Natural 21 hand (Ace and ten-valued card)

    @returns    Boolean true if Hand is a BlackJack hand, false otherwise
*/
bool Hand::checkForBlackJack()
{
   // state of hand is blackjack
   if (is_blackjack)
    {
       // emit signal isBlackJack()
        emit isBlackJack();
        return true;
    }
    else return false;
}

/*  @function   clear
    @brief      clears Hand (clears private member QVector of Cards)
*/
void Hand::clear()
{
    // delete cards in hand
    for (size_t i  = 0, size = cards_in_hand.size(); i < size; ++i) delete cards_in_hand[i];
    cards_in_hand.clear();

    // start fresh
    total_count = 0;
    is_blackjack = false;
}
