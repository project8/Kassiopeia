if(Kommon_FOUND)
    return()
endif()

set(Kommon_FOUND TRUE)

# Update this section

set(DEPENDS_LIBRARIES   gsl;gslcblas;m)
# The CMake names of the libraries in your module

# End

set(Kommon_VERSION_MAJOR 1)
set(Kommon_VERSION_MINOR 1)
set(Kommon_VERSION_PATCH 0)
set(Kommon_VERSION 1.1.0)

get_filename_component(MODULE_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
if(EXISTS "${MODULE_CMAKE_DIR}/ModuleTargets.cmake")
    include("${MODULE_CMAKE_DIR}/ModuleTargets.cmake")
elseif(NOT KASPER_TARGETS_INCLUDED)
    include("${MODULE_CMAKE_DIR}/../Kasper/KasperTargets.cmake")
    set(KASPER_TARGETS_INCLUDED TRUE)
endif()

set(Kommon_INCLUDE_DIRS /home/penny/project8/locust_mc/kassiopeia/install/include;/usr/local/root/include;/usr/local/include;/usr/local/include/vtk-6.2)

set(Kommon_LIBRARIES KommonCore;KommonRoot;KommonGsl;KommonVtk)
set(Kommon_Core_LIBRARIES KommonCore)
if( Kommon_USE_BOOST )
    set(Kommon_Boost_LIBRARIES KommonBoost)
endif( Kommon_USE_BOOST )
if( Kommon_USE_ROOT )
    set(Kommon_Root_LIBRARIES KommonRoot)
endif( Kommon_USE_ROOT )
if( Kommon_USE_GSL )
    set(Kommon_Gsl_LIBRARIES KommonGsl)
endif( Kommon_USE_GSL )
if( Kommon_USE_VTK )
    set(Kommon_Vtk_LIBRARIES KommonVtk)
endif( Kommon_USE_VTK )
