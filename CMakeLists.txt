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

set(HEADERS_UTILS src/Utils/Functions.hpp src/Utils/Constants.hpp src/Utils/Colors.hpp
    src/Utils/Maths/RandomGen.hpp)

set(SOURCES_UTILS)


# ********************************* General *********************************

set(HEADERS_GENERAL src/General/Place.hpp)

set(SOURCES_GENERAL src/General/Place.cpp)


# ********************************* Entities *********************************

set(HEADERS_ENTITIES src/Entities/Entity.hpp src/Entities/EntityVoid.hpp
    src/Entities/Entity.hpp src/Entities/EntityInt.hpp
        src/Entities/Entity.hpp src/Entities/EntityBool.hpp)

set(SOURCES_ENTITIES src/Entities/Entity.cpp src/Entities/EntityVoid.cpp
    src/Entities/Entity.hpp src/Entities/EntityInt.cpp
        src/Entities/Entity.hpp src/Entities/EntityBool.cpp)


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

set(HEADERS_MODEL_TH_INFO 
    src/Models/TheoreticalInfo/Universe/UniverseTheoreticalInfo.hpp)

set(SOURCES_MODEL_TH_INFO 
    src/Models/TheoreticalInfo/Universe/UniverseTheoreticalInfo.cpp
# experiments
    #src/Models/TheoreticalInfo/Experiment/.cpp
    )


# ********************************* Maths *********************************

set(HEADERS_MODEL_MATHS
    src/Models/Maths/Universe/UniverseMaths.hpp)

set(SOURCES_MODEL_MATHS 
    src/Models/Maths/Universe/UniverseMaths.cpp
# experiments
    #src/Models/Maths/Experiment/.cpp
    )


# ********************************* Classical ML algos *********************************

set(HEADERS_MODEL_CLASSICAL_ALGOS 
# Biology
    src/Models/ClassicalAlgos/Biology/AbstractTrait.hpp src/Models/ClassicalAlgos/Biology/Trait.hpp 
    src/Models/ClassicalAlgos/Biology/Gene/Gene.hpp
# Individuals
    # Algos
    src/Models/ClassicalAlgos/Individuals/IndividualLinear.hpp
    # Entities
    src/Models/ClassicalAlgos/Individuals/LinearEntity.hpp
# Universes
    src/Models/ClassicalAlgos/Universe/UniverseClassicalAlgos.hpp)

set(SOURCES_MODEL_CLASSICAL_ALGOS
# Biology
    src/Models/ClassicalAlgos/Biology/Gene/Gene.cpp
# Individuals
    # Algos
    src/Models/ClassicalAlgos/Individuals/IndividualLinear.cpp
    # Entities
    src/Models/ClassicalAlgos/Individuals/LinearEntity.cpp
# Universes
    src/Models/ClassicalAlgos/Universe/UniverseClassicalAlgos.cpp
# experiments
    #src/Models/ClassicalAlgos/Experiment/.cpp
    )


# ********************************* Evolutionary algorithms *********************************

set(HEADERS_MODEL_EVO_ALGInstruction.hppOS
    src/Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp)

set(SOURCES_MODEL_EVO_ALGOS
    src/Models/EvoAlgos/Universe/UniverseEvoAlgos.cpp
# experiments
    #src/Models/EvoAlgos/Experiment/.cpp
    )


# ********************************* Evolutionary biology *********************************

set(HEADERS_MODEL_BIO_EVO
    src/Models/BioEvo/Universe/UniverseBioEvo.hpp)

set(SOURCES_MODEL_BIO_EVO 
    src/Models/BioEvo/Universe/UniverseBioEvo.cpp
# experiments
    #src/Models/BioEvo/Experiment/.cpp
    )


# ********************************* Code eaters *********************************

set(HEADERS_MODEL_CODE_EATERS
    src/Models/CodeEaters/Universe/UniverseCodeEaters.hpp
# entities
    src/Models/CodeEaters/Entities/EntityUnaryId.hpp
        src/Models/CodeEaters/Entities/EntityUnaryNot.hpp)

set(SOURCES_MODEL_CODE_EATERS
    src/Models/CodeEaters/Universe/UniverseCodeEaters.cpp
# entities
    src/Models/CodeEaters/Entities/EntityUnaryId.cpp
        src/Models/CodeEaters/Entities/EntityUnaryNot.cpp
# experiments
    #src/Models/CodeEaters/Experiment/.cpp
    )


# ********************************* Economy *********************************

set(HEADERS_MODEL_ECONOMY
    src/Models/Economy/Universe/UniverseEconomy.hpp)

set(SOURCES_MODEL_ECONOMY
    src/Models/Economy/Universe/UniverseEconomy.cpp
# experiments
    #src/Models/Economy/Experiment/.cpp
    )


# ********************************* Finance *********************************

set(HEADERS_MODEL_FINANCE
    src/Models/Finance/Universe/UniverseFinance.hpp)

set(SOURCES_MODEL_FINANCE
    src/Models/Finance/Universe/UniverseFinance.cpp
# experiments
    #src/Models/Finance/Experiment/.cpp
    )



set(HEADERS_MODELS ${HEADERS_MODEL_CLASSICAL_INFO} ${HEADERS_MODEL_TH_INFO} ${HEADERS_MODEL_MATHS} 
    ${HEADERS_MODEL_CLASSICAL_ALGOS} ${HEADERS_MODEL_EVO_ALGOS} ${HEADERS_MODEL_BIO_EVO} 
    ${HEADERS_MODEL_CODE_EATERS} ${HEADERS_MODEL_ECONOMY} ${HEADERS_MODEL_FINANCE})

set(SOURCES_MODELS ${SOURCES_MODEL_CLASSICAL_INFO} ${SOURCES_MODEL_TH_INFO} ${SOURCES_MODEL_MATHS} 
    ${SOURCES_MODEL_CLASSICAL_ALGOS} ${SOURCES_MODEL_EVO_ALGOS} ${SOURCES_MODEL_BIO_EVO} 
    ${SOURCES_MODEL_CODE_EATERS} ${SOURCES_MODEL_ECONOMY} ${SOURCES_MODEL_FINANCE})


set(HEADERS_FRAMEWORK ${HEADERS_GENERAL} ${HEADERS_ENTITIES} ${HEADERS_INSTR} ${HEADERS_UNIVERSE} ${HEADERS_INDIVIDUAL} ${HEADERS_ENVIRONMENT} ${HEADERS_UTILS} 
    ${HEADERS_EXPERIMENTS} ${HEADERS_UNIT_TEST})

set(SOURCES_FRAMEWORK ${SOURCES_GENERAL} ${SOURCES_ENTITIES} ${SOURCES_INSTR} ${SOURCES_UNIVERSE} ${SOURCES_INDIVIDUAL} ${SOURCES_ENVIRONMENT} ${SOURCES_UTILS}
    ${SOURCES_EXPERIMENTS} ${SOURCES_UNIT_TEST})



add_executable(classical_info src/Models/ClassicalInfo/Experiment/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_CLASSICAL_INFO} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_CLASSICAL_INFO})
target_link_libraries(classical_info ${LIBS})

add_executable(classical_th_info src/Models/TheoreticalInfo/Experiment/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_TH_INFO} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_TH_INFO})
target_link_libraries(classical_th_info ${LIBS})

add_executable(classical_maths src/Models/Maths/Experiment/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_MATHS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_MATHS})
target_link_libraries(classical_maths ${LIBS})

add_executable(classical_algos src/Models/ClassicalAlgos/Experiment/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_CLASSICAL_ALGOS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_CLASSICAL_ALGOS})
target_link_libraries(classical_algos ${LIBS})

add_executable(classical_evo_algos src/Models/EvoAlgos/Experiment/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_EVO_ALGOS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_EVO_ALGOS})
target_link_libraries(classical_evo_algos ${LIBS})

add_executable(classical_bioevo src/Models/BioEvo/Experiment/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_BIO_EVO} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_BIO_EVO})
target_link_libraries(classical_bioevo ${LIBS})

add_executable(classical_code_eaters src/Models/CodeEaters/Experiment/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_CODE_EATERS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_CODE_EATERS})
target_link_libraries(classical_code_eaters ${LIBS})

add_executable(classical_economy src/Models/Economy/Experiment/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_ECONOMY} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_ECONOMY})
target_link_libraries(classical_economy ${LIBS})

add_executable(classical_finance src/Models/Finance/Experiment/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_FINANCE} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_FINANCE})
target_link_libraries(classical_finance ${LIBS})



# ********************************* Unit tests *********************************


# ********** evolutionary biology

set(HEADERS_UNIT_TESTS_BIO_EVO 
    src/UnitTests/BioEvo/test_1_empty.hpp)

add_executable(unit_tests_bio_evo src/UnitTests/BioEvo/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_BIO_EVO} ${HEADERS_UNIT_TESTS_BIO_EVO} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_BIO_EVO})
target_link_libraries(unit_tests_bio_evo ${LIBS})

# ********** classical algos

set(HEADERS_UNIT_TESTS_CLASSICAL_ALGOS 
    src/UnitTests/ClassicalAlgos/test_1_empty.hpp)

add_executable(unit_tests_classical_algos src/UnitTests/ClassicalAlgos/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_CLASSICAL_ALGOS} ${HEADERS_UNIT_TESTS_CLASSICAL_ALGOS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_CLASSICAL_ALGOS})
target_link_libraries(unit_tests_classical_algos ${LIBS})


# ********** classical computer science

set(HEADERS_UNIT_TESTS_CLASSICAL_INFO 
    src/UnitTests/ClassicalInfo/test_1_empty.hpp)

add_executable(unit_tests_classical_info src/UnitTests/ClassicalInfo/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_CLASSICAL_INFO} ${HEADERS_UNIT_TESTS_CLASSICAL_INFO} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_CLASSICAL_INFO})
target_link_libraries(unit_tests_classical_info ${LIBS})


# ********** code eaters

set(HEADERS_UNIT_TESTS_CODE_EATERS
    src/UnitTests/CodeEaters/test_1_empty.hpp
        src/UnitTests/CodeEaters/test_1_1.hpp
        src/UnitTests/CodeEaters/test_1_2.hpp
    src/UnitTests/CodeEaters/test_2_operations.hpp
        src/UnitTests/CodeEaters/test_2_1.hpp
            src/UnitTests/CodeEaters/test_2_1_1.hpp
    src/UnitTests/CodeEaters/test_3_metadata.hpp
        src/UnitTests/CodeEaters/test_3_1.hpp)

add_executable(unit_tests_code_eaters src/UnitTests/CodeEaters/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_CODE_EATERS} ${HEADERS_UNIT_TESTS_CODE_EATERS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_CODE_EATERS})
target_link_libraries(unit_tests_code_eaters ${LIBS})


# ********** economy

set(HEADERS_UNIT_TESTS_ECONOMY
    src/UnitTests/Economy/test_1_empty.hpp)

add_executable(unit_tests_economy src/UnitTests/Economy/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_ECONOMY} ${HEADERS_UNIT_TESTS_ECONOMY} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_ECONOMY})
target_link_libraries(unit_tests_economy ${LIBS})


# ********** evolutionary algorithms

set(HEADERS_UNIT_TESTS_EVO_ALGOS
    src/UnitTests/EvoAlgos/test_1_empty.hpp)

add_executable(unit_tests_evo_algos src/UnitTests/EvoAlgos/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_EVO_ALGOS} ${HEADERS_UNIT_TESTS_EVO_ALGOS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_EVO_ALGOS})
target_link_libraries(unit_tests_evo_algos ${LIBS})


# ********** finance

set(HEADERS_UNIT_TESTS_FINANCE
    src/UnitTests/Finance/test_1_empty.hpp)

add_executable(unit_tests_finance src/UnitTests/Finance/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_FINANCE} ${HEADERS_UNIT_TESTS_FINANCE} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_FINANCE})
target_link_libraries(unit_tests_finance ${LIBS})


# ********** maths

set(HEADERS_UNIT_TESTS_MATHS
    src/UnitTests/Maths/test_1_empty.hpp)

add_executable(unit_tests_maths src/UnitTests/Maths/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_MATHS} ${HEADERS_UNIT_TESTS_MATHS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_MATHS})
target_link_libraries(unit_tests_maths ${LIBS})


# ********** theorical computer science

set(HEADERS_UNIT_TESTS_TH_INFO
    src/UnitTests/TheoreticalInfo/test_1_empty.hpp)

add_executable(unit_tests_th_info src/UnitTests/TheoreticalInfo/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_TH_INFO} ${HEADERS_UNIT_TESTS_TH_INFO} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_TH_INFO})
target_link_libraries(unit_tests_th_info ${LIBS})



# ********** all

set(HEADERS_UNIT_TESTS_ALL 
    HEADERS_UNIT_TESTS_BIO_EVO HEADERS_UNIT_TESTS_CLASSICAL_ALGOS HEADERS_UNIT_TESTS_CLASSICAL_INFO 
    HEADERS_UNIT_TESTS_CODE_EATERS HEADERS_UNIT_TESTS_ECONOMY HEADERS_UNIT_TESTS_EVO_ALGOS 
    HEADERS_UNIT_TESTS_FINANCE HEADERS_UNIT_TESTS_MATHS HEADERS_UNIT_TESTS_TH_INFO)

set(SOURCES_UNIT_TESTS_ALL )

add_executable(unit_tests src/UnitTests/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODELS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODELS})
target_link_libraries(unit_tests ${LIBS})



add_executable(bioevo src/main.cpp ${HEADERS_FRAMEWORK} ${SOURCES_FRAMEWORK})
target_link_libraries(bioevo ${LIBS})
