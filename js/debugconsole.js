function DebugConsole() {
}

DebugConsole.prototype.log = function (output) {
	GapDebugConsole.log(output);
}

if (typeof debug == "undefined") debug = new DebugConsole();
