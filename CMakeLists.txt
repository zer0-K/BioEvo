cmake_minimum_required(VERSION 3.20)
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
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ─── Output directories ───────────────────────────────────────────────────────
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
 
# ********************************* External libraries *********************************

#set(Boost_INCLUDE_DIR "/home/adrien/Disque/Programmation/Packages/cpp/boost_1_81_0")
#FIND_PACKAGE(Boost COMPONENTS asio beast json)
#INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

# ─── Dear ImGui (vendored) ────────────────────────────────────────────────────
# Assumes you cloned / copied imgui into third_party/imgui/
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/third_party/imgui)
 
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)
 
# ─── SDL2 ─────────────────────────────────────────────────────────────────────
find_package(SDL2 REQUIRED)
 
# ─── OpenGL ───────────────────────────────────────────────────────────────────
find_package(OpenGL REQUIRED)


# ********************************* Utils *********************************

set(HEADERS_UTILS src/Utils/Functions.hpp src/Utils/Constants.hpp src/Utils/Colors.hpp
    src/Utils/Maths/RandomGen.hpp src/Utils/Logger.hpp)

set(SOURCES_UTILS)


# ********************************* General *********************************

set(HEADERS_GENERAL src/General/Place.hpp)

set(SOURCES_GENERAL src/General/Place.cpp)


# ********************************* Entities *********************************

set(HEADERS_ENTITIES src/Entities/Entity.hpp src/Entities/EntityVoid.hpp
    src/Entities/Entity.hpp src/Entities/EntityInt.hpp
        src/Entities/Entity.hpp src/Entities/EntityBool.hpp
        src/Entities/EntityList.hpp)

set(SOURCES_ENTITIES src/Entities/Entity.cpp src/Entities/EntityVoid.cpp
    src/Entities/Entity.hpp src/Entities/EntityInt.cpp
        src/Entities/Entity.hpp src/Entities/EntityBool.cpp
        src/Entities/EntityList.cpp)


# ********************************* Universe *********************************

set(HEADERS_UNIVERSE src/Universe/Universe.hpp)

set(SOURCES_UNIVERSE src/Universe/Universe.cpp)


# ********************************* Environment *********************************

set(HEADERS_ENVIRONMENT src/Environment/Environment.hpp)

set(SOURCES_ENVIRONMENT src/Environment/Environment.cpp)


# ********************************* Individual *********************************

set(HEADERS_INDIVIDUAL src/Individual/Individual.hpp)

set(SOURCES_INDIVIDUAL src/Individual/Individual.cpp)


# ********************************* Experiments *********************************

set(HEADERS_EXPERIMENTS src/Experiment/Experiment.hpp
    src/Experiment/ExperimentRunner.hpp)

set(SOURCES_EXPERIMENTS src/Experiment/Experiment.cpp
    src/Experiment/ExperimentRunner.cpp)



# ****************************************************************** Models ******************************************************************


# ********************************* Classical computer science *********************************

set(HEADERS_MODEL_CLASSICAL_INFO 
    src/Models/ClassicalInfo/Universe/UniverseClassicalInfo.hpp
)

set(SOURCES_MODEL_CLASSICAL_INFO 
    src/Models/ClassicalInfo/Universe/UniverseClassicalInfo.cpp
)


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
    src/Models/Maths/Universe/UniverseMaths.hpp
    src/Models/Maths/Playground/BasicOps/RecursiveBasicOps.hpp
#---------- Experiments
#----- Playground
# Basic ops
    src/Experiment/Maths/Playground/BasicOps/GenerationRecursiveOps.hpp)

set(SOURCES_MODEL_MATHS 
    src/Models/Maths/Universe/UniverseMaths.cpp
#---------- Experiments
#----- Playground
# Basic ops
    src/Experiment/Maths/Playground/BasicOps/GenerationRecursiveOps.cpp)


# ********************************* Classical ML algos *********************************

set(HEADERS_MODEL_CLASSICAL_ALGOS 
# Biology
    src/Models/ClassicalAlgos/Biology/AbstractTrait.hpp src/Models/ClassicalAlgos/Biology/Trait.hpp 
    src/Models/ClassicalAlgos/Biology/Gene/Gene.hpp src/Models/ClassicalAlgos/Biology/Gene/GeneGaussian.hpp
# Algos
    src/Models/ClassicalAlgos/Individuals/ClassicalIndividual.hpp
        src/Models/ClassicalAlgos/Individuals/LinearSimple.hpp
# Data
    src/Models/ClassicalAlgos/Data/ClassicalData.hpp
        src/Models/ClassicalAlgos/Data/ClassicalTestData.hpp src/Models/ClassicalAlgos/Data/ClassicalValidationData.hpp 
    src/Models/ClassicalAlgos/Data/Generation/DataGenerator.hpp
        src/Models/ClassicalAlgos/Data/Generation/DataGeneratorLinear.hpp
# Universes
    src/Models/ClassicalAlgos/Universe/UniverseClassicalAlgos.hpp
# Experiments
    src/Models/ClassicalAlgos/Experiment/LinearAlgos.hpp
        src/Models/ClassicalAlgos/Experiment/SimpleLinearAlgos.hpp)

set(SOURCES_MODEL_CLASSICAL_ALGOS
# Biology
    src/Models/ClassicalAlgos/Biology/Gene/Gene.cpp src/Models/ClassicalAlgos/Biology/Gene/GeneGaussian.cpp
# Algos
    src/Models/ClassicalAlgos/Individuals/ClassicalIndividual.cpp
        src/Models/ClassicalAlgos/Individuals/LinearSimple.cpp
# Data
    src/Models/ClassicalAlgos/Data/ClassicalData.cpp
        src/Models/ClassicalAlgos/Data/ClassicalTestData.cpp src/Models/ClassicalAlgos/Data/ClassicalValidationData.cpp 
    src/Models/ClassicalAlgos/Data/Generation/DataGenerator.cpp
        src/Models/ClassicalAlgos/Data/Generation/DataGeneratorLinear.cpp
# Universes
    src/Models/ClassicalAlgos/Universe/UniverseClassicalAlgos.cpp
# Experiments
    src/Models/ClassicalAlgos/Experiment/LinearAlgos.cpp
        src/Models/ClassicalAlgos/Experiment/SimpleLinearAlgos.cpp)


# ********************************* Evolutionary algorithms *********************************

set(HEADERS_MODEL_EVO_ALGOS
    src/Models/EvoAlgos/XASMAlgo/UtilityFunctions.hpp
    src/Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp src/Models/EvoAlgos/Universe/UniverseEvoXCustomNeighborhood.hpp
    src/Models/EvoAlgos/Universe/CustomNeighborhoods.hpp
# x86 evo algos
    src/Models/EvoAlgos/XASMAlgo/InstructionMapping.hpp
    src/Models/EvoAlgos/XASMAlgo/XASMAlgo.hpp src/Models/EvoAlgos/XASMAlgo/EvoX.hpp
    src/Models/EvoAlgos/XASMAlgo/FreeMolecules.hpp
# Parsing
    src/Models/EvoAlgos/XASMAlgo/Parsing/tRNATable.hpp
    src/Models/EvoAlgos/XASMAlgo/Parsing/XASMParser.hpp
    src/Models/EvoAlgos/XASMAlgo/Parsing/EvoXParser.hpp
#---------- Experiments
#----- BioEvo
# Replicators
    #src/Experiment/BioEvo/Replicators/EvoAlgos/EvoX/ReplicationEvoXQuine.hpp
#----- Classical Algos
# Function execution
    #src/Experiment/ClassicalInfo/FunctionExecution/EvoX/FunctionExecutionEvoX.hpp
    )

set(SOURCES_MODEL_EVO_ALGOS
    src/Models/EvoAlgos/Universe/UniverseEvoAlgos.cpp src/Models/EvoAlgos/Universe/UniverseEvoXCustomNeighborhood.cpp
# x86 evo algos
    src/Models/EvoAlgos/XASMAlgo/InstructionMapping.cpp
    src/Models/EvoAlgos/XASMAlgo/XASMAlgo.cpp src/Models/EvoAlgos/XASMAlgo/EvoX.cpp
    src/Models/EvoAlgos/XASMAlgo/FreeMolecules.cpp
# Parsing
    src/Models/EvoAlgos/XASMAlgo/Parsing/tRNATable.cpp
    src/Models/EvoAlgos/XASMAlgo/Parsing/XASMParser.cpp
    src/Models/EvoAlgos/XASMAlgo/Parsing/EvoXParser.cpp
#---------- Experiments
#----- BioEvo
# Replicators
    #src/Experiment/BioEvo/Replicators/EvoAlgos/EvoX/ReplicationEvoXQuine.cpp
#----- Classical Algos
# Function execution
    #src/Experiment/ClassicalInfo/FunctionExecution/EvoX/FunctionExecutionEvoX.cpp
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
    src/Models/CodeEaters/Entities/CodeEaters/CodeEater.hpp
    src/Models/CodeEaters/Entities/Base/EntityOperation.hpp
        src/Models/CodeEaters/Entities/Base/Boolean/EntityOperationBoolean.hpp
            src/Models/CodeEaters/Entities/Base/Boolean/EntityBoolId.hpp src/Models/CodeEaters/Entities/Base/Boolean/EntityBoolIdIn.hpp
                src/Models/CodeEaters/Entities/Base/Boolean/EntityNot.hpp src/Models/CodeEaters/Entities/Base/Boolean/EntityNotIn.hpp
            src/Models/CodeEaters/Entities/Base/Boolean/EntityAnd.hpp src/Models/CodeEaters/Entities/Base/Boolean/EntityAndIn.hpp
                src/Models/CodeEaters/Entities/Base/Boolean/EntityNand.hpp src/Models/CodeEaters/Entities/Base/Boolean/EntityNandIn.hpp
            src/Models/CodeEaters/Entities/Base/Boolean/EntityOr.hpp src/Models/CodeEaters/Entities/Base/Boolean/EntityOrIn.hpp
                src/Models/CodeEaters/Entities/Base/Boolean/EntityNor.hpp src/Models/CodeEaters/Entities/Base/Boolean/EntityNorIn.hpp
            src/Models/CodeEaters/Entities/Base/Boolean/EntityXor.hpp src/Models/CodeEaters/Entities/Base/Boolean/EntityXorIn.hpp
                src/Models/CodeEaters/Entities/Base/Boolean/EntityNxor.hpp src/Models/CodeEaters/Entities/Base/Boolean/EntityNxorIn.hpp
        src/Models/CodeEaters/Entities/Base/Int/EntityOperationInt.hpp
            src/Models/CodeEaters/Entities/Base/Int/EntityIncr.hpp 
            src/Models/CodeEaters/Entities/Base/Int/EntityAddInt.hpp src/Models/CodeEaters/Entities/Base/Int/EntityAddIntIn.hpp
                src/Models/CodeEaters/Entities/Base/Int/EntitySubInt.hpp src/Models/CodeEaters/Entities/Base/Int/EntitySubIntIn.hpp
            src/Models/CodeEaters/Entities/Base/Int/EntityMultInt.hpp src/Models/CodeEaters/Entities/Base/Int/EntityMultIntIn.hpp
                src/Models/CodeEaters/Entities/Base/Int/EntityDivInt.hpp src/Models/CodeEaters/Entities/Base/Int/EntityDivIntIn.hpp
    src/Models/CodeEaters/Entities/Base/Meta/EntityMetaOp.hpp
        src/Models/CodeEaters/Entities/Base/Meta/EntityOpCounter.hpp)

set(SOURCES_MODEL_CODE_EATERS
    src/Models/CodeEaters/Universe/UniverseCodeEaters.cpp
# entities
    src/Models/CodeEaters/Entities/CodeEaters/CodeEater.cpp
    src/Models/CodeEaters/Entities/Base/EntityOperation.cpp
        src/Models/CodeEaters/Entities/Base/Boolean/EntityOperationBoolean.cpp
            src/Models/CodeEaters/Entities/Base/Boolean/EntityBoolId.cpp src/Models/CodeEaters/Entities/Base/Boolean/EntityBoolIdIn.cpp
                src/Models/CodeEaters/Entities/Base/Boolean/EntityNot.cpp src/Models/CodeEaters/Entities/Base/Boolean/EntityNotIn.cpp
            src/Models/CodeEaters/Entities/Base/Boolean/EntityAnd.cpp src/Models/CodeEaters/Entities/Base/Boolean/EntityAndIn.cpp
                src/Models/CodeEaters/Entities/Base/Boolean/EntityNand.cpp src/Models/CodeEaters/Entities/Base/Boolean/EntityNandIn.cpp
            src/Models/CodeEaters/Entities/Base/Boolean/EntityOr.cpp src/Models/CodeEaters/Entities/Base/Boolean/EntityOrIn.cpp
                src/Models/CodeEaters/Entities/Base/Boolean/EntityNor.cpp src/Models/CodeEaters/Entities/Base/Boolean/EntityNorIn.cpp
            src/Models/CodeEaters/Entities/Base/Boolean/EntityXor.cpp src/Models/CodeEaters/Entities/Base/Boolean/EntityXorIn.cpp
                src/Models/CodeEaters/Entities/Base/Boolean/EntityNxor.cpp src/Models/CodeEaters/Entities/Base/Boolean/EntityNxorIn.cpp
        src/Models/CodeEaters/Entities/Base/Int/EntityOperationInt.cpp
            src/Models/CodeEaters/Entities/Base/Int/EntityIncr.cpp 
            src/Models/CodeEaters/Entities/Base/Int/EntityAddInt.cpp src/Models/CodeEaters/Entities/Base/Int/EntityAddIntIn.cpp
                src/Models/CodeEaters/Entities/Base/Int/EntitySubInt.cpp src/Models/CodeEaters/Entities/Base/Int/EntitySubIntIn.cpp
            src/Models/CodeEaters/Entities/Base/Int/EntityMultInt.cpp src/Models/CodeEaters/Entities/Base/Int/EntityMultIntIn.cpp
                src/Models/CodeEaters/Entities/Base/Int/EntityDivInt.cpp src/Models/CodeEaters/Entities/Base/Int/EntityDivIntIn.cpp
    src/Models/CodeEaters/Entities/Base/Meta/EntityMetaOp.cpp
        src/Models/CodeEaters/Entities/Base/Meta/EntityOpCounter.cpp
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


# ****************************************************************** Experiments ******************************************************************

# ********************************* By model

set(EXPERIMENTS_EVO_ALGOS 
    src/Experiment/BioEvo/Replicators/EvoAlgos/EvoX/ReplicationEvoXQuine.hpp 
    src/Experiment/BioEvo/Replicators/EvoAlgos/EvoX/ReplicationEvoXQuine.cpp
    src/Experiment/BioEvo/Trait/EvoAlgos/EvoX/EvoXDriveTrait.hpp
    src/Experiment/BioEvo/Trait/EvoAlgos/EvoX/EvoXDriveTrait.cpp
    src/Experiment/ClassicalInfo/FunctionExecution/EvoX/FunctionExecutionEvoX.hpp
    src/Experiment/ClassicalInfo/FunctionExecution/EvoX/FunctionExecutionEvoX.cpp
    src/Experiment/ClassicalInfo/FunctionExecution/EvoX/PhenotypicFunctionAcquisition.hpp
    src/Experiment/ClassicalInfo/FunctionExecution/EvoX/PhenotypicFunctionAcquisition.cpp
    src/Experiment/BioEvo/Replicators/EvoAlgos/EvoX/ReplicationEvoXQuine.hpp 
    src/Experiment/BioEvo/Replicators/EvoAlgos/EvoX/ReplicationEvoXQuine.cpp 
)

# ************************************************ By function

# ****************************** Classical info

# *************** Function execution

set(EXPERIMENT_RUNNERS_CLASSICAL_INFO_FUNC_EXEC src/Experiment/ClassicalInfo/FunctionExecution/ExperimentRunnerFunctionExecution.hpp
    src/Experiment/ClassicalInfo/FunctionExecution/EvoX/FunctionExecutionEvoX.hpp
    src/Experiment/ClassicalInfo/FunctionExecution/EvoX/FunctionExecutionEvoX.cpp
    src/Experiment/ClassicalInfo/FunctionExecution/EvoX/PhenotypicFunctionAcquisition.hpp
    src/Experiment/ClassicalInfo/FunctionExecution/EvoX/PhenotypicFunctionAcquisition.cpp
)
add_executable(classical-info-func-exec src/Experiment/ClassicalInfo/FunctionExecution/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODELS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODELS}
    ${EXPERIMENT_RUNNERS_CLASSICAL_INFO_FUNC_EXEC})
target_link_libraries(classical-info-func-exec ${LIBS})

# *************** all

set(EXPERIMENT_RUNNERS_CLASSICAL_INFO 
    src/Experiment/ClassicalInfo/ExperimentRunnerClassicalInfo.hpp
    ${EXPERIMENT_RUNNERS_CLASSICAL_INFO_FUNC_EXEC})
add_executable(classical-info-all src/Experiment/ClassicalInfo/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODELS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODELS}
    ${EXPERIMENT_RUNNERS_CLASSICAL_INFO})
target_link_libraries(classical-info-all ${LIBS})


# ****************************** Bio evo

# *************** Trait

set(EXPERIMENT_RUNNERS_BIO_EVO_TRAIT src/Experiment/BioEvo/Trait/ExperimentRunnerTraits.hpp
    src/Experiment/BioEvo/Trait/EvoAlgos/EvoX/EvoXDriveTrait.hpp
    src/Experiment/BioEvo/Trait/EvoAlgos/EvoX/EvoXDriveTrait.cpp
)
add_executable(bio-evo-trait src/Experiment/BioEvo/Trait/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODELS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODELS}
    ${EXPERIMENT_RUNNERS_BIO_EVO_TRAIT})
target_link_libraries(bio-evo-trait ${LIBS})

# *************** Gene

set(EXPERIMENT_RUNNERS_BIO_EVO_GENE src/Experiment/BioEvo/Gene/ExperimentRunnerGenes.hpp
    src/Experiment/BioEvo/Gene/EvoX/FreeMoleculesCreationEvoX.hpp
    src/Experiment/BioEvo/Gene/EvoX/FreeMoleculesCreationEvoX.cpp
    src/Experiment/BioEvo/Gene/EvoX/GeneToProgtein.hpp
    src/Experiment/BioEvo/Gene/EvoX/GeneToProgtein.cpp
    src/Experiment/BioEvo/Gene/EvoX/GeneCreationEvoX.hpp
    src/Experiment/BioEvo/Gene/EvoX/GeneCreationEvoX.cpp)
add_executable(bio-evo-gene src/Experiment/BioEvo/Gene/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODELS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODELS}
    ${EXPERIMENT_RUNNERS_BIO_EVO_GENE})
target_link_libraries(bio-evo-gene ${LIBS})

# *************** Genesis

set(EXPERIMENT_RUNNERS_BIO_EVO_GENESIS src/Experiment/BioEvo/Genesis/ExperimentRunnerGenesis.hpp
    src/Experiment/BioEvo/Genesis/EvoAlgosGenesis/GenerateBaseEvoX1.hpp
    src/Experiment/BioEvo/Genesis/EvoAlgosGenesis/GenerateBaseEvoX1.cpp
    src/Experiment/BioEvo/Genesis/EvoAlgosGenesis/GenerateBaseEvoX2.hpp
    src/Experiment/BioEvo/Genesis/EvoAlgosGenesis/GenerateBaseEvoX2.cpp)
add_executable(bio-evo-genesis src/Experiment/BioEvo/Genesis/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODELS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODELS}
    ${EXPERIMENT_RUNNERS_BIO_EVO_GENESIS})
target_link_libraries(bio-evo-genesis ${LIBS})

# *************** Replicators

set(EXPERIMENT_RUNNERS_BIO_EVO_REPLICATORS src/Experiment/BioEvo/Replicators/ExperimentRunnerReplicators.hpp
    src/Experiment/BioEvo/Replicators/EvoAlgos/EvoX/ReplicationEvoXQuine.hpp
    src/Experiment/BioEvo/Replicators/EvoAlgos/EvoX/ReplicationEvoXQuine.cpp
    src/Experiment/BioEvo/Replicators/EvoAlgos/EvoX/SelfCompilationEvoX.hpp
    src/Experiment/BioEvo/Replicators/EvoAlgos/EvoX/SelfCompilationEvoX.cpp
)
add_executable(bio-evo-replication src/Experiment/BioEvo/Replicators/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODELS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODELS}
    ${EXPERIMENT_RUNNERS_BIO_EVO_REPLICATORS})
target_link_libraries(bio-evo-replication ${LIBS})

# *************** Teleonomy

set(EXPERIMENT_RUNNERS_BIO_EVO_TELEONOMY src/Experiment/BioEvo/Teleonomy/ExperimentRunnerTeleonomy.hpp
    src/Experiment/BioEvo/Teleonomy/EvoX/EvoXTeleonomicalDesign.hpp
    src/Experiment/BioEvo/Teleonomy/EvoX/EvoXTeleonomicalDesign.cpp
)
add_executable(bio-evo-teleonomy src/Experiment/BioEvo/Teleonomy/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODELS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODELS}
    ${EXPERIMENT_RUNNERS_BIO_EVO_TELEONOMY})
target_link_libraries(bio-evo-teleonomy ${LIBS})

# *************** all

set(EXPERIMENT_RUNNERS_BIO_EVO 
    src/Experiment/BioEvo/ExperimentRunnerBioEvo.hpp
    ${EXPERIMENT_RUNNERS_BIO_EVO_TRAIT} ${EXPERIMENT_RUNNERS_BIO_EVO_GENE}
    ${EXPERIMENT_RUNNERS_BIO_EVO_GENESIS} ${EXPERIMENT_RUNNERS_BIO_EVO_REPLICATORS}
    ${EXPERIMENT_RUNNERS_BIO_EVO_TELEONOMY})
add_executable(bio-evo-all src/Experiment/BioEvo/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODELS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODELS}
    ${EXPERIMENT_RUNNERS_BIO_EVO})
target_link_libraries(bio-evo-all ${LIBS})


# ****************************** Maths

# *************** Playground

set(EXPERIMENT_RUNNERS_MATHS_RECURSIVE_OPS src/Experiment/Maths/Playground/ExperimentRunnerMathsPlayground.hpp)
add_executable(maths-recursive-ops src/Experiment/Maths/Playground/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODELS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODELS}
    ${EXPERIMENT_RUNNERS_MATHS_RECURSIVE_OPS})
target_link_libraries(maths-recursive-ops ${LIBS})

# *************** all

set(EXPERIMENT_RUNNERS_MATHS 
    src/Experiment/Maths/ExperimentRunnerMaths.hpp
    ${EXPERIMENT_RUNNERS_MATHS_RECURSIVE_OPS})
add_executable(maths-all src/Experiment/Maths/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODELS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODELS}
    ${EXPERIMENT_RUNNERS_MATHS})
target_link_libraries(maths-all ${LIBS})



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
    src/UnitTests/ClassicalAlgos/test_1_empty.hpp
    src/UnitTests/ClassicalAlgos/test_2_body.hpp
            src/UnitTests/ClassicalAlgos/test_2_1.hpp)

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
                src/UnitTests/CodeEaters/test_2_1_1_1.hpp src/UnitTests/CodeEaters/test_2_1_1_2.hpp
                src/UnitTests/CodeEaters/test_2_1_1_3.hpp src/UnitTests/CodeEaters/test_2_1_1_4.hpp
        src/UnitTests/CodeEaters/test_2_2.hpp
            src/UnitTests/CodeEaters/test_2_2_1.hpp
                src/UnitTests/CodeEaters/test_2_2_1_1.hpp src/UnitTests/CodeEaters/test_2_2_1_2.hpp
                src/UnitTests/CodeEaters/test_2_2_1_3.hpp
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
    src/UnitTests/EvoAlgos/X86TesterHelper.hpp
    src/UnitTests/EvoAlgos/test_1_empty.hpp
    src/UnitTests/EvoAlgos/test_2_x86.hpp
        src/UnitTests/EvoAlgos/test_2_1.hpp
            src/UnitTests/EvoAlgos/test_2_1_1.hpp src/UnitTests/EvoAlgos/test_2_1_2.hpp
            src/UnitTests/EvoAlgos/test_2_1_3.hpp src/UnitTests/EvoAlgos/test_2_1_4.hpp
            src/UnitTests/EvoAlgos/test_2_1_5.hpp src/UnitTests/EvoAlgos/test_2_1_6.hpp
    src/UnitTests/EvoAlgos/test_3_evox.hpp
        src/UnitTests/EvoAlgos/test_3_1.hpp
            src/UnitTests/EvoAlgos/test_3_1_1.hpp src/UnitTests/EvoAlgos/test_3_1_2.hpp
            src/UnitTests/EvoAlgos/test_3_1_3.hpp src/UnitTests/EvoAlgos/test_3_1_4.hpp
            src/UnitTests/EvoAlgos/test_3_1_5.hpp
        src/UnitTests/EvoAlgos/test_3_2.hpp
            src/UnitTests/EvoAlgos/test_3_2_x.hpp 
            src/UnitTests/EvoAlgos/test_3_2_1.hpp src/UnitTests/EvoAlgos/test_3_2_2.hpp
            src/UnitTests/EvoAlgos/test_3_2_3.hpp
    src/UnitTests/EvoAlgos/test_4_universe.hpp
        src/UnitTests/EvoAlgos/test_4_1.hpp
            src/UnitTests/EvoAlgos/test_4_1_1.hpp)

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



add_executable(bioevo_all src/main.cpp ${HEADERS_FRAMEWORK} ${SOURCES_FRAMEWORK})
target_link_libraries(bioevo_all ${LIBS})


# ─── apps ───────────────────────────────────────────────────────

find_package(GLEW REQUIRED)
# *************** Sandbox runner

add_executable(sandbox-runner src/Experiment/Sandbox/sandbox_runner.cpp
    ${HEADERS_FRAMEWORK} ${HEADERS_MODELS}
    ${SOURCES_FRAMEWORK} ${SOURCES_MODELS})
target_link_libraries(sandbox-runner ${LIBS})


# *************** EvoX

add_executable(EvoXApp
    apps/EvoX/main.cpp
    apps/EvoX/init.hpp apps/EvoX/cleanup.hpp
    # front
    apps/EvoX/front/common.hpp
    apps/EvoX/front/main_loop.hpp apps/EvoX/front/common.hpp
    apps/EvoX/front/window_main_menu.hpp apps/EvoX/front/window_choose_exp.hpp
    apps/EvoX/front/window_simulation.hpp apps/EvoX/front/simulation/simulation_tab.hpp
    apps/EvoX/front/simulation/advanced_editor_tab.hpp
    apps/EvoX/front/simulation/simulation_constants.hpp
    # back
    apps/EvoX/back/level/level.hpp 
    apps/EvoX/back/level/level_config.hpp apps/EvoX/back/app_state.hpp
    apps/EvoX/back/grid_fbo.hpp apps/EvoX/back/evox_universe.hpp
    apps/EvoX/back/tree.hpp apps/EvoX/back/level_select.hpp
    # EvoX engine sources (same set as sandbox-runner)
    ${HEADERS_FRAMEWORK} ${HEADERS_MODELS}
    ${SOURCES_FRAMEWORK} ${SOURCES_MODELS}
    ${IMGUI_SOURCES}
)
 target_include_directories(EvoXApp PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${SDL2_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
)
 
find_package(nlohmann_json REQUIRED)
target_link_libraries(EvoXApp PRIVATE
    ${SDL2_LIBRARIES}
    nlohmann_json::nlohmann_json
    OpenGL::GL
    GLEW::GLEW
)


# ─── Platform specifics ───────────────────────────────────────────────────────
if(WIN32)
    # Hide the console window on Windows in Release builds
    set_target_properties(EvoXApp PROPERTIES
        WIN32_EXECUTABLE $<IF:$<CONFIG:Debug>,FALSE,TRUE>
    )
    # Link against SDL2main on Windows
    target_link_libraries(EvoXApp PRIVATE SDL2::SDL2main)
endif()
 
if(UNIX AND NOT APPLE)
    target_link_libraries(EvoXApp PRIVATE dl)
endif()

# ─── Compiler warnings ────────────────────────────────────────────────────────
if(MSVC)
    target_compile_options(EvoXApp PRIVATE /W3)
else()
    target_compile_options(EvoXApp PRIVATE -Wall -Wextra -Wpedantic)
endif()
 
# ─── Install / packaging ──────────────────────────────────────────────────────
install(TARGETS EvoXApp DESTINATION .)

# Uncomment to enable CPack packaging:
# include(CPack)
# set(CPACK_GENERATOR "ZIP")
# set(CPACK_PACKAGE_NAME "CellularAutomataEngine")
# set(CPACK_PACKAGE_VERSION "0.1.0")

