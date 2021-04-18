#include "custom.h"
#include<QtWidgets>
#include<QDebug>

Custom::Custom( QWidget * parent)
{

    initTableWidget();

    calculationBtn = new QPushButton(QStringLiteral("重新计算"),this);
    connect(calculationBtn,&QPushButton::clicked,this,&Custom::calculation);
    QVBoxLayout * Vlayout = new QVBoxLayout(this);
    Vlayout->addWidget(calculationBtn);
    Vlayout->addWidget(tableWidget);
    setLayout(Vlayout);

}

void Custom::initTableWidget(){

    tableWidget = new QTableWidget(6,7,this);

    QStringList HHeadList;
    HHeadList<<"A"<<"B"<<"C"<<"D"<<"E"<<"F"<<QStringLiteral("重量(g)");
    tableWidget->setHorizontalHeaderLabels(HHeadList);

    QStringList VHeadList;
    VHeadList<<"1#"<<"2#"<<"3#"<<"4#"<<"5#"<<QStringLiteral("混合后元素含量");
    tableWidget->setVerticalHeaderLabels(VHeadList);

    for( int i = 0 ; i < tableWidget->rowCount()-1 ; i ++){

        for( int j = 0 ; j < tableWidget->columnCount()-1 ;j++){

            tableWidget->setItem(i,j,new QTableWidgetItem("0"));

        }

    }

    tableWidget->setItem(tableWidget->rowCount()-1,tableWidget->columnCount()-1,new QTableWidgetItem("1000"));

    tableWidget->show();
}

int Custom::calculation(){

    //qDebug<<"1";
    return -1;
}

