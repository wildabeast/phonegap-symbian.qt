/*
 * Geolocation.cpp
 *
 *  Created on: Nov 24, 2009
 *      Author: nitobi-test
 */

#include "Geolocation.h"

Geolocation::Geolocation(CommandManager *cm)
	{
		manager = cm;
	}

void Geolocation::start(int interval) {
	location = new XQLocation(this);
	location->open();
	
	// Connect the locationChanged() signal
	connect(location, SIGNAL(locationChanged(double, double, double, float)),
		this, SLOT(handleLocationChanged(double, double, double, float)));
	
	// One-off request for location
	location->startUpdates(interval);

}

void Geolocation::handleLocationChanged(double latitude, double longitude, double altitude, float speed) {
	manager->evaluateJS("navigator.geolocation.lastPosition = { coords: { latitude: " + 
			QString::number(latitude) + ", " +
			"longitude: " + QString::number(longitude) + ", " +
			"altitude: " + QString::number(altitude) + ", " +
			"speed: " + QString::number(speed) + "}, " +
			"timestamp: new Date().getTime() };");
}

void Geolocation::stop() {
	location->stopUpdates();
}
