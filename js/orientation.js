/**
 * This class provides access to the device orientation.
 * @constructor
 */
function Orientation() {
	/**
	 * The current orientation, or null if the orientation hasn't changed yet.
	 */
	this.currentOrientation = null;
	this.started = false;
}

/**
 * Asynchronously aquires the current orientation.
 * @param {Function} successCallback The function to call when the orientation
 * is known.
 * @param {Function} errorCallback The function to call when there is an error 
 * getting the orientation.
 */
Orientation.prototype.getCurrentOrientation = function(successCallback, errorCallback) {
	// If the orientation is available then call success
	// If the orientation is not available then call error
	
    if (typeof(successCallback) != 'function')
        successCallback = function() {};
    if (typeof(errorCallback) != 'function')
        errorCallback = function() {};

	if (this.currentOrientation != null) {
		successCallback(this.currentOrientation);
		return;
	}
	else if (this.started) {
		return;
	}
	else {
		this.start();
	}
	
    var timeout = 5000;
    var interval = 500;
    if (typeof(options) == 'object' && options.interval)
        interval = options.interval;
    if (typeof(options) == 'object' && options.timeout)
        timeout = options.timeout;

    var dis = this;
    var delay = 0;
    var timer = setInterval(function() {
        delay += interval;
		
		//if we have a new orientation, call success and cancel the timer
        if (this.currentOrientation != null) {
            successCallback(dis.currentOrientation);
            clearInterval(timer);
        } else if (delay >= timeout) { //else if timeout has occured then call error and cancel the timer
            errorCallback();
            clearInterval(timer);
        }
		//else the interval gets called again
    }, interval);
};

Orientation.prototype.start = function () {
	GapOrientation.start();
	this.started = true;
}

Orientation.prototype.stop = function () {
	GapOrientation.stop();
}

// Called by native phonegap code to update orientation 
Orientation.prototype.setOrientation = function (orientation) {
	this.currentOrientation = orientation;
}

/**
 * Asynchronously aquires the orientation repeatedly at a given interval.
 * @param {Function} successCallback The function to call each time the orientation
 * data is available.
 * @param {Function} errorCallback The function to call when there is an error 
 * getting the orientation data.
 */
Orientation.prototype.watchOrientation = function(successCallback, errorCallback, options) {
	// Invoke the appropriate callback with a new Position object every time the implementation 
	// determines that the position of the hosting device has changed. 
	
	this.getCurrentOrientation(successCallback, errorCallback);
	var frequency = (options != undefined)? options.frequency : 1000;
	return setInterval(function() {
		navigator.orientation.getCurrentOrientation(successCallback, errorCallback);
	}, frequency);
};

/**
 * Clears the specified orientation watch.
 * @param {String} watchId The ID of the watch returned from #watchOrientation.
 */
Orientation.prototype.clearWatch = function(watchId) {
	clearInterval(watchId);
};

/**
* This class encapsulates the possible orientation values.
* @constructor
*/
function DisplayOrientation() {
	this.code = null;
	this.message = "";
}
 
DisplayOrientation.PORTRAIT = 0;
DisplayOrientation.REVERSE_PORTRAIT = 1;
DisplayOrientation.LANDSCAPE_LEFT_UP = 2;
DisplayOrientation.LANDSCAPE_RIGHT_UP = 3;
DisplayOrientation.FACE_UP = 4;
DisplayOrientation.FACE_DOWN = 5;

if (typeof navigator.orientation == "undefined") navigator.orientation = new Orientation();