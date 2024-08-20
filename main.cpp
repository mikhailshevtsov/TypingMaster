#include "TypingMasterWindow.hpp"

#include <QApplication>

#include "TypingLine.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // TypingMasterWindow w;
    // w.show();

    TypingLine tl;
    tl.show();

    return a.exec();
}
