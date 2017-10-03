TEMPLATE = app
TARGET = cpu
INCLUDEPATH += .
QT += quick

SOURCES += \
    main.cpp

RESOURCES += \
    cpu.qrc

OTHER_FILES += \
    qml/window.qml \
    qml/CPUGaugeStyle.qml \
    qml/CPUStyle.qml

target.path = ./
INSTALLS += target
