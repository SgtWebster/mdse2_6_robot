//
// Created by cplwe on 07.05.2024.
//

#ifndef ROBOTERKLAUSUR_MOTOR_H
#define ROBOTERKLAUSUR_MOTOR_H

//#include "Robot.h"

class Motor {
public:
    Motor() = default; //TODO
    ~Motor() = default;

    void setSpeed(int speed) {motorSpeed = speed;};    //setter mit inplace implementierung
    int getSpeed() const {return motorSpeed;};         //getter mit inplace implementierung

    void emergencyBrake();           //setter mit inplace Emergency Brake implementierung



private:
    int motorSpeed = 0;
    static const int maxSpeed = 10;
    static const int minSpeed = 0;
};


#endif //ROBOTERKLAUSUR_MOTOR_H
