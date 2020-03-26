#ifndef EVENTWINDOW_H
#define EVENTWINDOW_H

#include <QDialog>

namespace Ui {
class EventWindow;
}

class EventWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EventWindow(const QDate& date, QWidget *parent = nullptr);
    ~EventWindow();

    void accept() override;
private:
    Ui::EventWindow *ui;
};

#endif // EVENTWINDOW_H
