#include "betwidget.h"
#include "ui_betwidget.h"

#include <QIcon>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <algorithm>


/* Constructor for BetWidget class object */
BetWidget::BetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BetWidget),
    bet_total(0),
    min_bet(false),
    balance_total(1000),
    doublesafe(true)
{
    ui->setupUi(this);

    // initialize QSound object for sound effect of handling chips
    chippick = new QSound(":/chipLay1.wav");

    // core outline of widget
    QVBoxLayout* outline_layout = new QVBoxLayout;

    // initialize label presenting header text - instructions for user to place bet
    header = new QLabel("Click on the chips to place your bet for this hand."); // upper label
    header->setStyleSheet(" QLabel { color : white; } ");
    QFont font = header->font();
    font.setPointSize(14); // set size as 14
    font.setBold(true); // set style as bold
    header->setFont(font); // set font

    outline_layout->addWidget(header, 0, Qt::AlignCenter);

    // initialize array storing QPushButtons with icons set as the chips and their layout
    buttons = new QPushButton*[5];
    QHBoxLayout* chips_layout = new QHBoxLayout;
    QWidget* chips = new QWidget;

    // 20 dollar chip
    QPixmap green(":/green.png");
    QIcon green_icon(green);
    buttons[0] = new QPushButton;
    buttons[0]->setIcon(green_icon);
    buttons[0]->setIconSize(QSize(80,80));
    buttons[0]->setFixedSize(QSize(80,80));
    buttons[0]->setStyleSheet(" QPushButton { background-color: rgba(0,0,0,0) } QPushButton:hover { border-style: outset; border-width: 2px; border-color: gold; } QPushButton:pressed { background-color : gold }");

    // 50 dollar chip
    QPixmap red(":/red.png");
    QIcon red_icon(red);
    buttons[1] = new QPushButton;
    buttons[1]->setIcon(red_icon);
    buttons[1]->setIconSize(QSize(80,80));
    buttons[1]->setFixedSize(QSize(80,80));
    buttons[1]->setStyleSheet(" QPushButton { background-color: rgba(0,0,0,0) } QPushButton:hover { border-style: outset; border-width: 2px; border-color: gold; } QPushButton:pressed { background-color : gold }");

    // 100 dollar chip
    QPixmap black(":/black.png");
    QIcon black_icon(black);
    buttons[2] = new QPushButton;
    buttons[2]->setIcon(black_icon);
    buttons[2]->setIconSize(QSize(80,80));
    buttons[2]->setFixedSize(QSize(80,80));
    buttons[2]->setStyleSheet(" QPushButton { background-color: rgba(0,0,0,0) } QPushButton:hover { border-style: outset; border-width: 2px; border-color: gold; } QPushButton:pressed { background-color : gold }");

    // 500 dollar chip
    QPixmap white(":/white.png");
    QIcon white_icon(white);
    buttons[3] = new QPushButton;
    buttons[3]->setIcon(white_icon);
    buttons[3]->setIconSize(QSize(80,80));
    buttons[3]->setFixedSize(QSize(80,80));
    buttons[3]->setStyleSheet(" QPushButton { background-color: rgba(0,0,0,0) } QPushButton:hover { border-style: outset; border-width: 2px; border-color: gold; } QPushButton:pressed { background-color : gold } ");

    // 1000 dollar chip
    QPixmap yellow(":/yellow.png");
    QIcon yellow_icon(yellow);
    buttons[4] = new QPushButton;
    buttons[4]->setIcon(yellow_icon);
    buttons[4]->setIconSize(QSize(80,80));
    buttons[4]->setFixedSize(QSize(80,80));
    buttons[4]->setStyleSheet(" QPushButton { background-color: rgba(0,0,0,0) } QPushButton:hover { border-style: outset; border-width: 2px; border-color: gold; } QPushButton:pressed { background-color : gold }");


    // sequentially add each QPushButton representing the chips to their layout
    for(size_t i = 0; i < 5; ++i)
    {
        chips_layout->addWidget(buttons[i], 0, Qt::AlignCenter);
    }

    // set layout to widget encapsulating all the chips
    chips->setLayout(chips_layout);
    outline_layout->addWidget(chips, 0, Qt::AlignCenter);


    // text, label showing bet amount
    QLabel* bet_text = new QLabel("   Bet:");
    bet_text->setStyleSheet(" QLabel { color : white; } ");

    bet_amount = new QLabel(QString::number(bet_total));
    bet_amount->setMaximumSize(70,30);
    bet_amount->setMinimumSize(70,30);
    bet_amount->setAlignment(Qt::AlignCenter);
    bet_amount->setStyleSheet(" QLabel { background-color : white; } ");


    // text, label showing players balance/bankroll
    QLabel* balance_text = new QLabel("     Bankroll:");
    balance_text->setStyleSheet(" QLabel { color : white; } ");

    balance_amount = new QLabel(QString::number(balance_total));
    balance_amount->setMaximumSize(70,30);
    balance_amount->setMinimumSize(70,30);
    balance_amount->setAlignment(Qt::AlignCenter);
    balance_amount->setStyleSheet(" QLabel { background-color : white; } ");


    // buttons to increment/decrement bet by $10
    increment = new QPushButton("+");
    increment->setMaximumSize(20,14);
    increment->setMinimumSize(20,14);
    //increment->setAlignment(Qt::AlignCenter);
    increment->setStyleSheet(" QPushButton:hover { background-color : Gainsboro; } ");

    decrement = new QPushButton("-");
    decrement->setMaximumSize(20,14);
    decrement->setMinimumSize(20,14);
    //decrement->setAlignment(Qt::AlignCenter);
    decrement->setStyleSheet(" QPushButton:hover { background-color : Gainsboro; } ");

    QWidget* increment_decrement = new QWidget;
    QVBoxLayout* increment_decrement_layout = new QVBoxLayout;

    increment_decrement_layout->addWidget(increment, 0, Qt::AlignCenter);
    increment_decrement_layout->addWidget(decrement, 0, Qt::AlignCenter);
    increment_decrement->setLayout(increment_decrement_layout);

    // placing widgets in external layout
    QWidget* bet_pool = new QWidget;
    QHBoxLayout* bet_pool_layout = new QHBoxLayout;

    bet_pool_layout->addWidget(increment_decrement, 0, Qt::AlignCenter);
    bet_pool_layout->addWidget(bet_text, 0, Qt::AlignCenter);
    bet_pool_layout->addWidget(bet_amount, 0, Qt::AlignCenter);
    bet_pool_layout->addWidget(balance_text, 0, Qt::AlignCenter);
    bet_pool_layout->addWidget(balance_amount, 0, Qt::AlignCenter);

    bet_pool->setLayout(bet_pool_layout);
    outline_layout->addWidget(bet_pool, 0, Qt::AlignCenter);


    // widget encapsulating QPushButtons representing options for player when placing bet (place bet/leave table)
    QWidget* deal_stand = new QWidget;
    QHBoxLayout* deal_stand_layout = new QHBoxLayout;

    place_bet = new QPushButton("Deal");
    place_bet->setFixedSize(150, 35);
    place_bet->setStyleSheet("QPushButton { background-color: rgba(0, 220, 0, 100); border-style: outset; border-width: 2px; border-color: white; color : white; } QPushButton:hover { border-style: outset; border-width: 2px; border-color: gold; color : gold; } ");

    leave_table = new QPushButton("Leave Table");
    leave_table->setFixedSize(150, 35);
    leave_table->setStyleSheet("QPushButton { background-color: rgba(0, 220, 0, 100); border-style: outset; border-width: 2px; border-color: white; color : white; } QPushButton:hover { border-style: outset; border-width: 2px; border-color: gold; color : gold; } ");

    deal_stand_layout->addWidget(place_bet, 0, Qt::AlignHCenter);
    deal_stand_layout->addWidget(leave_table, 0, Qt::AlignHCenter);
    deal_stand->setLayout(deal_stand_layout);

    outline_layout->addWidget(deal_stand, 0, Qt::AlignCenter);

    // connect functions for all of the widgets
    connect(buttons[0], SIGNAL(clicked(bool)), this, SLOT(add_20()));
    connect(buttons[1], SIGNAL(clicked(bool)), this, SLOT(add_50()));
    connect(buttons[2], SIGNAL(clicked(bool)), this, SLOT(add_100()));
    connect(buttons[3], SIGNAL(clicked(bool)), this, SLOT(add_500()));
    connect(buttons[4], SIGNAL(clicked(bool)), this, SLOT(add_1000()));
    connect(increment, SIGNAL(clicked(bool)), this, SLOT(add_10()));
    connect(decrement, SIGNAL(clicked(bool)), this, SLOT(subtract_10()));

    // finally, set complete external layout to the widget
    outline_layout->setSpacing(0);
    this->setLayout(outline_layout);
    this->show();
}

/* Destructor for BetWidget class object */
BetWidget::~BetWidget()
{
    delete ui;

    // delete each of the member widgets managed by the class object
    delete [] buttons;

    delete bet_amount;
    delete balance_amount;

    delete increment;
    delete decrement;

    delete header;

    delete place_bet;
    delete leave_table;
}

/*  @function   subtract_10
`   @brief      Subtracts $10 from bet amount
*/
void BetWidget::subtract_10()
{
    if (bet_total - 10 >= 0)
    {
        bet_total -= 10;
        balance_total += 10;
    }

    chippick->play();

    QCoreApplication::processEvents();
    repaint();
}

/*  @function   add_10
`   @brief      Adds $10 to bet amount
*/
void BetWidget::add_10()
{
    if (balance_total >= 10)
    {
        bet_total += 10;
        balance_total -= 10;
    }

    chippick->play();

    QCoreApplication::processEvents();
    repaint();
}

/*  @function   add_20
`   @brief      Adds $20 to bet amount
*/
void BetWidget::add_20()
{
    if (balance_total >= 20)
    {
        bet_total += 20;
        balance_total -= 20;
    }

    chippick->play();

    QCoreApplication::processEvents();
    repaint();
}

/*  @function   add_50
`   @brief      Adds $50 to bet amount
*/
void BetWidget::add_50()
{
    if (balance_total >= 50)
    {
        bet_total += 50;
        balance_total -= 50;
    }

    chippick->play();

    QCoreApplication::processEvents();
    repaint();
}

/*  @function   add_100
`   @brief      Adds $100 to bet amount
*/
void BetWidget::add_100()
{
    if (balance_total >= 100)
    {
        bet_total += 100;
        balance_total -= 100;
    }

    chippick->play();

    QCoreApplication::processEvents();
    repaint();
}

/*  @function   add_500
`   @brief      Adds $500 to bet amount
*/
void BetWidget::add_500()
{
    if (balance_total >= 500)
    {
        bet_total += 500;
        balance_total -= 500;
    }

    chippick->play();

    QCoreApplication::processEvents();
    repaint();
}

/*  @function   add_1000
`   @brief      Adds $1000 to bet amount
*/
void BetWidget::add_1000()
{
    if (balance_total >= 1000)
    {
        bet_total += 1000;
        balance_total -= 1000;
    }

    chippick->play();

    QCoreApplication::processEvents();
    repaint();
}

/*  @function   paintEvent
`   @brief      Adjusts on-screen display of bet amount and bankroll when they are altered

    @param e    QPaintEvent class object, default parameter
*/
void BetWidget::paintEvent(QPaintEvent *e)
{
    if (bet_total >= 10) min_bet = true;
    else min_bet = false;

    if (balance_total - bet_total >= 0) doublesafe = true;
    else doublesafe = false;

    bet_amount->setText(QString::number(bet_total));
    balance_amount->setText(QString::number(balance_total));
}

/*  @function       setHeaderText
`   @brief          Adjusts text displayed by header widget

    @param title    QString representing new title to be set
*/
void BetWidget::setHeaderText(const QString& title)
{
    header->setText(title);
}

/*  @function   double_down
`   @brief      Doubles bet amount and adjusts bankroll accordingly


*/
void BetWidget::double_down()
{
    if (doublesafe)
    {
        balance_total -= bet_total;
        bet_total += bet_total;
    }

}
