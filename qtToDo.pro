QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += sql charts

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    diarydetails.cpp \
    diarylistitem.cpp \
    main.cpp \
    personalcenter.cpp \
    qttodomainwindow.cpp \
    todolistitem.cpp \
    writediary.cpp

HEADERS += \
    diarydetails.h \
    diarylistitem.h \
    personalcenter.h \
    qttodomainwindow.h \
    todolistitem.h \
    writediary.h

FORMS += \
    diarydetails.ui \
    diarylistitem.ui \
    personalcenter.ui \
    qttodomainwindow.ui \
    todolistitem.ui \
    writediary.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
