QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# ifdef DEBUGのコードを確認する場合はコメントアウトを外してください。
# .proファイルを更新したらqmakeとリビルドすること。
#DEFINES += DEBUG
#DEFINES += VALUE_DEBUG

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    CreatePFIFile.cpp \
    SetVolumeObject.cpp \
    VTKFormat.cpp
INCLUDEPATH += $(KVS_DIR)
INCLUDEPATH += $(KVS_DIR)/include
INCLUDEPATH += $(VTK_INCLUDE_PATH)
LIBS += -L$(KVS_DIR)/lib -lkvsCore
LIBS += -L$(VTK_LIB_PATH) -lvtkCommonExecutionModel-9.1
LIBS += -L$(VTK_LIB_PATH) -lvtkCommonDataModel-9.1
LIBS += -L$(VTK_LIB_PATH) -lvtkCommonMisc-9.1
LIBS += -L$(VTK_LIB_PATH) -lvtkCommonSystem-9.1
LIBS += -L$(VTK_LIB_PATH) -lvtksys-9.1
LIBS += -L$(VTK_LIB_PATH) -lvtkCommonTransforms-9.1
LIBS += -L$(VTK_LIB_PATH) -lvtkCommonMath-9.1
LIBS += -L$(VTK_LIB_PATH) -lvtkCommonCore-9.1
LIBS += -L$(VTK_LIB_PATH) -lvtkzlib-9.1
LIBS += -L$(VTK_LIB_PATH) -lvtkIOCore-9.1
LIBS += -L$(VTK_LIB_PATH) -lvtkIOLegacy-9.1
LIBS += -L$(VTK_LIB_PATH) -lvtkFiltersCore-9.1

HEADERS += \
    CreatePFIFile.h \
    SetVolumeObject.h \
    VTKFormat.h
