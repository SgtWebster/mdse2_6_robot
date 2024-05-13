//
// Created by cplwe on 07.05.2024.
//

#include <iostream>
#include <unistd.h>


#include "Robot.h"

#include <cstdlib>
//#include "Sensor.h"


static int sensorID = 0;   //eindeutiger Identifer für Sensoren
#define MAX_ITERATION 30   //TODO - bei Abgabe auf 30 setzten
#define DEFAULT_SPEED 10


void Robot::eventLoop() {

    bufferRefresher();
    std::cout << "# # # Robot System by Oliver Ulrich Weber - Version 1.0 # # #" << std::endl;
    std::cout << "Booting system...  ...please stand bye..." << std::endl;

    std::shared_ptr<Robot> robo = std::make_shared<Robot>();
    std::cout << "DEBUG: Robot initialized" << std::endl;

    if (robo->roboMotor == nullptr) {
        std::cerr << "Robot initializion failed!" << std::endl;
        return;
    }

//    for (int i = 0; i < 3 ;i++) {   //TODO  -- wie soll ich den Schmarn eingeben?
//        robo->addSensor(std::make_shared<Sensor>(sensorID));
//        std::cout << "DEBUG: SENSOR - " << robo->getSensor(sensorID-1)->getSensorType() << " initialized - ID: " << sensorID-1 << std::endl;
//    }

    robo->addSensor(std::make_shared<UltrasonicSensor>(sensorID));
    std::cout << "DEBUG: " << robo->getSensor(sensorID-1)->getSensorType() << " initialized - global sensor ID: " << sensorID-1 << std::endl;

    robo->addSensor(std::make_shared<LaserSensor>(sensorID));
    std::cout << "DEBUG: " << robo->getSensor(sensorID-1)->getSensorType() << " initialized - global sensor ID: " << sensorID-1 << std::endl;

    robo->addSensor(std::make_shared<CameraSensor>(sensorID));
    std::cout << "DEBUG: " << robo->getSensor(sensorID-1)->getSensorType() << " initialized - global sensor ID: " << sensorID-1 << std::endl;

    bufferRefresher();
    std::cout << "System booted. Starting with operation." << std::endl;
    //vorab initalisierung für while schleife
    int iterationLoop = 0;
    int sensorStatus = 0;
    int sensorStatusTMP = 0;
    int i;
    robo->roboMotor->setSpeed(DEFAULT_SPEED);

    std::shared_ptr<Sensor> sensorTEMP = nullptr;

    bufferRefresher();
    std::cout.flush();
    while(true) {   //EIGENTLICHER PROGRAMMABLAUF!
        std::cout << "# # # # # # # # # # --- DEBUG: Iteration Counter: " << iterationLoop << " --- # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # " << std::endl;
        std::cout << "# Iteration Start Conditions: Speed: " << robo->roboMotor->getSpeed() << " - Robot emergecy mode: " << (robo->emergencyMode ? "ON" : "OFF") << " - Internal sensor emergecy mode : " << (robo->checkAllSensors_ifAnyInternalError() ? "ON" : "OFF") << std::endl;
        std::cout.flush();
        sensorStatus = 0;  //reset Iteration
        sensorStatusTMP = 0; //reset Iteration


        if ((robo->emergencyMode) && ((robo->getInternalErrorIteration()) < 4)) {  //wenn der Sensor einen Fehler hat, dann wird er resettet (versucht)
            std::cout << "..." << std::endl;
            std::cout << "DEBUG: Robot in emergency mode!                       ...please stand bye..." << std::endl;
            std::cout << "..." << std::endl;
        }
        else {

            for(i = 0; i < robo->roboSensors.size(); i++) {
                if((robo->emergencyMode) && ((robo->getInternalErrorIteration()) >= 4)) {
                    robo->setErrorMode_Reset();
                    std::cout << "DEBUG: Robot in emergency mode reset. Continuing with normal operation." << std::endl;
                }

                sensorTEMP = robo->getSensor(i);

                if (sensorTEMP == nullptr) {  //wenn der Sensor gar nicht erst exestiert, dann die Iteration überspringen.
                    std::cerr << "Sensor with ID " << i << " not initialized. Skipping iteration." << std::endl;
                    continue;
                }

                if (sensorTEMP->getErrorStat()) {  //wenn der Sensor einen Fehler hat, dann wird er resetet (versucht)
                    std::cout << "DEBUG: Sensor " << sensorTEMP->sensorID << " - " << sensorTEMP->getSensorType() << " ..." <<  std::endl;
                    std::cout << "--- Sensor in error-status..." << std::endl;
                    std::cout << "--- Start trying sensor reset." << std::endl;
                    try {
                        sensorTEMP->reset();
                        std::cout << "--- starts normal operation within next iteration." << std::endl;
                    }
                    catch (SensorResetException &errorReset) {
                        std::cout << "--- Sensor reset not successful. Sensor still in error-status." << std::endl;
                        std::cerr << errorReset.what() << std::endl;
                    }
                } else {
                    bufferRefresher();
                    try {
                        std::cout << "DEBUG: Status-Test for Sensor " << sensorTEMP->sensorID << " - ";
                        sensorStatusTMP = sensorTEMP->checkSensor();
                        std::cout << sensorStatusTMP << " Danger Level. (successful testrun without exceptions)" << std::endl;

                    }
                    catch (CriticalDangerException &errorCrit) {
                        robo->setEmergencyModeNow();
                        robo->roboMotor->emergencyBrake();
                        std::cout << sensorTEMP->getSensorType() << " - ID: " << sensorTEMP->sensorID << ":" << std::endl;
                        std::cout << "---ALERT! Critical danger detected. Emergency brake!" << std::endl;
                        std::cerr << errorCrit.what() << std::endl;
                        break;
                    }
                    catch (InternalErrorException &errorInternal) {
                        std::cout << sensorTEMP->getSensorType() << " - ID: " << sensorTEMP->sensorID << ":" << std::endl;
                        std::cout << "---ERROR. Internal sensor error. Sensor set to internal-emergecy-status." << std::endl;
                        std::cerr << errorInternal.what() << std::endl;
                    }
                    catch (...) {
                        std::cout << "TEST FAILED:" << std::endl;
                        std::cerr << "---CIRITICAL ERROR: Unhandeled Exception" << std::endl;
                    }
                }

                if (robo->emergencyMode) {
                    std::cout << "### Due to critical danger, emergency brake is active" << std::endl;
                    robo->roboMotor->emergencyBrake();
                }
                else if (sensorStatusTMP >= sensorStatus) {
                    sensorStatus = sensorStatusTMP;
                }

            }

        }

        //adjust speed
        if (robo->emergencyMode) {
            std::cout << "### Due to critical danger, emergency brake is active" << std::endl;
            robo->roboMotor->emergencyBrake();
        } else {

            if (robo->checkAllSensors_ifAnyInternalError()) {
                std::cout << "### Due to internal sensor emergecy-mode, maximum speed is capped to 1" << std::endl;
                robo->roboMotor->setSpeed(statusCode_toSpeed(sensorStatus));
                if (robo->roboMotor->getSpeed() > 1) {
                    robo->roboMotor->setSpeed(1);
                }
            } else {
                    std::cout << "--- Speed adjustment regarding to danger level " << sensorStatus << std::endl;
                    robo->roboMotor->setSpeed(statusCode_toSpeed(sensorStatus));
                    std::cout << "--- Speed adjusted to " << statusCode_toSpeed(sensorStatus) << " - normal operating" << std::endl;
                }
        }

        if (robo->emergencyMode) {
            std::cout << "### Emergecy mode is active ###" << std::endl;
            robo->riseInternalErrorIteration();
        }
        std::cout << "# Iteration End Conditions - Speed: " << robo->roboMotor->getSpeed() << " - Robot emergecy mode: " << (robo->emergencyMode ? "ON" : "OFF") << " - Internal sensor emergecy mode : " << (robo->checkAllSensors_ifAnyInternalError() ? "ON" : "OFF") << std::endl;
        std::cout << "# Occured errors: " << std::endl;
        bufferRefresher();
        iterationLoop++;
        if (iterationLoop >= MAX_ITERATION) {break;}
        sleep(1);
    }
    //return;
}

int Robot::addSensor(std::shared_ptr<Sensor> sensor) {
    this->roboSensors.emplace(sensorID, std::shared_ptr<Sensor>(std::move(sensor)));
    return ++sensorID;
}

std::shared_ptr<Sensor> Robot::getSensor(int id) {
    if (id < this->roboSensors.size() && id >= 0) {
        return this->roboSensors.find(id)->second;
    } else {
        std::cerr << "Sensor with ID " << id << " not initialized" << std::endl;
        return nullptr;
    }
}

void Robot::deleteSensor(int id) {
    if (id < this->roboSensors.size() && id >= 0 && this->roboSensors[id] != nullptr) {
        this->roboSensors[id] = nullptr;
        std::cout << "Sensor with ID " << id << " deleted" << std::endl;
    } else {
        std::cerr << "Sensor with ID " << id << " not initialized" << std::endl;
    }
}

void Robot::bufferRefresher() {
    std::cout.flush();
    std::cerr.flush();
}

bool Robot::checkAllSensors_ifAnyInternalError() {
    for(int i = 0; i < this->roboSensors.size(); i++) {
        if (this->getSensor(i)->getErrorStat()) {
            return true;
        }
    }
    return false;
}

int Robot::statusCode_toSpeed(int statusCode_newSpeed) {
    int result = 10 - (statusCode_newSpeed / 10);
    return result;
}



void Robot::setEmergencyModeNow() {
    emergencyMode = true;
    errorIterationRobot = 0;
}

void Robot::setErrorMode_Reset() {
    emergencyMode = false;
    errorIterationRobot = 0;
}

