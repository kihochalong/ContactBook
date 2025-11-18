#include "widget.h"
#include "ui_widget.h"

#include <QFile>
#include <QDebug>
#include <QFileDialog>

QString mFilename = "C:/Users/user/Documents/test.txt";

void Write(QString Filename, QString str)
{
    QFile mFile(Filename);
    if(!mFile.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "could not open file for write";
        return;
    }

    QTextStream out(&mFile);
    out << str;
    mFile.flush();
    mFile.close();
}


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QStringList ColTotle;

    ui->tableWidget->setColumnCount(4);
    ColTotle<<QStringLiteral("學號")<<QStringLiteral("班級")<<QStringLiteral("姓名")<<QStringLiteral("電話");
    ui->tableWidget->setHorizontalHeaderLabels(ColTotle);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QTableWidgetItem *inputRow1,*inputRow2,*inputRow3,*inputRow4;

    inputRow1 = new QTableWidgetItem(QString(ui->lineEdit->text()));
    inputRow2 = new QTableWidgetItem(QString(ui->lineEdit_2->text()));
    inputRow3 = new QTableWidgetItem(QString(ui->lineEdit_3->text()));
    inputRow4 = new QTableWidgetItem(QString(ui->lineEdit_4->text()));

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,inputRow1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,inputRow2);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,inputRow3);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,inputRow4);
}


void Widget::on_pushButton_2_clicked()
{
    QString saveFile = "";

    int rc,cc;
    rc=ui->tableWidget->rowCount();
    cc=ui->tableWidget->columnCount();
    mFilename = QFileDialog::getSaveFileName(this,"匯出檔案",".");
    for(int i = 0; i < ui->tableWidget->rowCount(); i++) {
        for(int j = 0; j < ui->tableWidget->columnCount(); j++) {
            saveFile += ui->tableWidget->item(i, j)->text() + ",";
        }
        saveFile += "\n";
    }

    Write(mFilename, saveFile);
}


void Widget::on_pushButton_4_clicked()
{
    close();
}


void Widget::on_pushButton_3_clicked()
{
    QFile f(QFileDialog::getOpenFileName(this, "匯入檔案"));
    if(!f.open(QFile::ReadOnly | QFile::Text)) return;

    ui->tableWidget->setRowCount(0);

    QTextStream in(&f);
    while(!in.atEnd()) {
        QStringList s = in.readLine().split(",");
        int r = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(r);
        for(int i = 0; i < s.size(); i++)
            ui->tableWidget->setItem(r, i, new QTableWidgetItem(s[i]));
    }
}

