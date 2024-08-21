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

    QString next() const;
    QString prev() const;

    bool seek(qsizetype pos) noexcept;
    qsizetype pos() const noexcept;

    const QString& buffer() const noexcept;

    bool atEnd() const;

private:
    QTextStream mTxt;
    QFile mFile;
    QString mBuffer;
    qsizetype mVisibleTextSize = 32;
    qsizetype mCurrent = 0;
};

#endif // TYPINGSOURCE_HPP
