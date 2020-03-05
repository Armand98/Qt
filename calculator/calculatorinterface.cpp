#include "calculatorinterface.h"
#include "ui_calculatorinterface.h"

#include <QSignalMapper>
#include "calculator.h"

CalculatorInterface::CalculatorInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculatorInterface),
    m_calculator(new Calculator(this))
{
    ui->setupUi(this);

    // Add code here
    QSignalMapper *signalMapper = new QSignalMapper(this);

    connect(ui->buttonZero, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->buttonZero, 0);

    connect(ui->buttonOne, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->buttonOne, 1);

    connect(ui->buttonTwo, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->buttonTwo, 2);

    connect(ui->buttonThree, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->buttonThree, 3);

    connect(ui->buttonFour, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->buttonFour, 4);

    connect(ui->buttonFive, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->buttonFive, 5);

    connect(ui->buttonSix, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->buttonSix, 6);

    connect(ui->buttonSeven, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->buttonSeven, 7);

    connect(ui->buttonEight, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->buttonEight, 8);

    connect(ui->buttonNine, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->buttonNine, 9);

    connect(ui->buttonAdd, SIGNAL(clicked()), m_calculator, SLOT(additionMode()));
    connect(ui->buttonSubtract, SIGNAL(clicked()), m_calculator, SLOT(subtractionMode()));
    connect(ui->buttonCalculate, SIGNAL(clicked()), m_calculator, SLOT(calculate()));
    connect(ui->buttonClear, SIGNAL(clicked()), m_calculator, SLOT(clear()));
    connect(ui->buttonAllClear, SIGNAL(clicked()), m_calculator, SLOT(allClear()));

    connect(signalMapper, SIGNAL(mapped(int)), m_calculator, SLOT(numEntered(int)));
    connect(m_calculator, SIGNAL(displayChanged(QString)), ui->entryLabel, SLOT(setText(QString)));

    m_calculator->allClear();
}

CalculatorInterface::~CalculatorInterface()
{
    delete ui;
}

void CalculatorInterface::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
