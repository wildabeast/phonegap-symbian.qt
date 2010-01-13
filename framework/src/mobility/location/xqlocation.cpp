// INCLUDE FILES
#include "xqlocation.h"
#ifdef Q_OS_SYMBIAN
#include "xqlocation_s60_p.h"
#else
#include "xqlocation_stub_p.h"
#endif

#include <QTimer>

/****************************************************
 *
 * XQLocation
 *
 ****************************************************/
/*!
    \class XQLocation
    \brief The XQLocation class can be used to provide regular updates about one's 
           global position, and other positioning module related information.
*/    

/*!
    Constructs an XQLocation object with the given parent.
    \sa open(), startUpdates(), requestUpdate()
*/
XQLocation::XQLocation(QObject* parent)
 : QObject(parent), d(new XQLocationPrivate(this))
{
}

/*!
    Destroys the XQLocation object. If there is an open connection to the positioning module,
    it will be closed.
*/
XQLocation::~XQLocation()
{
    delete d;
}

/*!
    \enum XQLocation::Error

    This enum defines the possible errors for a XQLocation object.
*/
/*! \var XQLocation::Error XQLocation::NoError
    No error occured.
*/
/*! \var XQLocation::Error XQLocation::OutOfMemoryError
    Not enough memory.
*/
/*! \var XQLocation::Error XQLocation::OpenError
    Error opening connection to locationing services.
*/
/*! \var XQLocation::Error XQLocation::DefaultModuleNotFoundError
    Default positioning module not found.
*/
/*! \var XQLocation::Error XQLocation::ModuleNotFoundError
    Positioning module not found.
*/
/*! \var XQLocation::Error XQLocation::InvalidUpdateIntervalError
    Invalid update interval.
*/
/*! \var XQLocation::Error XQLocation::AccessDeniedError
    Access is denied to locationing services.
*/
/*! \var XQLocation::Error XQLocation::InternalError
    Internal error.
*/
/*! \var XQLocation::Error XQLocation::UnknownError
    Unknown error.
*/

/*!
    \enum XQLocation::DeviceStatus

    This enum defines the possible statuses for a XQLocation object.

    \sa status(), statusChanged()
*/
/*! \var XQLocation::DeviceStatus XQLocation::StatusError
    This state is used to indicate that there are problems when
    trying to bring the positioning module online. For example, 
    the positioning module may have been unable to
    communicate with your device or it is just not responding as expected.     
    This status should not be confused with
    the complete loss of data quality status (see TDataQualityStatus), which indicates that
    the positioning module is functioning correctly, but is currently unable to obtain position
    information. 
*/
/*! \var XQLocation::DeviceStatus XQLocation::StatusDisabled
    Although the positioning module may be working properly, it has been taken off line and is
    regarded as being unavailable to obtain position information. This is generally
    done by the user via the control panel. In this state, location API will
    not use the module.
*/
/*! \var XQLocation::DeviceStatus XQLocation::StatusInactive
    This state signifies that the positioning module is not being used by location API.
    This typically occurs because there are no clients currently obtaining positions
    from it.
*/
/*! \var XQLocation::DeviceStatus XQLocation::StatusInitialising
    This is a transient state. The positioning module is being brought out of the Inactive state
    but has not reached either the Ready or Standby modes. The initializing state
    occurs when the module is first selected to provide a client
    application with location information.
*/
/*! \var XQLocation::DeviceStatus XQLocation::StatusStandBy
    This state indicates that the positioning module has entered the Sleep or Power save mode.
    This signifies that the module is online, but it is not actively retrieving
    position information. A module generally enters this mode when the next position
    update is not required for some time and it is more efficient to partially power
    down.
    Note: Not all positioning modules support this state, particularly when there is
          external hardware. 
*/
/*! \var XQLocation::DeviceStatus XQLocation::StatusReady
    The positioning module is online and is ready to retrieve position information.
*/
/*! \var XQLocation::DeviceStatus XQLocation::StatusActive
    The positioning module is actively in the process of retrieving position
    information.
    Note: Not all positioning modules support this state, particularly when there is
          external hardware. 
*/
/*! \var XQLocation::DeviceStatus XQLocation::StatusUnknown
    This is not a valid state and must never be reported.
*/

/*!
    \enum XQLocation::DataQuality

    This enum defines the possible data quality values for a XQLocation object.

    \sa dataQuality(), dataQualityChanged()
*/
/*! \var XQLocation::DataQuality XQLocation::DataQualityLoss
    This state indicates that the accuracy and contents of the position information
    has been completely compromised. It is no longer possible to return any coherent
    data. This situation occurs if the device has lost track of all the transmitters
    (for example, satellites or base stations). It should be noted that although it
    is currently not possible to obtain position information, the device may still be
    functioning correctly. This state should not be confused with a device error
    (see DeviceStatus above).
*/
/*! \var XQLocation::DataQuality XQLocation::DataQualityPartial
    This state signifies that there has been a partial degradation in the available
    position information. In particular, it is not possible to provide the required
    (or expected) quality of information. This situation may occur if the device has
    lost track of one of the transmitters (for example, satellites or base stations).
*/
/*! \var XQLocation::DataQuality XQLocation::DataQualityNormal
    The positioning device is functioning as expected.
*/
/*! \var XQLocation::DataQuality XQLocation::DataQualityUnknown
    This is an unassigned valued. This state should only be reported during an event
    indicating that a positioning module has been removed.
*/

/*!
    Sets the interval between each update.
    
    If startUpdates() has already been called, startUpdates() must
    be called again to make interval change effective.

    \param interval The interval between updates specified in milliseconds.
    \sa updateInterval(), startUpdates()
*/
void XQLocation::setUpdateInterval(int interval)
{
    if (interval < 0) {
        interval = 0;
    }
    d->updateInterval = interval;
}

/*! 

    \return update The interval between updates in milliseconds
    \sa setUpdateInterval(), startUpdates()
*/
int XQLocation::updateInterval() const
{
    return d->updateInterval;
}

/*! 
    \return The current status of the positioning module
    \sa statusChanged(), startUpdates(), requestUpdate(), stopUpdates()
*/
XQLocation::DeviceStatus XQLocation::status() const
{
    return d->status;
}

/*!
    \return The current quality of the data returned by the positioning module
    \sa dataQualityChanged(), startUpdates(), requestUpdate(), stopUpdates()
*/
XQLocation::DataQuality XQLocation::dataQuality() const
{
    return d->dataQuality;
}

/*!
    Opens the connection to the positioning module.

    \return NoError if the connection to positioning module module was successfully opened;
            otherwise returns error code.
    \sa close(), startUpdates(), requestUpdate(), stopUpdates()
*/
XQLocation::Error XQLocation::open()
{
    return d->openConnectionToPositioner();
}

/*!
    Closes the connection to positioning module.

    \sa open(), startUpdates(), requestUpdate(), stopUpdates()
*/
void XQLocation::close()
{
    d->closeConnectionToPositioner();
}

/*!
    This is a one-off request for the current location information. The locationChanged() etc. signals will 
    be emitted with the current position values.
    If the positioning module is not ready, the object will first be initialized and will provide
    an update once it has acquired a position fix.
    If the positioning module is not available, no signal will be emitted, instead the error() signal
    will be emitted.
    
    This slot can be called regardless of whether startUpdates() has already been called.
    This is useful if you need to retrieve the current positioning module values but you do not
    need the periodic updates offered by startUpdates().

    \sa startUpdates()
*/
void XQLocation::requestUpdate()
{
    d->requestUpdate();
}

/*!
    Starts emitting positioning module value updates with the interval specified by updateInterval(),
    or less frequently if updates are not available at a particular time. If the updateInterval()
    has been set to 0, position updates are emitted as soon as a valid update becomes available.
    If startUpdates() has already been called, this restarts with then new update interval that 
    has been set by updateInterval().

    If the positioning module is not ready, the object will first be initialized and will begin to provide
    updates once it has acquired position fix.

    \sa stopUpdates(), setUpdateInterval(), updateInterval(), requestUpdate()
*/
void XQLocation::startUpdates()
{
    d->startUpdates();
}

/*!
    Starts providing updates with an update interval of msec milliseconds.
     This is an overloaded member function, provided for convenience.
    

    \sa stopUpdates(), setUpdateInterval(), updateInterval(), requestUpdate()
*/
void XQLocation::startUpdates(int msec)
{
    d->startUpdates(msec);
}


/*!
    Stops emitting positioning module value updates at regular intervals.

    \sa startUpdates(), setUpdateInterval(), updateInterval()
*/
void XQLocation::stopUpdates()
{
    d->stopUpdates();
}

/*!
    \fn void XQLocation::locationChanged(double latitude, double longitude, double altitude, float speed)

    This signal is emitted when location and speed update is available.

    \param latitude a latitude in WGS84 format
    \param longitude a longitude in WGS84 format
    \param altitude an altitude in WGS84 format
    \param speed a speed, in metres per second.
    \sa startUpdates(), requestUpdate()
*/

/*!
    \fn void XQLocation::latitudeChanged(double latitude, float accuracy)
    
    This signal is emitted when a latitude update is available.

    \param latitude a latitude in WGS84 format
    \param accuracy the horizontal accuracy, in metres.
    \sa startUpdates(), requestUpdate(), locationChanged()
*/


/*!
    \fn void XQLocation::longitudeChanged(double longitude, float accuracy)

    This signal is emitted when a longitude update is available.

    \param longitude a longitude in WGS84 format
    \param accuracy the horizontal accuracy, in metres.
    \sa startUpdates(), requestUpdate(), locationChanged()
*/

/*!
    \fn void XQLocation::altitudeChanged(double altitude, float accuracy)

    This signal is emitted when an altitude update is available.

    \param altitude an altitude in WGS84 format
    \param accuracy the vertical accuracy, in metres.
    \sa startUpdates(), requestUpdate(), locationChanged()
*/

/*!
    \fn void XQLocation::speedChanged(float speed)

    This signal is emitted when a speed update is available.

    \param speed a speed, in metres per second.
    \sa startUpdates(), requestUpdate(), locationChanged()
*/

/*!
    \fn void XQLocation::statusChanged(XQLocation::DeviceStatus status)
    
    This signal is emitted when a status update is available.

    \param status a status of positioning module.
    \sa startUpdates(), requestUpdate()
*/

/*!
    \fn void XQLocation::dataQualityChanged(XQLocation::DataQuality dataQuality)

    This signal is emitted when a data quality update is available.

    \param dataQuality a data quality of positioning module.
    \sa startUpdates(), requestUpdate()
*/

/*!
    \fn void XQLocation::numberOfSatellitesInViewChanged(int numSatellites)

    This signal is emitted when a 'satellites in view' update is available.

    \param numSatellites the number of satellites in view.
    \sa startUpdates(), requestUpdate()
*/

/*!
    \fn void XQLocation::numberOfSatellitesUsedChanged(int numSatellites)

    This signal is emitted when a 'used satellites' update is available.

    \param numSatellites The number of satellites used in the position calculation.
    \sa startUpdates(), requestUpdate()
*/

/*!
    \fn void XQLocation::error(XQLocation::Error errorCode)

    This signal is emitted when an error has occured.

    \param errorCode a error code
    \sa startUpdates(), requestUpdate()
*/

// End of file
