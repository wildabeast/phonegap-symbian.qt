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
MKPATH = mkdir -p
CAT = cat
MAKE = make
OPEN = open
ECHO = echo
ECHO_N = echo -n
JAVA = java

all :: symbian.qt

clean :: clean_libs

clean_libs:
	-$(RM_RF) lib
	
symbian.qt: lib/phonegap.js

lib/phonegap.js: js/debugconsole.js js/geolocation.js js/notification.js js/position.js
	$(MKPATH) lib
	$(RM_F) $@
	$(CAT) js/debugconsole.js >> $@
	$(CAT) js/geolocation.js >> $@
	$(CAT) js/notification.js >> $@
	$(CAT) js/position.js >> $@
