function DebugConsole() {
}

DebugConsole.prototype.log = function (output, showTime) {
	if (showTime) {
		var now = "" + new Date().getTime();
		output = now.substring(now.length - 5) + ": " + output;
	}
	GapDebugConsole.log(output);
}

if (typeof debug == "undefined") debug = new DebugConsole();
