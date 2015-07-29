TEMPLATE = app
QT = gui core
win32 {
  DEFINES += QT_DLL
  CONFIG += release dll app_bundle qt windows
  TEMPLATE = app
  DEPENDPATH += . build src ui
  RC_FILE = win.rc
}
macx {
}
!win32 {
  CONFIG += qt release warn_on console
}
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
FORMS = ui/mainwindow.ui
HEADERS = src/ventetickets.h
SOURCES = src/ventetickets.cpp src/main.cpp
