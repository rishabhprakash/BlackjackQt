#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <chrono>
#include <random>
#include <QStackedWidget>
#include <QDebug>

/* Constructor for GameWindow class object */
GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    // set up geometry of playing window
    ui->setupUi(this);
    this->setGeometry(100, 60, 1200, 750);\
    this->setWindowTitle("Blackjack v1.4");

    // initialize game state to true (boolean indicator of whether player is still
    // in the game as opposed to standing)
    game_state = true;

    // sound effects
    cardslide = new QSound(":/cardSlide1.wav");
    chipsbet = new QSound(":/chipsHandle1.wav");
    winning = new QSound(":/chipsHandle5.wav");

    // set up Background of window to make it appear like a Blackjack table
    QPixmap background(":/table.jpg"); // background image
    QPalette palette; // set background as image using QPalette class
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

    // instantiate Deck to be used in the game
    current_deck = new Deck;

    // set up layout of window, core being central widget encapsulating all other children widgets
    QWidget* core = new QWidget;
    QVBoxLayout* outline = new QVBoxLayout; // external outline is vertical

    QSpacerItem* space = new QSpacerItem(0, 40);
    outline->addSpacerItem(space);

    infobutton = new QPushButton(this);
    QPixmap info(":/informationbutton.png");
    QIcon info_icon(info);
    infobutton->setIcon(info_icon);
    infobutton->setIconSize(QSize(20,20));
    infobutton->setGeometry(0,0,40,40);
    infobutton->setStyleSheet("QPushButton { background-color: rgba(0,0,0,0); }");
    infobutton->setToolTip("hello");

    tips = new QLabel(this);
    tips->setText("<b><font size='4', color = 'gold'>Deal</font></b>: Deal new hand.<br><b><font size='4', color = 'gold'>Leave Table</font></b>: Quit game.<br><b><font size='4', color = 'gold'>Hit</font></b>: Add a card to your hand.<br><b><font size='4', color = 'gold'>Stand</font></b>: Done drawing cards.<br><b><font size='4', color = 'gold'>Double down</font></b>: Double bet,<br>draw final card.");
    tips->setAlignment(Qt::AlignLeft);
    tips->setStyleSheet(" QLabel { background-color: rgba(0,0,0,0); color : white; } ");
    tips->setGeometry(10,40,350,120);
    //tips->hide();


    // label denoting Dealers hand
    QLabel* dealer_label = new QLabel("Dealer", this);
    dealer_label->setAlignment(Qt::AlignCenter);
    dealer_label->setMaximumSize(150, 30);
    dealer_label->setMinimumSize(150, 30);
    dealer_label->setStyleSheet(" QLabel { background-color: rgba(255,255,255,100); border-style: outset; border-width: 2px; border-color: white; color : white; } ");
    dealer_label->setGeometry(520, 10, 100, 25);

    // instantiate and position Dealers hand in layout
    dealers_hand = new Hand;
    dealer = new QWidget;
    dealer->setMinimumHeight(230);
    dealer->setMaximumHeight(230);
    dealer_layout = new QHBoxLayout;
    dealer->setLayout(dealer_layout);
    outline->addWidget(dealer, 0, Qt::AlignCenter);

    dealer_space = new QStackedWidget;

    // label displaying Dealers total hand count
    dealer_count = new QLabel(QString::number(0));
    dealer_count->setStyleSheet(" QLabel { background-color : white; } ");
    dealer_count->setAlignment(Qt::AlignCenter);
    dealer_count->setMaximumSize(70, 20);
    dealer_count->setMinimumSize(70, 20);
    //dealer_count->hide();

    dealer_count_space = new QLabel;
    dealer_count_space->setAlignment(Qt::AlignCenter);
    dealer_count_space->setMaximumSize(70, 20);
    dealer_count_space->setMinimumSize(70, 20);
    dealer_count_space->setStyleSheet("QLabel { background-color : rgba(0,0,0,0) } ");

    dealer_space->addWidget(dealer_count_space);
    dealer_space->addWidget(dealer_count);

    outline->addWidget(dealer_space, 0, Qt::AlignCenter);

    // buttons to Hit, Stand and Double Down instantiated in Horizontal layout
    QHBoxLayout* actions_layout = new QHBoxLayout;
    hit = new QPushButton("Hit");
    hit->setFixedSize(130, 35);
    hit->setStyleSheet("QPushButton { background-color: rgba(0, 220, 0, 100); font: 14px; border-style: outset; border-width: 2px; border-color: white; color : white; } QPushButton:hover { border-style: outset; border-width: 2px; border-color: gold; color : gold; } ");
    actions_layout->addWidget(hit, 0, Qt::AlignCenter);

    stand = new QPushButton("Stand");
    stand->setFixedSize(130, 35);
    stand->setStyleSheet("QPushButton { background-color: rgba(0, 220, 0, 100); font: 14px; border-style: outset; border-width: 2px; border-color: white; color : white; } QPushButton:hover { border-style: outset; border-width: 2px; border-color: gold; color : gold; } ");
    actions_layout->addWidget(stand, 0, Qt::AlignCenter);

    doubledown = new QPushButton("Double down");
    doubledown->setFixedSize(130, 35);
    doubledown->setStyleSheet("QPushButton { background-color: rgba(0, 220, 0, 100); font: 14px; border-style: outset; border-width: 2px; border-color: white; color : white; } QPushButton:hover { border-style: outset; border-width: 2px; border-color: gold; color : gold; } ");
    actions_layout->addWidget(doubledown, 0, Qt::AlignCenter);

    // Widget storing Hit and Stand buttons
    hit_stand = new QWidget;
    hit_stand->setLayout(actions_layout);

    // QLabel that declares winner of round of play
    winner = new QLabel;
    winner->setStyleSheet(" QLabel { background-color: rgba(0, 0, 0, 0); font: bold 48px; color : gold; } ");

    // The BetWidget, gameoverwidget, and areyousurewidget members are all stored in a stacked widget. They are all
    // positioned in the same place on the game window but appear (are brought to the front) in different situations.
    bet_widget = new BetWidget;
    end_widget = new gameoverwidget;
    check_window = new areyousurewidget;

    bet_area = new QStackedWidget;
    bet_area->addWidget(bet_widget);
    bet_area->addWidget(end_widget);
    bet_area->addWidget(check_window);

    outline->addWidget(bet_area, 0, Qt::AlignCenter);

    // Deal, Hit/Stand, and Winner are all stored in a stacked widget. They are all positioned in the
    // same place on the game window but appear (are brought to the front) in different situations.
    action_pool = new QStackedWidget;
    action_pool->addWidget(hit_stand);
    action_pool->addWidget(winner);
    action_pool->hide();

    outline->addWidget(action_pool, 0, Qt::AlignCenter);

    // instantiate and position players hand
    players_hand = new Hand;
    player = new QWidget;
    player->setMinimumHeight(230);
    player->setMaximumHeight(230);
    player_layout = new QHBoxLayout;
    player->setLayout(player_layout);
    outline->addWidget(player, 0, Qt::AlignCenter);

    player_count = new QLabel(QString::number(0));
    player_count->setStyleSheet(" QLabel { background-color : white; } ");
    player_count->setAlignment(Qt::AlignCenter);
    player_count->setMaximumSize(70, 20);
    player_count->setMinimumSize(70, 20);
    outline->addWidget(player_count, 0, Qt::AlignCenter);
    player_count->hide();

    // connections to specific functions upon clicking of buttons
    connect(bet_widget->place_bet, SIGNAL(clicked(bool)), this, SLOT(deal_new_hand()));
    connect(hit, SIGNAL(clicked(bool)), this, SLOT(action_hit()));
    connect(stand, SIGNAL(clicked(bool)), this, SLOT(action_stand()));
    connect(doubledown, SIGNAL(clicked(bool)), this, SLOT(double_down()));
    connect(bet_widget->leave_table, SIGNAL(clicked(bool)), this, SLOT(openCheckWindow()));
    connect(check_window->no, SIGNAL(clicked(bool)), this, SLOT(closeCheckWindow()));
    connect(this, SIGNAL(broke()), this, SLOT(openGameOverWindow()));
    connect(infobutton, SIGNAL(clicked(bool)), this, SLOT(showInfo()));

    connect(players_hand, SIGNAL(isBust()), this, SLOT(outcome()));
    connect(dealers_hand, SIGNAL(isBust()), this, SLOT(outcome()));

    outline->setSpacing(0);
    core->setLayout(outline);
    this->setCentralWidget(core);
}

/*  @function   deal_new_hand
    @brief      New hand dealt to both dealer and player
*/
void GameWindow::deal_new_hand()
{
    // in case the minimum bet has not been placed, do not deal hand and notify the player
    if (bet_widget->min_bet == false)
    {
        bet_widget->setHeaderText("You must place a minimum bet of $10 to play!");
        bet_widget->repaint();

        delay(1500);

        bet_widget->setHeaderText("Click on the chips to place your bet for this hand");
        bet_widget->repaint();
    }
    else // the minimum bet has been placed
    {
        // play chip handling sound
        chipsbet->play();
        // hide bet widget
        bet_area->hide();
        // display players card count
        player_count->show();

        // if player does not have enough money in bankroll to double down his bet, hide double down button
        if (bet_widget->doublesafe == false) doubledown->hide();
        else doubledown->show(); // if player does have enough money, show it

        // deal the hand, two cards dealt to each player and dealer
        this->player_hit(); // deal player one card
        this->dealer_hit(); // dealer gets one card
        (*dealers_hand)[0].flip(); // dealers first card is hidden (hole card)
        this->player_hit(); // player gets another
        this->dealer_hit(); // dealer gets another

        // finally, after dealing hand, present player with his/her options (to hit/stand/double down)
        action_pool->setCurrentWidget(hit_stand);
        action_pool->show();
    }
}

/*  @function   dealer_hit
    @brief      Drawsc card and adds it to dealers hand
*/
void GameWindow::dealer_hit()
{
    // play sound of card sliding
    cardslide->play();
    dealers_hand->drawCard(current_deck); // draw card

    // repaint
    QCoreApplication::processEvents();
    repaint();

    // automatically stand if 5 cards have been dealt
    if(dealers_hand->size() == 5) outcome();
}

/*  @function   player_hit
    @brief      Draws card and adds it to players hand
*/
void GameWindow::player_hit()
{
    // play sound of card sliding
    cardslide->play();
    players_hand->drawCard(current_deck); // draw card

    // repaint
    QCoreApplication::processEvents();
    repaint();

    // automatically stand if 5 cards have been dealt
    if(players_hand->size() == 5) action_stand();
}

/*  @function   action_hit
    @brief      Public slot called when hit button clicked, encapsulates player_hit function
*/
void GameWindow::action_hit()
{
    this->player_hit(); // hit player/draw card
}

/*  @function   action_stand
    @brief      Public slot called when stand button clicked
*/
void GameWindow::action_stand()
{
    // first, reveal dealers hidden card
    dealer_count->show();
    (*dealers_hand)[0].flip();
    cardslide->play();

    // next, show count of dealer
    dealer_space->setCurrentWidget(dealer_count);

    // repaint
    QCoreApplication::processEvents();
    repaint();

    // then, check for BlackJack in each of the two hands
    players_hand->checkForBlackJack();
    dealers_hand->checkForBlackJack();

    // go to outcome if either player has BlackJack as hand may end right here
    connect(dealers_hand, SIGNAL(isBlackJack()), this, SLOT(outcome()));
    connect(players_hand, SIGNAL(isBlackJack()), this, SLOT(outcome()));

    this->delay(500);

    // keep hitting dealers hand until total count is greater then or equal to 17 at which point dealer MUST stand
    jump: while (dealers_hand->get_total() < 17 && dealers_hand->size() != 0)
    {
        this->dealer_hit();

        this->delay(250);
    }

    // Draw if 'soft' seventeen
    if (dealers_hand->get_total() == 17)
    {
        bool flag = false;
        for (size_t i = 0, size = dealers_hand->size(); i < size; ++i)
        {
            if ((*dealers_hand)[i].getCount() == 11) { flag = true; break; }
        }
        if(flag) this->dealer_hit();
        if(dealers_hand->get_total() < 17) goto jump; // return to previous while loop if total less than 17 after draw
    }

    // go to outcome after done with dealers turn
    this->outcome();
}

/*  @function               delay
    @brief                  Delays/spaces out execution of code in time, necessary to adjust game speed

    @param milliseconds     unsigned int, amount of milliseconds by which execution is to be delayed
*/
void GameWindow::delay(unsigned int milliseconds)
{
    QTime dieTime = QTime::currentTime().addMSecs(milliseconds); // set target time
    while (QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

/*  @function   outcome
    @brief      This funtion evaluates outcome of round upon comparing hands of dealer and player
*/
void GameWindow::outcome()
{
    // this is a quick fix to a bug I haven't figured out yet
    if (dealers_hand->get_total() == 0 || players_hand->get_total() == 0) return;

    // case when either player or dealer (or both) have a Blackjack hand (natural 21)
    if (dealers_hand->is_blackjack == true || players_hand->is_blackjack == true)
    {
        if (dealers_hand->is_blackjack == true && players_hand->is_blackjack == true) // if its both, its a push
        {
            winner->setText("Push");

            bet_widget->balance_total += bet_widget->bet_total;
            bet_widget->bet_total = 0;

            QCoreApplication::processEvents();
            bet_widget->repaint();
        }
        else if (dealers_hand->is_blackjack) // if its the dealer
        {
            winner->setText("BlackJack! Dealer wins!");

            bet_widget->bet_total = 0;

            QCoreApplication::processEvents();
            bet_widget->repaint();

            dealers_hand->is_blackjack = false;
            this->delay(500);
        }
        else if  (players_hand->is_blackjack) // if its the player
        {
            winner->setText("BlackJack! Player wins!");

            bet_widget->balance_total += (2 * bet_widget->bet_total);
            bet_widget->balance_total += (bet_widget->bet_total)/2;
            bet_widget->bet_total = 0;

            QCoreApplication::processEvents();
            bet_widget->repaint();

            players_hand->is_blackjack = false;
            this->delay(500);
        }
    }


    // total count is equal, split pot equally (Push)
    else if (dealers_hand->get_total() == players_hand->get_total() )
    {
        winner->setText("Push");

        bet_widget->balance_total += bet_widget->bet_total;
        bet_widget->bet_total = 0;

        QCoreApplication::processEvents();
        bet_widget->repaint();
    }

    // if either of the players bust
    else if ((dealers_hand->get_total() > 21) || (players_hand->get_total() > 21))
    {
        if (dealers_hand->get_total() > 21) // if dealer busts
        {
            winner->setText("Dealer bust!");
            {
                bet_widget->balance_total += (2 * bet_widget->bet_total);
                bet_widget->bet_total = 0;

                QCoreApplication::processEvents();
                bet_widget->repaint();
            }
        }
        else // else, if player busts
        {
            winner->setText("Player bust!");
            {
                bet_widget->bet_total = 0;

                QCoreApplication::processEvents();
                bet_widget->repaint();
            }
        }
    }

    // neither player busts, ones hand has higher count than the other
    // case 1: dealer has hand closer to 21
    else if (dealers_hand->get_total() > players_hand->get_total())
    {
        winner->setText("Dealer wins!");
        {
            bet_widget->bet_total = 0;

            QCoreApplication::processEvents();
            bet_widget->repaint();
        }
    }
    // case 2: player has hand closer to 21
    else if (dealers_hand->get_total() < players_hand->get_total())
    {
        winner->setText("Player wins!");
        {
            bet_widget->balance_total += (2 * bet_widget->bet_total);
            bet_widget->bet_total = 0;

            QCoreApplication::processEvents();
            bet_widget->repaint();
        }
    }


    // show winner button, announce who won the round
    winner->setAlignment(Qt::AlignCenter);
    action_pool->setCurrentWidget(winner);

    this->delay(1000);
    winning->play(); // play sound of chips

    this->delay(2000);

    // if player is out of money after this hand, emit signal broke()
    if (bet_widget->balance_total == 0) emit broke();

    // hide player widgets
    action_pool->hide();
    player_count->hide();

    // set game_state to false
    game_state = false;

    // repaint
    QCoreApplication::processEvents();
    repaint();

    // show Deal button to start next round upon click
    bet_area->show();
    dealer_space->setCurrentWidget(dealer_count_space);
}

/*  @function   paintEvent
    @brief      Repaints game window depending on game_state. If in play, adds new cards dealt. If not, clears up the table.

    @param e    QPaintEvent class object, default parameter
*/
void GameWindow::paintEvent(QPaintEvent *e)
{
    // if false, that means a round just got over, so clear the table/hide all gameplay widgets
    if (game_state == false)
    {
        for (size_t i = 0, size = dealers_hand->size(); i < size; ++i)
        {
            (*dealers_hand)[i].getFace()->hide();
        }
        dealers_hand->clear();
        for (size_t i = 0, size = players_hand->size(); i < size; ++i)
        {
            (*players_hand)[i].getFace()->hide();
        }
        players_hand->clear();
        game_state = true;
        return;
    }

    // else, if true, that means a round is in session, so update window by adding new Card widgets to be displayed
    else
    {
        for(size_t i = 0, size = dealers_hand->size(); i < size; ++i)
        {
            dealer_layout->addWidget((*dealers_hand)[i].getFace(), 0, Qt::AlignCenter);
        }
        dealer_count->setText(QString::number(dealers_hand->get_total()));

        for(size_t i = 0, size = players_hand->size(); i < size; ++i)
        {
            player_layout->addWidget((*players_hand)[i].getFace(), 0, Qt::AlignCenter);
        }
        player_count->setText(QString::number(players_hand->get_total()));
        return;
    }
}

/*  @function   openCheckWindow
    @brief      If you choose to 'leave table' when you still have money, dialog asks if you are sure and is launched
                when this function/public slot is called (leave table is clicked).
*/
void GameWindow::openCheckWindow()
{
    if (bet_widget->balance_total == 0)
    {
        this->close();
        return;
    }
    else
    {
        bet_area->setCurrentWidget(check_window);
    }

    connect(check_window->yes, SIGNAL(clicked(bool)), this, SLOT(close())); // if clicked, quit entire application
}

/*  @function   closeCheckWindow
    @brief      When called, this function closes window prompting user if they are sure they want to quit
*/
void GameWindow::closeCheckWindow()
{
    bet_area->setCurrentWidget(bet_widget);
}

/*  @function   openGameOverWindow
    @brief      Opens a window presenting you with options when you run out of money (leave or buy in again)
*/
void GameWindow::openGameOverWindow()
{
    bet_area->setCurrentWidget(end_widget);

    connect(end_widget->end, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(end_widget->restart, SIGNAL(clicked(bool)), this, SLOT(start_new_game()));
}

/*  @function   start_new_game
    @brief      Restocks bank roll (buys in $1000), brings bet widget to the front to start a new round
*/
void GameWindow::start_new_game()
{
    bet_widget->balance_total += 1000; // restock bankroll

    QCoreApplication::processEvents(); // repaint/update screen
    bet_widget->repaint();

    bet_area->setCurrentWidget(bet_widget); // bring bet widget to the front to resume play
}

/*  @function   double_down
    @brief      Doubles current bet and draws one card before standing
*/
void GameWindow::double_down()
{
    bet_widget->double_down(); // double bet amount, adjust bankroll
    chipsbet->play(); // play sound of chips

    action_hit(); // add single card to players hand - if player busts, goes directly to outcome (calls outcome function)

    // stand if player hasnt already busted
    if (players_hand->get_total() != 0) action_stand();
}

/*  @function   showInfo
    @brief      Reveals button information to help player
*/
void GameWindow::showInfo()
{
    tips->show();

    QCoreApplication::processEvents();
    repaint();

    this->delay(2000);
    tips->hide();

    QCoreApplication::processEvents();
    repaint();
}

/* Destructor for GameWindow, deletes all child widgets */
GameWindow::~GameWindow()
{
    // common widgets
    delete current_deck;
    delete hit;
    delete stand;
    delete doubledown;
    delete hit_stand;
    delete winner;
    delete action_pool;

    delete infobutton;
    delete tips;

    delete bet_widget;
    delete check_window;
    delete end_widget;

    // dealers variables
    delete dealers_hand;
    delete dealer;
    delete dealer_count;
    delete dealer_count_space;
    delete dealer_space;

    // players variables
    delete players_hand;
    delete player;
    delete player_count;

    // sound variables
    delete cardslide;
    delete chipsbet;
    delete winning;

    delete ui;
}
