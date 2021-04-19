#ifndef CUSTOM_H
#define CUSTOM_H

#include "QTableWidget"

class QWidget;
class QPushButton;

class Custom: public QWidget
{
    Q_OBJECT
public:
    Custom( QWidget * parent = nullptr);

private:

    void initTableWidget();

    QTableWidget* tableWidget;
    QPushButton* calculationBtn;

    int a[10][10];//增广矩阵
    int initArr();
    int x[10];//解集
    bool free_x[10];//标记是否是不确定的变元

    int gcd(int a,int b);
    int lcm(int a,int b);
    int Gauss(int equ,int var);

public slots:
    int calculation();
    void tableItemChanged(QTableWidgetItem * item);
};

#endif // CUSTOM_H
