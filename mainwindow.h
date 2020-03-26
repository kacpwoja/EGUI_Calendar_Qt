#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMultiMap>
#include <event.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QMultiMap<QDate, Event>* eventList;
private:
    Ui::MainWindow *ui;
    QDate test;
    void testfun();
private slots:
    void selectToday();
    void updateTopText();
    void viewDay(const QDate& date);
};
#endif // MAINWINDOW_H
