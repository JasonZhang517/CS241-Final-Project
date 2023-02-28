QT       += core gui charts
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GridChart.cpp \
    PieChart.cpp \
    Prediction.cpp \
    Traveltime.cpp \
    chartWidget.cpp \
    input_controlling_layout.cpp \
    main.cpp \
    mainLayout.cpp \
    mainwindow.cpp \
    progressThread.cpp \
    tentative-dataclass.cpp

HEADERS += \
    GridChart.h \
    OrderInformation.h \
    PieChart.h \
    Prediction.h \
    ProgressDlg.h \
    Traveltime.h \
    chartWidget.h \
    input_controlling_layout.h \
    mainLayout.h \
    mainwindow.h \
    progressThread.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
