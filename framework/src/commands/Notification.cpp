/*
 * Notification.cpp
 *
 *  Created on: Nov 16, 2009
 *      Author: ryan
 */

#include "Notification.h"
#include "xqvibra.h"

Notification::Notification()
	{
	// TODO Auto-generated constructor stub

	}

void Notification::vibrate(int duration, int intensity) {
	XQVibra* vibra = new XQVibra(this);
	vibra->setIntensity(intensity);
	vibra->start(duration);
}
