#ifndef SCIENTIST_H
#define SCIENTIST_H
#include <QString>

class Scientist
{
private:
    int scientistID;
    QString firstName;
    QString lastName;

public:
    Scientist(int scientistID, QString firstName, QString lastName);
    QString getFirstName() const;
    void setFirstName(const QString &value);
    QString getLastName() const;
    void setLastName(const QString &value);
    int getScientistID() const;
    void setScientistID(int value);
    int getScientistID(QString firstName, QString lastName);
};

#endif // SCIENTIST_H
