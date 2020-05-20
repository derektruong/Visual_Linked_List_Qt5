#include "main_widget.h"
#include<QDir>
#include<QIcon>
#include<QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle(QString::fromUtf8("Mô phỏng danh sách liên kết đơn"));
    w.setFixedSize(1350,771);
    QString dir=QDir::currentPath();
    dir=dir.replace("\\","\\\\");
    w.setWindowIcon(QIcon(dir+"\\icon.ico"));
    w.show();
    return a.exec();
}
