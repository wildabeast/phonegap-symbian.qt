function DebugConsole() {
}

DebugConsole.prototype.log = function (output) {
	GapDebugConsole.log(output);
}

if (typeof navigator.debugconsole == "undefined") navigator.debugconsole = new DebugConsole();
