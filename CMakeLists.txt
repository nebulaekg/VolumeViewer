cmake_minimum_required(VERSION 2.8)

if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()

PROJECT(VolumeViewer)

IF(UNIX)
set(VTK_DIR /hpc/gram526/VTK/Build)
set(ITK_DIR /hpc/gram526/ITK/Build)
endif()

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})



find_package(Qt5 COMPONENTS Widgets PrintSupport  REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5PrintSupport_INCLUDE_DIRS})

IF(UNIX)
include_directories(/usr/local/matlab/extern/include)
set(MATLAB_LIB_DIR /usr/local/matlab/bin/glnxa64)
set(MATLAB_INCLUDE_DIR /usr/local/matlab/extern/include)
find_package(FFMPEG REQUIRED)
include_directories(${FFMPEG_INCLUDE_DIR})
set(_ffmpeg_libs ${FFMPEG_avformat_LIBRARY} ${FFMPEG_avcodec_LIBRARY}
  ${FFMPEG_avutil_LIBRARY}  ${FFMPEG_swresample_LIBRARY})
if(NOT VTK_FFMPEG_HAS_IMG_CONVERT)
  list(APPEND _ffmpeg_libs ${FFMPEG_swscale_LIBRARY})
endif()
endif()



find_package(ITK REQUIRED)
include(${ITK_USE_FILE})
if (ITKVtkGlue_LOADED)
  find_package(VTK REQUIRED)
  include(${VTK_USE_FILE})
endif()

 # We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
  add_definitions(${Qt5Widgets_DEFINITIONS})
  add_definitions(${Qt5PrintSupport_DEFINITIONS})

  # Executables fail to build with Qt 5 in the default configuration
  # without -fPIE. We add that here.
  set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

SET(VolumeViewer_RESOURCES icons.qrc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})


file(GLOB UI_FILES *.ui)
file(GLOB QT_WRAP *.h)
file(GLOB CXX_FILES *.cxx)

find_package(MatlabMex REQUIRED)
include(UseMatlabMex)


  QT5_WRAP_UI(UISrcs ${UI_FILES})
  QT5_WRAP_CPP(MOCSrcs ${QT_WRAP})
  QT5_ADD_RESOURCES(VolumeViewer_RESOURCES_RCC ${VolumeViewer_RESOURCES})


  add_executable(VolumeViewer WIN32 MACOSX_BUNDLE ${CXX_FILES} ${UISrcs} ${MOCSrcs} ${VolumeViewer_RESOURCES_RCC})


    target_link_libraries(VolumeViewer ${QT_QTMAIN_LIBRARY} ${VTK_LIBRARIES} ${Qt5Widgets_LIBRARIES}  ${Qt5PrintSupport_LIBRARIES} ${ITK_LIBRARIES} ${Glue} ${MEX_LIBRARIES} ${MATLAB_ENGINE_LIBRARIES})

# ${_ffmpeg_libs})


IF(WIN32) # Check if we are on Windows
  if(MSVC) # Check if we are using the Visual Studio compiler
    set_target_properties(VolumeViewer PROPERTIES LINK_FLAGS_RELEASE /SUBSYSTEM:WINDOWS)
  elseif(CMAKE_COMPILER_IS_GNUCXX)
    # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
  else()
    message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
  endif()
elseif(UNIX)
  # Nothing special required
else()
  message(SEND_ERROR "You are on an unsupported platform! (Not Win32 or Unix)")
ENDIF()
