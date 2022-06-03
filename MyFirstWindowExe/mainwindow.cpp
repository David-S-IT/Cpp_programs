#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <algorithm>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSave_clicked()
{
    ofstream fout("Employees.txt");
    fout << doTextFromDataBase().toStdString();
    fout.close();
}

void MainWindow::on_pushButtonDownload_clicked()
{
    employees.clear();

    doDataBaseFromText();

    ui->labelMain->setText(doTextFromDataBase());
}

void MainWindow::on_pushButtonAdd_clicked()
{
    QString name = ui->lineEdit_FIO->text();
    int year_birthday = ui->spinBoxYear_birthday->value();
    int salary = ui->spinBoxSalary->value();

    employees.push_back(Employee(name, year_birthday, salary));

    ui->labelMain->setText(doTextFromDataBase());
}

void MainWindow::on_pushButtonSearch_clicked()
{
    QString lookingEmployee = ui->lineEdit_FIO->text();
    Employee findedEmployee = *find_if(employees.begin(), employees.end(), [lookingEmployee](Employee& potentialEmployee){
            return lookingEmployee == potentialEmployee.getName();
        });

    int total = count_if(employees.begin(), employees.end(), [lookingEmployee](Employee& potentialEmployee){
        return lookingEmployee == potentialEmployee.getName();
    });

    ui->labelMain->setText(findedEmployee.getName() + " " + QString::number(findedEmployee.getYear_birthday()) + " " + QString::number(findedEmployee.getSalary())
                           + "\n\nThere are " + QString::number(total) + " such employee in total.");

}

void MainWindow::on_pushButton_clicked()
{
    QString lookingEmployeeName = ui->lineEdit_FIO->text();
    int lookingEmployeeYear = ui->spinBoxYear_birthday->value();

    Employee* deletedEmployee = find_if(employees.begin(), employees.end(), [lookingEmployeeName, lookingEmployeeYear](Employee& potentialEmployee){
            return lookingEmployeeName == potentialEmployee.getName() && lookingEmployeeYear == potentialEmployee.getYear_birthday();
        });

    if (any_of(employees.begin(), employees.end(), [lookingEmployeeName, lookingEmployeeYear](Employee& potentialEmployee){
               return lookingEmployeeName == potentialEmployee.getName() && lookingEmployeeYear == potentialEmployee.getYear_birthday();
           })) employees.erase(deletedEmployee);

    ui->labelMain->setText(doTextFromDataBase());
}

void MainWindow::on_pushButtonCalculateSalary_clicked()
{
    int summa = 0;
    for_each(employees.begin(), employees.end(), [&summa](Employee& potentialEmployee){
        summa += potentialEmployee.getSalary();
    });

    ui->labelMain->setText("You will should to pay: " + QString::number(summa) + "$");
}
