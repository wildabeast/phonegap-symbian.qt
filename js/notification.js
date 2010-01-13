function Notification() {
}

Notification.prototype.vibrate = function (duration, intensity) {
	if (isNaN(duration))
		duration = 3000;
	if (isNaN(intensity))
		intensity = 50;
	GapNotification.vibrate(duration, intensity);	
}

if (typeof navigator.notification == "undefined") navigator.notification = new Notification();
