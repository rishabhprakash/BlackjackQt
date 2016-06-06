#include "gameoverwidget.h"
#include "ui_gameoverwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

/* Constructor for gameoverwidget class object */
gameoverwidget::gameoverwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameoverwidget)
{
    ui->setupUi(this);

    QVBoxLayout* layout = new QVBoxLayout; // outline layout
    layout->setSpacing(0);
    this->setStyleSheet("QWidget { background-color: rgba(0,0,0,0); }");

    notif = new QLabel("Your all out of money!", this); // label widget with notification text
    notif->setStyleSheet(" QLabel { color : gold; } ");
    QFont font = notif->font();
    font.setPointSize(56); // set size as 36
    font.setBold(true); // set style as bold
    notif->setFont(font); // set font
    layout->addWidget(notif, 0, Qt::AlignCenter);

    QHBoxLayout* bar = new QHBoxLayout; // layout which orients restart and leave buttons
    restart = new QPushButton("Play Again"); // restart button
    restart->setFixedSize(200, 50);
    restart->setStyleSheet("QPushButton { background-color: rgba(0, 220, 0, 100); font: 18px; border-style: outset; border-width: 2px; border-color: white; color : white; } QPushButton:hover { border-style: outset; border-width: 2px; border-color: gold; color : gold; } ");
    bar->addWidget(restart, 0, Qt::AlignCenter);
    connect(restart, SIGNAL(clicked(bool)), this, SLOT(close())); // if clicked, quit entire application

    end = new QPushButton("Leave the Table"); // leave button
    end->setFixedSize(200, 50);
    end->setStyleSheet("QPushButton { background-color: rgba(0, 220, 0, 100); font: 18px; border-style: outset; border-width: 2px; border-color: white; color : white; } QPushButton:hover { border-style: outset; border-width: 2px; border-color: gold; color : gold; } ");
    bar->addWidget(end, 0, Qt::AlignCenter);
    connect(end, SIGNAL(clicked(bool)), this, SLOT(close())); // if clicked, close this side-window

    // yes and no buttons stored in common widget
    QWidget* bar_widget = new QWidget;
    bar_widget->setLayout(bar);
    layout->addWidget(bar_widget, 0, Qt::AlignCenter);

    // label, yes and no all pieced together in layout
    this->setLayout(layout);
}

/* Destructor for gameoverwidget class object */
gameoverwidget::~gameoverwidget()
{
    delete notif;
    delete restart;
    delete end;

    delete ui;
}
