# $Id: ModuleConfig.cmake.in 11925 2012-01-23 14:54:05Z s_voec01 $

if(KGeoBag_FOUND)
    return()
endif()

set(KGeoBag_FOUND TRUE)

# Update this section

set(DEPENDS_LIBRARIES )
# The CMake names of the libraries in your module

# End

set(KGeoBag_VERSION_MAJOR 2)
set(KGeoBag_VERSION_MINOR 1)
set(KGeoBag_VERSION_PATCH 0)
set(KGeoBag_VERSION 2.1.0)

get_filename_component(MODULE_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
if(EXISTS "${MODULE_CMAKE_DIR}/ModuleTargets.cmake")
    include("${MODULE_CMAKE_DIR}/ModuleTargets.cmake")
elseif(NOT KASPER_TARGETS_INCLUDED)
    include("${MODULE_CMAKE_DIR}/../Kasper/KasperTargets.cmake")
    set(KASPER_TARGETS_INCLUDED TRUE)
endif()

set(KGeoBag_CFLAGS Kommon_USE_ROOT)
set(KGeoBag_INCLUDE_DIRS /home/penny/project8/locust_mc/kassiopeia/install/include;/usr/local/include;/usr/local/include/vtk-6.2;/usr/local/root/include)
set(KGeoBag_LIBRARIES KGeoBagMath;KGeoBagMathLinearAlgebra;KGeoBagMathSpaceTree;KGeoBagCore;KGeoBagShapes;KGeoBagMesh;KGeoBagAxialMesh;KGeoBagDiscreteRotationalMesh;KGeoBagAppearance;KGeoBagMetrics;KGeoBagRandom;KGeoBagIntersection;KGeoBagDeformation;KGeoBagBasicVisualization;KGeoBagVtkVisualization;KGeoBagROOTVisualization;KGeoBagBindings /usr/local/root/lib/libCore.so;/usr/local/root/lib/libCint.so;/usr/local/root/lib/libRIO.so;/usr/local/root/lib/libNet.so;/usr/local/root/lib/libHist.so;/usr/local/root/lib/libGraf.so;/usr/local/root/lib/libGraf3d.so;/usr/local/root/lib/libGpad.so;/usr/local/root/lib/libTree.so;/usr/local/root/lib/libRint.so;/usr/local/root/lib/libPostscript.so;/usr/local/root/lib/libMatrix.so;/usr/local/root/lib/libPhysics.so;/usr/local/root/lib/libMathCore.so;/usr/local/root/lib/libThread.so;/usr/lib/x86_64-linux-gnu/libdl.so)
set(KGeoBag_MPI_LIBRARIES "-L/home/penny/project8/locust_mc/kassiopeia/install/lib")
foreach(LIB KGeoBagMath;KGeoBagMathLinearAlgebra;KGeoBagMathSpaceTree;KGeoBagCore;KGeoBagShapes;KGeoBagMesh;KGeoBagAxialMesh;KGeoBagDiscreteRotationalMesh;KGeoBagAppearance;KGeoBagMetrics;KGeoBagRandom;KGeoBagIntersection;KGeoBagDeformation;KGeoBagBasicVisualization;KGeoBagVtkVisualization;KGeoBagROOTVisualization;KGeoBagBindings)
set(KGeoBag_MPI_LIBRARIES "${KGeoBag_MPI_LIBRARIES} -l${LIB}_mpi")
endforeach(LIB)
set(KGeoBag_MPI_LIBRARIES "${KGeoBag_MPI_LIBRARIES} /usr/local/root/lib/libCore.so;/usr/local/root/lib/libCint.so;/usr/local/root/lib/libRIO.so;/usr/local/root/lib/libNet.so;/usr/local/root/lib/libHist.so;/usr/local/root/lib/libGraf.so;/usr/local/root/lib/libGraf3d.so;/usr/local/root/lib/libGpad.so;/usr/local/root/lib/libTree.so;/usr/local/root/lib/libRint.so;/usr/local/root/lib/libPostscript.so;/usr/local/root/lib/libMatrix.so;/usr/local/root/lib/libPhysics.so;/usr/local/root/lib/libMathCore.so;/usr/local/root/lib/libThread.so;/usr/lib/x86_64-linux-gnu/libdl.so")
