#-------------------------------------------------
#
# Project created by QtCreator 2016-04-16T20:19:04
#
#-------------------------------------------------

QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Blackjack
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gamewindow.cpp \
    card.cpp \
    hand.cpp \
    deck.cpp \
    betwidget.cpp \
    ruleswindow.cpp \
    gameoverwidget.cpp \
    areyousurewidget.cpp

HEADERS  += mainwindow.h \
    gamewindow.h \
    card.h \
    hand.h \
    deck.h \
    betwidget.h \
    ruleswindow.h \
    gameoverwidget.h \
    areyousurewidget.h

FORMS    += mainwindow.ui \
    gamewindow.ui \
    card.ui \
    hand.ui \
    deck.ui \
    betwidget.ui \
    ruleswindow.ui \
    areyousure.ui \
    gameover.ui \
    gameoverwidget.ui \
    areyousurewidget.ui

RESOURCES += \
    images.qrc \
    cards.qrc \
    chips.qrc \
    sounds.qrc

DISTFILES += \
    ../Desktop/blackjack.jpg
