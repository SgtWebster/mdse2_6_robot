//
// Created by cplwe on 07.05.2024.
//

#ifndef ROBOTERKLAUSUR_ROBOT_H
#define ROBOTERKLAUSUR_ROBOT_H

#include <vector>
#include <memory>
#include <map>

#include "SensorSubclasses.h"
#include "Motor.h"



class Robot {
private:

    std::shared_ptr <Motor> roboMotor;
    std::map<int, std::shared_ptr<Sensor>> roboSensors;

    int errorIterationRobot = 0;    //...Iterationen, die der Roboter im Error Mode ist

public:

    Robot() { roboMotor = std::make_shared<Motor>();}

    ~Robot() = default;

    bool emergencyMode = false;   //...wenn true, ist der Roboter im Notfallmodus und STEHT STILL

    int addSensor(std::shared_ptr<Sensor> sensor);
    std::shared_ptr<Sensor> getSensor(int id);
    void deleteSensor(int id);
    static void eventLoop();

    void setErrorMode_Reset();
    void setEmergencyModeNow();
    //bool getEmergencyMode() {return emergencyMode;}
    int getInternalErrorIteration() const {return errorIterationRobot;}
    void riseInternalErrorIteration() {errorIterationRobot++;}


    static void bufferRefresher();

    bool checkAllSensors_ifAnyInternalError();

    static int statusCode_toSpeed(int statusCode_newSpeed);

//    void setInternalErrorMode();
//    bool getInternalErrorMode() {return internalErrorMode;}


};



#endif //ROBOTERKLAUSUR_ROBOT_H
