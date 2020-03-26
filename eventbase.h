#ifndef EVENTBASE_H
#define EVENTBASE_H

#include <QObject>
#include <QDate>
#include <QMap>
#include <QVector>
#include <event.h>

class EventBase: public QObject
{
    Q_OBJECT

public:
    class EventBaseException : public QException {};

    static EventBase& GetInstance()
    {
        static EventBase instance;
        return instance;
    }

    int count(const QDate& date) const noexcept;
    void add(const QDate& date, const Event& event);
    void remove(const QDate& date, const Event& event);
    const QVector<Event>* getEvents(const QDate& date);

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

#define EventDB EventBase::GetInstance()

#endif // EVENTBASE_H
