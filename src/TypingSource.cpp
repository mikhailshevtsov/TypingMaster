#include "TypingSource.hpp"

#include <QDebug>

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
    mFile.open(QFile::ReadOnly);

    mTxt.setDevice(&mFile);

    mBuffer = mTxt.read(mBufferSize).simplified();
    mCurrent = startPos <= mBuffer.size() ? startPos : 0;
}

void TypingSource::nextChar()
{
    if (mCurrent >= mBuffer.size() - visibleTextSize() / 2 - 1)
    {
        // Copy visible chars from end of buffer to its begin
        std::copy(mBuffer.cend() - visibleTextSize(), mBuffer.cend(), mBuffer.begin());
        mBuffer.replace(visibleTextSize(), mBufferSize, mTxt.read(mBufferSize - visibleTextSize()).simplified());
        mCurrent = visibleTextSize() / 2;
    }
    else
        ++mCurrent;
}

QChar TypingSource::peekChar()
{
    return mBuffer[mCurrent];
}

QString TypingSource::visibleText()
{
    qsizetype begin = (mCurrent >= visibleTextSize() / 2) ? (mCurrent - visibleTextSize() / 2) : 0;
    return mBuffer.mid(begin, visibleTextSize());
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

qsizetype TypingSource::bufferSize() const noexcept
{
    return mBufferSize;
}

qsizetype TypingSource::visibleTextSize() const noexcept
{
    return mVisibleTextSize;
}

bool TypingSource::atEnd() const
{
    return mTxt.atEnd();
}
