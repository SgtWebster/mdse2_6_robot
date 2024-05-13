all: factory

factory: main.o Motor.o Robot.o Sensor.o SensorSubclasses.o
	g++ -o PROJECTNAME main.o Motor.o Robot.o Sensor.o SensorSubclasses.o-Werror -Wall

main.o: main.cpp
	g++ -c -o main.o main.cpp

Motor.o: Motor.cpp
	g++ -c -o Motor.o Motor.cpp -Werror

Robot.o: Robot.cpp
	g++ -c -o Robot.o Robot.cpp -Werror

Sensor.o: Sensor.cpp
	g++ -c -o Sensor.o Sensor.cpp -Werror

SensorSubclasses.o: SensorSubclasses.cpp
	g++ -c -o SensorSubclasses.o SensorSubclasses.cpp -Werror

clean:
	rm -f factory main.o Motor.o Robot.o Sensor.o SensorSubclasses.o