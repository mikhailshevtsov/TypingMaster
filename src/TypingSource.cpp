#include "TypingSource.hpp"

#include <QTextStream>

TypingSource::TypingSource()
{}

TypingSource::TypingSource(const QString& fileName, qsizetype startPos)
{
    open(fileName, startPos);
}

void TypingSource::open(const QString& fileName, qsizetype startPos)
{
    if (mFile.isOpen())
        mFile.close();

    mFile.setFileName(fileName);
    mFile.open(QFile::Text | QFile::ReadOnly);
    mBuffer = QTextStream(&mFile).readAll().simplified();
    mCurrent = (startPos <= mBuffer.size() ? startPos : mBuffer.size());
}

void TypingSource::nextChar()
{
    if (mCurrent < mBuffer.size())
        ++mCurrent;
}

QChar TypingSource::peekChar()
{
    return mCurrent < mBuffer.size() ? mBuffer[mCurrent] : '\0';
}

QString TypingSource::prev() const
{
    qsizetype begin = (mCurrent >= mVisibleTextSize / 2) ? (mCurrent - mVisibleTextSize / 2) : 0;
    qsizetype count = (mCurrent >= mVisibleTextSize / 2) ? mVisibleTextSize / 2 : mCurrent;
    return mBuffer.mid(begin, count);
}

QString TypingSource::next() const
{
    return mBuffer.mid(mCurrent, mVisibleTextSize / 2);
}

bool TypingSource::seek(qsizetype pos) noexcept
{
    if (pos <= mBuffer.size())
    {
        mCurrent = pos;
        return true;
    }
    return false;
}

qsizetype TypingSource::pos() const noexcept
{
    return mCurrent;
}

const QString& TypingSource::buffer() const noexcept
{
    return mBuffer;
}

bool TypingSource::atEnd() const
{
    return mCurrent >= mBuffer.size();
}
