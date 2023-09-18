#include "mainwindow.h"
#include "./ui_mainwindow.h"

double calcValue = 0.0;
bool addTriggered = false;
bool divTriggered = false;
bool multTriggered = false;
bool subTriggered = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcValue));
    QPushButton *numButtons[10];
    for(int i = 0; i < 10; ++i)
    {
        QString buttonName = "button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(buttonName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(numPressed()));
    }

    connect(ui->buttonadd, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->buttonmultiply, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->buttonsub, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->buttondivide, SIGNAL(released()), this, SLOT(mathButtonPressed()));

    connect(ui->buttonequals, SIGNAL(released()), this, SLOT(equalButtonPressed()));

    connect(ui->buttonsigns, SIGNAL(released()), this, SLOT(numSignChanged()));

    connect(ui->buttonClear, SIGNAL(released()), this, SLOT(clearPressed()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text(); //gets text off of button so we know what button was pressed
    QString displayVal = ui->Display->text();
    if(displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0)
    {
        ui->Display->setText(buttonValue);
    }
    else
    {
        QString newValue = displayVal + buttonValue;
        double newValueDb = newValue.toDouble();
        ui->Display->setText(QString::number(newValueDb, 'g', 16));
    }

}

void MainWindow::mathButtonPressed()
{
    divTriggered = false;
    addTriggered = false;
    multTriggered = false;
    subTriggered = false;
    //need to set all of these to false again

    QString displayVal = ui->Display->text();
    calcValue = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender(); //casting whatever we got to a QPushButton and getting what was pressed
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0)
        divTriggered = true;
    else if(QString::compare(butVal, "X", Qt::CaseInsensitive) == 0)
        multTriggered = true;
    else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0)
        addTriggered = true;
    else
        subTriggered = true;

    ui->Display->setText("");
}

void MainWindow::equalButtonPressed()
{
    double answer = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplay = displayVal.toDouble();
    if(addTriggered || subTriggered || multTriggered || divTriggered)
    {
        if(addTriggered)
            answer = calcValue + dblDisplay;
        else if(subTriggered)
            answer = calcValue - dblDisplay;
        else if(multTriggered)
            answer = calcValue * dblDisplay;
        else
            answer = calcValue / dblDisplay;
    }

    ui->Display->setText(QString::number(answer));
}

void MainWindow::numSignChanged()
{
    QString displayVal = ui->Display->text();
    static QRegularExpression reg("[-]?[0-9.]*"); //we MAY have a negative sign (? says maybe) and will have 0-9 or a decimal (* means multiple)
    //QRegularExpressionMatch match = reg.
    //MUST HAVE library included
    if(reg.match(displayVal).hasMatch() == true)
    {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}

void MainWindow::clearPressed()
{
    ui->Display->setText(QString::number(0));
}
