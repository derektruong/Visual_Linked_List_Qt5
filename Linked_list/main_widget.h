#ifndef WIDGET_H
#define WIDGET_H

#include<QWidget>
#include <QVector>
#include<QLabel>
#include"single_list.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget;
               class xl_them_dialog;}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QLabel* setNode(int pos,int num);
    QLabel* arrow(int);

private slots:

    void on_go_insert_first_clicked();

    void on_go_insert_mid_clicked();

    void on_go_insert_tail_clicked();

    void on_go_search_clicked();

    void on_go_bypos_replace_clicked();

    void on_go_byvalue_replace_clicked();

    void on_go_delete_clicked();

    void on_go_size_clicked();

    void on_go_delete_2_clicked();

    void on_go_asc_sort_clicked();

    void on_go_desc_sort_clicked();

    void on_go_random_create_clicked();

    void on_go_new_create_clicked();

private:
    Ui::Widget *ui;
    QVector <QLabel*> node;
    QVector <QLabel*> arr;
    QVector<int> value;
    int sizeNode=0;
    //QLabel *nodeNull=new QLabel(this);
};
#endif // WIDGET_H
