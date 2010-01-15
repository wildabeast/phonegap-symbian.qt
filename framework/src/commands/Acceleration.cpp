/*
 * Acceleration.cpp
 *
 *  Created on: Jan 12, 2010
 *      Author: nitobi-test
 */

#include "Acceleration.h"

Acceleration::Acceleration(CommandManager *cm)
	{
		manager = cm;
	}

void Acceleration::start(int interval) {
	accel = new XQAccelerationSensor(this);
	
	accel->open();
	accel->addFilter(*this);
	accel->startReceiving();
}

bool Acceleration::filter(int& xAcceleration, int& yAcceleration, int& zAcceleration)
{
    //labelX->setText(QString("X = %1").arg(xAcceleration));

	manager->evaluateJS("navigator.accelerometer.setAcceleration(" + QString::number(xAcceleration) + ", " + 
			QString::number(yAcceleration) + ", " +
			QString::number(zAcceleration) + ")");

    return false;
}

void Acceleration::stop() {
	accel->close();
}
