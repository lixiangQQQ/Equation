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
public slots:
    int calculation();
};

#endif // CUSTOM_H
