#ifndef EVENT_H
#define EVENT_H

#include <QDate>
#include <QTime>
#include <QString>
#include <QPair>
#include <QException>
#include <QJsonObject>

class Event
{
public:
    // Exception for invalid arguments
    class EventException : public QException {};

    // Constructors
    Event() = default;
    Event(const QDate& date): _date(date), _time({QTime(00,00), QTime(23,59)}), _title(""), _location("") {}
    Event(const QDate& date, const QTime& timeStart, const QTime& timeEnd, const QString title = "", const QString& location = "");
    Event(const QDate& date, const QPair<QTime, QTime>& time, const QString title = "", const QString& location = "") { Event(date, time.first, time.second, title, location); }

    // Copy Constructors and operator=
    Event(const Event& src) = default;
    Event(Event&& src) = default;

    Event& operator=(const Event& rhs) = default;
    Event& operator=(Event&& rhs) = default;

    // Comparison
    bool operator==(const Event& rhs) const noexcept;
    bool operator!=(const Event& rhs) const noexcept;

    // Destructor
    ~Event() = default;

    // Get
    const QDate& date() const noexcept { return _date; }
    QPair<QTime, QTime> time() const noexcept { return QPair<QTime, QTime>(_time.start, _time.end); }
    const QTime& timeStart() const noexcept { return _time.start; }
    const QTime& timeEnd() const noexcept { return _time.end; }
    const QString& title() const noexcept { return _title; }
    const QString& location() const noexcept { return _location; }

    // Set
    void date(const QDate& date) noexcept { _date = date; }
    void time(const QTime& timeStart, const QTime& timeEnd);
    void time(const QPair<QTime, QTime>& time) { return this->time(time.first, time.second); };
    void timeStart(const QTime& timeStart);
    void timeEnd(const QTime& timeEnd);
    void title(const QString& title) noexcept { _title = title; }
    void location(const QString& location) noexcept { _location = location; }

    // JSON read/write
    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;
private:
    QDate _date;
    struct time{
        QTime start;
        QTime end;
    }_time;
    QString _title;
    QString _location;
};

#endif // EVENT_H
