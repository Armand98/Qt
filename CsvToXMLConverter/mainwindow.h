#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamWriter>
#include "experiment.h"
#include "scientist.h"
#include "project.h"
#include "scientist.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QList<Experiment*> experimentList;
    QList<Scientist*> scientistList;
    QList<Project*> projectsList;
    QList<QString> columnNames;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<QString> readCSVFile(QString url);
    void processData(QVector<QString> rows);
    void saveXml();
    void saveJson(QVector<QString> rows);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
