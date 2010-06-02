/*
 * Camera.cpp
 *
 *  Created on: Jan 15, 2010
 *      Author: nitobi-test
 */

#include "Camera.h"
#include <QTimer>

Camera::Camera(CommandManager *cm)
	{
    m_camera = new XQCamera(this);
    m_viewFinder = new XQViewFinderWidget;
    m_viewFinder->setCamera(*m_camera);
    m_viewFinder->setViewfinderSize(QSize(640, 480));
    
    //connect(m_camera, SIGNAL(captureCompleted(QByteArray)), this, SLOT(imageCaptured(QByteArray)));
    //connect(m_camera, SIGNAL(captureCompleted(QImage*)), this, SLOT(captured(QImage*)));
    
    //connect(m_camera, SIGNAL(cameraReady()), m_viewFinder, SLOT(start()));
    //connect(captureButton, SIGNAL(clicked()), m_camera, SLOT(capture()));
    
    //m_camera->open(0);

	}

void Camera::takePicture() {
	m_viewFinder->start();
}

void Camera::imageCaptured(QByteArray imageData)
{
    // Stop the viewfinder and show the captured image in the viewfinder
    m_viewFinder->stop();

    // Get the image data into an image class 
    QImage capturedImage = QImage::fromData(imageData);
    m_viewFinder->setImage(capturedImage);
    m_camera->releaseImageBuffer();

    // Restart the viewfinder after 5 seconds
    QTimer::singleShot(5000, m_viewFinder, SLOT(start()));
}
