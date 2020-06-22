#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_pushButton_clicked()
{
    QString filter = "CSV (*.csv)";
    QString title = "Otwórz plik CSV";
    QString url = "C://";
    QString fileName = QFileDialog::getOpenFileName(this, title, url, filter);
    ui->lineEdit->setText(fileName);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString csvFileName = ui->lineEdit->text();
    if(!csvFileName.isEmpty()) {
        QVector<QString> rows = readCSVFile(csvFileName);
        processData(rows);
        saveXml();
        ui->lineEdit->setText("");
    } else {
        ui->lineEdit->setText("Błąd pliku CSV");
    }
}

// ZADANIE CSV -> JSON
void MainWindow::on_pushButton_3_clicked()
{
    QString csvFileName = ui->lineEdit->text();
    if(!csvFileName.isEmpty()) {
        QVector<QString> rows = readCSVFile(csvFileName);
        saveJson(rows);
        ui->lineEdit->setText("");
    } else {
        ui->lineEdit->setText("Błąd pliku CSV");
    }
}

void MainWindow::saveJson(QVector<QString> rows) {
    QRegExp rx("\\,");
    columnNames = rows.at(0).split(rx);
    rows.remove(0);

    QVector<QJsonObject> jsonObjectsList;

    // create a list of Json Objects
    foreach(QString row, rows) {
        QStringList words = row.split(rx);
        QVariantMap map;

        for(int i=0; i<words.length(); i++) {
            map.insert(columnNames.at(i), words.at(i));
        }

        QJsonObject jsonObj = QJsonObject::fromVariantMap(map);
        jsonObjectsList.push_back(jsonObj);
    }

    QString filename = QFileDialog::getSaveFileName(this,
                                       tr("Save JSON"), ".",
                                       tr("Json files (*.json)"));

    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);

    foreach(QJsonObject jObj, jsonObjectsList) {
        QJsonDocument JsonDocument;
        JsonDocument.setObject(jObj);
        file.write(JsonDocument.toJson());
    }
    file.close();
}

QVector<QString> MainWindow::readCSVFile(QString url) {

    QVector<QString> rows;
    QFile inputFile(url);
    if(inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);

        while (!in.atEnd()) {
            QString line = in.readLine();
            rows.append(line);
        }
        inputFile.close();
    }

    return rows;
}

void MainWindow::processData(QVector<QString> rows) {
    QRegExp rx("\\,");
    columnNames = rows.at(0).split(rx);
    rows.remove(0);

    // Create a list of experiments (with OK result)
    foreach(QString row , rows) {

        QStringList wordsInLine = row.split(rx);
        QString result = wordsInLine.at(2);

        if(result == "OK") {
            int experimentID = wordsInLine.at(0).toInt();
            QString person = wordsInLine.at(1);
            double temperature = wordsInLine.at(3).toDouble();
            int pressure = wordsInLine.at(4).toInt();
            int wind = wordsInLine.at(5).toInt();
            QString projectName = wordsInLine.at(6);

            Experiment *experiment = new Experiment(experimentID, person, result, temperature, pressure, wind, projectName);
            experimentList.push_back(experiment);
        }
    }

    // Create a list of experiments (with BAD result)
    foreach(QString row , rows) {

        QStringList wordsInLine = row.split(rx);
        QString result = wordsInLine.at(2);

        if(result != "OK") {
            int experimentID = wordsInLine.at(0).toInt();
            QString person = wordsInLine.at(1);
            double temperature = wordsInLine.at(3).toDouble();
            int pressure = wordsInLine.at(4).toInt();
            int wind = wordsInLine.at(5).toInt();
            QString projectName = wordsInLine.at(6);

            Experiment *experiment = new Experiment(experimentID, person, result, temperature, pressure, wind, projectName);
            experimentList.push_back(experiment);
        }
    }

    int scientistID = 1;
    // create a list of scientists
    foreach(Experiment *experiment, experimentList) {

        QStringList person = experiment->getPerson().split(" ");
        QString firstName = person.at(0);
        QString lastName = person.at(1);

        bool personDoesNotExists = true;
        foreach(Scientist *person, scientistList) {
            if((person->getFirstName() == firstName) && (person->getLastName() == lastName)) {
                personDoesNotExists = false;
                break;
            }
        }
        if(personDoesNotExists) {
            scientistList.push_back(new Scientist(scientistID++, firstName, lastName));
        }
    }

    // create a list of projects
    foreach(Experiment *experiment, experimentList) {

        QString projectName = experiment->getProjectName();
        int experimentID = experiment->getExperimentID();

        int tempScientistID = 0;
        QStringList person = experiment->getPerson().split(" ");
        QString firstName = person.at(0);
        QString lastName = person.at(1);

        // get scientist ID based on his/her first name and last name
        foreach(Scientist *person, scientistList) {
            tempScientistID = person->getScientistID(firstName, lastName);
            if(tempScientistID != 0) {
                break;
            }
        }

        int scientistID = tempScientistID;
        QString result = experiment->getResult();
        double temperature = experiment->getTemperature();
        int pressure = experiment->getPressure();
        int wind = experiment->getWind();

        bool projectDoesNotExists = true;
        int index = 0;

        while(index<projectsList.length()) {
            if(projectsList.at(index)->getProjectName() == projectName) {
                projectDoesNotExists = false;
                break;
            }
            index++;
        }

        if(projectDoesNotExists) {
            Project *project = new Project(projectName, experimentID, scientistID, result, temperature, pressure, wind);
            projectsList.push_back(project);
        } else {
            projectsList.at(index)->addAttributesToExistingProject(experimentID, scientistID, result, temperature, pressure, wind);
        }
    }
}

void MainWindow::saveXml()
{

    QString filename = QFileDialog::getSaveFileName(this,
                                       tr("Save Xml"), ".",
                                       tr("Xml files (*.xml)"));

    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    foreach(Project *project, projectsList) {
        xmlWriter.writeStartElement("Projekt");
        xmlWriter.writeAttribute("nazwa", project->getProjectName());

        for(int i=0; i<project->getExperimentIDVector().length(); i++) {
            xmlWriter.writeStartElement("Eksperyment");
            xmlWriter.writeAttribute("id", QString::number(project->getExperimentIDVectorAt(i)));
            xmlWriter.writeAttribute("naukowiec_id", QString::number(project->getScientistIDVectorAt(i)));

            xmlWriter.writeTextElement("Rezultat", project->getResultVectorAt(i));
            xmlWriter.writeTextElement("Temperatura", QString::number(project->getTemperatureVectorAt(i)));
            xmlWriter.writeTextElement("Ciśnienie", QString::number(project->getPressureVectorAt(i)));
            xmlWriter.writeTextElement("Wiatr", QString::number(project->getWindVectorAt(i)));

            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();

    }

    foreach(Scientist *scientist, scientistList) {
        xmlWriter.writeStartElement("Naukowiec");
        xmlWriter.writeAttribute("id", QString::number(scientist->getScientistID()));

        xmlWriter.writeTextElement("Imie", scientist->getFirstName());
        xmlWriter.writeTextElement("Nazwisko", scientist->getLastName());
        xmlWriter.writeEndElement();
    }
        file.close();
}
