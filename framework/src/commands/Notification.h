/*
 * Notification.h
 *
 *  Created on: Nov 16, 2009
 *      Author: ryan
 */

#ifndef NOTIFICATION_H_
#define NOTIFICATION_H_

#include <qobject.h>

class Notification : public QObject
	{
	Q_OBJECT
public:
	Notification();

public slots:
	void vibrate( int duration=5000, int intensity=50 );
	};

#endif /* NOTIFICATION_H_ */
