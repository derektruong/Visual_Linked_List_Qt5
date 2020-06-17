#include "main_widget.h"
#include "ui_main_widget.h"
#include "list.h"
#include<QLabel>
#include<QPixmap>
#include<QDir>
#include<QMenu>
#include<QPoint>
#include<QMouseEvent>
#include<math.h>
#include<iostream>
#include<windows.h>
#define MAX 100

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //Khởi tạo node mang bản chất label
    for(int i=0;i<MAX;++i){
        QLabel *newnode=new QLabel(this);
        node.insert(i,newnode);
    }
    //Khởi tạo arrow mang bản chất label
    for(int i=0;i<MAX;++i){
        QLabel *newarr=new QLabel(this);
        arr.insert(i,newarr);
    }
    //Mảng value lưu các giá trị label tại thời điểm xác định
    //Xác định số lượng label hiện tại
    sizeNode=0;
    ui->spinBox_random->setMaximum(50);
    ui->spinBox_insert_first->setMinimum(-99);
    ui->spinBox1_insert_mid->setMinimum(-99);
    ui->spinBox_insert_tail->setMinimum(-99);
    ui->spinBox_search->setMinimum(-99);
    ui->spinBox_replace_bypos_2->setMinimum(-99);
    ui->spinBox_replace_byvalue_1->setMinimum(-99);
    ui->spinBox_replace_byvalue_2->setMinimum(-99);
}

Widget::~Widget()
{
    for(int i=0;i<MAX;++i){
        node.remove(i);
        arr.remove(i);
        value.remove(i);
    }
    delete ui;
}

//Hàm xử lý tạo node(quan trọng)
QLabel* Widget::setNode(int pos,int num){
    QLabel *nodenew=new QLabel(this);
    QFont f( "Arial", 14, QFont::Bold);
    nodenew->setFont(f);
    nodenew->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:0.299, y1:0, x2:1, y2:0, stop:0 rgba(205, 86, 121, 255), stop:1 rgba(46, 214, 51, 255));border-style: outset;border-radius:20px;");
    QString s= QString::number(num);
    QString s1= QString::number(pos);
    //Here is how to change position:
    //Trường hợp tạo *pTail
    if(pos==sizeNode-1 && pos!=0){
        //Hàng 1
        if(pos<9){
            nodenew->setToolTip("Position: "+s1);
            nodenew->setText((s+"    *pTail"));
            nodenew->setGeometry(QRect(170+(pos-1)*150,35,100,55));//170+(pos-1)*150,80,100,55
        }
        //Hàng 2
        else if(pos>=9 && pos<18) {
            nodenew->setToolTip("Position: "+s1);
            nodenew->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:0.639955, y1:0.386, x2:0, y2:0.386, stop:0 rgba(205, 86, 121, 255), stop:1 rgba(46, 214, 51, 255));border-style: outset;border-radius:20px");
            //nodenew->setText((" "+s+"   *pTail"));
            nodenew->setText(" *pTail   "+s);
            nodenew->setGeometry(QRect(1370-(pos-8)*150,135,100,55));//1370-(pos-8)*150,180,100,55
        }
        //Hàng 3
        else if(pos>=18 && pos<27) {
            nodenew->setToolTip("Position: "+s1);
            nodenew->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:0.299, y1:0, x2:1, y2:0, stop:0 rgba(205, 86, 121, 255), stop:1 rgba(46, 214, 51, 255));border-style: outset;border-radius:20px;");
            //nodenew->setText((" "+s+"   *pTail"));
            nodenew->setText(s+"    *pTail");
            nodenew->setGeometry(QRect(20+(pos-18)*150,235,100,55));//1370-(pos-8)*150,180,100,55
        }
        //Hàng 4
        else if(pos>=27 && pos<35) {
            nodenew->setToolTip("Position: "+s1);
            nodenew->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:0.639955, y1:0.386, x2:0, y2:0.386, stop:0 rgba(205, 86, 121, 255), stop:1 rgba(46, 214, 51, 255));border-style: outset;border-radius:20px");
            //nodenew->setText((" "+s+"   *pTail"));
            nodenew->setText(" *pTail   "+s);
            if (pos==27) nodenew->setGeometry(QRect(1370-(pos-26)*150,335,100,55));
            else nodenew->setGeometry(QRect(1370-(pos-26)*140,335,100,55));
        }
        //Hàng 5
        else if(pos>=35 && pos<43) {
            nodenew->setToolTip("Position: "+s1);
            nodenew->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:0.299, y1:0, x2:1, y2:0, stop:0 rgba(205, 86, 121, 255), stop:1 rgba(46, 214, 51, 255));border-style: outset;border-radius:20px;");
            //nodenew->setText((" "+s+"   *pTail"));
            nodenew->setText(s+"    *pTail");
            nodenew->setGeometry(QRect(250+(pos-35)*140,435,100,55));
        }
        //Hàng 6
        else if(pos>=43 && pos<51) {
            nodenew->setToolTip("Position: "+s1);
            nodenew->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:0.639955, y1:0.386, x2:0, y2:0.386, stop:0 rgba(205, 86, 121, 255), stop:1 rgba(46, 214, 51, 255));border-style: outset;border-radius:20px");
            //nodenew->setText((" "+s+"   *pTail"));
            nodenew->setText(" *pTail   "+s);
            if (pos==43) nodenew->setGeometry(QRect(1370-(pos-42)*150,535,100,55));
            else nodenew->setGeometry(QRect(1370-(pos-42)*140,535,100,55));
        }
    }
    //Trường hợp tạo *pHead
    if(pos==0){
        nodenew->setToolTip("Position: "+s1);
        nodenew->setText((s+"  *pHead"));
        nodenew->setAlignment(Qt::AlignCenter);
        nodenew->setGeometry(QRect(20,35,100,55));//20,80,100,55
        ///

    }
    //Trường hợp tạo node NULL
    if (pos==sizeNode) {
        //Hàng 1
        if(pos<9){
            nodenew->setText("NULL");
            nodenew->setAlignment(Qt::AlignCenter);
            nodenew->setStyleSheet("background-color: rgb(255, 199, 107);border-style: outset;border-radius:20px");
            QRect r(node.pos(sizeNode-1)->geometry());
            nodenew->setGeometry(r.x()+150,r.y(),r.width(),r.height());
        }
        else if(pos==9) {
            nodenew->setText("NULL");
            nodenew->setAlignment(Qt::AlignCenter);
            nodenew->setStyleSheet("background-color: rgb(255, 199, 107);border-style: outset;border-radius:20px");
            QRect r(node.pos(sizeNode-1)->geometry());
            nodenew->setGeometry(r.x(),r.y()+100,r.width(),r.height());
        }
        //Hàng 2
        else if(pos>9 && pos<18) {
            nodenew->setText("NULL");
            nodenew->setAlignment(Qt::AlignCenter);
            nodenew->setStyleSheet("background-color: rgb(255, 199, 107);border-style: outset;border-radius:20px");
            QRect r(node.pos(sizeNode-1)->geometry());
            nodenew->setGeometry(r.x()-150,r.y(),r.width(),r.height());
        }
        else if(pos==18) {
            nodenew->setText("NULL");
            nodenew->setAlignment(Qt::AlignCenter);
            nodenew->setStyleSheet("background-color: rgb(255, 199, 107);border-style: outset;border-radius:20px");
            QRect r(node.pos(sizeNode-1)->geometry());
            nodenew->setGeometry(r.x(),r.y()+100,r.width(),r.height());
        }
        //Hàng 3
        else if(pos>18&&pos<27) {
            nodenew->setText("NULL");
            nodenew->setAlignment(Qt::AlignCenter);
            nodenew->setStyleSheet("background-color: rgb(255, 199, 107);border-style: outset;border-radius:20px");
            QRect r(node.pos(sizeNode-1)->geometry());
            nodenew->setGeometry(r.x()+150,r.y(),r.width(),r.height());
        }
        else if(pos==27) {
            nodenew->setText("NULL");
            nodenew->setAlignment(Qt::AlignCenter);
            nodenew->setStyleSheet("background-color: rgb(255, 199, 107);border-style: outset;border-radius:20px");
            QRect r(node.pos(sizeNode-1)->geometry());
            nodenew->setGeometry(r.x(),r.y()+100,r.width(),r.height());
        }
        //Hàng 4
        else if(pos>27&&pos<35) {
            nodenew->setText("NULL");
            nodenew->setAlignment(Qt::AlignCenter);
            nodenew->setStyleSheet("background-color: rgb(255, 199, 107);border-style: outset;border-radius:20px");
            QRect r(node.pos(sizeNode-1)->geometry());
            nodenew->setGeometry(r.x()-140,r.y(),r.width(),r.height());
        }
        else if(pos==35) {
            nodenew->setText("NULL");
            nodenew->setAlignment(Qt::AlignCenter);
            nodenew->setStyleSheet("background-color: rgb(255, 199, 107);border-style: outset;border-radius:20px");
            QRect r(node.pos(sizeNode-1)->geometry());
            nodenew->setGeometry(r.x(),r.y()+100,r.width(),r.height());
        }
        //Hàng 5
        else if(pos>35&&pos<43) {
            nodenew->setText("NULL");
            nodenew->setAlignment(Qt::AlignCenter);
            nodenew->setStyleSheet("background-color: rgb(255, 199, 107);border-style: outset;border-radius:20px");
            QRect r(node.pos(sizeNode-1)->geometry());
            nodenew->setGeometry(r.x()+140,r.y(),r.width(),r.height());
        }
        else if(pos==43) {
            nodenew->setText("NULL");
            nodenew->setAlignment(Qt::AlignCenter);
            nodenew->setStyleSheet("background-color: rgb(255, 199, 107);border-style: outset;border-radius:20px");
            QRect r(node.pos(sizeNode-1)->geometry());
            nodenew->setGeometry(r.x(),r.y()+100,r.width(),r.height());
        }
        //Hàng 6
        else if(pos>43&&pos<51) {
            nodenew->setText("NULL");
            nodenew->setAlignment(Qt::AlignCenter);
            nodenew->setStyleSheet("background-color: rgb(255, 199, 107);border-style: outset;border-radius:20px");
            QRect r(node.pos(sizeNode-1)->geometry());
            nodenew->setGeometry(r.x()-140,r.y(),r.width(),r.height());
        }
        else if(pos==51) {
            nodenew->setText("NULL");
            nodenew->setAlignment(Qt::AlignCenter);
            nodenew->setStyleSheet("background-color: rgb(255, 199, 107);border-style: outset;border-radius:20px");
            QRect r(node.pos(sizeNode-1)->geometry());
            nodenew->setGeometry(r.x(),r.y()+100,r.width(),r.height());
        }
    }
    //Trường hợp tạo *pNext
    if (pos>0 && pos<sizeNode-1) {
        //Hàng 1
        if(pos<9){
            nodenew->setToolTip("Position: "+s1);
            if(num<0) nodenew->setText((s+"  *pNext"));
            else if(num>=0&&num<10) nodenew->setText((" "+s+"   *pNext"));
            else if(num>=10) nodenew->setText((" "+s+"  *pNext"));
            nodenew->setGeometry(QRect(170+(pos-1)*150,35,100,55));

        }
        //Hàng 2
        else if(pos>=9&&pos<18){
            nodenew->setToolTip("Position: "+s1);
            nodenew->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:0.639955, y1:0.386, x2:0, y2:0.386, stop:0 rgba(205, 86, 121, 255), stop:1 rgba(46, 214, 51, 255));border-style: outset;border-radius:20px");
            if(num<10) nodenew->setText(("*pNext  "+s));
            else if(num>=10) nodenew->setText(("*pNext   "+s));
            nodenew->setGeometry(QRect(1370-(pos-8)*150,135,100,55));//1370-(pos-8)*150,180,100,55
        }
        //Hàng 3
        else if(pos>=18&&pos<27){
            nodenew->setToolTip("Position: "+s1);
            nodenew->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:0.299, y1:0, x2:1, y2:0, stop:0 rgba(205, 86, 121, 255), stop:1 rgba(46, 214, 51, 255));border-style: outset;border-radius:20px;");
            if(num<0) nodenew->setText((s+"  *pNext"));
            else if(num>=0&&num<10) nodenew->setText((" "+s+"   *pNext"));
            else if(num>=10) nodenew->setText((" "+s+"  *pNext"));
            nodenew->setGeometry(QRect(20+(pos-18)*150,235,100,55));//1370-(pos-8)*150,180,100,55
        }
        //Hàng 4
        else if(pos>=27&&pos<35){
            nodenew->setToolTip("Position: "+s1);
            nodenew->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:0.639955, y1:0.386, x2:0, y2:0.386, stop:0 rgba(205, 86, 121, 255), stop:1 rgba(46, 214, 51, 255));border-style: outset;border-radius:20px");
            if(num<10) nodenew->setText(("*pNext  "+s));
            else if(num>=10) nodenew->setText(("*pNext   "+s));
            if (pos==27) nodenew->setGeometry(QRect(1370-150,335,100,55));
            else nodenew->setGeometry(QRect(1370-(pos-26)*140,335,100,55));
        }
        //Hàng 5
        else if(pos>=35&&pos<43){
            nodenew->setToolTip("Position: "+s1);
            nodenew->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:0.299, y1:0, x2:1, y2:0, stop:0 rgba(205, 86, 121, 255), stop:1 rgba(46, 214, 51, 255));border-style: outset;border-radius:20px;");
            if(num<0) nodenew->setText((s+"  *pNext"));
            else if(num>=0&&num<10) nodenew->setText((" "+s+"   *pNext"));
            else if(num>=10) nodenew->setText((" "+s+"  *pNext"));
            nodenew->setGeometry(QRect(250+(pos-35)*140,435,100,55));
        }
        //Hàng 6
        else if(pos>=43&&pos<51){
            nodenew->setToolTip("Position: "+s1);
            nodenew->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:0.639955, y1:0.386, x2:0, y2:0.386, stop:0 rgba(205, 86, 121, 255), stop:1 rgba(46, 214, 51, 255));border-style: outset;border-radius:20px");
            if(num<10) nodenew->setText(("*pNext  "+s));
            else if(num>=10) nodenew->setText(("*pNext   "+s));
            if (pos==43) nodenew->setGeometry(QRect(1370-150,535,100,55));
            else nodenew->setGeometry(QRect(1370-(pos-42)*140,535,100,55));
        }
    }
    // myWidget is any QWidget-derived class
    nodenew->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(nodenew, SIGNAL(customContextMenuRequested(const QPoint&)),
       this, SLOT(ShowContextMenu()));
    //
    return  nodenew;
}

//Hàm xử lý tạo mũi tên(là label chứa file ảnh hình mũi tên)(quan trọng)
QLabel* Widget::arrow(int sn){
    // Draw the line itself
    QLabel *arrow=new QLabel(this);
    QString dir=QDir::currentPath();
    dir=dir.replace("\\","\\\\");
    QPixmap pixmap1(dir+"\\arrow.png");
    arrow->setPixmap(pixmap1.scaled(50,50,Qt::KeepAspectRatio));
    //Hàng 1
    if(sn==0){
        QRect r1(120,45,100,35);//120,90,100,35
        arrow->setGeometry(r1);
        arrow->lower();
    }
    else if(sn>0&&sn<=7) {
        QRect r2(270+150*(sn-1),45,100,35);//270+150*(sn-1),90,100,35
        arrow->setGeometry(r2);
        arrow->lower();
    }
    //Dọc 1
    else if(sn==8){
        QPixmap pixmap2(dir+"\\arrow1.png");
        arrow->setPixmap(pixmap2.scaled(20,60,Qt::KeepAspectRatio));
        QRect r3(1285,95,100,35);//1278,140,100,35
        arrow->setGeometry(r3);
        arrow->lower();
    }
    //Hàng 2
    else if(sn>8&&sn<=16) {
        QPixmap pixmap3(dir+"\\arrow2.png");
        arrow->setPixmap(pixmap3.scaled(50,50,Qt::KeepAspectRatio));
        QRect r4(1320-150*(sn-8),145,100,35);//1320-150*(sn-8),190,100,35
        arrow->setGeometry(r4);
        arrow->lower();
    }
    //Dọc 2
    else if(sn==17){
        QPixmap pixmap4(dir+"\\arrow1.png");
        arrow->setPixmap(pixmap4.scaled(20,60,Qt::KeepAspectRatio));
        QRect r4(35,195,100,35);//1278,140,100,35
        arrow->setGeometry(r4);
        arrow->lower();
    }
    //Hàng 3
    else if(sn>17&&sn<=25) {
        QPixmap pixmap5(dir+"\\arrow.png");
        arrow->setPixmap(pixmap5.scaled(50,50,Qt::KeepAspectRatio));
        QRect r5(-30+150*(sn-17),245,100,35);//1320-150*(sn-8),190,100,35
        arrow->setGeometry(r5);
        arrow->lower();
    }
    //Dọc 3
    else if(sn==26){
        QPixmap pixmap6(dir+"\\arrow1.png");
        arrow->setPixmap(pixmap6.scaled(20,60,Qt::KeepAspectRatio));
        QRect r6(1285,295,100,35);//1278,140,100,35
        arrow->setGeometry(r6);
        arrow->lower();
    }
    //Hàng 4
    else if(sn>26&&sn<=33) {
        QPixmap pixmap7(dir+"\\arrow2.png");
        arrow->setPixmap(pixmap7.scaled(40,50,Qt::KeepAspectRatio));
        QRect r7(1330-140*(sn-26),345,100,35);
        arrow->setGeometry(r7);
        arrow->lower();
    }
    //Dọc 4
    else if(sn==34){
        QPixmap pixmap8(dir+"\\arrow1.png");
        arrow->setPixmap(pixmap8.scaled(20,60,Qt::KeepAspectRatio));
        QRect r8(255,395,100,35);//1278,140,100,35
        arrow->setGeometry(r8);
        arrow->lower();
    }
    //Hàng 5
    else if(sn>34&&sn<=41) {
        QPixmap pixmap9(dir+"\\arrow.png");
        arrow->setPixmap(pixmap9.scaled(40,50,Qt::KeepAspectRatio));
        QRect r9(210+140*(sn-34),445,100,35);
        arrow->setGeometry(r9);
        arrow->lower();
    }
    //Dọc 5
    else if(sn==42){
        QPixmap pixmap10(dir+"\\arrow1.png");
        arrow->setPixmap(pixmap10.scaled(20,60,Qt::KeepAspectRatio));
        QRect r10(1285,495,100,35);//1278,140,100,35
        arrow->setGeometry(r10);
        arrow->lower();
    }
    //Hàng 6
    else if(sn>42&&sn<=59) {
        QPixmap pixmap11(dir+"\\arrow2.png");
        arrow->setPixmap(pixmap11.scaled(40,50,Qt::KeepAspectRatio));
        QRect r11(1330-140*(sn-42),545,100,35);
        arrow->setGeometry(r11);
        arrow->lower();
    }
    return arrow;
}

//Xử lí thêm vào đầu
void Widget::on_go_insert_first_clicked()
{
    int num;
    if(sizeNode==0){
        sizeNode++;

        num=ui->spinBox_insert_first->value();
        value.insert(0,num);
        for(int i=0;i<=sizeNode;i++){;
            if(i==sizeNode) node.replace(i,setNode(i,0));
            else node.replace(i,setNode(i,value.pos(i)));
            node.pos(i)->show();

            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            if(i<sizeNode){
                arr.replace(i,arrow(i));
                arr.pos(i)->show();
            }
        }
        ui->label->setText("Inserted!");
    }
    else if(sizeNode>0&&sizeNode<50){
        for(int i=0;i<=sizeNode+50;i++){
            node.pos(i)->hide();
            arr.pos(i)->hide();
        }
        num=ui->spinBox_insert_first->value();
        value.insert(0,num);
        sizeNode++;
        for(int i=0;i<=sizeNode;i++){
            //hiện label node
            if(i==sizeNode) node.replace(i,setNode(i,0));
            else node.replace(i,setNode(i,value.pos(i)));
                node.pos(i)->show();
            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            if(i<sizeNode){
                arr.replace(i,arrow(i));
                arr.pos(i)->show();
            }
        }
        ui->label->setText("Inserted!");
    }
    else if(sizeNode>=50){
        ui->label->setText("Sorry! Max size of list is 50 nodes!");
    }
}

//Xử lí thêm vào giữa
void Widget::on_go_insert_mid_clicked()
{
    int pos=ui->spinBox2_insert_mid->value();
    int num=ui->spinBox1_insert_mid->value();
    if(pos==0 || pos==sizeNode){
        ui->label->setText("If you want to insert into first or tail position, please choose Insert Fisrt or Insert Tail!");
    }
    else if(pos>sizeNode || pos<0){
        ui->label->setText("Error! Out of range!");
    }
    else if(sizeNode>0&&sizeNode<50){
        for(int i=0;i<=sizeNode+50;i++){
            node.pos(i)->hide();
            arr.pos(i)->hide();
        }
        value.insert(pos,num);
        sizeNode++;
        for(int i=0;i<=sizeNode;i++){
            //hiện label node
            if(i==sizeNode) node.replace(i,setNode(i,0));
            else node.replace(i,setNode(i,value.pos(i)));
                node.pos(i)->show();
            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            if(i<sizeNode){
                arr.replace(i,arrow(i));
                arr.pos(i)->show();
            }
        }
        ui->label->setText("Inserted!");
    }
    else if(sizeNode>=50){
        ui->label->setText("Sorry! Max size of list is 50 nodes!");
    }
}

//Xử lí thêm vào cuối
void Widget::on_go_insert_tail_clicked()
{
    int num;
    if(sizeNode==0){
        sizeNode++;
        num=ui->spinBox_insert_tail->value();
        value.insert(0,num);
        for(int i=0;i<=sizeNode;i++){;
            if(i==sizeNode) node.replace(i,setNode(i,0));
            else node.replace(i,setNode(i,value.pos(i)));
            node.pos(i)->show();

            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            if(i<sizeNode){
                arr.replace(i,arrow(i));
                arr.pos(i)->show();
            }
        }
        ui->label->setText("Inserted!");
    }
    else if(sizeNode>0&&sizeNode<50){
        for(int i=0;i<=sizeNode+50;i++){
            node.pos(i)->hide();
            arr.pos(i)->hide();
        }
        num=ui->spinBox_insert_tail->value();
        sizeNode++;
        value.insert(sizeNode-1,num);
        for(int i=0;i<=sizeNode;i++){
            //hiện label node
            if(i==sizeNode) node.replace(i,setNode(i,0));
            else node.replace(i,setNode(i,value.pos(i)));
                node.pos(i)->show();
            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            if(i<sizeNode){
                arr.replace(i,arrow(i));
                arr.pos(i)->show();
            }
        }
        ui->label->setText("Inserted!");
    }
    else if(sizeNode>=50){
        ui->label->setText("Sorry! Max size of list is 50 nodes!");
    }
}

//Xử lí tìm kiếm
void Widget::on_go_search_clicked()
{
    for(int i=0;i<=sizeNode+50;i++){
        node.pos(i)->hide();
        arr.pos(i)->hide();
    }
    bool flag=false;//Biến check có tìm thấy hay không
    int num=ui->spinBox_search->value();
    for(int i=0;i<sizeNode;i++){
        if(value.pos(i)==num){
            flag=true;
            node.pos(i)->setStyleSheet("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));border-style: outset;border-radius:20px");
            node.pos(i)->show();
            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            if(i<sizeNode){
                arr.replace(i,arrow(i));
                arr.pos(i)->show();
            }
            //break;
        }
        else{
            node.replace(i,setNode(i,value.pos(i)));
            node.pos(i)->show();
            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            if(i<sizeNode){
                arr.replace(i,arrow(i));
                arr.pos(i)->show();
            }
        }
    }
    node.replace(sizeNode,setNode(sizeNode,0));
    node.pos(sizeNode)->show();

    if(flag==true) ui->label->setText("Found!");
    else if(flag==false) ui->label->setText("Not found!");

}

//Xử lí thay thế theo vị trí
void Widget::on_go_bypos_replace_clicked()
{
    for(int i=0;i<=sizeNode+50;i++){
        node.pos(i)->hide();
        arr.pos(i)->hide();
    }
    int pos=ui->spinBox_replace_bypos_1->value();
    int num=ui->spinBox_replace_bypos_2->value();
    if(pos>sizeNode || pos<0){
        ui->label->setText("Error! Out of range!");
    }
    else{
        for(int i=0;i<sizeNode;i++){
            if(i==pos){
                //value.replace(i,num);
                value.replace(i,num);//
                node.replace(i,setNode(i,num));
                node.pos(i)->setStyleSheet("background-color: rgb(162, 246, 255);border-style: outset;border-radius:20px");
                node.pos(i)->show();
                //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
                if(i<sizeNode){
                    arr.replace(i,arrow(i));
                    arr.pos(i)->show();
                }
            }
            else{
                node.replace(i,setNode(i,value.pos(i)));
                node.pos(i)->show();
                //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
                if(i<sizeNode){
                    arr.replace(i,arrow(i));
                    arr.pos(i)->show();
                }
            }
            ui->label->setText("Replaced!");
        }
        node.replace(sizeNode,setNode(sizeNode,0));
        node.pos(sizeNode)->show();
    }
}

//Xử lí thay thế theo giá trị
void Widget::on_go_byvalue_replace_clicked()
{
    bool flag=false;//Biến check có tìm thấy hay không
    int old_value=ui->spinBox_replace_byvalue_1->value();
    int new_value=ui->spinBox_replace_byvalue_2->value();
    for(int i=0;i<=sizeNode+50;i++){
        node.pos(i)->hide();
        arr.pos(i)->hide();
    }
    for(int i=0;i<sizeNode;i++){
        if(value.pos(i)==old_value){
            flag=true;
            value.replace(i,new_value);//
            node.replace(i,setNode(i,value.pos(i)));
            node.pos(i)->setStyleSheet("background-color: rgb(162, 246, 255);border-style: outset;border-radius:20px");
            node.pos(i)->show();
            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            if(i<sizeNode){
                arr.replace(i,arrow(i));
                arr.pos(i)->show();
            }
        }
        else{
            node.replace(i,setNode(i,value.pos(i)));
            node.pos(i)->show();
            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            if(i<sizeNode){
                arr.replace(i,arrow(i));
                arr.pos(i)->show();
            }
        }
    }
    node.replace(sizeNode,setNode(sizeNode,0));
    node.pos(sizeNode)->show();

    if(flag==true) ui->label->setText("Replaced!");
    else if(flag==false) ui->label->setText("Not found!");
}
//Xử lí xoá tại giá xác định
void Widget::on_go_delete_0_clicked()
{
    bool flag=true;//Biến check có tìm thấy hay không
    int value_temp=ui->spinBox_remove_byvalue->value();
    if(sizeNode==0){
       ui->label->setText("List is empty!");
       return;
    }
    int j;
        for(j=0;j<sizeNode;j++){
            if(value.pos(j)==value_temp){
                flag=true;
                break;
            }
            flag=false;
        }

    if(!flag){
        ui->label->setText("Not found!");
        return;
    }
    for(int i=0;i<=sizeNode+50;i++){
            node.pos(i)->hide();
            arr.pos(i)->hide();
    }
        value.remove(j);
        node.remove(j);
        arr.remove(j);
        sizeNode--;
        if(sizeNode>0){
            for(int i=0;i<=sizeNode;i++){
                if(i==sizeNode) node.replace(i,setNode(i,0));
                else node.replace(i,setNode(i,value.pos(i)));
                node.pos(i)->show();
                //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
                if(i<sizeNode){
                    arr.replace(i,arrow(i));
                    arr.pos(i)->show();
                }
            }
        }
        ui->label->setText("Removed!");

}
//Xử lí xoá tại vị trí xác định
void Widget::on_go_delete_1_clicked()
{
    int pos=ui->spinBox_delete->value();
    if(pos>=sizeNode || pos<0){
        ui->label->setText("Error! Out of range!");
    }
    else if(sizeNode==0){
        ui->label->setText("List is empty!");
    }
    else if(sizeNode>0&&sizeNode<=50){
        for(int i=0;i<=sizeNode+50;i++){
            node.pos(i)->hide();
            arr.pos(i)->hide();
        }
        value.remove(pos);
        node.remove(pos);
        arr.remove(pos);
        sizeNode--;
        if(sizeNode>0){
            for(int i=0;i<=sizeNode;i++){
                if(i==sizeNode) node.replace(i,setNode(i,0));
                else node.replace(i,setNode(i,value.pos(i)));
                node.pos(i)->show();
                //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
                if(i<sizeNode){
                    arr.replace(i,arrow(i));
                    arr.pos(i)->show();
                }
            }
        }
        ui->label->setText("Removed!");
    }
}


//Xử lí xoá tại toàn bộ danh sách
void Widget::on_go_delete_2_clicked()
{
    if(sizeNode==0){
        ui->label->setText("List is empty!");
    }
    else{
        for(int j=0;j<MAX;j++){
            for(int i=0;i<=sizeNode+50;i++){
                node.pos(i)->hide();
                arr.pos(i)->hide();
            }
        }
        for(int i=0;i<=sizeNode+50;i++){
            value.remove(i);
            node.pos(i)->hide();
            if(i<sizeNode){
                arr.pos(i)->hide();
            }
        }
        for(int i=0;i<MAX;++i){
            node.remove(i);
            arr.remove(i);
        }
        value.clear();
        sizeNode=0;
        for(int i=0;i<MAX;++i){
            QLabel *newnode=new QLabel(this);
            node.insert(i,newnode);
        }
        //Khởi tạo arrow mang bản chất label
        for(int i=0;i<MAX;++i){
            QLabel *newarr=new QLabel(this);
            arr.insert(i,newarr);
        }

        //Mảng value lưu các giá trị label tại thời điểm xác định
        ui->label->setText("Deleted!");
    }
}


//Xử lí xem số lượng node
void Widget::on_go_size_clicked()
{
    if(sizeNode==0){
        ui->label->setText("List is empty!");
    }
    else{
        QString s= QString::number(sizeNode);
        ui->label->setText("List has "+s+" nodes!");
    }
}

//Xử lí sắp xếp tăng dần
void Widget::on_go_asc_sort_clicked()
{

    if(sizeNode==0){
        ui->label->setText("List is empty!");
    }
    else{
        //Start tạo mảng phụ sắp xếp tăng dần
        int value_temp[sizeNode];
        for(int i=0;i<sizeNode;++i){
            value_temp[i]=value.pos(i);
        }
        for(int i=0;i<sizeNode-1;++i){
            for(int j=i+1;j<sizeNode;++j){
                if(value_temp[i]>value_temp[j]) std::swap(value_temp[i],value_temp[j]);
            }
        }
        //end
        for(int i=0;i<=sizeNode+50;i++){
            node.pos(i)->hide();
            arr.pos(i)->hide();
        }
        for(int i=0;i<=sizeNode;i++){
            if(i<sizeNode) value.replace(i,value_temp[i]);
            if(i==sizeNode) node.replace(i,setNode(i,0));
            else node.replace(i,setNode(i,value_temp[i]));
            node.pos(i)->show();
            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            if(i<sizeNode){
                arr.replace(i,arrow(i));
                arr.pos(i)->show();
            }
        }
        ui->label->setText("Sorted!");
    }
}

//Xử lí sắp xếp giảm dần
void Widget::on_go_desc_sort_clicked()
{
    if(sizeNode==0){
        ui->label->setText("List is empty!");
    }
    else{
        //Start tạo mảng phụ sắp xếp
        int value_temp[sizeNode];
        for(int i=0;i<sizeNode;++i){
            value_temp[i]=value.pos(i);
        }
        for(int i=0;i<sizeNode-1;++i){
            for(int j=i+1;j<sizeNode;++j){
                if(value_temp[i]<value_temp[j]) std::swap(value_temp[i],value_temp[j]);
            }
        }
        //end
        for(int i=0;i<=sizeNode+50;i++){
            node.pos(i)->hide();
            arr.pos(i)->hide();
        }
        for(int i=0;i<=sizeNode;i++){
            //hiện label node
            if(i<sizeNode) value.replace(i,value_temp[i]);
            if(i==sizeNode) node.replace(i,setNode(i,0));
            else node.replace(i,setNode(i,value_temp[i]));
            node.pos(i)->show();
            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            //hiện label mũi tên
            if(i<sizeNode){
                arr.replace(i,arrow(i));
                arr.pos(i)->show();
            }
        }
        ui->label->setText("Sorted!");
    }
}


//Xử lí tạo mới danh sách bằng random
void Widget::on_go_random_create_clicked()
{
    int num=ui->spinBox_random->value();
    if(num==0){
        ui->label->setText("List is empty!");
        return;
    }
    //Delete all
    for(int i=0;i<=sizeNode+50;i++){
        node.pos(i)->hide();
        arr.pos(i)->hide();
    }

    for(int i=0;i<=sizeNode+50;i++){
        value.remove(i);
        node.pos(i)->hide();
        //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
        if(i<sizeNode){
            arr.pos(i)->hide();
        }
    }
    for(int i=0;i<MAX;++i){
        node.remove(i);
        arr.remove(i);
    }
    value.clear();
    sizeNode=0;
    for(int i=0;i<MAX;++i){
        QLabel *newnode=new QLabel(this);
        node.insert(i,newnode);
    }
    //Khởi tạo arrow mang bản chất label
    for(int i=0;i<MAX;++i){
        QLabel *newarr=new QLabel(this);
        arr.insert(i,newarr);
    }


    //Tạo list mới random
    srand(time(NULL));

    sizeNode=num;
    for(int i=0;i<sizeNode;i++){
        int ran=rand()%100;
        value.insert(i,ran);
    }
    for(int i=0;i<=sizeNode;i++){
        //hiện label node
        if(i==sizeNode) node.replace(i,setNode(i,0));
        else node.replace(i,setNode(i,value.pos(i)));
            node.pos(i)->show();
        //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
        if(i<sizeNode){
            arr.replace(i,arrow(i));
            arr.pos(i)->show();
        }
    }
    ui->label->setText("Created!");
}
//Xử lí tạo mới danh sách bằng input
void Widget::on_go_new_create_clicked()
{
    //Tạo list tự tạo
    QString s=ui->lineEdit_create->text();
    QStringList splitStr=s.split(",");
    sizeNode=splitStr.size();
    if(sizeNode>50){
        ui->label->setText("Sorry! Max size of list is 50 nodes!");
        return;
    }
    //Delete all
    for(int i=0;i<=sizeNode+50;i++){
        node.pos(i)->hide();
        arr.pos(i)->hide();
    }
    for(int i=0;i<=sizeNode+50;i++){
        value.remove(i);
        node.pos(i)->hide();
        //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
        if(i<sizeNode){
            arr.pos(i)->hide();
        }
    }
    for(int i=0;i<MAX;++i){
        node.remove(i);
        arr.remove(i);
    }
    value.clear();
    sizeNode=0;
    for(int i=0;i<MAX;++i){
        QLabel *newnode=new QLabel(this);
        node.insert(i,newnode);
    }
    //Tạo list tự tạo
    sizeNode=splitStr.size();
    //Khởi tạo arrow mang bản chất label
    for(int i=0;i<MAX;++i){
        QLabel *newarr=new QLabel(this);
        arr.insert(i,newarr);
    }

    for(int i=0;i<splitStr.size();i++){
        int num=splitStr[i].toInt();
        value.insert(i,num);
    }
    for(int i=0;i<=sizeNode;i++){
        //hiện label node
        if(i==sizeNode) node.replace(i,setNode(i,0));
        else node.replace(i,setNode(i,value.pos(i)));
            node.pos(i)->show();
        //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
        if(i<sizeNode){
            arr.replace(i,arrow(i));
            arr.pos(i)->show();
        }
    }
    ui->label->setText("Created!");
}
void Widget::go_delete(int pos){
    for(int i=0;i<=sizeNode+50;i++){
        node.pos(i)->hide();
        arr.pos(i)->hide();
    }
    value.remove(pos);
    node.remove(pos);
    arr.remove(pos);
    sizeNode--;
    if(sizeNode>0){
        for(int i=0;i<=sizeNode;i++){
            if(i==sizeNode) node.replace(i,setNode(i,0));
            else node.replace(i,setNode(i,value.pos(i)));
            node.pos(i)->show();
            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            if(i<sizeNode){
                arr.replace(i,arrow(i));
                arr.pos(i)->show();
            }
        }
    }
    ui->label->setText("Removed!");
}
void Widget::ShowContextMenu() // this is a slot
{
    // for most widgets
    QRect p(QWidget::geometry());
    QPoint mousePoint=QCursor::pos();

    QMenu myMenu;

    myMenu.addAction("Remove this node");
    myMenu.addAction("Insert at this node");
    myMenu.addAction("Replace this node");
    // ...
    QAction* selectedItem=new QAction(this);
    selectedItem = myMenu.exec(QCursor::pos());
    QAction *select1=myMenu.actions().at(0);
    QAction *select2=myMenu.actions().at(1);
    QAction *select3=myMenu.actions().at(2);
        if (selectedItem==select1){
            //
            int i=0;
            for(i=0;i<sizeNode;i++){
                QRect r(node.pos(i)->geometry());
                int cx=mousePoint.rx()-p.x();
                int cy=mousePoint.ry()-p.y();
                if(cx>=r.x() && cx<=r.x()+100 && cy>=r.y() && cy<=r.y()+55) break;
            }
            go_delete(i);
        }
        if (selectedItem==select2){
            //
            int i=0;
            for(i=0;i<sizeNode;i++){
                QRect r(node.pos(i)->geometry());
                int cx=mousePoint.rx()-p.x();
                int cy=mousePoint.ry()-p.y();
                if(cx>=r.x() && cx<=r.x()+100 && cy>=r.y() && cy<=r.y()+55) break;
            }
            QString s= QString::number(i);
            if(i>0 && i<sizeNode){
                ui->label->setText("Select insert mid at position "+s+"!");
                ui->spinBox2_insert_mid->setValue(i);
            }
            if(i==0) {
                ui->label->setText("Select insert first!");
            }
            if(i==sizeNode) ui->label->setText("Select insert tail!");
        }
        if (selectedItem==select3){
            //
            int i=0;
            for(i=0;i<sizeNode;i++){
                QRect r(node.pos(i)->geometry());
                int cx=mousePoint.rx()-p.x();
                int cy=mousePoint.ry()-p.y();
                if(cx>=r.x() && cx<=r.x()+100 && cy>=r.y() && cy<=r.y()+55) break;
            }
            QString s= QString::number(i);
                ui->label->setText("Select replace by position at position "+s+"!");
                ui->spinBox_replace_bypos_1->setValue(i);
         }

    delete selectedItem;
    selectedItem=NULL;
}
