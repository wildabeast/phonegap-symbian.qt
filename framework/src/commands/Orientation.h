/*
 * Orientation.h
 *
 *  Created on: Jan 12, 2010
 *      Author: nitobi-test
 */

#ifndef ORIENTATION_H_
#define ORIENTATION_H_

#include <qobject.h>
#include "xqdeviceorientation.h"
#include "CommandManager.h"

//forward declaration
class CommandManager;

class Orientation : public QObject
	{
	Q_OBJECT
public:
	Orientation(CommandManager *cm);
	
private:
	XQDeviceOrientation *orientation;
	CommandManager *manager;
	
public slots:
	void start(int interval=1000);
	void stop();
	
private slots:
	void handleOrientationChanged(XQDeviceOrientation::DisplayOrientation o);
	};

#endif /* ORIENATATION_H_ */
