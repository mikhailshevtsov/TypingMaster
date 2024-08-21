#include "src/TypingMasterWindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TypingMasterWindow w;
    w.show();

    return a.exec();
}
