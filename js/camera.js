/**
 * This class provides access to the device camera.
 * @constructor
 */
function Camera() {
	this.success_callback = null;
	this.error_callback = null;
}

/**
 * We use the Platform Services 2.0 API here. So we must include a portion of the
 * PS 2.0 source code (camera API). 
 * @param {Function} successCallback
 * @param {Function} errorCallback
 * @param {Object} options
 */
Camera.prototype.getPicture = function(successCallback, errorCallback, options){
	GapCamera.takePicture();
}

if (typeof navigator.camera == "undefined") navigator.camera = new Camera();