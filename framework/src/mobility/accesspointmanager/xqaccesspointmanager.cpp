// INCLUDE FILES
#include "xqaccesspointmanager.h"
#include "xqwlan_p.h"
#ifdef Q_OS_SYMBIAN
#include "xqaccesspointmanager_s60_p.h"
#else
#include "xqaccesspointmanager_stub_p.h"
#endif

/****************************************************
 *
 * XQAccessPointManager
 *
 ****************************************************/
/*!
    \class XQAccessPointManager

    \brief The XQAccessPointManager class can be used to list the available
           Internet Access Points and to set the Access Point to use for internet access.
*/

/*!
    Constructs a XQAccessPointManager object with the given parent.
    \sa listIAPs(), defaultIAP(), setDefaultIAP()
*/
XQAccessPointManager::XQAccessPointManager(QObject *parent)
    : QObject(parent),
      d(new XQAccessPointManagerPrivate)
{
}

/*!
    Destroys the XQAccessPointManager object.
*/
XQAccessPointManager::~XQAccessPointManager()
{
    delete d;
}

/*!
    Returns the Access Point that will be used for internet access(i.e. default Access Point)
    
    Note: An Access Point will only be returned if a default Access Point
          has been set using the setDefaultAccessPoint() method.

    \return currently used Access Point on success; otherwise returns null Access Point
    \sa setDefaultAccessPoint()
*/
const XQAccessPoint& XQAccessPointManager::defaultAccessPoint() const
{
    return d->defaultAccessPoint();
}

/*!
    Returns true if SetDefaultAccessPoint is supported; otherwise returns false.
    
    Note: SetDefaultAccessPoint is not supported by the current Open C release.
           A new release of Open C will be coming out soon that does support this function.

    \return true if SetDefaultAccessPoint is supported; otherwise returns false.

    \sa defaultAccessPoint(), setDefaultAccessPoint()
*/
bool XQAccessPointManager::isSetDefaultAccessPointSupported() const
{
    return d->isSetDefaultAccessPointSupported();
}

/*!
    Returns the list of Access Points.
    
    Note: All access points are listed, including access
          points that can not be currently used to connect
          internet.

    \return The list of all Access Points.
    \sa defaultAccessPoint(), setDefaultAccessPoint()
*/
QList<XQAccessPoint> XQAccessPointManager::accessPoints() const
{
    return d->accessPoints();
}

/*!
    Returns the list of available Access Points.
    
    Note: Not all access points are returned. The returned list
          contains only the access points that can currently
          be used to connect to the internet.

    \return The list of available Access Points.
    \sa defaultAccessPoint(), setDefaultAccessPoint()
*/
QList<XQAccessPoint> XQAccessPointManager::availableAccessPoints() const
{
    return d->availableAccessPoints();
}

/*!
    \return The list of Access Points that are currently providing
    a connection to the internet.

    \sa defaultAccessPoint(), setDefaultAccessPoint()
*/
QList<XQAccessPoint> XQAccessPointManager::activeAccessPoints() const
{
    return d->activeAccessPoints();
}

/*!
    Sets the default Access Point.
    After calling this method, all Qt network connections from your application will use
    the given Access Point.

    \return True if the Access Point was successfully set; otherwise returns false.
    \sa defaultAccessPoint()
*/
bool XQAccessPointManager::setDefaultAccessPoint(const XQAccessPoint& accessPoint)
{
    return d->setDefaultAccessPoint(accessPoint);
}

/*!
    Uses the network access behaviour according to the system's default settings.
    
    If the system normally shows an access point selection dialog when connecting to the internet,
    that dialog will be shown to the user when this method is called.
    
    If the system has been set up to use a default access point for connections to the internet,
    this method will return that access point. The access point selection dialog will not be shown to user.
 
    If a connection can be succesfully initialized, the Access Point for the connection will be returned
    to the caller.
    
    Note: setDefaultAccessPoint() must be called to actually take the returned Access Point into use,
    i.e. so that internet connections will connect through that Access Point.

    \return Access Point on success; otherwise returns null Access Point.
    \sa setDefaultAccessPoint()
*/
XQAccessPoint XQAccessPointManager::systemAccessPoint() const
{
    return d->systemAccessPoint();
}

/*!
    If a preferred Access Point can be found, the Access Point will be returned
    to the caller. The preferred Access Point is determined using the following rules/order:
    
    \li If a network connection is already active, it returns the Access Point for
       the active connection.
    \li If a WLAN Access Point is available, it returns the first WLAN Access Point.
    \li If a GPRS/3G Access Point is available, it returns the first GPRS/3G Access Point<br>
    
    Note: setDefaultAccessPoint() must be called to actually take the Access Point into use.

    \return Preferred Access Point on success; otherwise returns a null Access Point.
    \sa setDefaultAccessPoint()
*/
XQAccessPoint XQAccessPointManager::preferredAccessPoint() const
{
    return d->preferredAccessPoint();
}

/*!
    \return Access Point with the given id. If there is no Access Point with that id, then
    a null Access Point is returned.
*/
XQAccessPoint XQAccessPointManager::accessPointById(unsigned long int id) const
{
    return d->accessPointById(id);
}

/*!
    \return The list of available WLANs.
*/
QList<XQWLAN> XQAccessPointManager::availableWLANs() const
{
    return d->availableWLANs2();
}

/****************************************************
 *
 * XQAccessPoint
 *
 ****************************************************/
class XQAccessPointPrivate
{
public:
    XQAccessPointPrivate(): ref(1), id(0), modemBearer(XQAccessPoint::ModemBearerUnknown)  {}
    XQAccessPointPrivate(const XQAccessPointPrivate& copy)
        : ref(1),id(copy.id), name(copy.name), gprsName(copy.gprsName) {}
    ~XQAccessPointPrivate() {}
    
    QAtomicInt        ref;
    unsigned long int id;
    QString           name;
    QString           gprsName;
    XQAccessPoint::ModemBearer modemBearer;
};

/*!
    \class XQAccessPoint

    \brief The XQAccessPoint class can be used for storing and handling internet
           Access Points.

*/

/*!
    Constructs a null XQAccessPoint object
*/
XQAccessPoint::XQAccessPoint()
    :  d(0)
{
}

/*!
    Constructs a new XQAccessPoint object using the given \a name and \a id.

    \param name The name of the Access Point
    \param id The id of the Access Point
*/
XQAccessPoint::XQAccessPoint(const QString& name, unsigned long int id)
    :  d(new XQAccessPointPrivate)
{
    d->id = id;
    d->name = name;
}

/*!
    Constructs a copy of the \a other Access Point.

    \param other The access point to be copied
*/
XQAccessPoint::XQAccessPoint(const XQAccessPoint& other)
    : d(other.d)
{
    if (d) {
        d->ref.ref();
    }
}

/*!
    Destroys the XQAccessPoint object.
*/
XQAccessPoint::~XQAccessPoint()
{
}

/*!
    Sets the Access Point id.

    \sa id()
*/
void XQAccessPoint::setId(unsigned long int id)
{
    detach();
    d->id = id;
}

/*!
    \return The id for this access point
    \sa setId()
*/
unsigned long int XQAccessPoint::id() const
{
    return d ? d->id : 0;
}

/*!
    Sets the Access Point name.

    \sa name()
*/
void XQAccessPoint::setName(const QString& name)
{
    detach();
    d->name = name;
}

/*!
    \return The name for this access point
    \sa setName()
*/
QString XQAccessPoint::name() const
{
    return d ? d->name : QString();
}

/*!
    Sets the Access Point GPRS name.

    \sa gprsName()
*/
void XQAccessPoint::setGprsName(const QString& name)
{
    detach();
    d->gprsName = name;
}

/*!
    \return The GPRS name for this access point
    \sa setGPRSName()
*/
QString XQAccessPoint::gprsName() const
{
    return d ? d->gprsName : QString();
}

/*!
    Sets the Access Point modem bearer.

    \sa modemBearer()
*/
void XQAccessPoint::setModemBearer(XQAccessPoint::ModemBearer bearer)
{
    detach();
    d->modemBearer = bearer;
}

/*!
    \return The modem bearer for this access point
    \sa setModemBearer()
*/
XQAccessPoint::ModemBearer XQAccessPoint::modemBearer() const
{
    return d ? d->modemBearer : XQAccessPoint::ModemBearerUnknown;
}

/*!
    \return True if the Access Point object is null; otherwise returns false.
*/
bool XQAccessPoint::isNull() const
{
    return !d; 
}


/*!
    Assigns the \a other Access Point to this Access Point and returns a
    reference to this Access Point.
*/
XQAccessPoint& XQAccessPoint::operator=(const XQAccessPoint& other)
{
    if (d == other.d) {
        return *this;
    }
    if (other.d) {
        other.d->ref.ref();
    }
    if (d && !d->ref.deref()) {
        delete d;
    }
    d = other.d;
    return *this;
}

void XQAccessPoint::detach()
{
    if (!d) {
        d = new XQAccessPointPrivate;
    } else {
        qAtomicDetach(d);
    }
}


/****************************************************
 *
 * XQWLAN
 *
 ****************************************************/
/*!
    \class XQWLAN

    \brief The XQWLAN class can be used for reading WLAN related information.
    Note: You can view information about the WLANS, but the
    XQAccessPointManager API does not provide a way to take the WLAN into use.

*/

/*!
    Constructs a null XQWLAN object
*/
XQWLAN::XQWLAN()
    : d(0)
{
}

/*!
    Constructs a copy of the \a other WLAN.

    \param other the WLAN to be copied
*/
XQWLAN::XQWLAN(const XQWLAN& other)
    : d(other.d)
{
    if (d) {
        d->ref.ref();
    }
}

/*!
    Destroys the XQWLAN object.
*/
XQWLAN::~XQWLAN()
{
    if (d && !d->ref.deref()) {
        delete d;
    }
}
 
/*!
    \return the name (SSID) of the WLAN.
*/
QString XQWLAN::name() const
{
    return d ? d->ssid : QString(); 
}

/*!
    \return The MAC Address of the WLAN
*/
QString XQWLAN::macAddress() const
{
    return d ? d->mac : QString(); 
}

/*!
    \return The signal strength of the WLAN
*/
short int XQWLAN::signalStrength() const
{
    return d ? d->signalStrength : -1;
}

/*!
    \return True if this WLAN uses a preshared key; otherwise returns false
*/
bool XQWLAN::usesPreSharedKey() const
{
    return d ? d->usesPreSharedKey : false;
}

/*!
    \return The network mode of the WLAN
*/
XQWLAN::WlanNetworkMode XQWLAN::networkMode() const
{
    return d ? d->networkMode : XQWLAN::WlanNetworkModeUnknown;
}

/*!
    \return The security mode of the WLAN
*/
XQWLAN::WlanSecurityMode XQWLAN::securityMode() const
{
    return d ? d->securityMode : XQWLAN::WlanSecurityModeUnknown;
}

/*!
    \return True if this WLAN is visible; otherwise returns false
*/
bool XQWLAN::isVisible() const
{
    return d ? d->visibility : false;
}

/*!
 \return True if this WLAN object is null; otherwise returns false
*/
bool XQWLAN::isNull() const
{
    return !d;
}

/*!
    Assigns the \a other WLAN to this WLAN and returns a
    reference to this WLAN.
*/
XQWLAN& XQWLAN::operator=(const XQWLAN& other)
{
    if (d == other.d) {
        return *this;
    }
    if (other.d) {
        other.d->ref.ref();
    }
    if (d && !d->ref.deref()) {
        delete d;
    }
    d = other.d;
    return *this;
}

void XQWLAN::detach()
{
    if (!d) {
        d = new XQWLANPrivate;
    } else {
        qAtomicDetach(d);
    }
}

// End of file
