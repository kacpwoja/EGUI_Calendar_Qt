#ifndef EVENTBASE_H
#define EVENTBASE_H

#include <QObject>
#include <QDate>
#include <QMap>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include "event.h"

class EventBase: public QObject
{
    Q_OBJECT

public:
    class EventBaseException : public QException {};

    // Singleton implementation using C++11 magic static
    static EventBase& GetInstance()
    {
        static EventBase instance;
        return instance;
    }

    // All methods needed for the calendar program
    int count(const QDate& date) const noexcept;
    void add(const Event& event);
    void remove(const Event& event);
    const QVector<Event>* getEvents(const QDate& date);
    void clear();

    // JSON read/write
    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

signals:
    void baseUpdated();

private:
    EventBase() = default;
    EventBase(const EventBase& src) = delete;
    EventBase( EventBase&& src) = delete;
    EventBase& operator=(const EventBase& src) = delete;
    EventBase& operator=(EventBase&& src) = delete;
    ~EventBase();

    QMap<QDate, QVector<Event>*> base;
};

// For easier and cleaner usage
#define EventDB EventBase::GetInstance()

#endif // EVENTBASE_H
