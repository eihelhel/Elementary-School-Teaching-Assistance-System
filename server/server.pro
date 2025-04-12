QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
#    GlobalSignalManager.cpp \
    function.cpp \
    main.cpp \
    student.cpp \
    student_work.cpp \
    text_five.cpp \
    text_four.cpp \
    text_one.cpp \
    text_three.cpp \
    text_two.cpp \
    widget.cpp

HEADERS += \
#    GlobalSignalManager.h \
    function.h \
    student.h \
    student_work.h \
    text_five.h \
    text_four.h \
    text_one.h \
    text_three.h \
    text_two.h \
    widget.h

FORMS += \
    student.ui \
    student_work.ui \
    text_five.ui \
    text_four.ui \
    text_one.ui \
    text_three.ui \
    text_two.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
