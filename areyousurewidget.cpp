#include "areyousurewidget.h"
#include "ui_areyousurewidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

/* Constructor for areyousurewidget class object */
areyousurewidget::areyousurewidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::areyousurewidget)
{
    ui->setupUi(this);

    QVBoxLayout* layout = new QVBoxLayout; // outline layout

    sure = new QLabel("Are you sure?", this); // label widget with confirmation text
    sure->setStyleSheet(" QLabel { color : gold; } ");
    QFont font = sure->font();
    font.setPointSize(56); // set size as 36
    font.setBold(true); // set style as bold
    sure->setFont(font); // set font
    layout->addWidget(sure, 0, Qt::AlignCenter);

    QHBoxLayout* bar = new QHBoxLayout; // layout which orients yes and no buttons
    yes = new QPushButton("Yes"); // yes button
    yes->setFixedSize(200, 50);
    yes->setStyleSheet("QPushButton { background-color: rgba(0, 220, 0, 100); font: 18px; border-style: outset; border-width: 2px; border-color: white; color : white; } QPushButton:hover { border-style: outset; border-width: 2px; border-color: gold; color : gold; } ");
    bar->addWidget(yes, 0, Qt::AlignCenter);
    connect(yes, SIGNAL(clicked(bool)), this, SLOT(close())); // if clicked, close this side-window()

    no = new QPushButton("No"); // no button
    bar->addWidget(no, 0, Qt::AlignCenter);
    no->setFixedSize(200, 50);
    no->setStyleSheet("QPushButton { background-color: rgba(0, 220, 0, 100); font: 18px; border-style: outset; border-width: 2px; border-color: white; color : white; } QPushButton:hover { border-style: outset; border-width: 2px; border-color: gold; color : gold; } ");

    // yes and no buttons stored in common widget
    QWidget* bar_widget = new QWidget;
    bar_widget->setLayout(bar);
    layout->addWidget(bar_widget, 0, Qt::AlignCenter);

    this->setLayout(layout);
    this->setStyleSheet("QWidget { background-color : rgba(0,0,0,0); }");

}

/* Destructor for areyousurewidget class object */
areyousurewidget::~areyousurewidget()
{
    delete sure;
    delete yes;
    delete no;

    delete ui;
}
