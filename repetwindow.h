#ifndef REPETWINDOW_H
#define REPETWINDOW_H

#include <QWidget>
#include "wordbase.h"
#include <memory>
#include <QTextEdit>
#include <QKeyEvent>
#include <QDebug>

QT_BEGIN_NAMESPACE
class QPushButton;
class QGridLayout;
class QLabel;
class QVBoxLayout;
class QCheckBox;
class QScrollArea;
class QGroupBox;
class QTextEdit;
class QStackedLayout;
QT_END_NAMESPACE

class ReptWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ReptWindow(QPushButton *back, std::shared_ptr<WordBase> base);

    void infoUPD(); ///update
    QPair<int, int> getWH(){
        return QPair<int, int>(height(), height());
    } //return width and height
signals:

public slots:
    void reptStartButt();
    void mainUpdate(); ///update content of lateRep and todayRep
    void backMainButt();
    void checkButt();

private:
    std::shared_ptr<WordBase> base_ptr;

    QStackedLayout *stackWidget;
    ///main_window///
    //QWidget *firstWindow;
    QWidget *mainWindow;
    QGridLayout *mainLayout;
    QGroupBox *lateRep;
    QScrollArea *lateScroll;
    QGroupBox *todayRep;
    QScrollArea *todayScroll;
    QPushButton *backB;
    QPushButton *reptStart;
    QLabel *info;
    //QString *infoString;

    //QVector<int> todayR;
    QList<QCheckBox*> late;
    QList<QCheckBox*> today;
    ///child_window ///
    QGroupBox *rightAnswerBox;
    QGroupBox *yourAnswerBox;
    QWidget *childWindow;
    QGridLayout *childLayout;
    QPushButton *check;
    QPushButton *backMain;
    QString *downLabelStr;
    QLabel *rightAnswer;
    QLabel *yourAnswer;
    QLabel *engWord;
    QTextEdit *answer;
    QLabel *downLabel_1;
    QLabel *downLabel_2;
    //reppeat staff
    QQueue<int> *repList; ///list of IDsets to repeat
    WordSet *currentSet;
    int currentID;
    int current;
    int end;
    ///function_member///
    bool getChecked(); //get chosen sets of QLate and QToday. return true if user chose nothing or is nothing to chose
    void makeMainW();
    void makeChild(); //second window after press Start! button
    void setLoad(); //load set to currentSet
    void workDone(); //show measega when you repeat ewrything
    void nothingToRept(); //show message when nothing left to reppeat or user chose nothing to repeat
    //void warningWindow();
    //void repeatMachine();
};

#endif // REPETWINDOW_H
