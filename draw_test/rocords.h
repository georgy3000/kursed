#ifndef ROCORDS_H
#define ROCORDS_H
#include <QString>


class rocords
{
    QString _NN;
    int _LL;
    int _SS;

public:
    rocords();
    rocords(QString n,int l,int s){
        _NN=n; //имя файла
        _LL=l; //номер уровня
        _SS=s; //счёт
    }

    QString NN();
    int LL();
    int SS();

};

#endif
