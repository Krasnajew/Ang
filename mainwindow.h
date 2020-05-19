#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
//#include "info.h"
#include "wordbase.h"
#include "basewindow.h"
#include "addword.h"
#include "repetwindow.h"

#include <memory>

QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
class QTextEdit;
class QGridLayout;
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    //~MainWindow();
    void infoLaybelAct();
    //void resizeEvent(QResizeEvent *event) override;
public slots:
    void changeWindow();
    void backHome();

private:
    //std::unique_ptr<WordBase> wordB; //WordBase base;
    std::shared_ptr<WordBase> wordB;
    QWidget *home;
    //Info *infoWindow;
    BaseWindow *baseWindow;
    AddWord *addWordWindow;
    ReptWindow *reptWindow;
    //QWidget *bla;

    QPushButton *addButton;
    //QPushButton *kalendaryButton;
    QPushButton *baseButton;
    //QPushButton *infoButton;
    QPushButton *exitButton;
    QPushButton *repeatButton;

    QPushButton *backBase;
    QPushButton *backInfo;
    QPushButton *backCal;
    QPushButton *backAdd;
    QPushButton *backRepeat;

    //QTextEdit *mainInfo;

    //QLabel *nRepWord;
    //QLabel *nLearnWord;
    //QLabel *name;

    QGridLayout *mainLayout;

    //int repWordCount();

};

#endif // MAINWINDOW_H
