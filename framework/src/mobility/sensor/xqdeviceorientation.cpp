#include "xqdeviceorientation.h"
#include "xqdeviceorientation_p.h"

/*!
    \class XQDeviceOrientation

    \brief The XQDeviceOrientation class is used to determine the orientation
    of the device.

    Note that the orientation is calculated from the values received from
    acceleration sensor so the orientation is reliable only when the speed of
    the device is constant.
*/

/*!
    \enum XQDeviceOrientation::DisplayOrientation

    This enum defines the possible orientations of the device.
*/

/*! \var XQDeviceOrientation::DisplayOrientation XQDeviceOrientation::OrientationUndefined
    The orientation can't be determined.
*/

/*! \var XQDeviceOrientation::DisplayOrientation XQDeviceOrientation::OrientationDisplayUp
    The orientation of the device is up, i.e. standing.
*/

/*! \var XQDeviceOrientation::DisplayOrientation XQDeviceOrientation::OrientationDisplayDown
    The device is upside down, i.e. bottom up.
*/

/*! \var XQDeviceOrientation::DisplayOrientation XQDeviceOrientation::OrientationDisplayLeftUp
    The left side of the device is up.
*/

/*! \var XQDeviceOrientation::DisplayOrientation XQDeviceOrientation::OrientationDisplayRightUp
    The right side of the device is up.
*/

/*! \var XQDeviceOrientation::DisplayOrientation XQDeviceOrientation::OrientationDisplayUpwards
    The device is laying on its back.
*/

/*! \var XQDeviceOrientation::DisplayOrientation XQDeviceOrientation::OrientationDisplayDownwards
    The device is laying on its face.
*/


/*!
    Constructs a XQDeviceOrientation object with the given parent
*/
XQDeviceOrientation::XQDeviceOrientation(QObject* parent):
    QObject(parent),
    d(new XQDeviceOrientationPrivate(*this))
{
}

/*!
    Destroys the XQDeviceOrientation, deleting all its children.
*/
XQDeviceOrientation::~XQDeviceOrientation()
{
}

/*!
    Opens sensor connection
*/
void XQDeviceOrientation::open()
{
    d->open();
}

/*!
    Closes sensor connection
*/
void XQDeviceOrientation::close()
{
    d->close();
}

/*!
    Sets the rounding resolution of the rotation angles. For example, say
    the resolution is set to 10 degrees; if the raw angle is 109 degrees, then
    110 degrees will be reported, if the raw angle is 93 degrees, then 90 degrees
    will be reported.
    
    Note: If this function is not called, the
    default rounding resolution of 15 degrees is used.
    
    
    \param resolution Resolution in degrees.
*/
void XQDeviceOrientation::setResolution(int resolution)
{
    d->setResolution(resolution);
}

/*!
    \return Current rotation esolution in degrees
*/
int XQDeviceOrientation::resolution() const
{
    return d->resolution();
}

/*!
    \return X-axis rotation in degrees (0-359).
*/
int XQDeviceOrientation::xRotation() const
{
    return d->xRotation();
}

/*!
    \return Y-axis rotation in degrees (0-359).
*/
int XQDeviceOrientation::yRotation() const
{
    return d->yRotation();
}

/*!
    \return Z-axis rotation in degrees (0-359).
*/
int XQDeviceOrientation::zRotation() const
{
    return d->zRotation();
}

/*!
    \return Current device orientation
*/
XQDeviceOrientation::DisplayOrientation XQDeviceOrientation::orientation() const
{
    return d->orientation();
}

/*!
    \fn void XQDeviceOrientation::rotationChanged(int xRotation, int yRotation, int zRotation);
    
    This signal is emitted when the angle of rotation of the device has changed.

    \param xRotation Rotation of x axis in degrees (0-359).
    \param yRotation Rotation of y axis in degrees (0-359).
    \param zRotation Rotation of z axis in degrees (0-359).
*/

/*!
    \fn void XQDeviceOrientation::orientationChanged(XQDeviceOrientation::DisplayOrientation orientation);
    
    This signal is emitted when the orientation of the device has changed.

    \param orientation Current orientation
    \sa setResolution()
*/
