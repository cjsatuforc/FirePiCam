cmake_minimum_required(VERSION 2.8)
project( firepicam )
SET(COMPILE_DEFINITIONS -Werror)
set(firepicam_VERSION_MAJOR 0)
set(firepicam_VERSION_MINOR 1)
set(firepicam_VERSION_PATCH 1)
set(firepicam_VERSION_STRING ${firepicam_VERSION_MAJOR}.${firepicam_VERSION_MINOR}.${firepicam_VERSION_PATCH})

include (InstallRequiredSystemLibraries)
SET(CPACK_RESOURCE_FILE_LICENSE  
     "${CMAKE_CURRENT_SOURCE_DIR}/LICENCE")
SET(CPACK_PACKAGE_VERSION_MAJOR "${firepicam_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${firepicam_VERSION_MINOR}")
include (CPack)

configure_file (
	"${PROJECT_SOURCE_DIR}/version.h.in"
	"${PROJECT_BINARY_DIR}/version.h"
	)

include_directories(/opt/vc/include)
include_directories(/opt/vc/include/interface/vcos/pthreads)
include_directories(/opt/vc/include/interface/vmcs_host/linux)
include_directories(/opt/vc/userland)

add_library(firepicam SHARED RaspiCamControl.c RaspiCLI.c RaspiPreview.c FirePiCam.c)
target_link_libraries(firepicam /opt/vc/lib/libmmal_core.so /opt/vc/lib/libmmal_util.so /opt/vc/lib/libmmal_vc_client.so /opt/vc/lib/libvcos.so /opt/vc/lib/libbcm_host.so)
set_target_properties(firepicam PROPERTIES VERSION ${firepicam_VERSION_STRING} SOVERSION ${firepicam_VERSION_MAJOR})

add_executable(firepistill FirePiStill.c)
target_link_libraries(firepistill /opt/vc/lib/libmmal_core.so /opt/vc/lib/libmmal_util.so /opt/vc/lib/libmmal_vc_client.so /opt/vc/lib/libvcos.so /opt/vc/lib/libbcm_host.so ${firepicam_BINARY_DIR}/libfirepicam.so)

install (TARGETS firepicam DESTINATION lib)
install (FILES FirePiCam.h DESTINATION include)


