#ifndef DAYWINDOW_H
#define DAYWINDOW_H

#include <QDialog>

namespace Ui {
class DayWindow;
}

class DayWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DayWindow(QWidget *parent = nullptr);
    ~DayWindow();

private:
    Ui::DayWindow *ui;
};

#endif // DAYWINDOW_H
