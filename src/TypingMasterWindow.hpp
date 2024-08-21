#ifndef TYPINGMASTERWINDOW_H
#define TYPINGMASTERWINDOW_H

#include "TypingSource.hpp"
class TypingLine;
class Stopwatch;

#include <QMainWindow>

class TypingMasterWindow : public QMainWindow
{
    Q_OBJECT

public:
    TypingMasterWindow(QWidget* parent = nullptr);
    ~TypingMasterWindow();

    enum class State { Active, Inactive };
    void keyPressEvent(QKeyEvent* event) override;

private:
    State mState = State::Inactive;

    TypingSource mTypingSource;
    TypingLine* mTypingLine;
    Stopwatch* mStopwatch;

    QWidget* mCentralWgt;
};
#endif // TYPINGMASTERWINDOW_H
