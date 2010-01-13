#include "XQAccSensor.h"
#include "XQAccSensor_p.h"

/*!
    \class XQAccelerationSensor

    \brief The XQAccelerationSensor class is used to determine current
    acceleration of the device.

    Note that the orientation of the device affects on the acceleration sensors
    due to acceleration caused by Earth's gravity. Therefore it is wrong to
    assume that the axis values are zero when the device stands still.
    
    XQAccelerationSensor axis data shouldn't be directly used to determine the
    device orientation, though. It may sound good to use XQAccelerationSensor
    in a game that is controlled by leaning the device but the data ranges and
    even axis orientation may differ highly in different devices. Instead, use
    the XQDeviceOrientation class for that purpose.
*/

/*!
    Constructs a XQAccelerationSensor object with parent \a parent.
    \sa open(), startReceiving()
*/
XQAccelerationSensor::XQAccelerationSensor(QObject* parent):
    XQSensor(*new XQAccelerationSensorPrivate(*this), parent)
{
}

/*!
    Destroys the XQAccelerationSensor, deleting all its children.
*/
XQAccelerationSensor::~XQAccelerationSensor()
{
}

/*!
    Adds the given filter to the top of filter stack.
*/
void XQAccelerationSensor::addFilter(XQAbstractAccelerationSensorFilter& filter)
{
    static_cast<XQAccelerationSensorPrivate*>(d)->addFilter(filter);
}


/*!
    \return The list of filters that are on the stack
*/
QList<XQAbstractAccelerationSensorFilter*>& XQAccelerationSensor::filters()
{
    return static_cast<XQAccelerationSensorPrivate*>(d)->filters();
}

/*!
    \return Raw x-axis acceleration data
*/
int XQAccelerationSensor::xAcceleration() const
{
    return static_cast<XQAccelerationSensorPrivate*>(d)->xAcceleration();
}

/*!
    \return Raw y-axis acceleration data
*/
int XQAccelerationSensor::yAcceleration() const
{
    return static_cast<XQAccelerationSensorPrivate*>(d)->yAcceleration();
}

/*!
    \return Raw z-axis acceleration data
*/
int XQAccelerationSensor::zAcceleration() const
{
    return static_cast<XQAccelerationSensorPrivate*>(d)->zAcceleration();
}

/*!
    \class XQAbstractAccelerationSensorFilter

    \brief The XQAbstractAccelerationSensorFilter is an interface that can be
    used to filter and/or manipulate data received from the acceleration sensor.
    
    The client which is interested in sensor events implements this interface.

    There may potentially be several filters in stack. They are called in
    reverse order (i.e. the last filter added to the stack is always called first).
    Each filter may manipulate the acceleration data and also allow or deny the next filter in
    stack to be called.
*/

/*!
    \fn virtual bool XQAbstractAccelerationSensorFilter::filter(int& xAcceleration, int& yAcceleration, int& zAcceleration) = 0;
    
    This function is called when the acceleration of the device changes.

    \param xAcceleration Reference to x-axis acceleration value
    \param yAcceleration Reference to y-axis acceleration value
    \param zAcceleration Reference to z-axis acceleration value
    \return True if this filter has "filtered out" the event, i.e. the event
    is not to be sent to the next filter in the stack. Returning false allows the next
    filter in the stack to be called.
    \sa XQSensor::startReceiving()
*/

/*!
    \class XQAccelerationDataPostFilter

    \brief The XQAccelerationDataPostFilter is a special acceleration sensor
    filter. It modifies the acceleration sensor data so that the orientation of each
    acceleration axis is the same for all devices.
*/
