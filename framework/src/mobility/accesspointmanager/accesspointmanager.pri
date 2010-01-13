HEADERS += src/mobility/accesspointmanager/xqaccesspointmanager.h

SOURCES += src/mobility/accesspointmanager/xqaccesspointmanager.cpp

symbian: { 
    HEADERS += src/mobility/accesspointmanager/xqaccesspointmanager_s60_p.h
    SOURCES += src/mobility/accesspointmanager/xqaccesspointmanager_s60_p.cpp
}
else { 
    HEADERS += src/mobility/accesspointmanager/xqaccesspointmanager_stub_p.h
    SOURCES += src/mobility/accesspointmanager/xqaccesspointmanager_stub_p.cpp
}

!exists($${EPOCROOT}epoc32/include/wlanmgmtcommon.h) {
    message("Warning: WLAN Management API not found! (See: http://wiki.forum.nokia.com/index.php/WLAN_Management_API)")
}

symbian:LIBS += -lcommdb \
        -lapengine \
        -lapsettingshandlerui \
        -lconnmon \
        -lcentralrepository \
        -lesock \
        -lecom \
        -lefsrv
