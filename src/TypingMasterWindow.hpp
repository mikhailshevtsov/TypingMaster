#ifndef TYPINGMASTERWINDOW_H
#define TYPINGMASTERWINDOW_H

#include "TypingSource.hpp"
class TypingLine;

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

    TypingLine* mTypingLine;
    TypingSource mTypingSource;
};
#endif // TYPINGMASTERWINDOW_H
