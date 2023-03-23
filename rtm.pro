TEMPLATE    = app
TARGET      = rtm
INCLUDEPATH += .

QMAKE_LFLAGS_DEBUG += #-fsanitize=undefined -fsanitize=address -fsanitize=leak # -fanalyzer 
QMAKE_CXXFLAGS_DEBUG += -O0 -Wall -g3 -std=c++17 #-fsanitize=undefined -fsanitize=address -fsanitize=leak # -fanalyzer 

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3 -std=c++17

QT              += core widgets gui
CONFIG          += release warn_on #debug

# Così non inquino la cartella del progetto
OBJECTS_DIR     = objs
MOC_DIR         = objs
DESTDIR         = build

DEFINES += NDEBUG # Disabilita gli assert

# Input
HEADERS += \
    src/core/electric_locomotive.h \
    src/core/vehicle_types.h \
    src/core/passenger_coach.h \
    src/core/goods_wagon.h \
    src/core/railway_vehicle.h \
    src/core/railyard.h \
    src/core/load_limit_panel.h \
    src/core/generic_visitor_interface.h \
    \
    src/core/converter/converter.h \
    src/core/converter/json_converter_visitor.h \
    \
    src/utils/vector.h \
    \
    src/views/main_window.h \
    src/views/gui_settings.h \
    \
    src/views/editors/vehicle_editor.h \
    src/views/editors/visitors/vehicle_editor_visitor.h \
    \
    src/views/editors/components/image_manager.h \
    src/views/editors/components/railway_vehicle_info_manager.h \
    src/views/editors/components/locomotive_info_manager.h \
    src/views/editors/components/electric_locomotive_info_manager.h \
    src/views/editors/components/railroad_car_info_manager.h \
    src/views/editors/components/passenger_coach_info_manager.h \
    src/views/editors/components/goods_wagon_info_manager.h \
    \
    src/views/viewers/vehicle_viewer.h \
    \
    src/views/viewers/components/railway_vehicle_viewer.h \
    src/views/viewers/components/railroad_car_viewer.h \
    src/views/viewers/components/goods_wagon_viewer.h \
    src/views/viewers/components/locomotive_viewer.h \
    src/views/viewers/components/electric_locomotive_viewer.h \
    src/views/viewers/components/passenger_coach_viewer.h \
    src/views/viewers/components/search_bar.h \
    \
    src/views/viewers/visitors/vehicle_viewer_visitor.h


SOURCES += \
  \
  src/main.cpp \
  \
  src/core/electric_locomotive.cpp \
  src/core/vehicle_types.cpp \
  src/core/passenger_coach.cpp \
  src/core/goods_wagon.cpp \
  src/core/railway_vehicle.cpp \
  src/core/railyard.cpp \
  src/core/load_limit_panel.cpp \
  \
  src/core/converter/converter.cpp \
  src/core/converter/json_converter_visitor.cpp \
  \
  src/views/main_window.cpp \
  src/views/gui_settings.cpp \
  \
  src/views/editors/vehicle_editor.cpp \
  src/views/editors/visitors/vehicle_editor_visitor.cpp \
  \
  src/views/editors/components/image_manager.cpp \
  src/views/editors/components/railway_vehicle_info_manager.cpp \
  src/views/editors/components/locomotive_info_manager.cpp \
  src/views/editors/components/electric_locomotive_info_manager.cpp \
  src/views/editors/components/railroad_car_info_manager.cpp \
  src/views/editors/components/passenger_coach_info_manager.cpp \
  src/views/editors/components/goods_wagon_info_manager.cpp \
  \
  src/views/viewers/vehicle_viewer.cpp \
  \
  src/views/viewers/components/railway_vehicle_viewer.cpp \
  src/views/viewers/components/railroad_car_viewer.cpp \
  src/views/viewers/components/goods_wagon_viewer.cpp \
  src/views/viewers/components/locomotive_viewer.cpp \
  src/views/viewers/components/electric_locomotive_viewer.cpp \
  src/views/viewers/components/passenger_coach_viewer.cpp \
  src/views/viewers/components/search_bar.cpp \
  \
  src/views/viewers/visitors/vehicle_viewer_visitor.cpp


RESOURCES += \
  resources.qrc \
  languages/it_lang_pack.qm

TRANSLATIONS = \
    languages/it_lang_pack.ts
