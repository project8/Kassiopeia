# CMakeLists for KEMField/Interface/BoundaryIntegrators/Magnetic
# Author: W. Gosda

# header files
set( MAGNETICBOUNDARYINTEGRATOR_MAGNETIC_HEADER_BASENAMES
    KMagnetostaticBoundaryIntegratorPolicy.hh

)

set( MAGNETICBOUNDARYINTEGRATOR_MAGNETIC_HEADER_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

foreach( BASENAME ${MAGNETICBOUNDARYINTEGRATOR_MAGNETIC_HEADER_BASENAMES} )
    list( APPEND MAGNETICBOUNDARYINTEGRATOR_MAGNETIC_HEADER_FILENAMES ${MAGNETICBOUNDARYINTEGRATOR_MAGNETIC_HEADER_PATH}/${BASENAME} )
endforeach( BASENAME )

# source files
set( MAGNETICBOUNDARYINTEGRATOR_MAGNETIC_SOURCE_BASENAMES
    KMagnetostaticBoundaryIntegratorPolicy.cc
)

set( MAGNETICBOUNDARYINTEGRATOR_MAGNETIC_SOURCE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
foreach( BASENAME ${MAGNETICBOUNDARYINTEGRATOR_MAGNETIC_SOURCE_BASENAMES} )
    list( APPEND MAGNETICBOUNDARYINTEGRATOR_MAGNETIC_SOURCE_FILENAMES ${MAGNETICBOUNDARYINTEGRATOR_MAGNETIC_SOURCE_PATH}/${BASENAME} )
endforeach( BASENAME )

# library
add_library( KEMFieldMagneticBoundaryIntegrators SHARED
    ${MAGNETICBOUNDARYINTEGRATOR_MAGNETIC_SOURCE_FILENAMES} ${MAGNETICBOUNDARYINTEGRATOR_MAGNETIC_HEADER_FILENAMES} )
#set_target_properties( KEMFieldMagneticBoundaryIntegrators PROPERTIES COMPILE_FLAGS -Wno-overloaded-virtual )

target_include_directories(KEMFieldMagneticBoundaryIntegrators
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
target_link_libraries( KEMFieldMagneticBoundaryIntegrators
    PUBLIC
        KEMMagnetostaticBoundaryIntegrals
        KEMFieldExceptions
)

if(KEMField_USE_OPENCL)
    target_link_libraries(KEMFieldMagneticBoundaryIntegrators PUBLIC KEMOpenCLPlugin)
endif(KEMField_USE_OPENCL)

# install
kasper_install_headers( ${MAGNETICBOUNDARYINTEGRATOR_MAGNETIC_HEADER_FILENAMES} )
kasper_install_libraries( KEMFieldMagneticBoundaryIntegrators )
