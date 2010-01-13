/*
 * Orienatation.cpp
 *
 *  Created on: Jan 12, 2010
 *      Author: nitobi-test
 */

#include "Orientation.h"

Orientation::Orientation(CommandManager *cm)
	{
		manager = cm;
	}

void Orientation::start(int interval) {

	manager->debug("qt starting orientation");
	// Create the orientation sensor object
	orientation = new XQDeviceOrientation(this);
	
	// Opens orientation sensor data flow
	orientation->open();
	
	// Set the number of degrees the device must rotate
	// before you are notified
	//orientation->setResolution(5);  //degrees
	
	// Connect the X rotation change sensor signal to your application
	//connect(orientation, SIGNAL(xRotationChanged(int)),
	//	this, SLOT(updateXRotation(int)));
	
	// Connect the device orientation changed signal to your application
	connect(orientation, SIGNAL(orientationChanged(XQDeviceOrientation::DisplayOrientation)),
		this, SLOT(handleOrientationChanged(XQDeviceOrientation::DisplayOrientation)));
	
	// Read the current orientation
	//int xRotation = orientation->xRotation();


}

void Orientation::handleOrientationChanged(XQDeviceOrientation::DisplayOrientation o) {
	manager->debug("qt orientation changed");
	manager->evaluateJS("navigator.orientation.currentOrientation = " + QString::number(o));
	manager->evaluateJS("debug.log(navigator.orientation.currentOrientation);");
}

void Orientation::stop() {
	//location->stopUpdates();
}
