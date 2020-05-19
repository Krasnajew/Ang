#include "repetwindow.h"
#include <QtWidgets>
#include <QStackedLayout>

ReptWindow::ReptWindow(QPushButton *back, std::shared_ptr<WordBase> base):
    base_ptr(base)
{

    repList = new QQueue<int>;

    mainWindow = new QWidget;
    childWindow = new QWidget;
    stackWidget = new QStackedLayout;
    mainLayout = new QGridLayout;
    info = new QLabel(tr("Zaznacz zestawy które chcesz powtórzyć i naciśnij 'Start!'"));
    info ->setAlignment(Qt::AlignCenter);

    backB=back;
    reptStart = new QPushButton(tr("Start!"));
    connect(reptStart, &QPushButton::clicked, this, &ReptWindow::reptStartButt);
    lateRep = new QGroupBox(tr("Przegapione powtórki"));
    lateRep->setMaximumSize(500, 100);

    todayRep = new QGroupBox(tr("Dzisiejsze powtórki"));
    lateScroll = new QScrollArea;
    todayScroll = new QScrollArea;

    mainUpdate();
    makeMainW();
    makeChild();

    mainWindow->setLayout(mainLayout);
    childWindow->setLayout(childLayout);
    stackWidget->addWidget(mainWindow);
    stackWidget->addWidget(childWindow);

    setLayout(stackWidget);

}
void ReptWindow::reptStartButt()
{
    // test czy wybrano jakikolwiek set
    if(getChecked()) return;
    setLoad();
    stackWidget->setCurrentIndex(1);
}
void ReptWindow::backMainButt()
{
    QMessageBox msgBox;
    msgBox.setText("Pozostalo " + QString::number(end-current) + " słówek do powtórzenia. Wyjscie spowoduje zresetowanie czegos tam. Czy napewno wyjść? Później to lepiej napisze lol" );
    QPushButton *okButton = msgBox.addButton(tr("Ok"), QMessageBox::ActionRole);
    QPushButton *cancelButton = msgBox.addButton(tr("Cancel"), QMessageBox::ActionRole);

    msgBox.exec(); // tworzy okno dialogowe i po jego zamknięciu zwraca id przycisku wciśniętego

    if (msgBox.clickedButton() == okButton) {
        getChecked();
        stackWidget->setCurrentIndex(0);
        backB->animateClick();
    } else if (msgBox.clickedButton() == cancelButton) {
        return;
    }
}
void ReptWindow::checkButt()
{
    if(answer->toPlainText().isEmpty()) return;

    rightAnswer->setText(currentSet->getEngPln(current));
    yourAnswer->setText(answer->toPlainText());
    answer->clear();
    engWord->setText(currentSet->getEng(current+1));
    current++;
    downLabel_2->setText("Pozostało: " + QString::number(end-current) +" słówek");
    if(current == end)
    {
        setLoad();
        base_ptr->erSetfTer(currentID);
        getChecked();
        mainUpdate();
        makeMainW();
    }
}
void ReptWindow::mainUpdate()
{
    //get information about set, that user shoud repeat
    QVector<int> todayR = base_ptr->todaySet();
    QSet<int> lateR = base_ptr->lateSet();

    if(late.empty() != true)
    {
        late.clear();
    }
    if(today.empty()!= true)
    {
        today.clear();
    }
    delete lateRep;
    delete todayRep;
    lateRep = new QGroupBox(tr("spozniony"));
    todayRep = new QGroupBox(tr("dzisiaj"));
    auto lateLayout = new QVBoxLayout;
    auto todayLayout = new QVBoxLayout;
    //QScrollArea *scrol = new QScrollArea;

    ///create QCheckBox
    if(todayR.empty() != true)
    {
        std::for_each(todayR.begin(), todayR.end(), [this, &todayLayout](int i){
            this->today.push_back(new QCheckBox(QString::number(i)));
            today.back()->setChecked(true);
            todayLayout -> addWidget(today.back());
        });
    }
    if(lateR.empty() != true)
    {
        std::for_each(lateR.begin(), lateR.end(), [this, &lateLayout](int i){
            this->late.push_back(new QCheckBox(QString::number(i)));
            //late.back()->setChecked(true);
            lateLayout ->addWidget(late.back());
        });
    }
    lateRep->setLayout(lateLayout);
    todayRep->setLayout(todayLayout);
}
bool ReptWindow::getChecked()
{
    repList->clear();

    if(today.isEmpty() && late.isEmpty())
    {
        nothingToRept();
        return true;
    }
    else
    {
        if(!(today.isEmpty()))
        {
            std::for_each(today.begin(), today.end(), [this](auto i)
            {
                if(i->QAbstractButton::isChecked())
                {
                    this->repList->enqueue(i->text().toInt());
                }
            });
        }
        if(!(late.isEmpty()))
        {
            std::for_each(late.begin(), late.end(), [this](auto i)
            {
                if(i->QAbstractButton::isChecked())
                {
                    this->repList->enqueue(i->text().toInt());
                }
            });
        }
        if(repList->isEmpty())
        {
            nothingToRept();
            return true;
        }

    }
    return false;
}

void ReptWindow::makeMainW()
{
    mainLayout ->addWidget(info, 0, 0);
    mainLayout ->addWidget(lateRep, 1, 0);
    mainLayout ->addWidget(todayRep, 2, 0);
    mainLayout ->addWidget(reptStart, 3, 0);
    mainLayout ->addWidget(backB, 4, 0);

}

void ReptWindow::makeChild()
{
    childLayout = new QGridLayout;

    rightAnswerBox = new QGroupBox("Prawidłowa odpowiedź");
    rightAnswer= new QLabel(tr("..............."));
    rightAnswer->setAlignment(Qt::AlignCenter);
    //rightAnswerStr = new QString;
    yourAnswer = new QLabel(tr("..............."));
    yourAnswer->setAlignment(Qt::AlignCenter);
    engWord = new QLabel;
    engWord ->setAlignment(Qt::AlignCenter);
    //engWordStr = new QString;
    answer = new QTextEdit;
    answer -> setFixedSize(170, 25);
    //setInfo = new QLabel(tr("Wcisnij enter by przejsc dalej"));
    //setInfoStr = new QString;
    backMain = new QPushButton(tr("Powrót"));
    connect(backMain, &QPushButton::clicked, this, &ReptWindow::backMainButt);
    downLabel_1 = new QLabel("Zestaw 4");
    downLabel_2 = new QLabel("Pozostalo 69 slowek");
    downLabelStr = new QString;
    check = new QPushButton(tr("Sprawdz!"));
    connect(check, &QPushButton::clicked, this, &ReptWindow::checkButt);

    childLayout -> addWidget(engWord, 0, 0);
    childLayout -> addWidget(answer, 0, 1);
    childLayout -> addWidget(check, 0, 2);

    //childLayout -> addWidget(upLabel, 1, 0);
    //childLayout -> addWidget(upLabel2, 1, 1);
    childLayout -> addWidget(rightAnswer, 2, 0);
    childLayout -> addWidget(yourAnswer, 2, 1);

    //childLayout -> addWidget(setInfo, 3, 0);
    childLayout -> addWidget(backMain, 3, 0);
    childLayout -> addWidget(downLabel_1, 3, 1);
    childLayout -> addWidget(downLabel_2, 3, 2);
}

void ReptWindow::setLoad()
{
    if(repList->size() == 0 )
    {
        currentSet = nullptr;
        workDone(); //if nothing left to repeat, show message
        return;
    }
    currentID = repList->dequeue();
    currentSet = base_ptr->getSet(currentID);
    current = 0;
    end = currentSet->getSize();
    engWord->setText(currentSet->getEng(0)); //tu sie wypierdala
    downLabel_1->setText("Zestaw nr " + QString::number(currentID));
    downLabel_2->setText("Pozostało: " + QString::number(end) + " słówek");

}

void ReptWindow::workDone()
{
    QMessageBox msgBox;
    msgBox.setText("Wszystko powtórzone, dobra robota!");
    QPushButton *okButton = msgBox.addButton(tr("Ok"), QMessageBox::ActionRole);
    //QPushButton *cancelButton = msgBox.addButton(tr("Cancel"), QMessageBox::ActionRole);

    msgBox.exec(); // tworzy okno dialogowe i po jego zamknięciu zwraca id przycisku wciśniętego

    if (msgBox.clickedButton() == okButton) {
        stackWidget->setCurrentIndex(0);
        backB->animateClick();
    }
}

void ReptWindow::nothingToRept()
{
    QMessageBox msgBox;
    msgBox.setText("Nie wybrano zestawów do powtórzenia lub żadne już nie zostały.");
    //msgBox.setInformativeText("Uzupełnij pola by przejść dalej.");
    msgBox.setStandardButtons(QMessageBox::Ok);

    msgBox.exec(); // tworzy okno dialogowe i po jego zamknięciu zwraca id przycisku wciśniętego

}
