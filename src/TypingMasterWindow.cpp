#include "TypingMasterWindow.hpp"

#include "TypingLine.hpp"

#include <QKeyEvent>

TypingMasterWindow::TypingMasterWindow(QWidget* parent)
    : QMainWindow(parent)
{
    mTypingLine = new TypingLine;
    mTypingLine->resize(1000, 300);
    mTypingLine->setTypingText("Enter to Start ", " Escape to Stop");
    setCentralWidget(mTypingLine);

    mTypingSource.open("../../phrases.en");
}

TypingMasterWindow::~TypingMasterWindow() {}

void TypingMasterWindow::keyPressEvent(QKeyEvent* event)
{
    switch (mState)
    {
    case State::Inactive:
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Space) // begin typing session
        {
            mState = State::Active;
            mTypingLine->setTypingText(mTypingSource.prev(), mTypingSource.next());
        }
        break;

    case State::Active:
        if (event->key() == Qt::Key_Escape || mTypingSource.atEnd()) // pause or finish typing session
        {

        }
        else if (event->text().size() == 1) // user typed char
        {
            QChar typedChar = event->text().front();
            if (typedChar == mTypingSource.peekChar())
            {
                mTypingSource.nextChar();
                mTypingLine->setTypingText(mTypingSource.prev(), mTypingSource.next());
            }
            else
            {

            }
        }
        break;
    }
    QMainWindow::keyPressEvent(event);
}
