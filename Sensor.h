//
// Created by cplwe on 07.05.2024.
//

#ifndef ROBOTERKLAUSUR_SENSOR_H
#define ROBOTERKLAUSUR_SENSOR_H

#include <string>
#include <iostream>
#include "RobotExceptions.h"


class Sensor {
protected:
    static constexpr int minErrorStatus = 0;
    static constexpr int maxErrorStatus = 100;

    static constexpr int chanceCriticalDanger = 20;    //...Sensor hat eine x Wahrscheinlichkeit um einen Critical Fehler zu werfen  (zB x = 10 für 10%ige wahrscheinlichkeit)
    static constexpr int chanceInternalError = 20;     //...Sensor hat eine x Wahrscheinlichkeit um einen Internal Fehler zu werfen

    static constexpr int chanceReset = 20;             //...Sensor hat eine x Wahrscheinlichkeit um nach einem Fehler wieder resetet werden zu können

    std::string sensorType = "default";

    bool errorStat = false;     //if there is a malfunction, this will be set to TRUE oida

    //int errorIteration;

    int randomInt(int min, int max);     //generate a random number between min and max
public:
    const int sensorID;

    Sensor(int sensorID, std::string typeName = "default") : sensorID(sensorID), sensorType(typeName) {}
    ~Sensor() = default;


    int checkSensor();      //check status of the sensor - status 0 -> OK - status 100 -> extrem dangerous
    bool getErrorStat();    //if there is a malfunction, this will return TRUE, until the sensor will be resettet with reset()

    void sensorError();      //set the sensor to error state
    int getErrorStatIteration();   //Iteration++ - nach 3 Iterationen kann der Sensor wieder resetet werden

    void reset();

    [[nodiscard]] std::string getSensorType() const {return sensorType;};
};


#endif //ROBOTERKLAUSUR_SENSOR_H
