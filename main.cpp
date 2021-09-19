#include "gui.h"

#include <QApplication>

#include "Lab1/lab1.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GUI w;
    w.show();
    return a.exec();

    return 0;
}
