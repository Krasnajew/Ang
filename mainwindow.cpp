#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wordbase.h"
#include <QtWidgets>
#include <memory>


MainWindow::MainWindow()
{
    wordB = std::make_shared<WordBase>(tr("baza.txt"));
    home = new QWidget();

    backBase = new QPushButton(tr("back home"));
    connect(backBase, &QPushButton::clicked, this, &MainWindow::backHome);
    backInfo = new QPushButton(tr("back home"));
    connect(backInfo, &QPushButton::clicked, this, &MainWindow::backHome);
    backAdd = new QPushButton(tr("back home"));
    connect(backAdd, &QPushButton::clicked, this, &MainWindow::backHome);
    backCal = new QPushButton(tr("back home"));
    connect(backCal, &QPushButton::clicked, this, &MainWindow::backHome);
    backRepeat = new QPushButton(tr("back home"));
    connect(backRepeat, &QPushButton::clicked, this, &MainWindow::backHome);

    baseWindow = new BaseWindow(backBase, wordB);
    //infoWindow = new Info(backInfo);
    addWordWindow = new AddWord(backAdd, wordB);
    reptWindow = new ReptWindow(backRepeat, wordB);

    mainLayout = new QGridLayout();
    addButton = new QPushButton(tr("Dodaj słówka"));
    addButton->setProperty("index", 1);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::changeWindow);
    //kalendaryButton = new QPushButton(tr("Kalendarz"));
    //kalendaryButton->setProperty("index", 2);
    //connect();
    baseButton = new QPushButton(tr("Słownik"));
    baseButton->setProperty("index", 3);
    connect(baseButton, &QPushButton::clicked, this, &MainWindow::changeWindow);
    //infoButton = new QPushButton(tr("Informacje"));
    //infoButton->setProperty("index", 4);
    //connect(infoButton, &QPushButton::clicked, this, &MainWindow::changeWindow);
    repeatButton = new QPushButton(tr("Zacznij powtórkę"));
    repeatButton->setProperty("index", 5);
    connect(repeatButton, &QPushButton::clicked, this, &MainWindow::changeWindow);

    exitButton = new QPushButton(tr("Wyjście"));
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::close);

    /*nRepWord = new QLabel(tr("Dzisiaj do powtorzenia n słówek"));
    nRepWord ->setAlignment(Qt::AlignCenter);
    nLearnWord = new QLabel(tr("Łącznie nauczyłeś się 0 słówek!"));
    nLearnWord ->setAlignment(Qt::AlignCenter);*/

    mainLayout ->addWidget(addButton, 0, 0);
    mainLayout ->addWidget(repeatButton, 1, 0);
    mainLayout ->addWidget(baseButton, 2, 0);
    mainLayout ->addWidget(exitButton, 3, 0);
    //mainLayout ->addWidget(nRepWord, 1, 1);
    //mainLayout ->addWidget(nLearnWord, 2, 1);

    home -> setLayout(mainLayout);

    setWindowTitle(tr("Turbo PowtarzaTron 3000"));
    resize(500, 270);
    setCentralWidget(home); ////whyyyyyyyy
    //repWordCount();

}

void MainWindow::changeWindow()
{
    centralWidget()->setParent(nullptr);
    QPushButton *temp = qobject_cast<QPushButton*>(sender());
    int index = temp->property("index").toInt();
    switch(index)
    {

        case 1:
        setCentralWidget(addWordWindow);
        break;
        case 2:
        break;
        case 3:
        baseWindow->baseStringUPD();
        setCentralWidget(baseWindow);
        break;
        case 4:
        //setCentralWidget(infoWindow);
        break;
        case 5:
        auto d = reptWindow->getWH();
        setFixedSize(d.first, d.second);
        setCentralWidget(reptWindow);
        break;

    }

}

void MainWindow::backHome()
{
    centralWidget()->setParent(nullptr);
    setCentralWidget(home);
    setFixedSize(500, 270);
}

