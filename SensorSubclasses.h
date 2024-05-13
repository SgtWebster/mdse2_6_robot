//
// Created by cplwe on 07.05.2024.
//

#ifndef ROBOTERKLAUSUR_SENSORSUBCLASSES_H
#define ROBOTERKLAUSUR_SENSORSUBCLASSES_H

#include "Sensor.h"

#include <utility>

class UltrasonicSensor : public Sensor {
    public:
        explicit UltrasonicSensor(int sensorID, std::string typeName = "UltrasonicSensor") : Sensor(sensorID, std::move(typeName)) {}

protected:
//    static constexpr int minErrorStatus = 0;
    static constexpr int maxErrorStatus = 600;

    static constexpr int chanceCriticalDanger = 10;    //...Sensor hat eine x Wahrscheinlichkeit um einen Critical Fehler zu werfen  (zB x = 10 für 10%ige wahrscheinlichkeit)
    static constexpr int chanceInternalError = 20;     //...Sensor hat eine x Wahrscheinlichkeit um einen Internal Fehler zu werfen

    static constexpr int chanceReset = 60;             //...Sensor hat eine x Wahrscheinlichkeit um nach einem Fehler wieder resetet werden zu können
};


class LaserSensor : public Sensor {
public:
    explicit LaserSensor(int sensorID, std::string typeName = "LaserSensor") : Sensor(sensorID, std::move(typeName)) {}

protected:
//    static constexpr int minErrorStatus = 0;
    static constexpr int maxErrorStatus = 80;

    static constexpr int chanceCriticalDanger = 20;    //...Sensor hat eine x Wahrscheinlichkeit um einen Critical Fehler zu werfen  (zB x = 10 für 10%ige wahrscheinlichkeit)
    static constexpr int chanceInternalError = 10;     //...Sensor hat eine x Wahrscheinlichkeit um einen Internal Fehler zu werfen

    static constexpr int chanceReset = 50;             //...Sensor hat eine x Wahrscheinlichkeit um nach einem Fehler wieder resetet werden zu können
};

class CameraSensor : public Sensor {
public:
    explicit CameraSensor(int sensorID, std::string typeName = "CameraSensor") : Sensor(sensorID, std::move(typeName)) {}

protected:
//    static constexpr int minErrorStatus = 0;
    static constexpr int maxErrorStatus = 100;

    static constexpr int chanceCriticalDanger = 25;    //...Sensor hat eine x Wahrscheinlichkeit um einen Critical Fehler zu werfen  (zB x = 10 für 10%ige wahrscheinlichkeit)
    static constexpr int chanceInternalError = 40;     //...Sensor hat eine x Wahrscheinlichkeit um einen Internal Fehler zu werfen

    static constexpr int chanceReset = 40;             //...Sensor hat eine x Wahrscheinlichkeit um nach einem Fehler wieder resetet werden zu können
};


#endif //ROBOTERKLAUSUR_SENSORSUBCLASSES_H
