#include "TypingMasterWindow.hpp"

#include "TypingLine.hpp"
#include "Stopwatch.hpp"

#include <QWidget>
#include <QVBoxLayout>
#include <QKeyEvent>

TypingMasterWindow::TypingMasterWindow(QWidget* parent)
    : QMainWindow(parent)
{
    // Setup TypingSource
    mTypingSource.open("../../phrases.en");

    // Setup TypingLine
    mTypingLine = new TypingLine;
    mTypingLine->setFixedSize(1000, 100);
    mTypingLine->setTypingText("Enter to Start ", " Escape to Stop");

    // Setup Stopwatch
    mStopwatch = new Stopwatch(this);

    // Setup central widget
    mCentralWgt = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(mStopwatch, 0, Qt::AlignRight);
    layout->addWidget(mTypingLine, Qt::AlignCenter);
    mCentralWgt->setLayout(layout);
    setCentralWidget(mCentralWgt);
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
            mStopwatch->start();
        }
        break;

    case State::Active:
        if (event->key() == Qt::Key_Escape || mTypingSource.atEnd()) // pause or finish typing session
        {
            mState = State::Inactive;
            mStopwatch->stop();
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
