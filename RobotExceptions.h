//
// Created by cplwe on 10.05.2024.
//

#ifndef ROBOTERKLAUSUR_ROBOTEXCEPTIONS_H
#define ROBOTERKLAUSUR_ROBOTEXCEPTIONS_H

#include <stdexcept>

// Basisklasse für alle Exceptions - als Tochterklasse von std::runtime_error


class RobotExceptions : public std::runtime_error {
public:
    explicit RobotExceptions(const std::string& message) : std::runtime_error(message) {
    }
};

class CriticalDangerException : public RobotExceptions {
public:
    explicit CriticalDangerException(const std::string& message) : RobotExceptions(message) {
    }
};

class InternalErrorException : public RobotExceptions {
public:
    explicit InternalErrorException(const std::string& message) : RobotExceptions(message) {
    }
};

class SensorResetException : public RobotExceptions {
public:
    explicit SensorResetException(const std::string &message) : RobotExceptions(message) {
    }
};

#endif //ROBOTERKLAUSUR_ROBOTEXCEPTIONS_H
