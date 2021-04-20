#include "custom.h"
#include<QtWidgets>
#include<qdebug.h>
#include<math.h>
#include <armadillo>

Custom::Custom( QWidget * parent)
{
    //initArr();
    initTableWidget();

    calculationBtn = new QPushButton(QStringLiteral("重新计算"),this);
    connect(calculationBtn,&QPushButton::clicked,this,&Custom::calculation);
    QVBoxLayout * Vlayout = new QVBoxLayout(this);
    Vlayout->addWidget(calculationBtn);
    Vlayout->addWidget(tableWidget);
    setLayout(Vlayout);

    QString str = QString::fromStdString(arma::arma_version::as_string());
    qDebug()<<str;

}

void Custom::initTableWidget(){

    tableWidget = new QTableWidget(6,7,this);



    QStringList HHeadList;
    HHeadList<<"A(%)"<<"B(%)"<<"C(%)"<<"D(%)"<<"E(%)"<<"F(%)"<<QStringLiteral("重量(g)");
    tableWidget->setHorizontalHeaderLabels(HHeadList);

    QStringList VHeadList;
    VHeadList<<"1#"<<"2#"<<"3#"<<"4#"<<"5#"<<QStringLiteral("混合后元素含量");
    tableWidget->setVerticalHeaderLabels(VHeadList);

    for( int i = 0 ; i < tableWidget->rowCount() ; i ++){

        for( int j = 0 ; j < tableWidget->columnCount() ;j++){

            tableWidget->setItem(i,j,new QTableWidgetItem("0"));

        }

    }

    tableWidget->setItem(tableWidget->rowCount()-1,tableWidget->columnCount()-1,new QTableWidgetItem("1000"));
    tableWidget->show();
    connect(tableWidget,&QTableWidget::itemChanged,this,&Custom::tableItemChanged);

}

int Custom::calculation(){

    arma::mat A1(4,3,arma::fill::zeros);
    arma::vec B1(4,arma::fill::zeros);
    arma::vec X1;

    A1 = {
            {5,4,-4},
            {-4,-3,5},
            {-1,-1,-1},
            {-8,-7,1}
         };
    B1 = {4,-5,1,-1};
    solve(X1, A1, B1);
    A1.print("A1:");
    B1.print("B1:");
    X1.print("X1:");

    return 0;

    qDebug()<<QStringLiteral("点击重新计算按钮");


    arma::mat A(tableWidget->columnCount()-1,tableWidget->rowCount()-1,arma::fill::zeros);
    arma::vec B(tableWidget->columnCount()-1,arma::fill::zeros);
    arma::vec X(tableWidget->rowCount()-1,arma::fill::zeros);

    for( int i = 0 ; i < tableWidget->columnCount()-1; i ++){ //按列顺序优先遍历

        for( int j = 0 ; j < tableWidget->rowCount()-1 ;j++){

            if(tableWidget->item(j,i)!=nullptr){


                QString str = tableWidget->item(j,i)->text();
                double w = str.toDouble();
                A(i,j) = w;

            }

        }

    }

    double a1[10] = {0};

    for(int i = 0 ;  i < tableWidget->columnCount()-1; i++){

        if(tableWidget->item(tableWidget->rowCount()-1,i)!=nullptr){

            QString str = tableWidget->item(tableWidget->rowCount()-1,i)->text();
            double w = str.toDouble();
            B[i] = 1000*w;

        }

    }

    bool status = solve(X, A, B);
    A.print("A:");
    B.print("B:");
    if( status ){

        for(int i = 0 ; i < tableWidget->columnCount()-1;i++){
            qDebug()<<X[i];
        }


    }else{
        QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("无解"),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }




    /*int a1[10] = {0};

    for(int i = 0 ;  i < tableWidget->columnCount()-1; i++){

        if(tableWidget->item(tableWidget->rowCount()-1,i)!=nullptr){

            QString str = tableWidget->item(tableWidget->rowCount()-1,i)->text();
            int w = str.toInt();
            a1[i] = (1000*w)/100;

        }

    }

    for( int i = 0 ; i < tableWidget->columnCount()-1; i ++){ //按列顺序优先遍历

        for( int j = 0 ; j < tableWidget->rowCount()-1 ;j++){

            if(tableWidget->item(j,i)!=nullptr){



//                if(j==tableWidget->columnCount()-1){

//                    a[i][j] = a1[i];

//                }else{

//                    QString str = tableWidget->item(i,j)->text();
//                    int w = str.toInt();
//                    a[i][j] = w;

//                }
                QString str = tableWidget->item(j,i)->text();
                int w = str.toInt();
                a[i][j] = w;

                //qDebug()<<a[i][j];
            }

        }


    }

    for( int i = 0 ; i < 10 ; i ++){

        int len = tableWidget->columnCount()-1;
        a[len][i] = a1[i];

    }



    for( int i = 0 ; i < 10 ; i ++){

        for( int j = 0; j < 10 ; j++){
            qDebug()<<a[i][j];
        }

    }

    int var = tableWidget->rowCount()-1; //未知数个数
    int free_num = Gauss(tableWidget->columnCount()-1,var);
    if (free_num == -1) {

        QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("无解"),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    }
    else if (free_num == -2){

        QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("有浮点解,无整数解"),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    }
    else if (free_num > 0)
    {
//        printf("无穷多解! 自由变元个数为%d\n", free_num);
//        for (i = 0; i < var; i++)
//        {
//            if (free_x[i]) printf("x%d 是不确定的\n", i + 1);
//            else printf("x%d: %d\n", i + 1, x[i]);
//        }
        QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("无穷多解！"),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    else
    {
        for (int i = 0; i < var; i++)
        {
            printf("x%d: %d\n", i + 1, x[i]);
        }
    }*/

    return -1;
}

void Custom::tableItemChanged( QTableWidgetItem * item){

    qDebug()<<QStringLiteral("单元格改变");

}


int Custom::initArr(){

    for( int i = 0 ;  i < 10 ; i ++){
        for( int j = 0;j<10;j++){
            a[i][j] = 0;
        }
    }
    return 0;
}

int Custom::gcd(int a,int b)
{
    int t;
    while(b!=0)
    {
        t=b;
        b=a%b;
        a=t;
    }
    return a;
}

int Custom::lcm(int a,int b)
{
    return a/gcd(a,b)*b;//先除后乘防溢出
}

// 高斯消元法解方程组(Gauss-Jordan elimination).(-2表示有浮点数解，但无整数解，
//-1表示无解，0表示唯一解，大于0表示无穷解，并返回自由变元的个数)
//有equ个方程，var个变元。增广矩阵行数为equ,分别为0到equ-1,列数为var+1,分别为0到var.
int Custom::Gauss(int equ,int var)
{
    int i,j,k;
    int max_r;// 当前这列绝对值最大的行.
    int col;//当前处理的列
    int ta,tb;
    int LCM;
    int temp;
    int free_x_num;
    int free_index;

    for(int i=0; i<=var; i++)
    {
        x[i]=0;
        free_x[i]=true;
    }

    //转换为阶梯阵.
    col=0; // 当前处理的列
    for(k = 0; k < equ && col < var; k++,col++)
    {
        // 枚举当前处理的行.
// 找到该col列元素绝对值最大的那行与第k行交换.(为了在除法时减小误差)
        max_r=k;
        for(i=k+1; i<equ; i++)
        {
            if(abs(a[i][col])>abs(a[max_r][col])) max_r=i;
        }
        if(max_r!=k)
        {
            // 与第k行交换.
            for(j=k; j<var+1; j++) std::swap(a[k][j],a[max_r][j]);
        }
        if(a[k][col]==0)
        {
            // 说明该col列第k行以下全是0了，则处理当前行的下一列.
            k--;
            continue;
        }
        for(i=k+1; i<equ; i++)
        {
            // 枚举要删去的行.
            if(a[i][col]!=0)
            {
                LCM = lcm(abs(a[i][col]),abs(a[k][col]));
                ta = LCM/abs(a[i][col]);
                tb = LCM/abs(a[k][col]);
                if(a[i][col]*a[k][col]<0)tb=-tb;//异号的情况是相加
                for(j=col; j<var+1; j++)
                {
                    a[i][j] = a[i][j]*ta-a[k][j]*tb;
                }
            }
        }
    }

    //  Debug();

    // 1. 无解的情况: 化简的增广阵中存在(0, 0, ..., a)这样的行(a != 0).
    for (i = k; i < equ; i++)
    {
        // 对于无穷解来说，如果要判断哪些是自由变元，那么初等行变换中的交换就会影响，则要记录交换.
        if (a[i][col] != 0) return -1;
    }
    // 2. 无穷解的情况: 在var * (var + 1)的增广阵中出现(0, 0, ..., 0)这样的行，即说明没有形成严格的上三角阵.
    // 且出现的行数即为自由变元的个数.
    if (k < var)
    {
        // 首先，自由变元有var - k个，即不确定的变元至少有var - k个.
        for (i = k - 1; i >= 0; i--)
        {
            // 第i行一定不会是(0, 0, ..., 0)的情况，因为这样的行是在第k行到第equ行.
            // 同样，第i行一定不会是(0, 0, ..., a), a != 0的情况，这样的无解的.
            free_x_num = 0; // 用于判断该行中的不确定的变元的个数，如果超过1个，则无法求解，它们仍然为不确定的变元.
            for (j = 0; j < var; j++)
            {
                if (a[i][j] != 0 && free_x[j]) free_x_num++, free_index = j;
            }
            if (free_x_num > 1) continue; // 无法求解出确定的变元.
            // 说明就只有一个不确定的变元free_index，那么可以求解出该变元，且该变元是确定的.
            temp = a[i][var];
            for (j = 0; j < var; j++)
            {
                if (a[i][j] != 0 && j != free_index) temp -= a[i][j] * x[j];
            }
            x[free_index] = temp / a[i][free_index]; // 求出该变元.
            free_x[free_index] = 0; // 该变元是确定的.
        }
        return var - k; // 自由变元有var - k个.
    }
    // 3. 唯一解的情况: 在var * (var + 1)的增广阵中形成严格的上三角阵.
    // 计算出Xn-1, Xn-2 ... X0.
    for (i = var - 1; i >= 0; i--)
    {
        temp = a[i][var];
        for (j = i + 1; j < var; j++)
        {
            if (a[i][j] != 0) temp -= a[i][j] * x[j];
        }
        if (temp % a[i][i] != 0) return -2; // 说明有浮点数解，但无整数解.
        x[i] = temp / a[i][i];
    }
    return 0;
}
