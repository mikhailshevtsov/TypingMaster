#include "Stopwatch.hpp"

#include <QTimer>

Stopwatch::Stopwatch(QWidget* parent)
    : QLabel(parent)
{
    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), SLOT(displayEllapsedTime()));

    setText(mEllapsedTime.toString("m:ss"));
}

void Stopwatch::start()
{
    if (!isActive())
        mTimer->start(1000);
}

void Stopwatch::stop()
{
    if (isActive())
        mTimer->stop();
}

void Stopwatch::reset()
{
    stop();
    mEllapsedTime = QTime();
    setText(mEllapsedTime.toString("m:ss"));
}

bool Stopwatch::isActive() const
{
    return mTimer->isActive();
}

const QTime& Stopwatch::ellapsedTime() const
{
    return mEllapsedTime;
}

void Stopwatch::displayEllapsedTime()
{
    mEllapsedTime = mEllapsedTime.addSecs(1);
    setText(mEllapsedTime.toString("m:ss"));
}

