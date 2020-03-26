#ifndef EVENTWINDOW_H
#define EVENTWINDOW_H

#include <QDialog>
#include "event.h"

namespace Ui {
class EventWindow;
}

class EventWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EventWindow(const QDate& date, QWidget *parent = nullptr);
    explicit EventWindow(const Event& event, QWidget *parent = nullptr);
    ~EventWindow();

    void accept() override;
private:
    bool edit;
    Event old_event;
    Ui::EventWindow *ui;
};

#endif // EVENTWINDOW_H
