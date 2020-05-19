#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QWidget>
#include "wordbase.h"
#include <QScopedPointer>
#include <memory>


QT_BEGIN_NAMESPACE
class QPushButton;
class QGridLayout;
class QTextEdit;
class QLabel;
QT_END_NAMESPACE

class BaseWindow : public QWidget
{
    Q_OBJECT
public:
    explicit BaseWindow(QPushButton *back, std::shared_ptr<WordBase> baseW);

signals:

public slots:
    void openFile();
    void baseStringUPD();
private:
    //std::unique_ptr<WordBase> wordB;
    std::shared_ptr<WordBase> base_ptr; //pointer to main word library

    QGridLayout *layout;
    QString *baseString;
    QPushButton *loadButton;
    QPushButton *openTxt;
    QTextEdit *base;
    //QLabel *fileName;
};

#endif // BASEWINDOW_H
