INCLUDEPATH += $$APP_LAYER_SYSTEMINCLUDE

HEADERS += src/mobility/location/xqlocation.h

SOURCES += src/mobility/location/xqlocation.cpp

symbian: { 
    HEADERS += src/mobility/location/xqlocation_s60_p.h
    SOURCES += src/mobility/location/xqlocation_s60_p.cpp
}
else { 
    HEADERS += src/mobility/location/xqlocation_stub_p.h
    SOURCES += src/mobility/location/xqlocation_stub_p.cpp
}

symbian:LIBS += -llbs
