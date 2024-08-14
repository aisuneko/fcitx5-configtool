if(ENABLE_X11)
add_library(X11Import UNKNOWN IMPORTED)
set_target_properties(X11Import PROPERTIES
    IMPORTED_LOCATION "${X11_X11_LIB}"
    INTERFACE_INCLUDE_DIRECTORIES "${X11_X11_INCLUDE_PATH}")

add_library(X11XkblibImport INTERFACE IMPORTED)
set_target_properties(X11XkblibImport PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${X11_Xkblib_INCLUDE_PATH}")
else()
include_directories(${WAYLAND_CLIENT_INCLUDE_DIRS})
include_directories(${XKBCOMMON_INCLUDE_DIRS})
endif()

add_library(layoutlib STATIC keyboardlayoutwidget.cpp)
set_target_properties(layoutlib PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
if (ENABLE_X11)
target_link_libraries(layoutlib PUBLIC Fcitx5::Utils Qt${QT_MAJOR_VERSION}::Widgets PRIVATE X11Import X11XkblibImport PkgConfig::XkbFile)
if (QT_MAJOR_VERSION STREQUAL 5)
target_link_libraries(layoutlib PUBLIC Qt${QT_MAJOR_VERSION}::X11Extras)
endif()
else()
target_link_libraries(layoutlib PUBLIC Fcitx5::Utils Qt${QT_MAJOR_VERSION}::Widgets Qt${QT_MAJOR_VERSION}::WaylandCompositor PRIVATE ${WAYLAND_CLIENT_LIBRARIES} ${XKBCOMMON_LIBRARIES})
endif()
target_include_directories(layoutlib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set(kbd_layout_viewer_SOURCES
  main.cpp
  )

add_executable(kbd-layout-viewer5 ${kbd_layout_viewer_SOURCES})

target_link_libraries(kbd-layout-viewer5 Fcitx5::Utils Qt${QT_MAJOR_VERSION}::Widgets Qt${QT_MAJOR_VERSION}::WaylandCompositor layoutlib)

if(ENABLE_X11)
target_compile_definitions(kbd-layout-viewer5 PRIVATE ENABLE_X11)
endif()
install(TARGETS kbd-layout-viewer5 DESTINATION ${KDE_INSTALL_BINDIR})
fcitx5_translate_desktop_file(
  kbd-layout-viewer5.desktop.in
  kbd-layout-viewer5.desktop PO_DIRECTORY ${PROJECT_SOURCE_DIR}/po/fcitx5-configtool)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/kbd-layout-viewer5.desktop"
  DESTINATION ${KDE_INSTALL_APPDIR})
