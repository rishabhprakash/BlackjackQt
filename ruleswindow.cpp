#include "ruleswindow.h"
#include "ui_ruleswindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

/* Constructor for RulesWindow class object */
RulesWindow::RulesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RulesWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("The Rules of Blackjack");

    QPixmap background(":/rulesbackground.jpg"); // background image
    QPalette palette; // set background as image using QPalette class
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

    QWidget* central_widget = new QWidget(this);
    central_widget->setFixedHeight(650);
    QVBoxLayout* outline = new QVBoxLayout(central_widget);
    outline->setSpacing(0);

    QLabel* intro_header = new QLabel("\nWelcome to BlackJack!", this);
    QLabel* intro_text = new QLabel(this);
    intro_text->setText("\nBlackjack is a popular American casino game, now found throughout the world. It is a banking game in which the aim of the player is to achieve a\nhand whose points total nearer to 21 than the banker's hand, but without exceeding 21.");
    intro_header->setStyleSheet(" QLabel { font: bold 32px; color : gold } ");
    intro_text->setStyleSheet(" QLabel { font: bold 14px; color : white } ");

    QSpacerItem* space_1 = new QSpacerItem(0, 25);
    QSpacerItem* space_2 = new QSpacerItem(0, 25);

    QLabel* objective_header = new QLabel("<h3>Objective</h3>", this);
    QLabel* objective_text = new QLabel(this);
    objective_text->setText("The aim of the game is to accumulate a higher point total than the dealer, but without going over 21. You compute your score by adding the values of your individual\ncards. The cards 2 through 10 have their face value, J, Q, and K are worth 10 points each, and the Ace is worth either 1 or 11 points (player's choice).");
    objective_header->setStyleSheet(" QLabel { color : gold } ");
    objective_text->setStyleSheet(" QLabel { color : white } ");

    QLabel* deal_header = new QLabel("<h3>The Deal and Getting BlackJack</h3>", this);
    QLabel* deal_text = new QLabel(this);
    deal_text->setText("At the start of a blackjack game, the players and the dealer receive two cards each. The players' cards are normally dealt face up, while the dealer has one face down\n(called the hole card) and one face up. The best possible blackjack hand is an opening deal of an ace with any ten-point card. This is called a 'BlackJack' or a\nnatural 21, and the player holding this automatically wins unless the dealer also has a blackjack. If a player and the dealer each have a blackjack, the result is\na push for that player. If the dealer has a blackjack, all players not holding a blackjack lose.");
    deal_header->setStyleSheet(" QLabel { color : gold } ");
    deal_text->setStyleSheet(" QLabel { color : white } ");

    QLabel* player_header = new QLabel("<h3>Players Turn</h3>", this);
    QLabel* player_text = new QLabel(this);
    player_text->setText("Once the cards have been dealt, it is the player's turn. The player can keep his hand as it is (stand) or take more cards from the deck (hit), one at a time, until either the\nplayer judges that the hand is strong enough to go up against the dealer's hand and stands, or until it goes over 21, in which case the player immediately\nloses (busts).");
    player_header->setStyleSheet(" QLabel { color : gold } ");
    player_text->setStyleSheet(" QLabel { color : white } ");

    QLabel* dealer_header = new QLabel("<h3>Dealers Turn and Showdown</h3>", this);
    QLabel* dealer_text = new QLabel(this);
    dealer_text->setText("When all players have finished their actions, either decided to stand or busted, the dealer turns over his hidden hole card. If the dealer has a natural 21 (blackjack) with\nhis two cards, he won't take any more cards. All players lose, except players who also have a blackjack, in which case it is a push - the bet is returned to the player.\nIf the dealer doesn't have a natural, he hits (takes more cards) or stands depending on the value of the hand. Contrary to the player, though, the dealer's action is\ncompletely dictated by the rules. The dealer must hit if the value of the hand is lower than 17, otherwise the dealer will stand.\n");
    dealer_header->setStyleSheet(" QLabel { color : gold } ");
    dealer_text->setStyleSheet(" QLabel { color : white } ");

    QLabel* bet_header = new QLabel("<h3>Minimum Bet and Payoff</h3>", this);
    QLabel* bet_text = new QLabel(this);
    bet_text->setText("You begin the game with a bankroll of $1000. The minimum bet to participate in a hand is $10. Winning a hand pays 1-1 and BlackJack pays 3-2.");
    bet_header->setStyleSheet(" QLabel { color : gold } ");
    bet_text->setStyleSheet(" QLabel { color : white } ");

    outline->addSpacerItem(space_1);

    outline->addWidget(intro_header, 0, Qt::AlignCenter);
    outline->addWidget(intro_text, 0, Qt::AlignCenter);

    outline->addSpacerItem(space_2);

    outline->addWidget(objective_header, 0, Qt::AlignCenter);
    outline->addWidget(objective_text, 0, Qt::AlignCenter);

    outline->addWidget(deal_header, 0, Qt::AlignCenter);
    outline->addWidget(deal_text, 0, Qt::AlignCenter);

    outline->addWidget(player_header, 0, Qt::AlignCenter);
    outline->addWidget(player_text, 0, Qt::AlignCenter);

    outline->addWidget(dealer_header, 0, Qt::AlignCenter);
    outline->addWidget(dealer_text, 0, Qt::AlignCenter);

    outline->addWidget(bet_header, 0, Qt::AlignCenter);
    outline->addWidget(bet_text, 0, Qt::AlignCenter);

    QWidget* return_start = new QWidget;
    QHBoxLayout* return_start_layout = new QHBoxLayout;

    return_to_main = new QPushButton("Return", this);
    return_to_main->setFixedSize(150, 35);
    return_to_main->setStyleSheet("QPushButton { background-color: rgba(0, 220, 0, 100); border-style: outset; border-width: 2px; border-color: white; color : white; } QPushButton:hover { border-style: outset; border-width: 2px; border-color: gold; color : gold; } ");
    connect(return_to_main, SIGNAL(clicked(bool)), this, SLOT(close()));

    start_new_game = new QPushButton("Start New Game", this);
    start_new_game->setFixedSize(150, 35);
    start_new_game->setStyleSheet("QPushButton { background-color: rgba(0, 220, 0, 100); border-style: outset; border-width: 2px; border-color: white; color : white; } QPushButton:hover { border-style: outset; border-width: 2px; border-color: gold; color : gold; } ");
    connect(start_new_game, SIGNAL(clicked(bool)), this, SLOT(close()));

    return_start_layout->addWidget(return_to_main, 0, Qt::AlignCenter);
    return_start_layout->addWidget(start_new_game, 0, Qt::AlignCenter);
    return_start->setLayout(return_start_layout);
    outline->addWidget(return_start, 0, Qt::AlignCenter);

    central_widget->setLayout(outline);
    this->setCentralWidget(central_widget);
    this->setGeometry(100, 100, 1200, 700);
 }

/* Destrctor for RulesWindow class object */
RulesWindow::~RulesWindow()
{
    delete return_to_main;
    delete start_new_game;

    delete ui;
}
