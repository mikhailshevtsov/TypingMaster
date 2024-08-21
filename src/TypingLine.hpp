#ifndef TYPINGLINE_HPP
#define TYPINGLINE_HPP

#include <QFrame>

class TypingLine : public QFrame
{
    Q_OBJECT

public:
    TypingLine(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event) override;

public slots:
    void setTypingText(const QString& left, const QString& right);

private:
    QString mLeftText;
    QString mRightText;
};

#endif // TYPINGLINE_HPP
