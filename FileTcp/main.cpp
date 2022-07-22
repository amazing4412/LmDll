#include "widget.h"
#include "clienwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    ClienWidget N;
    N.show();

    return a.exec();
}
