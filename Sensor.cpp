//
// Created by cplwe on 07.05.2024.
//
#include "Sensor.h"
#include <random>

int Sensor::randomInt(int min, int max) {
    std::random_device rand;
    std::mt19937 generatedNumber(rand());
    std::uniform_int_distribution<> dist(min, max);

    return dist(generatedNumber);    //generiert und retouriert eine Zufallszahl im min/max Bereich
}

int Sensor::checkSensor() {

    if(randomInt(0, 100) <= chanceCriticalDanger) { //Prüfung auf kritische Gefahr
        throw CriticalDangerException("ERROR: Critical Danger detected - Sensor ID: " + std::to_string(sensorID) + " SensorType: " + sensorType);
    }

    if(randomInt(0, 100) <= chanceInternalError) { //Prüfung auf internen Fehler
        this->sensorError();
        throw InternalErrorException("ERROR: Internal Error detected - Sensor ID: " + std::to_string(sensorID) + " SensorType: " + sensorType + " - set to internal sensor emergecy mode");
    }

    return randomInt(minErrorStatus, maxErrorStatus);  // Rückgabewert zwischen 0 und 100 bzw was der jeweilige Sensortype vorsieht
}


void Sensor::sensorError() {
    this->errorStat = true;
//    errorIteration = 0;
    //std::cerr << "ERROR: Sensor ID " << this->sensorID << " - " << this->sensorType << " - set to Internal ErrorState (cooldown)" << std::endl;
}

bool Sensor::getErrorStat() {
//    errorIteration++;
    return errorStat;
}

//int Sensor::getErrorStatIteration() {
//    return errorIteration;
//}

void Sensor::reset() {
    if (randomInt(0, 100) <= chanceReset) {
        std::cout << "--- Sensor ID " << this->sensorID << " - " << this->sensorType << " - reset successful" << std::endl;
        this->errorStat = false;
        //errorIteration = 0;
    } else {
        throw SensorResetException("ERROR: Sensor RESET FAILED - Sensor ID: " + std::to_string(sensorID) + " SensorType: " + sensorType);
    }
}



