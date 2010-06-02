#include "xqcamera.h"
#include "xqcamera_p.h"

#include <QSize>

/*!
    \class XQCamera
    \brief The XQCamera class can be used to take photos with the device's onboard camera.
*/

/*!
    \enum XQCamera::Error

    This enum defines the possible errors for a XQCamera object.
*/
/*! \var XQCamera::Error XQCamera::NoError
    No error occured.
*/
/*! \var XQCamera::Error XQCamera::OutOfMemoryError
    Not enough memory.
*/
/*! \var XQCamera::Error XQCamera::InUseError
    Resource already in use.
*/
/*! \var XQCamera::Error XQCamera::NotReadyError
    Camera is not yet ready
*/
/*! \var XQCamera::Error XQCamera::UnknownError
    Unknown error.
*/

/*!
    Constructs a XQCamera object with the given parent.
*/
XQCamera::XQCamera(QObject* parent)
    : QObject(parent), d(new XQCameraPrivate(this))
{
}

/*!
    Destroys the XQCamera object.
*/
XQCamera::~XQCamera()
{
    delete d;
}

/*!
    Opens the camera. This function also reserves and powers on the camera.
    The cameraReady() signal  is emitted when the camera is ready to be used.
    
    \param index The index indicating which camera to open. The default value is 0.
    \return If false is returned it means an error has occurred. Call error() to get the 
    XQCamera::Error value that indicates which error occurred
    \sa error()
*/
bool XQCamera::open(int index)
{
    return d->open(index);
}

/*!
    Sets the size of image that will be captured from the camera
    \param size Requested image size
*/
void XQCamera::setCaptureSize(QSize size)
{
    d->setCaptureSize(size);
}

/*!
    Starts capturing the actual image. When the image is ready,
    the captureCompleted() signal is emitted.
    
    \return If false is returned it means an error has occurred. Call error() to get the 
    XQCamera::Error value that indicates which error occurred.
    \sa captureCompleted(), error()
*/
bool XQCamera::capture()
{
    return d->capture();
}

/*!
    Closes the camera. This function also releases and powers off the camera.
*/
void XQCamera::close()
{
    d->close();
}

/*!
    Starts focusing the camera. The focused() signal is emitted when the camera is focused.
    
	Note: Does nothing if AutoFocus is not supported.
    
    \return If false is returned it means an error has occurred. Call error() to get the 
    XQCamera::Error value that indicates which error occurred.
    \sa focused()
*/
bool XQCamera::focus()
{
    return d->focus();
}

/*!
    Cancels the focussing of the camera.
*/
void XQCamera::cancelFocus()
{
    d->cancelFocus();
}

/*!
    Returns the number of cameras available in the device.

    \return Number of cameras available on the device.
*/
int XQCamera::camerasAvailable()
{
    return XQCameraPrivate::camerasAvailable();
}

/*!
    Releases memory for the last captured image.
    Client must call this in response to \a captureCompleted(QByteArray imageData) function,
    after processing the data/bitmap is complete.
*/
void XQCamera::releaseImageBuffer()
{
    d->releaseImageBuffer();
}

/*!
    Returns the type of error that occurred if the latest function call failed. Otherwise it returns NoError
    \return Error code
*/
XQCamera::Error XQCamera::error() const
{
    return d->error();
}
    

/*!
    \fn void XQCamera::cameraReady();
    
    This signal is emitted when the camera is ready to be used. The image may
    be from viewfinder of actual capturing.
*/

/*!
    \fn void XQCamera::focused();
    
    This signal is emitted when the focus procedure has completed.
*/

/*!
    \fn void XQCamera::captureCompleted(QByteArray image);
    
    This signal is emitted when the image has been captured.
    \param image Captured image. Note that the buffer is released right after
    this function call.
*/
    
/*!
    \fn  void error(XQCamera::Error error);
    
    This signal is emitted when an error has occurred with the camera.
    \param error Indicates the type of error that has occurred.
*/

// End of file
