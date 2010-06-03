SHELL = /bin/sh
CHMOD = chmod
CP = cp
MV = mv
NOOP = $(SHELL) -c true
RM_F = rm -f
RM_RF = rm -rf
TEST_F = test -f
TOUCH = touch
UMASK_NULL = umask 0
DEV_NULL = > /dev/null 2>&1
MKPATH = mkdir
CAT = cat
MAKE = make
OPEN = open
ECHO = echo
ECHO_N = echo -n
JAVA = java

all :: build

clean :: clean_libs clean_build

clean_libs:
	-$(RM_RF) lib

clean_build:
	cd framework/ && make clean
	
build: js qmake phone_debug sis

sis:
	cd framework/ && make sis
	
qmake:
	cd framework/ && qmake
	
emulator_debug:
	cd framework/ && make debug-winscw
	
phone_debug:
	cd framework/ && make debug-gcce
	
phone_release:
	cd framework/ && make release-gcce
	
run: js qmake emulator_debug
	cd framework/ && make run
	
js: lib/phonegap.js

lib/phonegap.js: js/acceleration.js js/accelerometer.js js/camera.js js/debugconsole.js js/geolocation.js js/notification.js js/orientation.js js/position.js
	$(RM_RF) lib
	$(MKPATH) lib
	$(RM_F) $@
	$(CAT) js/acceleration.js >> $@
	$(CAT) js/accelerometer.js >> $@
	$(CAT) js/camera.js >> $@
	$(CAT) js/debugconsole.js >> $@
	$(CAT) js/geolocation.js >> $@
	$(CAT) js/notification.js >> $@
	$(CAT) js/orientation.js >> $@
	$(CAT) js/position.js >> $@
	$(CP) $@ framework/www/phonegap.js
