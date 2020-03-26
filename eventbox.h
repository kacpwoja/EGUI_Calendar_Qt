#ifndef EVENTBOX_H
#define EVENTBOX_H

#include <QWidget>
#include "event.h"

namespace Ui {
class EventBox;
}

class EventBox : public QWidget
{
    Q_OBJECT

public:
    explicit EventBox(const Event& event, QWidget *parent = nullptr);
    ~EventBox();

    QSize sizeHint() const;

private:
    Ui::EventBox *ui;
    Event _event;

private slots:
    void editEvent();
    void removeEvent();
};

#endif // EVENTBOX_H
