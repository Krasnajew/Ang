#ifndef ADDWORD_H
#define ADDWORD_H

#include <QWidget>
#include "wordbase.h"
#include <QScopedPointer>
#include <memory>

QT_BEGIN_NAMESPACE
class QPushButton;
class QGridLayout;
class QTextEdit;
class QLabel;
class QRadioButton;
class QVBoxLayout;
QT_END_NAMESPACE

class AddWord : public QWidget
{
    Q_OBJECT
public:
    explicit AddWord(QPushButton *back, std::shared_ptr<WordBase> base);
    ~AddWord(){saveTemp();}
public slots:
    //void addButt;
    void editButt();
    void clearButt();
    void saveButt();
    void addButt();
    void otherAddButt();

private:
    WordSet tempSet;
    std::shared_ptr<WordBase> base_ptr; //pointer to main word library
    QGridLayout *layout;

    QPushButton *addButton;
    QRadioButton *editButton;
    QPushButton *clearButton;
    QPushButton *saveButton;

    QTextEdit *words;

    QWidget *addWindow;
    QGridLayout *addLayout;
    QLabel *message;
    QTextEdit *write;
    QTextEdit *wordEng;
    QTextEdit *wordPln;
    QPushButton *close;
    QPushButton *add;

    /////
    void makeAddWindow();
    void saveTemp();
    void loadTemp();
    void setWords();
};


#endif // ADDWORD_H

