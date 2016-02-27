# $Id: ModuleConfig.cmake.in 11925 2012-01-23 14:54:05Z s_voec01 $

if(Kassiopeia_FOUND)
    return()
endif()

set(Kassiopeia_FOUND TRUE)

# Update this section

set(DEPENDS_LIBRARIES KommonCore;KommonRoot;KommonGsl;KommonVtk /usr/local/root/lib/libCore.so;/usr/local/root/lib/libCint.so;/usr/local/root/lib/libRIO.so;/usr/local/root/lib/libNet.so;/usr/local/root/lib/libHist.so;/usr/local/root/lib/libGraf.so;/usr/local/root/lib/libGraf3d.so;/usr/local/root/lib/libGpad.so;/usr/local/root/lib/libTree.so;/usr/local/root/lib/libRint.so;/usr/local/root/lib/libPostscript.so;/usr/local/root/lib/libMatrix.so;/usr/local/root/lib/libPhysics.so;/usr/local/root/lib/libMathCore.so;/usr/local/root/lib/libThread.so;/usr/lib/x86_64-linux-gnu/libdl.so)
list(REMOVE_DUPLICATES DEPENDS_LIBRARIES)

# End

set(Kassiopeia_VERSION_MAJOR 3)
set(Kassiopeia_VERSION_MINOR 1)
set(Kassiopeia_VERSION_PATCH 0)
set(Kassiopeia_VERSION 3.1.0)

get_filename_component(MODULE_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
if(EXISTS "${MODULE_CMAKE_DIR}/ModuleTargets.cmake")
    include("${MODULE_CMAKE_DIR}/ModuleTargets.cmake")
elseif(NOT KASPER_TARGETS_INCLUDED)
    include("${MODULE_CMAKE_DIR}/../Kasper/KasperTargets.cmake")
    set(KASPER_TARGETS_INCLUDED TRUE)
endif()

set(Kassiopeia_INCLUDE_DIRS /home/penny/project8/locust_mc/kassiopeia/install/include;/usr/local/root/include;/usr/local/include/vtk-6.2)
set(Kassiopeia_LIBRARIES KassiopeiaUtility;KassiopeiaMath;KassiopeiaObjects;KassiopeiaOperators;KassiopeiaFields;KassiopeiaGeometry;KassiopeiaGenerators;KassiopeiaTrajectories;KassiopeiaNavigators;KassiopeiaInteractions;KassiopeiaTerminators;KassiopeiaModifiers;KassiopeiaWriters;KassiopeiaReaders;KassiopeiaVisualization;KassiopeiaSimulation;KassiopeiaBindings)
