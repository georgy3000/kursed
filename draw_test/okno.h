#ifndef OKNO_H
#define OKNO_H

#include <QDialog>
#include <QFile>
#include <QTextStream>

namespace Ui {
class okno;
}

class okno : public QDialog
{
    Q_OBJECT

public:
    explicit okno(QWidget *parent = nullptr);
    ~okno();

private slots:
    void on_pushButton_clicked();

private:
    Ui::okno *ui;
};

#endif // OKNO_H
