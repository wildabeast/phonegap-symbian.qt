PhoneGap Symbian Qt
=============================================================
PhoneGap Symbian Qt is a Symbian OS Application framework, built upon the Qt framework for Symbian, which allow a developer to build 
a native application for Symbian S60 devices using web technologies. The same set of web application files can be ported to PhoneGap
BlackBerry, iPhone, Android & Palm.

Pre-requisites
-------------------------------------------------------------
In order to build PhoneGap Symbian Qt, the following tools are required:

1. Carbide C++ (Optional, required only for PhoneGap Developers as opposed to PhoneGap users)
2. ActiverPerl v5
3. S60 SDK (3rd Ed. FP1 or higher. But probably 5th edition). Ensure you run plugins/vistapatch if you are on ms vista.
4. Open C/C++ Plugin
5. Qt 4.6 for Symbian (http://qt.nokia.com/products/platform/symbian)

Info on 1-4: http://doc.trolltech.com/4.6-snapshot/requirements-symbian.html

Getting Started
-------------------------------------------------------------
Copy or create your index.html and associated js, css, and assets to phonegap-symbian.qt/framework/www/.
Run Start -> Programs -> Qt for Symbian by Nokia v4.6.0 -> Qt for Symbian command prompt, cd to phonegap-symbian.qt/.
Make targets:
- make run : to build your application and run it in the S60 emulator
- make build : to build a .sis file for deployment to a device

Some of the device features used by PhoneGap require Application signing. Refer to www.symbiansigned.com for info
on the different types. Use Open Signed Online to quickly get a signed sis file which can be installed to one device
only.

Changing App Name
-------------------------------------------------------------
Open the file phonegap-symbian.qt/framework/PhoneGap.pkg, and change PhoneGap to your app name in the following lines:

; standard SIS file header
#{"PhoneGap"},(0xE666C00E),1,0,0

Using the Debug Console
-------------------------------------------------------------
Open the file phonegap-symbian.qt/framework/src/BrowserView.cpp, and change the showConsole variable to true:

const bool showConsole = true;

Then to print to the debug console from javascript, simply use 

debug.log("booyakasha");

Notes
-------------------------------------------------------------
- APIs complete so far: Geolocation, Vibration, Accelerometer, Orientation
- Still in development; report bugs to the phonegap google group at groups.google.com/group/phonegap
