cmake_minimum_required(VERSION 3.0)
project(BioEvo)

# Prefix
if (NOT PREFIX)
    set(PREFIX ${CMAKE_CURRENT_BINARY_DIR})
endif (NOT PREFIX)
set(CMAKE_INSTALL_PREFIX ${PREFIX} CACHE STRING "Installation prefix." FORCE)

if (CXX)
    set(CMAKE_CXX_COMPILER ${CXX})
endif (CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})




# ********************************* Code Eaters *********************************

set(HEADERS src/CodeEater/PreprocessingDefinitions.hpp src/CodeEater/Constants.hpp src/CodeEater/Universe.hpp src/CodeEater/CodeEaters/CodeEater.hpp
    src/CodeEater/Computing/Utils/Permutation.hpp src/CodeEater/Computing/Utils/FunctionPattern.hpp src/CodeEater/Computing/Utils/ComputationResult.hpp
        src/CodeEater/Computing/FunctionPatternComputer.hpp src/CodeEater/Computing/FunctionProcessor.hpp src/CodeEater/Computing/StateChanger.hpp 
        src/CodeEater/Computing/EatingProcessor.hpp src/CodeEater/Computing/NeighborhoodManager.hpp src/CodeEater/Computing/RuleApplier.hpp
        src/CodeEater/Computing/RuleNumberComputer.hpp
    src/CodeEater/Experiments/Experiment.hpp src/CodeEater/Experiments/Experiment1.hpp src/CodeEater/Experiments/Experiment2.hpp 
        src/CodeEater/Experiments/Experiment3.hpp)
set(SOURCES src/CodeEater/main.cpp src/CodeEater/CodeEaters/CodeEater.cpp src/CodeEater/Universe.cpp 
    src/CodeEater/Computing/Utils/Permutation.cpp src/CodeEater/Computing/Utils/FunctionPattern.cpp src/CodeEater/Computing/Utils/ComputationResult.cpp
        src/CodeEater/Computing/FunctionPatternComputer.cpp src/CodeEater/Computing/FunctionProcessor.cpp src/CodeEater/Computing/StateChanger.cpp 
        src/CodeEater/Computing/EatingProcessor.cpp src/CodeEater/Computing/NeighborhoodManager.cpp src/CodeEater/Computing/RuleApplier.cpp
        src/CodeEater/Computing/RuleNumberComputer.cpp
    src/CodeEater/Experiments/Experiment.cpp src/CodeEater/Experiments/Experiment1.cpp src/CodeEater/Experiments/Experiment2.cpp 
        src/CodeEater/Experiments/Experiment3.cpp)
add_executable(code_eater_experience ${HEADERS} ${SOURCES})

target_link_libraries(code_eater_experience ${LIBS})

