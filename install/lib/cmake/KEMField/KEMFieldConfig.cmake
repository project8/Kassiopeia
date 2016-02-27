# $Id: $

if(KEMField_FOUND)
    return()
endif()

set(KEMField_FOUND TRUE)

# Update this section

set(DEPENDS_LIBRARIES )
# The CMake names of the libraries in your module

# End

set(KEMField_VERSION_MAJOR 2)
set(KEMField_VERSION_MINOR 1)
set(KEMField_VERSION_PATCH 0)
set(KEMField_VERSION 2.1.0)

get_filename_component(MODULE_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
if(EXISTS "${MODULE_CMAKE_DIR}/ModuleTargets.cmake")
    include("${MODULE_CMAKE_DIR}/ModuleTargets.cmake")
elseif(NOT KASPER_TARGETS_INCLUDED)
    include("${MODULE_CMAKE_DIR}/../Kasper/KasperTargets.cmake")
    set(KASPER_TARGETS_INCLUDED TRUE)
endif()

set(KEMField_CFLAGS Kommon_USE_ROOT;KEMFIELD_USE_KOMMON;KEMFIELD_USE_KMESSAGE;KEMFIELD_SPARSE_MATRIX_BUFFER_SIZE_MB=2048;KEMFIELD_MULTIPOLE_BUFFER_SIZE_MB=32;KEMFIELD_USE_KGEOBAG)
set(KEMField_INCLUDE_DIRS /home/penny/project8/locust_mc/kassiopeia/install/include)
set(KEMField_LIBRARIES KEMCore;KEMHashGenerator;KEMStructuredASCII;KEMIO;KEMFileManipulation;KEMMath;KFMMathUtilities;KVectorMath;KEMSurfaces;KEMElectrostaticBoundaryIntegrals;KEMElectromagnets;KEMIntegratingFieldSolver;KEMZHGenerator;KEMZHSolver;KFMCore;KFMMath;KFMKernel;KFMTree;KFMElectrostatics;KFMInterfaceExtraction;KFMInterfaceFieldSolvers;KFMUtility;KEMVisualization;KEMGeoBagPlugin )
set(KEMField_MPI_LIBRARIES "-L/home/penny/project8/locust_mc/kassiopeia/install/lib")
foreach(LIB KEMCore;KEMHashGenerator;KEMStructuredASCII;KEMIO;KEMFileManipulation;KEMMath;KFMMathUtilities;KVectorMath;KEMSurfaces;KEMElectrostaticBoundaryIntegrals;KEMElectromagnets;KEMIntegratingFieldSolver;KEMZHGenerator;KEMZHSolver;KFMCore;KFMMath;KFMKernel;KFMTree;KFMElectrostatics;KFMInterfaceExtraction;KFMInterfaceFieldSolvers;KFMUtility;KEMVisualization;KEMGeoBagPlugin)
set(KEMField_MPI_LIBRARIES "${KEMField_MPI_LIBRARIES} -l${LIB}_mpi")
endforeach(LIB)
set(KEMField_MPI_LIBRARIES "${KEMField_MPI_LIBRARIES} ")
