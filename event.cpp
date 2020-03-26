#include "event.h"

Event::Event(const QDate& date, const QTime& timeStart, const QTime& timeEnd, const QString title, const QString& location)
{
    if(timeStart >= timeEnd)
        throw EventException();

    _date = date;
    _time.start = timeStart;
    _time.end = timeEnd;
    _title = title;
    _location = location;
}

bool Event::operator==(const Event &rhs) const noexcept
{
    return !(*this!=rhs);
}

bool Event::operator!=(const Event &rhs) const noexcept
{
    if(_date != rhs._date)
        return true;

    if(_time.start != rhs._time.start)
        return true;

    if(_time.end != rhs._time.end)
        return true;

    if(_title != rhs._title)
        return true;

    if(_location != rhs._location)
        return true;

    return false;
}

void Event::time(const QTime& timeStart, const QTime& timeEnd)
{
    if(timeStart >= timeEnd)
        throw EventException();

    _time.start = timeStart;
    _time.end = timeEnd;
}
void Event::timeStart(const QTime& timeStart)
{
    if(timeStart >= _time.end)
        throw EventException();

    _time.start = timeStart;

}
void Event::timeEnd(const QTime& timeEnd)
{
    if(_time.start >= timeEnd)
        throw EventException();

    _time.end = timeEnd;
}

void Event::read(const QJsonObject& json)
{
    _date = QDate::fromString(json["date"].toString(), "ddMMyyyy");
    _time.start = QTime::fromString(json["timeStart"].toString(), "hhmm");
    _time.end = QTime::fromString(json["timeEnd"].toString(), "hhmm");
    _title = json["title"].toString();
    _location = json["location"].toString();
}

void Event::write(QJsonObject& json) const
{
    json["date"] =_date.toString("ddMMyyyy");
    json["timeStart"] = _time.start.toString("hhmm");
    json["timeEnd"] = _time.end.toString("hhmm");
    json["title"] = _title;
    json["location"] = _location;
}
