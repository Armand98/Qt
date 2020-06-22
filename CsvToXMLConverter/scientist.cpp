#include "scientist.h"

QString Scientist::getFirstName() const
{
    return firstName;
}

void Scientist::setFirstName(const QString &value)
{
    firstName = value;
}

int Scientist::getScientistID() const
{
    return scientistID;
}

void Scientist::setScientistID(int value)
{
    scientistID = value;
}

int Scientist::getScientistID(QString firstName, QString lastName)
{
    if(this->firstName == firstName && this->lastName == lastName) {
        return this->scientistID;
    } else {
        return 0;
    }
}

QString Scientist::getLastName() const
{
    return lastName;
}

void Scientist::setLastName(const QString &value)
{
    lastName = value;
}

Scientist::Scientist(int scientistID, QString firstName, QString secondName)
{
    this->scientistID = scientistID;
    this->firstName = firstName;
    this->lastName = secondName;
}
