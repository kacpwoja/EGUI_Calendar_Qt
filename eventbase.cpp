#include "eventbase.h"
#include <QDate>
#include <QMap>
#include <QVector>
#include <event.h>

EventBase::~EventBase()
{
    QVector<Event>* vec;
    foreach (vec, base)
        delete vec;
}

int EventBase::count(const QDate& date) const noexcept
{
    auto it = base.find(date);

    if(it == base.end())
        return 0;

    return it.value()->length();
}

void EventBase::add(const Event& event)
{
    auto it = base.find(event.date());

    if(it == base.end())
    {
        it = base.insert(event.date(), new QVector<Event>);
    }

    it.value()->append(event);

    std::sort(it.value()->begin(), it.value()->end(), [](const Event& a, const Event& b) { return a.timeStart() < b.timeStart();} );

    emit baseUpdated();
}

void EventBase::remove(const Event& event)
{
    auto it = base.find(event.date());

    if(it == base.end())
    {
        throw EventBaseException();
    }

    it.value()->removeOne(event);

    if(it.value()->empty())
    {
        delete it.value();
        base.remove(event.date());
    }

    emit baseUpdated();
}

const QVector<Event>* EventBase::getEvents(const QDate& date)
{
    auto it = base.find(date);

    if(it == base.end())
        return Q_NULLPTR;

    return it.value();
}
