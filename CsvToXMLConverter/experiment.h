#ifndef EXPERIMENT_H
#define EXPERIMENT_H
#include <QString>

class Experiment
{
private:
    int experimentID;
    QString person;
    QString result;
    double temperature;
    int pressure;
    int wind;
    QString projectName;

public:
    Experiment(int experimentID, QString person, QString result,
               double temperature, int pressure, int wind, QString projectName);


    QString getProjectName() const;
    int getWind() const;
    int getPressure() const;
    double getTemperature() const;
    QString getResult() const;
    QString getPerson() const;
    int getExperimentID() const;
};

#endif // EXPERIMENT_H
