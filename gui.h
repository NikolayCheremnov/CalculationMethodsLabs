#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>

#include "Lab1/lab1.h"
#include "Logger/stringlogger.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();

private slots:

    // Lab1 slots
    void on_Lab1SolveBtn_clicked();

private:
    Ui::GUI *ui;

    // Lab1
    void sendOutput(QTextEdit* output, QString msg);
};
#endif // GUI_H
