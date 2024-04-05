# CMakeLists for KEMField/FastMultipole/Magnetostatics
# Author: P. L. Slocum, after J. P. Barrett

set (KFMMAGNETOSTATICS_HEADERFILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticParameters.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticElement.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticNode.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticTree.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticElementContainerBase.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticElementContainer.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticMultipoleSet.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticLocalCoefficientSet.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticMultipoleCalculator.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticMultipoleCalculatorAnalytic.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticMultipoleCalculatorNumeric.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticLocalCoefficientCalculatorNumeric.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticMultipoleBatchCalculatorBase.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticMultipoleBatchCalculator.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticRegionSizeEstimator.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticTreeBuilder.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticFieldMapper_SingleThread.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticBoundaryIntegratorEngine_SingleThread.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticLocalCoefficientFieldCalculator.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticTreeInformationExtractor.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticTreeData.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticNodeWorkScoreCalculator.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticNodeInspector.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticNearFieldToLocalCoefficientCalculator.hh
)

set (KFMMAGNETOSTATICS_SOURCEFILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/KFMMagnetostaticMultipoleSet.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/KFMMagnetostaticLocalCoefficientSet.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/KFMMagnetostaticMultipoleCalculatorAnalytic.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/KFMMagnetostaticMultipoleCalculatorNumeric.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/KFMMagnetostaticLocalCoefficientCalculatorNumeric.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/KFMMagnetostaticMultipoleBatchCalculator.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/KFMMagnetostaticRegionSizeEstimator.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/KFMMagnetostaticTreeBuilder.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/KFMMagnetostaticFieldMapper_SingleThread.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/KFMMagnetostaticBoundaryIntegratorEngine_SingleThread.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/KFMMagnetostaticLocalCoefficientFieldCalculator.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/KFMMagnetostaticTreeData.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/KFMMagnetostaticNodeWorkScoreCalculator.cc
)

if (KEMField_USE_MPI)
    list (APPEND KFMMAGNETOSTATICS_HEADERFILES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/KFMMagnetostaticTreeBuilder_MPI.hh
    )
    list (APPEND KFMMAGNETOSTATICS_SOURCEFILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/KFMMagnetostaticTreeBuilder_MPI.cc
    )
endif (KEMField_USE_MPI)

add_library (KFMMagnetostatics SHARED
    ${KFMMAGNETOSTATICS_SOURCEFILES} ${KFMMAGNETOSTATICS_HEADERFILES})
target_include_directories(KFMMagnetostatics
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
target_link_libraries (KFMMagnetostatics
    PUBLIC
        KEMFileManipulation
        KFMCore
        KFMMath
        KFMVectorMath
        KFMKernel
        KFMTree
)

kasper_install_headers (${KFMMAGNETOSTATICS_HEADERFILES})
kasper_install_libraries (KFMMagnetostatics)
