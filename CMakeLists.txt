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

set(HEADERS_COMMON src/PreprocessingDefinitions.hpp src/Constants.hpp src/Utils/Log/logpaths.hpp src/Utils/Log/Logger.hpp 
    src/Universe.hpp src/Framework.hpp src/ExperimentOld.hpp src/Individual.hpp src/Environment.hpp src/Buffer.hpp src/Flow.hpp
    src/Solution.hpp)
set(SOURCES_COMMON src/Constants.cpp src/Utils/Log/logpaths.cpp src/Utils/Log/Logger.cpp 
    src/Universe.cpp src/Framework.cpp src/ExperimentOld.cpp src/Individual.cpp src/Environment.cpp src/Buffer.cpp src/Flow.cpp
    src/Solution.cpp src/main.cpp)


# ********************************* Experiments *********************************

set(HEADERS_EXPERIMENTS src/Experiments/ClassicalAlgos/experiment_classical_algo_1.hpp)
set(SOURCES_EXPERIMENTS src/Experiments/ClassicalAlgos/experiment_classical_algo_1.cpp)


# ********************************* Classical algos *********************************

set(HEADERS_CLASSIC src/ClassicalAlgos/ClassicalUniverse.hpp 
    src/ClassicalAlgos/LinearRegression/FlowLinear.hpp src/ClassicalAlgos/LinearRegression/EnvironmentLinear.hpp
        src/ClassicalAlgos/LinearRegression/Individuals/LinearRegressionIndividual.hpp
        src/ClassicalAlgos/LinearRegression/BufferLinear.hpp)
set(SOURCES_CLASSIC src/ClassicalAlgos/ClassicalUniverse.cpp
    src/ClassicalAlgos/LinearRegression/FlowLinear.cpp src/ClassicalAlgos/LinearRegression/EnvironmentLinear.cpp
        src/ClassicalAlgos/LinearRegression/Individuals/LinearRegressionIndividual.cpp
        src/ClassicalAlgos/LinearRegression/BufferLinear.cpp)


# ********************************* Code Eaters *********************************

set(HEADERS src/CodeEater/ConstantsCodeEater.hpp src/CodeEater/UniverseCodeEater.hpp src/CodeEater/CodeEaters/CodeEater.hpp
    src/CodeEater/Computing/Utils/Permutation.hpp src/CodeEater/Computing/Utils/FunctionPattern.hpp src/CodeEater/Computing/Utils/ComputationResult.hpp
        src/CodeEater/Computing/FunctionPatternComputer.hpp src/CodeEater/Computing/FunctionProcessor.hpp src/CodeEater/Computing/StateChanger.hpp 
        src/CodeEater/Computing/EatingProcessor.hpp src/CodeEater/Computing/NeighborhoodManager.hpp src/CodeEater/Computing/RuleApplier.hpp
        src/CodeEater/Computing/RuleNumberComputer.hpp
    src/CodeEater/Experiments/ExperimentOldCodeEater.hpp src/CodeEater/Experiments/ExperimentOldCodeEater1.hpp src/CodeEater/Experiments/ExperimentOldCodeEater2.hpp 
        src/CodeEater/Experiments/ExperimentOldCodeEater3.hpp)
set(SOURCES src/CodeEater/CodeEaters/CodeEater.cpp src/CodeEater/UniverseCodeEater.cpp 
    src/CodeEater/Computing/Utils/Permutation.cpp src/CodeEater/Computing/Utils/FunctionPattern.cpp src/CodeEater/Computing/Utils/ComputationResult.cpp
        src/CodeEater/Computing/FunctionPatternComputer.cpp src/CodeEater/Computing/FunctionProcessor.cpp src/CodeEater/Computing/StateChanger.cpp 
        src/CodeEater/Computing/EatingProcessor.cpp src/CodeEater/Computing/NeighborhoodManager.cpp src/CodeEater/Computing/RuleApplier.cpp
        src/CodeEater/Computing/RuleNumberComputer.cpp
    src/CodeEater/Experiments/ExperimentOldCodeEater.cpp src/CodeEater/Experiments/ExperimentOldCodeEater1.cpp src/CodeEater/Experiments/ExperimentOldCodeEater2.cpp 
        src/CodeEater/Experiments/ExperimentOldCodeEater3.cpp)
add_executable(bioevo ${HEADERS_COMMON} ${HEADERS_CLASSIC} ${HEADERS} ${HEADERS_EXPERIMENTS} 
    ${SOURCES_COMMON} ${SOURCES_CLASSIC} ${SOURCES} ${SOURCES_EXPERIMENTS})

target_link_libraries(bioevo ${LIBS})

