#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QDesktopServices>
#include <QUrl>

/* Constructor for MainWindow class object */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set up core widget to encapsulate all widgets in layout
    QWidget* central_widget = new QWidget;
    QVBoxLayout* outline = new QVBoxLayout;

    // layout for header bar
    QWidget* header_bar = new QWidget;
    QVBoxLayout* header_layout = new QVBoxLayout;

    // header text
    QLabel* header = new QLabel(" Welcome to BlackJack!");
    header->setStyleSheet(" QLabel { color : white; } ");

    // set headers font size and style using QFont object
    QFont font = header->font();
    font.setPointSize(50); // set size as 36
    font.setBold(true); // set style as bold
    header->setFont(font); // set font

    // add header widgets to outline layout
    header_layout->addWidget(header, 0, Qt::AlignCenter);

    // subheader
    QLabel* subheader = new QLabel("Dealer draws at soft 17    |    Insurance pays 2 to 1");
    subheader->setStyleSheet(" QLabel { color : gold; } ");

    // set headers font size and style using QFont object
    QFont subfont = subheader->font();
    subfont.setPointSize(16); // set size as 16
    subfont.setBold(true); // set style as bold
    subfont.setFamily("Arial");
    subheader->setFont(subfont); // set font
    header_layout->addWidget(subheader, 0, Qt::AlignCenter);

    header_bar->setLayout(header_layout);
    outline->addWidget(header_bar, 0, Qt::AlignCenter);

    // instantiate widget encapsulating all the buttons presenting users with options upon launch
    QWidget* central_bar = new QWidget;
    QHBoxLayout* central_layout = new QHBoxLayout;

    // insatantiate each of the buttons - rules, start a new game, or check out my GitHub
    rules_button = new QPushButton("Blackjack Rules");
    rules_button->setFixedSize(150, 40);
    rules_button->setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 30); font: 14px; border-style: outset; border-width: 2px; border-color: white; color : white; } QPushButton:hover { border-style: outset; border-width: 2px; border-color: gold; color : gold; } ");

    new_game = new QPushButton("Start a new game!");
    new_game->setFixedSize(150, 40);
    new_game->setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 30); font: 14px; border-style: outset; border-width: 2px; border-color: white; color : white; } QPushButton:hover { border-style: outset; border-width: 2px; border-color: gold; color : gold; } ");

    github_link = new QPushButton("My GitHub");
    github_link->setFixedSize(150, 40);
    github_link->setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 30); font: 14px; border-style: outset; border-width: 2px; border-color: white; color : white; } QPushButton:hover { border-style: outset; border-width: 2px; border-color: gold; color : gold; } ");

    // add each button to central layout
    central_layout->addWidget(rules_button, 0 , Qt::AlignCenter);
    central_layout->addWidget(new_game, 0 , Qt::AlignCenter);
    central_layout->addWidget(github_link, 0 , Qt::AlignCenter);

    // set layout to encapsulating widget
    central_bar->setLayout(central_layout);
    outline->addWidget(central_bar, 0, Qt::AlignCenter);

    // set layout, geometry (placement) of window
    central_widget->setLayout(outline);
    this->setCentralWidget(central_widget);
    this->setGeometry(250, 250, 1000, 500);
    this->setWindowTitle("Blackjack v1.4");

    // set background of window
    QPixmap background(":/blackjack.jpg"); // background image
    QPalette palette; // set background as image using QPalette class
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

    // Necessary connect functions connecting buttons to respective functions to be called
    connect(new_game, SIGNAL(clicked(bool)), this, SLOT(startNewGame()));
    connect(github_link, SIGNAL(clicked(bool)), this, SLOT(openGitHub()));
    connect(rules_button, SIGNAL(clicked(bool)), this, SLOT(openRulesWindow()));
}


/*  @function   openGitHub
    @brief      Opens my GitHub page with the code for this game on users deafult browser
*/
void MainWindow::openGitHub()
{
    QDesktopServices::openUrl(QUrl("https://github.com/rishabhprakash/BlackJackQt", QUrl::TolerantMode));
}

/*  @function   startNewGame
    @brief      Launches new game window
*/
void MainWindow::startNewGame()
{
    current_game = new GameWindow;
    current_game->show();
}

/*  @function   openRulesWindow
    @brief      Launches new window displaying rules of the game
*/
void MainWindow::openRulesWindow()
{
    rules = new RulesWindow;
    rules->show();

    connect(rules->start_new_game, SIGNAL(clicked(bool)), this, SLOT(startNewGame()));
}

/* Destructor for MainWindow class object */
MainWindow::~MainWindow()
{
    delete ui;

    delete rules;
    delete new_game;
    delete github_link;
}

