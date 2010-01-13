#include "xqsensor.h"
#include "xqsensor_p.h"

/*!
    \class XQSensor

    \brief The XQSensor is a base class for available concrete sensors.
*/

XQSensor::XQSensor(XQSensorPrivate& dd, QObject* parent):
    QObject(parent), d(&dd)
{
}

/*!
    Destroys the XQSensor object.
*/
XQSensor::~XQSensor()
{
    delete d;
}

/*!
    \enum XQSensor::Error

    This enum defines the possible errors for a XQSensor object.
*/
/*! \var XQSensor::Error XQSensor::NoError
    No error occured.
*/
/*! \var XQSensor::Error XQSensor::OutOfMemoryError
    Not enough memory.
*/
/*! \var XQSensor::Error XQSensor::NotFoundError
    Not found.
*/
/*! \var XQSensor::Error XQSensor::UnknownError
    Unknown error.
*/

/*!
    Opens the access to a sensor. If the sensor access can't be opened, the error() method
    returns an error code
    \sa close(), startReceiving(), stopReceiving(), error()
*/
void XQSensor::open()
{
    d->open();
}

/*!
    Closes the access to a sensor.
    \sa open(), startReceiving(), stopReceiving()
*/
void XQSensor::close()
{
    d->close();
}

/*!
    Starts actively monitoring the sensor and emits signals about changes in
    sensor data.
    \sa stopReceiving(), error()
*/
void XQSensor::startReceiving()
{
    d->startReceiving();
}

/*!
    Stops monitoring the sensor.
    \sa startReceiving()
*/
void XQSensor::stopReceiving()
{
    d->stopReceiving();
}

/*!
        \return The current error code or Error XQSensor::NoError if there is no error.
*/
XQSensor::Error XQSensor::error() const
{
    return d->error();
}

// End of file
