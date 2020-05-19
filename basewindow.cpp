#include "basewindow.h"
#include <QtWidgets>
#include "wordbase.h"
#include <QTextStream>
#include <memory>

//#include "wordbase.h"

BaseWindow::BaseWindow(QPushButton *back, std::shared_ptr<WordBase> baseW):
    base_ptr(baseW)
{

   //wordB = std::make_unique<WordBase>();

    layout = new QGridLayout;

    //loadButton = new QPushButton(tr("Wczytaj"));
    //connect();
    openTxt = new QPushButton(tr("Otwórz plik .txt"));
    connect(openTxt, &QPushButton::clicked, this, &BaseWindow::openFile);
    //QString temp;
    baseString = new QString;
    baseStringUPD();

    //base = new QTextEdit(baseW->getBaseString()); ///zajrzec lol
    base = new QTextEdit(*baseString);
    base->setReadOnly(true);

    //fileName = new QLabel("ścieżka pliku: "+ baseWord->getBaseFileName());

    //layout ->addWidget(loadButton,0,0);
    layout ->addWidget(openTxt, 0, 0);
    layout ->addWidget(back, 1, 0);
    layout ->addWidget(base, 0, 1, 4, 2);
    //layout ->addWidget(fileName, 3, 0);

    setLayout(layout);

}

void BaseWindow::openFile()
{
    QDesktopServices::openUrl(QUrl("baza.txt"));
}

void BaseWindow::baseStringUPD()
{
        baseString->clear();
        std::copy_if(base_ptr->getBaseString().begin(), base_ptr->getBaseString().end(), std::back_inserter(*baseString), [](auto c){
        if((c == '*')) return false;
        else if(c=='&') return false;
        else return true;
    });
}
