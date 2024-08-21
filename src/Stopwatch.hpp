#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <QLabel>
#include <QTime>
class QTimer;

class Stopwatch : public QLabel
{
    Q_OBJECT

public:
    Stopwatch(QWidget* parent = nullptr);

    bool isActive() const;
    const QTime& ellapsedTime() const;

public slots:
    void start();
    void stop();
    void reset();

private slots:
    void displayEllapsedTime();

private:
    QTime mEllapsedTime = QTime(0, 0, 0);
    QTimer* mTimer;
};

#endif // STOPWATCH_HPP
