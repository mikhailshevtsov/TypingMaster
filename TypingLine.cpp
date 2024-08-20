#include "TypingLine.hpp"

#include <QPainter>

TypingLine::TypingLine(QWidget* parent)
    : QFrame(parent)
{}

void TypingLine::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // paint rect
    painter.setPen(Qt::NoPen);
    QLinearGradient gradient(rect().topLeft(), rect().topRight());
    gradient.setColorAt(0.0, Qt::lightGray);
    gradient.setColorAt(0.49999, Qt::lightGray);
    gradient.setColorAt(0.50001, "#E2E0D1");
    painter.setBrush(gradient);
    painter.drawRoundedRect(rect(), 30, 30);

    QRectF leftRect = rect();
    leftRect.setRight(rect().center().x());

    QRectF rightRect = rect();
    rightRect.setLeft(rect().center().x() * 1.01);

    // setup font for painting text
    QFont font;
    font.setPixelSize(rect().height() * 0.6);
    font.setFamily("Comic Sans MS");
    font.setLetterSpacing(QFont::PercentageSpacing, 105);
    painter.setFont(font);
    QTextOption op;

    // paint left rect and text
    op.setAlignment(Qt::AlignRight | Qt::AlignTop);
    op.setWrapMode(QTextOption::NoWrap);
    painter.setPen(QPen(Qt::darkGray));
    painter.drawText(leftRect, mLeftText, op);

    // paint right rect and text
    op.setAlignment(Qt::AlignLeft | Qt::AlignTop);
    op.setWrapMode(QTextOption::NoWrap);
    painter.setPen(QPen("#3A3023"));
    painter.drawText(rightRect, mRightText, op);

    // setup pen for painting main rect
    QPen pen("#3A3023");
    pen.setWidth(15);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawRoundedRect(rect(), 30, 30);
}

void TypingLine::setTypingText(const QString& left, const QString& right)
{
    mLeftText = left;
    mRightText = right;
    repaint();
}
