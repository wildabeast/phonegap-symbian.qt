/*
 * Geolocation.h
 *
 *  Created on: Nov 24, 2009
 *      Author: nitobi-test
 */

#ifndef GEOLOCATION_H_
#define GEOLOCATION_H_

#include <qobject.h>
#include "xqlocation.h"
#include "CommandManager.h"

//forward declaration
class CommandManager;

class Geolocation : public QObject
	{
	Q_OBJECT
public:
	Geolocation(CommandManager *cm);
	
private:
	XQLocation *location;
	CommandManager *manager;
	
public slots:
	void start(int interval=1000);
	void stop();
	
private slots:
	void handleLocationChanged(double latitude, double longitude, double altitude, float speed);
	};

#endif /* GEOLOCATION_H_ */
