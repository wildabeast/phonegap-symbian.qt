/*
 * Acceleration.h
 *
 *  Created on: Jan 12, 2010
 *      Author: nitobi-test
 */

#ifndef ACCELERATION_H_
#define ACCELERATION_H_

#include <qobject.h>
#include "xqaccsensor.h"
#include "CommandManager.h"

// Forward Declaration
class CommandManager;

class Acceleration : public QObject,
	public XQAbstractAccelerationSensorFilter
	{
	Q_OBJECT
public:
	Acceleration(CommandManager *cm);
	
private:
	XQAccelerationSensor *accel;
	CommandManager *manager;

protected:
	bool filter(int& xAcceleration, int& yAcceleration, int& zAcceleration);
	
public slots:
	void start(int interval=1000);
	void stop();
	};

#endif /* ACCELERATION_H_ */
