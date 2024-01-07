QT       += core gui
QT       += sql
QT += widgets printsupport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Product.cpp \
    ProductArraylist.cpp \
    UserArrayList.cpp \
    Username.cpp \
    Utils.cpp \
    inventory_dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    newproductinfo.cpp \
    newuserprevilege.cpp \
    sale.cpp \
    saleshistory.cpp \
    signin.cpp

HEADERS += \
    Product.h \
    ProductArraylist.h \
    UserArrayList.h \
    Username.h \
    inventory_dialog.h \
    mainwindow.h \
    newproductinfo.h \
    newuserprevilege.h \
    sale.h \
    saleshistory.h \
    signin.h

FORMS += \
    inventory_dialog.ui \
    mainwindow.ui \
    newproductinfo.ui \
    newuserprevilege.ui \
    sale.ui \
    saleshistory.ui \
    signin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
