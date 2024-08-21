#ifndef TYPINGSOURCE_HPP
#define TYPINGSOURCE_HPP

#include <QTextStream>
#include <QFile>

class TypingSource
{
public:
    TypingSource();
    TypingSource(const QString& fileName, qsizetype startPos = 0);
    void open(const QString& fileName, qsizetype startPos = 0);

    void nextChar();
    QChar peekChar();

    QString next();
    QString prev();

    bool seek(qsizetype pos) noexcept;
    qsizetype pos() const noexcept;

    qsizetype bufferSize() const noexcept;
    qsizetype visibleTextSize() const noexcept;

    bool atEnd() const;

private:
    QTextStream mTxt;
    QFile mFile;
    QString mBuffer;
    qsizetype mBufferSize = 128;
    qsizetype mVisibleTextSize = 32;
    qsizetype mCurrent = 0;
};

#endif // TYPINGSOURCE_HPP
