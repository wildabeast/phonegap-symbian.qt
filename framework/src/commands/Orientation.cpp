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
	QString oVal = "";
	if (o == XQDeviceOrientation::OrientationDisplayUp) {
		oVal = "0";
	}
	else if (o == XQDeviceOrientation::OrientationDisplayDown) {
		oVal = "1";
	}
	else if (o == XQDeviceOrientation::OrientationDisplayLeftUp) {
		oVal = "2";
	}
	else if (o == XQDeviceOrientation::OrientationDisplayRightUp) {
		oVal = "3";
	}
	else if (o == XQDeviceOrientation::OrientationDisplayUpwards) {
		oVal = "4";
	}
	else if (o == XQDeviceOrientation::OrientationDisplayDownwards) {
		oVal = "5";
	}
	else {
		manager->debug("qt invalid orientation");
		return;
	}

	manager->evaluateJS("navigator.orientation.setOrientation(" + oVal + ");");
	//manager->evaluateJS("debug.log('orientation:' + navigator.orientation.currentOrientation);");
}

void Orientation::stop() {
	orientation->close();
}
