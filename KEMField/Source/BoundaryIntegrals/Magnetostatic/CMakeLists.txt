# CMakeLists for KEMField/MagnetostaticBoundaryIntegrals
# Author: T.J. Corona

set (MAGNETOSTATICBOUNDARYINTEGRALS_HEADERFILES
  include/KMagnetostaticBoundaryIntegrator.hh
  Core/include/KMagnetostaticBoundaryIntegratorFactory.hh  
  #${CMAKE_CURRENT_SOURCE_DIR}/include/KMagnetostaticRingIntegrator.hh
  include/KMagnetostaticLineSegmentIntegrator.hh
  Analytic/include/KMagnetostaticAnalyticLineSegmentIntegrator.hh
  )

set (MAGNETOSTATICBOUNDARYINTEGRALS_SOURCEFILES
  src/KMagnetostaticBoundaryIntegrator.cc
  Core/src/KMagnetostaticBoundaryIntegratorFactory.cc
  #${CMAKE_CURRENT_SOURCE_DIR}/src/KMagnetostaticRingIntegrator.cc
  src/KMagnetostaticLineSegmentIntegrator.cc
  Analytic/src/KMagnetostaticAnalyticLineSegmentIntegrator.cc
)

##################################################

add_library (KEMMagnetostaticBoundaryIntegrals SHARED
    ${MAGNETOSTATICBOUNDARYINTEGRALS_SOURCEFILES} ${MAGNETOSTATICBOUNDARYINTEGRALS_HEADERFILES})

# get header paths from collected header files
foreach(HEADER ${MAGNETOSTATICBOUNDARYINTEGRALS_HEADERFILES})
    get_filename_component(DIRNAME ${CMAKE_CURRENT_SOURCE_DIR}/${HEADER} DIRECTORY)
    target_include_directories(KEMMagnetostaticBoundaryIntegrals PUBLIC $<BUILD_INTERFACE:${DIRNAME}>)
endforeach(HEADER)
    
target_include_directories(KEMMagnetostaticBoundaryIntegrals
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
target_link_libraries (KEMMagnetostaticBoundaryIntegrals
    PUBLIC
        KEMCore
        KEMSurfaces
        KEMFieldExceptions
        KEMBoundaryIntegralsCore
)

kasper_install_headers (${MAGNETOSTATICBOUNDARYINTEGRALS_HEADERFILES})
kasper_install_libraries (KEMMagnetostaticBoundaryIntegrals)
