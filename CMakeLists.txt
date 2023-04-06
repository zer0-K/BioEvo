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


# ********************************* Common *********************************

set(HEADERS_COMMON src/Universe.hpp src/Experiment.hpp src/Individual.hpp src/Environment.hpp src/Buffer.hpp src/Flow.hpp
    src/Constants.hpp src/PreprocessingDefinitions.hpp)
set(SOURCES_COMMON src/Universe.cpp src/Experiment.cpp src/Individual.cpp src/Environment.cpp src/Buffer.cpp src/Flow.cpp
    src/main.cpp)


# ********************************* Code Eaters *********************************

set(HEADERS src/CodeEater/ConstantsCodeEater.hpp src/CodeEater/UniverseCodeEater.hpp src/CodeEater/CodeEaters/CodeEater.hpp
    src/CodeEater/Computing/Utils/Permutation.hpp src/CodeEater/Computing/Utils/FunctionPattern.hpp src/CodeEater/Computing/Utils/ComputationResult.hpp
        src/CodeEater/Computing/FunctionPatternComputer.hpp src/CodeEater/Computing/FunctionProcessor.hpp src/CodeEater/Computing/StateChanger.hpp 
        src/CodeEater/Computing/EatingProcessor.hpp src/CodeEater/Computing/NeighborhoodManager.hpp src/CodeEater/Computing/RuleApplier.hpp
        src/CodeEater/Computing/RuleNumberComputer.hpp
    src/CodeEater/Experiments/ExperimentCodeEater.hpp src/CodeEater/Experiments/ExperimentCodeEater1.hpp src/CodeEater/Experiments/ExperimentCodeEater2.hpp 
        src/CodeEater/Experiments/ExperimentCodeEater3.hpp)
set(SOURCES src/CodeEater/CodeEaters/CodeEater.cpp src/CodeEater/UniverseCodeEater.cpp 
    src/CodeEater/Computing/Utils/Permutation.cpp src/CodeEater/Computing/Utils/FunctionPattern.cpp src/CodeEater/Computing/Utils/ComputationResult.cpp
        src/CodeEater/Computing/FunctionPatternComputer.cpp src/CodeEater/Computing/FunctionProcessor.cpp src/CodeEater/Computing/StateChanger.cpp 
        src/CodeEater/Computing/EatingProcessor.cpp src/CodeEater/Computing/NeighborhoodManager.cpp src/CodeEater/Computing/RuleApplier.cpp
        src/CodeEater/Computing/RuleNumberComputer.cpp
    src/CodeEater/Experiments/ExperimentCodeEater.cpp src/CodeEater/Experiments/ExperimentCodeEater1.cpp src/CodeEater/Experiments/ExperimentCodeEater2.cpp 
        src/CodeEater/Experiments/ExperimentCodeEater3.cpp)
add_executable(code_eater_experience ${HEADERS_COMMON} ${HEADERS} ${SOURCES_COMMON} ${SOURCES})

target_link_libraries(code_eater_experience ${LIBS})

