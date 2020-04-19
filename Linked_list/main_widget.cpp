#include "main_widget.h"
#include "ui_main_widget.h"
#include<QVector>
#include<QLabel>
#include<QLineF>
#include<QPainter>
#include<QPixmap>
#include<QDir>
#include<math.h>
#include"single_list.h"
#include<iostream>
#include<windows.h>
#include<algorithm>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //Khởi tạo node mang bản chất label
    node.resize(100);
    for(int i=0;i<100;++i){
        node[i]=new QLabel(this);
    }
    //Khởi tạo arrow mang bản chất label
    arr.resize(100);
    for(int i=0;i<100;++i){
        arr[i]=new QLabel(this);
    }
    //Mảng value lưu các giá trị label tại thời điểm xác định
    value.resize(100);
    //Xác định số lượng label hiện tại
    sizeNode=0;
}

Widget::~Widget()
{
    for(int i=0;i<100;++i){
        delete node[i];
        delete arr[i];
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
        if(pos<9){
            nodenew->setToolTip("Value of node: "+s+"\nPosition: "+s1+"\nCurrent pointer: pTail");
            nodenew->setText((" "+s+"   *pTail"));
            nodenew->setGeometry(QRect(170+(pos-1)*150,80,100,55));
        }
        else if(pos>=9) {
            nodenew->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:0.639955, y1:0.386, x2:0, y2:0.386, stop:0 rgba(205, 86, 121, 255), stop:1 rgba(46, 214, 51, 255));border-style: outset;border-radius:20px");
            nodenew->setToolTip("Value of node: "+s+"\nPosition: "+s1+"\nCurrent pointer: pTail");
            //nodenew->setText((" "+s+"   *pTail"));
            nodenew->setText(" *pTail   "+s);
            nodenew->setGeometry(QRect(1370-(pos-8)*150,180,100,55));
        }
    }
    //Trường hợp tạo *pHead
    if(pos==0){
        nodenew->setToolTip("Value of node: "+s+"\nPosition: "+s1+"\nCurrent pointer: pHead");
        nodenew->setText((" "+s+"  *pHead"));
        nodenew->setAlignment(Qt::AlignCenter);
        nodenew->setGeometry(QRect(20,80,100,55));
    }
    //Trường hợp tạo node NULL
    if (pos==sizeNode) {
        if(pos<9){
            nodenew->setText("NULL");
            nodenew->setAlignment(Qt::AlignCenter);
            nodenew->setStyleSheet("background-color: rgb(255, 199, 107);border-style: outset;border-radius:20px");
            QRect r(node[sizeNode-1]->geometry());
            nodenew->setGeometry(r.x()+150,r.y(),r.width(),r.height());
        }
        else if(pos==9) {
            nodenew->setText("NULL");
            nodenew->setAlignment(Qt::AlignCenter);
            nodenew->setStyleSheet("background-color: rgb(255, 199, 107);border-style: outset;border-radius:20px");
            QRect r(node[sizeNode-1]->geometry());
            nodenew->setGeometry(r.x(),r.y()+100,r.width(),r.height());
        }
        else if(pos>9) {
            nodenew->setText("NULL");
            nodenew->setAlignment(Qt::AlignCenter);
            nodenew->setStyleSheet("background-color: rgb(255, 199, 107);border-style: outset;border-radius:20px");
            QRect r(node[sizeNode-1]->geometry());
            nodenew->setGeometry(r.x()-150,r.y(),r.width(),r.height());
        }
    }
    //Trường hợp tạo *pNext
    if (pos>0 && pos<sizeNode-1) {
        if(pos<9){
            nodenew->setToolTip("Value of node: "+s+"\nPosition: "+s1+"\nCurrent pointer: pNext");
            if(num<10) nodenew->setText((" "+s+"   *pNext"));
            else if(num>=10) nodenew->setText((" "+s+"  *pNext"));
            nodenew->setGeometry(QRect(170+(pos-1)*150,80,100,55));
        }
        else if(pos>=9){
            nodenew->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:0.639955, y1:0.386, x2:0, y2:0.386, stop:0 rgba(205, 86, 121, 255), stop:1 rgba(46, 214, 51, 255));border-style: outset;border-radius:20px");
            nodenew->setToolTip("Value of node: "+s+"\nPosition: "+s1+"\nCurrent pointer: pNext");
            if(num<10) nodenew->setText(("*pNext  "+s));
            else if(num>=10) nodenew->setText(("*pNext   "+s));
            nodenew->setGeometry(QRect(1370-(pos-8)*150,180,100,55));
        }
    }
    return nodenew;
}


//Hàm xử lý tạo mũi tên(là label chứa file ảnh hình mũi tên)(quan trọng)
QLabel* Widget::arrow(int sn){
    // Draw the line itself
    QLabel *arrow=new QLabel(this);
    QString dir=QDir::currentPath();
    dir=dir.replace("\\","\\\\");
    QPixmap pixmap1(dir+"\\arrow.png");
    arrow->setPixmap(pixmap1.scaled(50,50,Qt::KeepAspectRatio));

    if(sn==0){
        QRect r1(120,90,100,35);
        arrow->setGeometry(r1);
    }
    else if(sn>0&&sn<=7) {
        QRect r2(270+150*(sn-1),90,100,35);
        arrow->setGeometry(r2);
    }
    else if(sn==8){
        QPixmap pixmap2(dir+"\\arrow1.png");
        arrow->setPixmap(pixmap2.scaled(20,60,Qt::KeepAspectRatio));
        QRect r3(1278,140,100,35);
        arrow->setGeometry(r3);
    }
    else if(sn>8) {
        QPixmap pixmap3(dir+"\\arrow2.png");
        arrow->setPixmap(pixmap3.scaled(50,50,Qt::KeepAspectRatio));
        QRect r4(1320-150*(sn-8),190,100,35);
        arrow->setGeometry(r4);
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
        for(int i=0;i<=sizeNode;i++){
            node[i]=setNode(i,value[i]);
            node[i]->show();
            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            if(i<sizeNode){
                arr[i]=arrow(i);
                arr[i]->show();
            }
        }
        ui->label->setText("Inserted!");

    }
    else if(sizeNode>0&&sizeNode<17){
        for(int j=0;j<25;j++){
            for(int i=0;i<=sizeNode+20;i++){
                node[i]->hide();
                arr[i]->hide();
            }
        }
        num=ui->spinBox_insert_first->value();
        value.insert(0,num);
        sizeNode++;
        for(int i=0;i<=sizeNode;i++){
            //hiện label node
            node[i]=setNode(i,value[i]);
            node[i]->show();
            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            if(i<sizeNode){
                arr[i]=arrow(i);
                arr[i]->show();
            }
        }
        ui->label->setText("Inserted!");
    }
    else if(sizeNode>=17){
        ui->label->setText("Sorry! Max size of list is 17 nodes!");
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
        ui->label->setText("Error! Overflow error in range select!");
    }
    else if(sizeNode>0&&sizeNode<17){
        for(int j=0;j<25;j++){
            for(int i=0;i<=sizeNode+20;i++){
                node[i]->hide();
                arr[i]->hide();
            }
        }

        value.insert(pos,num);
        sizeNode++;
        for(int i=0;i<=sizeNode;i++){
            //hiện label node
            node[i]=setNode(i,value[i]);
            node[i]->show();
            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            //hiện label mũi tên
            if(i<sizeNode){
                arr[i]=arrow(i);
                arr[i]->show();
            }
        }
        ui->label->setText("Inserted!");
    }
    else if(sizeNode>=17){
        ui->label->setText("Sorry! Max size of list is 17 nodes!");
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
            node[i]=setNode(i,value[i]);
            node[i]->show();
            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            //hiện label mũi tên
            if(i<sizeNode){
                arr[i]=arrow(i);
                arr[i]->show();
            }
        }
        ui->label->setText("Inserted!");
    }
    else if(sizeNode>0&&sizeNode<17){
        for(int j=0;j<25;j++){
            for(int i=0;i<=sizeNode+20;i++){
                node[i]->hide();
                arr[i]->hide();
            }
        }

        num=ui->spinBox_insert_tail->value();
        sizeNode++;
        value.insert(sizeNode-1,num);
        for(int i=0;i<=sizeNode;i++){
            node[i]=setNode(i,value[i]);
            node[i]->show();
            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            //hiện label mũi tên
            if(i<sizeNode){
                arr[i]=arrow(i);
                arr[i]->show();
            }
        }
        ui->label->setText("Inserted!");
    }
    else if(sizeNode>=17){
        ui->label->setText("Sorry! Max size of list is 17 nodes!");
    }
}

//Xử lí tìm kiếm
void Widget::on_go_search_clicked()
{
    bool flag=false;//Biến check có tìm thấy hay không
    for(int i=0;i<sizeNode;i++){
        node[i]=setNode(i,value[i]);
        node[i]->show();
    }
    int num=ui->spinBox_search->value();
    for(int i=0;i<sizeNode;i++){
        if(value[i]==num){
            flag=true;
            node[i]->setStyleSheet("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));border-style: outset;border-radius:20px");
            node[i]->show();
            break;
        }
        node[i]->setStyleSheet("background-color: rgb(79, 185, 255);border-style: outset;border-radius:20px");
        node[i]->show();
        Sleep(300);
    }
    if(flag==true) ui->label->setText("Found!");
    else if(flag==false) ui->label->setText("Not found!");

}

//Xử lí thay thế theo vị trí
void Widget::on_go_bypos_replace_clicked()
{
    for(int i=0;i<sizeNode;i++){
        node[i]=setNode(i,value[i]);
        node[i]->show();
    }
    int pos=ui->spinBox_replace_bypos_1->value();
    int num=ui->spinBox_replace_bypos_2->value();
    if(pos>sizeNode || pos<0){
        ui->label->setText("Error! Overflow error in range select!");
    }
    else{
        for(int i=0;i<sizeNode;i++){
            if(i==pos){
                value.replace(i,num);
                node[i]=setNode(i,num);
                node[i]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255, 0, 0, 255), stop:0.166 rgba(255, 255, 0, 255), stop:0.333 rgba(0, 255, 0, 255), stop:0.5 rgba(0, 255, 255, 255), stop:0.666 rgba(0, 0, 255, 255), stop:0.833 rgba(255, 0, 255, 255), stop:1 rgba(255, 0, 0, 255));border-style: outset;border-radius:20px");
                node[i]->show();
            }
            ui->label->setText("Replaced!");
        }
    }
}

//Xử lí thay thế theo giá trị
void Widget::on_go_byvalue_replace_clicked()
{
    bool flag=false;//Biến check có tìm thấy hay không
    int old_value=ui->spinBox_replace_byvalue_1->value();
    int new_value=ui->spinBox_replace_byvalue_2->value();
    for(int i=0;i<sizeNode;i++){
        node[i]=setNode(i,value[i]);
        node[i]->show();
    }
    for(int i=0;i<sizeNode;i++){
        if(value[i]==old_value){
            flag=true;
            value.replace(i,new_value);
            node[i]=setNode(i,new_value);
            node[i]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255, 0, 0, 255), stop:0.166 rgba(255, 255, 0, 255), stop:0.333 rgba(0, 255, 0, 255), stop:0.5 rgba(0, 255, 255, 255), stop:0.666 rgba(0, 0, 255, 255), stop:0.833 rgba(255, 0, 255, 255), stop:1 rgba(255, 0, 0, 255));border-style: outset;border-radius:20px");
            node[i]->show();
        }
    }
    if(flag==true) ui->label->setText("Replaced!");
    else if(flag==false) ui->label->setText("Not found!");
}

//Xử lí xoá tại vị trí xác định
void Widget::on_go_delete_clicked()
{

    int pos=ui->spinBox_delete->value();
    if(pos>sizeNode || pos<0){
        ui->label->setText("Error! Overflow error in range select!");
    }
    else if(sizeNode==0){
        ui->label->setText("List is empty!");
    }
    else if(sizeNode>0&&sizeNode<=17){
        for(int j=0;j<25;j++){
            for(int i=0;i<=sizeNode+20;i++){
                node[i]->hide();
                arr[i]->hide();
            }
        }
        value.remove(pos);
        node.remove(pos);
        arr.remove(pos);
        sizeNode--;
        for(int i=0;i<=sizeNode;i++){
            node[i]=setNode(i,value[i]);
            node[i]->show();
            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            if(i<sizeNode){
                arr[i]=arrow(i);
                arr[i]->show();
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
        for(int i=0;i<=sizeNode;i++){
            value.remove(i);
            node[i]->hide();
            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            if(i<sizeNode){
                arr[i]->hide();
            }
        }
        for(int i=0;i<100;++i){
            delete node[i];
            delete arr[i];
        }
        value.clear();
        sizeNode=0;
        node.resize(100);
        for(int i=0;i<100;++i){
            node[i]=new QLabel(this);
        }
        //Khởi tạo arrow mang bản chất label
        arr.resize(100);
        for(int i=0;i<100;++i){
            arr[i]=new QLabel(this);
        }
        //Mảng value lưu các giá trị label tại thời điểm xác định
        value.resize(100);
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
        std::sort(value.begin(),value.begin()+sizeNode);
        for(int j=0;j<25;j++){
            for(int i=0;i<=sizeNode+20;i++){
                node[i]->hide();
                arr[i]->hide();
            }
        }
        for(int i=0;i<=sizeNode;i++){
            node[i]=setNode(i,value[i]);
            node[i]->show();
            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            if(i<sizeNode){
                arr[i]=arrow(i);
                arr[i]->show();
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
        std::sort(value.rbegin(),value.rend());
        for(int j=0;j<25;j++){
            for(int i=0;i<=sizeNode+20;i++){
                node[i]->hide();
                arr[i]->hide();
            }
        }
        for(int i=0;i<=sizeNode;i++){
            //hiện label node
            node[i]=setNode(i,value[i]);
            node[i]->show();
            //Vẽ arrow giữa các node(Chú ý: Không được thay đổi cách này nếu không bị lỗi mất số)
            //hiện label mũi tên
            if(i<sizeNode){
                arr[i]=arrow(i);
                arr[i]->show();
            }
        }
        ui->label->setText("Sorted!");
    }
}
