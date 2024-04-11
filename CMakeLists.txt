cmake_minimum_required(VERSION 3.6)
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
    src/Models/EvoAlgos/X86Algo/UtilityFunctions.hpp
    src/Models/EvoAlgos/Universe/UniverseEvoAlgos.hpp src/Models/EvoAlgos/Universe/UniverseEvoXCustomNeighborhood.hpp
    src/Models/EvoAlgos/Universe/CustomNeighborhoods.hpp
# x86 evo algos
    src/Models/EvoAlgos/X86Algo/InstructionMapping.hpp
    src/Models/EvoAlgos/X86Algo/X86Algo.hpp src/Models/EvoAlgos/X86Algo/EvoX.hpp
    src/Models/EvoAlgos/X86Algo/FreeGenes.hpp
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
    src/Models/EvoAlgos/X86Algo/InstructionMapping.cpp
    src/Models/EvoAlgos/X86Algo/X86Algo.cpp src/Models/EvoAlgos/X86Algo/EvoX.cpp
    src/Models/EvoAlgos/X86Algo/FreeGenes.cpp
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

set(EXPERIMENTS_CLASSICAL_INFO )
add_executable(classical_info src/Models/ClassicalInfo/Experiment/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_CLASSICAL_INFO} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_CLASSICAL_INFO}
    ${EXPERIMENTS_CLASSICAL_INFO})
target_link_libraries(classical_info ${LIBS})

set(EXPERIMENTS_TH_INFO )
add_executable(th_info src/Models/TheoreticalInfo/Experiment/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_TH_INFO} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_TH_INFO}
    ${EXPERIMENTS_TH_INFO})
target_link_libraries(th_info ${LIBS})

set(EXPERIMENTS_MATHS )
add_executable(maths src/Models/Maths/Experiment/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_MATHS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_MATHS}
    ${EXPERIMENTS_MATHS})
target_link_libraries(maths ${LIBS})

set(EXPERIMENTS_CLASSICAL_ALGOS )
add_executable(classical_algos src/Models/ClassicalAlgos/Experiment/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_CLASSICAL_ALGOS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_CLASSICAL_ALGOS}
    ${EXPERIMENTS_CLASSICAL_ALGOS})
target_link_libraries(classical_algos ${LIBS})

set(EXPERIMENTS_EVO_ALGOS 
    src/Experiment/BioEvo/Replicators/EvoAlgos/EvoX/ReplicationEvoXQuine.hpp 
    src/Experiment/BioEvo/Replicators/EvoAlgos/EvoX/ReplicationEvoXQuine.cpp
    src/Experiment/BioEvo/Trait/EvoAlgos/EvoX/EvoXDriveTrait.hpp
    src/Experiment/BioEvo/Trait/EvoAlgos/EvoX/EvoXDriveTrait.cpp
    src/Experiment/ClassicalInfo/FunctionExecution/EvoX/FunctionExecutionEvoX.hpp
    src/Experiment/ClassicalInfo/FunctionExecution/EvoX/FunctionExecutionEvoX.cpp
    src/Experiment/ClassicalInfo/FunctionExecution/EvoX/GeneticFunctionAcquisition.hpp
    src/Experiment/ClassicalInfo/FunctionExecution/EvoX/GeneticFunctionAcquisition.cpp
    src/Experiment/BioEvo/Replicators/EvoAlgos/EvoX/ReplicationEvoXQuine.hpp 
    src/Experiment/BioEvo/Replicators/EvoAlgos/EvoX/ReplicationEvoXQuine.cpp 
)
add_executable(evo_algos src/Models/EvoAlgos/Experiment/main.cpp 
    src/Models/EvoAlgos/Experiment/ExperimentRunnerEvoAlgos.hpp
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_EVO_ALGOS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_EVO_ALGOS}
    ${EXPERIMENTS_EVO_ALGOS})
target_link_libraries(evo_algos ${LIBS})

set(EXPERIMENTS_BIO_EVO )
add_executable(bioevo src/Models/BioEvo/Experiment/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_BIO_EVO} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_BIO_EVO}
    ${EXPERIMENTS_BIO_EVO})
target_link_libraries(bioevo ${LIBS})

set(EXPERIMENTS_CODE_EATERS )
add_executable(code_eaters src/Models/CodeEaters/Experiment/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_CODE_EATERS} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_CODE_EATERS}
    ${EXPERIMENTS_CODE_EATERS})
target_link_libraries(code_eaters ${LIBS})

set(EXPERIMENTS_ECONOMY )
add_executable(economy src/Models/Economy/Experiment/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_ECONOMY} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_ECONOMY}
    ${EXPERIMENTS_ECONOMY})
target_link_libraries(economy ${LIBS})

set(EXPERIMENTS_FINANCE )
add_executable(finance src/Models/Finance/Experiment/main.cpp 
    ${HEADERS_FRAMEWORK} ${HEADERS_MODEL_FINANCE} 
    ${SOURCES_FRAMEWORK} ${SOURCES_MODEL_FINANCE}
    ${EXPERIMENTS_FINANCE})
target_link_libraries(finance ${LIBS})


# ************************************************ By function

# ****************************** Classical info

# *************** Function execution

set(EXPERIMENT_RUNNERS_CLASSICAL_INFO_FUNC_EXEC src/Experiment/ClassicalInfo/FunctionExecution/ExperimentRunnerFunctionExecution.hpp
    src/Experiment/ClassicalInfo/FunctionExecution/EvoX/FunctionExecutionEvoX.hpp
    src/Experiment/ClassicalInfo/FunctionExecution/EvoX/FunctionExecutionEvoX.cpp
    src/Experiment/ClassicalInfo/FunctionExecution/EvoX/GeneticFunctionAcquisition.hpp
    src/Experiment/ClassicalInfo/FunctionExecution/EvoX/GeneticFunctionAcquisition.cpp
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
    src/Experiment/BioEvo/Gene/EvoX/FreeGeneCreationEvoX.hpp
    src/Experiment/BioEvo/Gene/EvoX/FreeGeneCreationEvoX.cpp)
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
    src/UnitTests/ClassicalAlgos/test_2_genes.hpp
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
