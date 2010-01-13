HEADERS += src/mobility/vibra/xqvibra.h \
    src/mobility/vibra/xqvibra_p.h

SOURCES += src/mobility/vibra/xqvibra.cpp \
    src/mobility/vibra/xqvibra_p.cpp

symbian:LIBS += -lhwrmvibraclient
