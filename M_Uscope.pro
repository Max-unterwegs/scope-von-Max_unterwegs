QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    fft_transform.cpp \
    kiss_fft.c \
    main.cpp \
    qcustomplot.cpp \
    scope.cpp \
    voltparamrech.cpp

HEADERS += \
    _kiss_fft_guts.h \
    fft_transform.h \
    kiss_fft.h \
    kiss_fft_log.h \
    qcustomplot.h \
    scope.h \
    voltparamrech.h

FORMS += \
    scope.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QMAKE_CXXFLAGS += -Wa,-mbig-obj

DISTFILES +=

RESOURCES += \
    icos.qrc
