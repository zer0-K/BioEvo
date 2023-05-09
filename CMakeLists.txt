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
FIND_PACKAGE(Boost COMPONENTS asio beast json)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})


# ********************************* Declarations *********************************


set(HEADERS_DECL src/Declaration/PreprocessingDefinitions.hpp src/Declaration/Constants.hpp)

set(SOURCES_DECL src/Declaration/Constants.cpp)



# ********************************* General *********************************


set(HEADERS_GENERAL src/Framework.hpp src/Universe.hpp src/Solution.hpp
    src/Entity.hpp src/ExperimentOld.hpp)

set(SOURCES_GENERAL src/main.cpp
    src/Framework.cpp src/Universe.cpp src/Solution.cpp
    src/Entity.cpp src/ExperimentOld.cpp)


# ********************************* Utils *********************************

set(HEADERS_UTILS src/Utils/Builder.hpp 
    src/Utils/Config/config.hpp src/Utils/Config/ConfigRunner.hpp
    src/Utils/Convert/toarray.hpp src/Utils/Convert/tostring.hpp
    src/Utils/json/interprete_json.hpp
    src/Utils/Log/logpaths.hpp src/Utils/Log/Logger.hpp
    src/Utils/Math/Pair.hpp src/Utils/Math/RandomGen.hpp)

set(SOURCES_UTILS
    src/Utils/Config/config.cpp src/Utils/Config/ConfigRunner.cpp
    src/Utils/Convert/toarray.cpp src/Utils/Convert/tostring.cpp
    src/Utils/json/interprete_json.cpp
    src/Utils/Log/logpaths.cpp src/Utils/Log/Logger.cpp
    src/Utils/Math/RandomGen.cpp)


# ********************************* Server *********************************

set(HEADERS_SERVER src/Server/Server.hpp)

set(SOURCES_SERVER src/Server/Server.cpp)


# ********************************* Experiments *********************************

set(HEADERS_EXPERIMENTS src/Experiments/experiment_1.hpp)

set(SOURCES_EXPERIMENTS src/Experiments/experiment_1.cpp)


# ********************************* Flow *********************************

set(HEADERS_FLOW src/Flow/Flow.hpp src/Flow/FlowList.hpp
    src/Flow/FlowLinear1_x.hpp src/Flow/FlowLinear1_f_x.hpp
    src/Flow/InputLinearEnvironment.hpp src/Flow/InputLinearIndividual.hpp src/Flow/OutputLinearEnvironment.hpp src/Flow/OutputLinearIndividual.hpp
    src/Flow/Buffer/Buffer.hpp src/Flow/Buffer/BufferLinear.hpp)

set(SOURCES_FLOW src/Flow/Flow.cpp src/Flow/FlowList.cpp
    src/Flow/FlowLinear1_x.cpp src/Flow/FlowLinear1_f_x.cpp
    src/Flow/InputLinearEnvironment.cpp src/Flow/InputLinearIndividual.cpp src/Flow/OutputLinearEnvironment.cpp src/Flow/OutputLinearIndividual.cpp
    src/Flow/Buffer/Buffer.cpp src/Flow/Buffer/BufferLinear.cpp)


# ********************************* Biology *********************************

set(HEADERS_BIOLOGY src/Biology/AbstractTrait.hpp src/Biology/Trait.hpp
    src/Biology/Gene/Gene.hpp src/Biology/Gene/GeneLinear.hpp)

set(SOURCES_BIOLOGY
    src/Biology/Gene/Gene.cpp src/Biology/Gene/GeneLinear.cpp)


# ********************************* Environment *********************************

set(HEADERS_ENVIRONMENT src/Environment/Environment.hpp src/Environment/EnvironmentLinear.hpp)

set(SOURCES_ENVIRONMENT src/Environment/Environment.cpp src/Environment/EnvironmentLinear.cpp)


# ********************************* Individual *********************************

set(HEADERS_INDIVIDUAL src/Individual/Individual.hpp src/Individual/IndividualLinear.hpp)

set(SOURCES_INDIVIDUAL src/Individual/Individual.cpp src/Individual/IndividualLinear.cpp)



# ********************************* Code Eaters *********************************

set(HEADERS_CODE_EATER src/CodeEater/ConstantsCodeEater.hpp src/CodeEater/UniverseCodeEater.hpp src/CodeEater/CodeEaters/CodeEater.hpp
    src/CodeEater/Computing/Utils/Permutation.hpp src/CodeEater/Computing/Utils/FunctionPattern.hpp src/CodeEater/Computing/Utils/ComputationResult.hpp
        src/CodeEater/Computing/FunctionPatternComputer.hpp src/CodeEater/Computing/FunctionProcessor.hpp src/CodeEater/Computing/StateChanger.hpp 
        src/CodeEater/Computing/EatingProcessor.hpp src/CodeEater/Computing/NeighborhoodManager.hpp src/CodeEater/Computing/RuleApplier.hpp
        src/CodeEater/Computing/RuleNumberComputer.hpp
    src/ExperimentOld.hpp src/CodeEater/Experiments/ExperimentOldCodeEater.hpp src/CodeEater/Experiments/ExperimentOldCodeEater1.hpp 
        src/CodeEater/Experiments/ExperimentOldCodeEater2.hpp src/CodeEater/Experiments/ExperimentOldCodeEater3.hpp)
set(SOURCES_CODE_EATER src/CodeEater/CodeEaters/CodeEater.cpp src/CodeEater/UniverseCodeEater.cpp 
    src/CodeEater/Computing/Utils/Permutation.cpp src/CodeEater/Computing/Utils/FunctionPattern.cpp src/CodeEater/Computing/Utils/ComputationResult.cpp
        src/CodeEater/Computing/FunctionPatternComputer.cpp src/CodeEater/Computing/FunctionProcessor.cpp src/CodeEater/Computing/StateChanger.cpp 
        src/CodeEater/Computing/EatingProcessor.cpp src/CodeEater/Computing/NeighborhoodManager.cpp src/CodeEater/Computing/RuleApplier.cpp
        src/CodeEater/Computing/RuleNumberComputer.cpp
    src/ExperimentOld.cpp src/CodeEater/Experiments/ExperimentOldCodeEater.cpp src/CodeEater/Experiments/ExperimentOldCodeEater1.cpp 
        src/CodeEater/Experiments/ExperimentOldCodeEater2.cpp src/CodeEater/Experiments/ExperimentOldCodeEater3.cpp)
#add_executable(bioevo ${HEADERS_GENERAL} ${HEADERS_CODE_EATER} ${HEADERS_EXPERIMENTS} 
#    ${SOURCES_GENERAL} ${SOURCES_CODE_EATER} ${SOURCES_EXPERIMENTS})



set(HEADERS_ALL ${HEADERS_DECL} ${HEADERS_GENERAL} ${HEADERS_UTILS} ${HEADERS_SERVER} ${HEADERS_EXPERIMENTS} 
    ${HEADERS_FLOW} ${HEADERS_BIOLOGY} ${HEADERS_ENVIRONMENT} ${HEADERS_INDIVIDUAL} ${HEADERS_CODE_EATER})

set(SOURCES_ALL ${SOURCES_DECL} ${SOURCES_GENERAL} ${SOURCES_UTILS} ${SOURCES_SERVER} ${SOURCES_EXPERIMENTS} 
    ${SOURCES_FLOW} ${SOURCES_BIOLOGY} ${SOURCES_ENVIRONMENT} ${SOURCES_INDIVIDUAL} ${SOURCES_CODE_EATER})



# TODO : remove ExperimentOld
add_executable(bioevo ${HEADERS_ALL} ${SOURCES_ALL})
target_link_libraries(bioevo ${Boost_LIBRARIES} ${LIBS} /usr/bin/lib/libboost_json.a)
