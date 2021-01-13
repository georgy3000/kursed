#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "okno.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    okno *window;
    void ui_lock(bool to_lock);

private slots:
    void on_btn_parsemap_clicked();
    void on_action_5_triggered();
    void on_action_10_triggered();
    void on_action_12_triggered();
    //void on_pte_mapinput_blockCountChanged(int newBlockCount);
};
#endif // MAINWINDOW_H
