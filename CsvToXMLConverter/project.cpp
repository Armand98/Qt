#include "project.h"

QString Project::getProjectName() const
{
    return projectName;
}

int Project::getExperimentIDVectorAt(int index)
{
    return experimentIDVector.at(index);
}

int Project::getScientistIDVectorAt(int index)
{
    return scientistIDVector.at(index);
}

QString Project::getResultVectorAt(int index)
{
    return resultVector.at(index);
}

double Project::getTemperatureVectorAt(int index)
{
    return temperatureVector.at(index);
}

int Project::getPressureVectorAt(int index)
{
    return pressureVector.at(index);
}

int Project::getWindVectorAt(int index)
{
    return windVector.at(index);
}

void Project::addAttributesToExistingProject(int experimentID, int scientistID, QString result,
                                             double temperature, int pressure, int wind)
{
    experimentIDVector.push_back(experimentID);
    scientistIDVector.push_back(scientistID);
    resultVector.push_back(result);
    temperatureVector.push_back(temperature);
    pressureVector.push_back(pressure);
    windVector.push_back(wind);
}


QVector<int> Project::getExperimentIDVector() const
{
    return experimentIDVector;
}

Project::Project(QString projectName, int experimentID, int scientistID, QString result,
                 double temperature, int pressure, int wind)
{
    this->projectName = projectName;
    this->experimentIDVector.push_back(experimentID);
    this->scientistIDVector.push_back(scientistID);
    this->resultVector.push_back(result);
    this->temperatureVector.push_back(temperature);
    this->pressureVector.push_back(pressure);
    this->windVector.push_back(wind);

}
