#ifndef PROJECT_H
#define PROJECT_H
#include <QString>
#include <QVector>

class Project
{
private:
    QString projectName;
    QVector<int> experimentIDVector;
    QVector<int> scientistIDVector;
    QVector<QString> resultVector;
    QVector<double> temperatureVector;
    QVector<int> pressureVector;
    QVector<int> windVector;

public:
    Project(QString projectName, int experimentID, int scientistID, QString result,
            double temperature, int pressure, int wind);

    QString getProjectName() const;
    int getExperimentIDVectorAt(int index);
    int getScientistIDVectorAt(int index);
    QString getResultVectorAt(int index);
    double getTemperatureVectorAt(int index);
    int getPressureVectorAt(int index);
    int getWindVectorAt(int index);

    void addAttributesToExistingProject(int experimentID, int scientistID, QString result,
                                        double temperature, int pressure, int wind);
    QVector<int> getExperimentIDVector() const;
};

#endif // PROJECT_H
