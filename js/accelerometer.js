/**
 * This class provides access to the device accelerometer.
 * @constructor
 */
function Accelerometer() {
	/**
	 * The current acceleration, or null if the acceleration hasn't changed yet.
	 */
	this.currentAcceleration = null;
	this.started = false;
}

/**
 * Asynchronously aquires the current orientation.
 * @param {Function} successCallback The function to call when the orientation
 * is known.
 * @param {Function} errorCallback The function to call when there is an error 
 * getting the orientation.
 */
Accelerometer.prototype.getCurrentAcceleration = function(successCallback, errorCallback) {
	// If the acceleration is available then call success
	// If the acceleration is not available then call error
    if (typeof(successCallback) != 'function')
        successCallback = function() {};
    if (typeof(errorCallback) != 'function')
        errorCallback = function() {};

	if (this.currentAcceleration != null) {
		successCallback(this.currentAcceleration);
		return;
	}
	else if (this.started) {
		return;
	}
	else {
		this.start();
	}
	
    var timeout = 10000;
    var interval = 500;
    if (typeof(options) == 'object' && options.interval)
        interval = options.interval;
    if (typeof(options) == 'object' && options.timeout)
        timeout = options.timeout;

    var dis = this;
    var delay = 0;
    var timer = setInterval(function() {
        delay += interval;
		//if we have a new acceleration, call success and cancel the timer
        if (dis.currentAcceleration != null) {
			clearInterval(timer);
            successCallback(dis.currentAcceleration);
        } else if (delay >= timeout) { //else if timeout has occured then call error and cancel the timer
			clearInterval(timer);
			errorCallback();
        }
		//else the interval gets called again
    }, interval);
};

Accelerometer.prototype.setAcceleration = function (xAccel, yAccel, zAccel) {
	//debug.log("setAccel: " + xAccel + "," + yAccel + "," + zAccel, true);
	this.currentAcceleration = new Acceleration(xAccel, yAccel, zAccel);
}

Accelerometer.prototype.start = function () {
	GapAcceleration.start();
	this.started = true;
}

Accelerometer.prototype.stop = function () {
	GapAcceleration.stop();
}

/**
 * Asynchronously aquires the acceleration repeatedly at a given interval.
 * @param {Function} successCallback The function to call each time the acceleration
 * data is available.
 * @param {Function} errorCallback The function to call when there is an error 
 * getting the Accelerometer data.
 */
Accelerometer.prototype.watchAcceleration = function(successCallback, errorCallback, options) {
	// Invoke the appropriate callback with a new Acceleration object every time the implementation 
	// determines that the acceleration of the hosting device has changed. 
	
	this.getCurrentAcceleration(successCallback, errorCallback);
	var frequency = (options != undefined)? options.frequency : 1000;
	return setInterval(function() {
		navigator.accelerometer.getCurrentAcceleration(successCallback, errorCallback);
	}, frequency);
};

/**
 * Clears the specified acceleration watch.
 * @param {String} watchId The ID of the watch returned from #watchAcceleration.
 */
Accelerometer.prototype.clearWatch = function(watchId) {
	clearInterval(watchId);
};

if (typeof navigator.accelerometer == "undefined") navigator.accelerometer = new Accelerometer();