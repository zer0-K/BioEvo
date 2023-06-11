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

#set(Boost_INCLUDE_DIR "/home/adrien/Disque/Programmation/Packages/cpp/boost_1_81_0")
#FIND_PACKAGE(Boost COMPONENTS asio beast json)
#INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})


# ********************************* Utils *********************************

set(HEADERS_UTILS src/Utils/Constants.hpp src/Utils/Colors.hpp)

set(SOURCES_UTILS)


# ********************************* General *********************************

set(HEADERS_GENERAL 
    src/General/Entity.hpp src/General/VoidEntity.hpp src/General/Place.hpp)

set(SOURCES_GENERAL 
    src/General/Entity.cpp src/General/VoidEntity.cpp src/General/Place.cpp)


# ********************************* Experiments *********************************

set(HEADERS_EXPERIMENTS src/Experiment/Experiment.hpp
    src/Experiment/ExperimentRunner.hpp)

set(SOURCES_EXPERIMENTS src/Experiment/Experiment.cpp
    src/Experiment/ExperimentRunner.cpp)


# ********************************* Universe *********************************

set(HEADERS_UNIVERSE src/Universe/Universe.hpp)

set(SOURCES_UNIVERSE src/Universe/Universe.cpp)


# ********************************* Environment *********************************

set(HEADERS_ENVIRONMENT src/Environment/Environment.hpp)

set(SOURCES_ENVIRONMENT src/Environment/Environment.cpp)


# ********************************* Individual *********************************

set(HEADERS_INDIVIDUAL src/Individual/Individual.hpp)

set(SOURCES_INDIVIDUAL src/Individual/Individual.cpp)



# ****************************************************************** Models ******************************************************************


# ********************************* Classical computer science *********************************

set(HEADERS_MODEL_CLASSICAL_INFO 
    src/Models/ClassicalInfo/Universe/UniverseClassicalInfo.hpp
# experiments
    src/Models/ClassicalInfo/Experiment/ConsoleApp.hpp)

set(SOURCES_MODEL_CLASSICAL_INFO 
    src/Models/ClassicalInfo/Universe/UniverseClassicalInfo.cpp
# experiments
    src/Models/ClassicalInfo/Experiment/ConsoleApp.cpp)


# ********************************* Theoretical computer science *********************************

set(HEADERS_MODEL_TH_INFO )

set(SOURCES_MODEL_TH_INFO )


# ********************************* Maths *********************************

set(HEADERS_MODEL_MATHS )

set(SOURCES_MODEL_MATHS )


# ********************************* Classical ML algos *********************************

set(HEADERS_MODEL_CLASSICAL_ALGOS )

set(SOURCES_MODEL_CLASSICAL_ALGOS )


# ********************************* Evolutionary algorithms *********************************

set(HEADERS_MODEL_EVO_ALGO )

set(SOURCES_MODEL_EVO_ALGO )


# ********************************* Evolutionary biology *********************************

set(HEADERS_MODEL_BIO_EVO )

set(SOURCES_MODEL_BIO_EVO )


# ********************************* Code eaters *********************************

set(HEADERS_MODEL_CODE_EATERS )

set(SOURCES_MODEL_CODE_EATERS )


# ********************************* Economy *********************************

set(HEADERS_MODEL_ECONOMY )

set(SOURCES_MODEL_ECONOMY )


# ********************************* Finance *********************************

set(HEADERS_MODEL_FINANCE )

set(SOURCES_MODEL_FINANCE )


# ********************************* Unit tests *********************************

set(HEADERS_UNIT_TEST 
# classical info
    src/UnitTest/ClassicalInfo/test_1_empty.hpp
# theoretical info
# maths
# classical algos
# evolutionary algorithms
# evolutionary biology
# code eaters
# economy
# finance
    )

set(SOURCES_UNIT_TEST )


set(HEADERS_MODELS ${HEADERS_MODEL_CLASSICAL_INFO} ${HEADERS_MODEL_TH_INFO} ${HEADERS_MODEL_MATHS} 
    ${HEADERS_MODEL_CLASSICAL_ALGOS} ${HEADERS_MODEL_EVO_ALGO} ${HEADERS_MODEL_BIO_EVO} 
    ${HEADERS_MODEL_CODE_EATERS} ${HEADERS_MODEL_ECONOMY} ${HEADERS_MODEL_FINANCE})

set(SOURCES_MODELS ${SOURCES_MODEL_CLASSICAL_INFO} ${SOURCES_MODEL_TH_INFO} ${SOURCES_MODEL_MATHS} 
    ${SOURCES_MODEL_CLASSICAL_ALGOS} ${SOURCES_MODEL_EVO_ALGO} ${SOURCES_MODEL_BIO_EVO} 
    ${SOURCES_MODEL_CODE_EATERS} ${SOURCES_MODEL_ECONOMY} ${SOURCES_MODEL_FINANCE})


set(HEADERS_FRAMEWORK ${HEADERS_GENERAL} ${HEADERS_UNIVERSE} ${HEADERS_INDIVIDUAL} ${HEADERS_ENVIRONMENT} ${HEADERS_UTILS} 
    ${HEADERS_EXPERIMENTS} ${HEADERS_UNIT_TEST})

set(SOURCES_FRAMEWORK ${SOURCES_GENERAL} ${SOURCES_UNIVERSE} ${SOURCES_INDIVIDUAL} ${SOURCES_ENVIRONMENT} ${SOURCES_UTILS}
    ${SOURCES_EXPERIMENTS} ${SOURCES_UNIT_TEST})


add_executable(classical_info src/Models/ClassicalInfo/Experiment/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_CLASSICAL_INFO} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_CLASSICAL_INFO})
target_link_libraries(classical_info ${LIBS})


add_executable(unit_tests src/UnitTest/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODELS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODELS})
target_link_libraries(unit_tests ${LIBS})

add_executable(bioevo src/main.cpp ${HEADERS_FRAMEWORK} ${SOURCES_FRAMEWORK})
target_link_libraries(bioevo ${LIBS})
