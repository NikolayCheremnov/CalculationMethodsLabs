#include "gui.h"

#include <QApplication>

#include "Lab1/lab1.h"


int main(int argc, char *argv[])
{
    printf("Starting tests ...\n");

    Lab1 test(true, &clog);
    try {
    test.TestSimpleLU();
    } catch (exception ex) {
        printf(ex.what());
    }

//    QApplication a(argc, argv);
//    GUI w;
//    w.show();
//    return a.exec();

    return 0;
}
