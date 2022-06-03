#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;




class Employee{
    QString name;
    int year_birthday;
    int salary;

public:
    Employee(){}
    Employee(QString name, int year_birthday, int salary) : name(name), year_birthday(year_birthday), salary(salary) {}

    void setName(QString newName) {newName = name;}
    void setYear_birthday(int newYear_birthday) {newYear_birthday = year_birthday;}
    void setSalary(int newSalary) {newSalary = salary;}

    QString getName() {return name;}
    int getYear_birthday() {return year_birthday;}
    int getSalary() {return salary;}
};




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonSave_clicked();

    void on_pushButtonDownload_clicked();

    void on_pushButtonAdd_clicked();

    void on_pushButtonSearch_clicked();

    void on_pushButton_clicked();

    void on_pushButtonCalculateSalary_clicked();

private:
    Ui::MainWindow *ui;

    QVector<Employee>employees;

    QString doTextFromDataBase(){
        QString newText = "Employees:\nFIO year_birthday salary:";
        for (int i = 0; i < employees.length(); ++i)
            newText += "\n" + employees[i].getName() + " " + QString::number(employees[i].getYear_birthday()) + " " + QString::number(employees[i].getSalary());
        return newText;
    }

    void doDataBaseFromText(){
        ifstream fin("Employees.txt");

        fin.seekg(37);
        while (!fin.eof()) {
            string Sname;
            fin >> Sname;
            QString name = QString::fromUtf8(Sname.c_str());

            int year_birthday;
            fin >> year_birthday;

            int salary;
            fin >> salary;

            employees.push_back(Employee(name, year_birthday, salary));
        }

        fin.close();
    }

};
#endif // MAINWINDOW_H
