#include "experiment.h"

QString Experiment::getProjectName() const
{
    return projectName;
}

int Experiment::getWind() const
{
    return wind;
}

int Experiment::getPressure() const
{
    return pressure;
}

double Experiment::getTemperature() const
{
    return temperature;
}

QString Experiment::getResult() const
{
    return result;
}

QString Experiment::getPerson() const
{
    return person;
}

int Experiment::getExperimentID() const
{
    return experimentID;
}

Experiment::Experiment(int experimentID, QString person, QString result,
                       double temperature, int pressure, int wind, QString projectName)
{
    this->experimentID = experimentID;
    this->person = person;
    this->result = result;
    this->temperature = temperature;
    this->pressure = pressure;
    this->wind = wind;
    this->projectName = projectName;
}
