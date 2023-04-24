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
set(CMAKE_BUILD_TYPE Debug)


# ********************************* External libraries *********************************

set(Boost_INCLUDE_DIR "/home/adrien/Disque/Programmation/Packages/cpp/boost_1_81_0")
FIND_PACKAGE(Boost COMPONENTS asio beast)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})


# ********************************* Common *********************************

set(HEADERS_COMMON_BASIC src/Server/Server.hpp 
    src/PreprocessingDefinitions.hpp src/Constants.hpp src/Utils/Log/logpaths.hpp src/Utils/Log/Logger.hpp 
    src/Utils/Convert/tostring.hpp
    src/Utils/Math/Pair.hpp src/Utils/Math/RandomGen.hpp
    src/Utils/Result/Result.hpp src/Utils/Result/Result1.hpp
    src/Universe.hpp src/Framework.hpp src/ExperimentOld.hpp src/Individual.hpp src/Environment.hpp src/Buffer.hpp src/Flow.hpp
    src/Solution.hpp)
set(SOURCES_COMMON_BASIC src/Server/Server.cpp
    src/Constants.cpp src/Utils/Log/logpaths.cpp src/Utils/Log/Logger.cpp 
    src/Utils/Convert/tostring.cpp src/Utils/Math/RandomGen.cpp
    src/Utils/Result/Result.cpp src/Utils/Result/Result1.cpp
    src/Universe.cpp src/Framework.cpp src/ExperimentOld.cpp src/Individual.cpp src/Environment.cpp src/Buffer.cpp src/Flow.cpp
    src/Solution.cpp src/main.cpp)


# *********************** Biology ***********************

set(HEADERS_COMMON_BIO src/Biology/Gene.hpp src/Biology/AbstractTrait.hpp src/Biology/Trait.hpp)
set(SOURCES_COMMON_BIO src/Biology/Gene.cpp)

set(HEADERS_COMMON ${HEADERS_COMMON_BASIC} ${HEADERS_COMMON_BIO})
set(SOURCES_COMMON ${SOURCES_COMMON_BASIC} ${SOURCES_COMMON_BIO})


# ********************************* Experiments *********************************

set(HEADERS_EXPERIMENTS src/Experiments/Experiment_1_00/experiment_1_00.hpp)
set(SOURCES_EXPERIMENTS src/Experiments/Experiment_1_00/experiment_1_00.cpp)


# ********************************* Classical algos *********************************

# ********************** Experiment 1 **********************


set(HEADERS_CLASSIC_LINEAR 
    src/Experiments/Experiment_1_00/Flow/InputLinearIndividual.hpp
        src/Experiments/Experiment_1_00/Flow/OutputLinearIndividual.hpp
        src/Experiments/Experiment_1_00/Flow/InputLinearEnvironment.hpp
        src/Experiments/Experiment_1_00/Flow/OutputLinearEnvironment.hpp
    src/Experiments/Experiment_1_00/EnvironmentLinear.hpp
    src/Experiments/Experiment_1_00/Individuals/LinearRegressionIndividual.hpp
    src/Experiments/Experiment_1_00/Flow/BufferLinear.hpp
    src/Experiments/Experiment_1_00/GeneLinear.hpp)
set(SOURCES_CLASSIC_LINEAR 
    src/Experiments/Experiment_1_00/Flow/InputLinearIndividual.cpp
        src/Experiments/Experiment_1_00/Flow/OutputLinearIndividual.cpp
        src/Experiments/Experiment_1_00/Flow/InputLinearEnvironment.cpp
        src/Experiments/Experiment_1_00/Flow/OutputLinearEnvironment.cpp
    src/Experiments/Experiment_1_00/EnvironmentLinear.cpp
    src/Experiments/Experiment_1_00/Individuals/LinearRegressionIndividual.cpp
    src/Experiments/Experiment_1_00/Flow/BufferLinear.cpp
    src/Experiments/Experiment_1_00/GeneLinear.cpp)



set(HEADERS_CLASSIC src/ClassicalAlgos/ClassicalUniverse.hpp
    ${HEADERS_CLASSIC_LINEAR}) 
set(SOURCES_CLASSIC src/ClassicalAlgos/ClassicalUniverse.cpp
    ${SOURCES_CLASSIC_LINEAR})


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

target_link_libraries(bioevo ${Boost_LIBRARIES} ${LIBS})

