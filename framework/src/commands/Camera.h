/*
 * Camera.h
 *
 *  Created on: Jan 15, 2010
 *      Author: nitobi-test
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <qobject.h>
#include "xqcamera.h"
#include "xqviewfinderwidget.h"
#include "CommandManager.h"

// Forward Declaration
class CommandManager;

class Camera: public QObject
	{
	Q_OBJECT
public:
	Camera(CommandManager *cm);
	
private:
    XQCamera* m_camera;
    XQViewFinderWidget* m_viewFinder;

public slots:
	void takePicture();
	void imageCaptured(QByteArray imageData);

	};
#endif /* CAMERA_H_ */
