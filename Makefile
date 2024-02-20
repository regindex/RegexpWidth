SOURCE_FILES = main.cpp internal/verificator.hpp internal/parser.hpp
CHECK_FILES = internal/graph/graph.cpp internal/graph/edge.cpp internal/partialOrder.cpp
MPC_FILES = internal/mpc.hpp internal/mpc/graph.cpp internal/mpc/naive.cpp internal/mpc/pflow.cpp
CONVERSION_FILES = 	internal/conversion/common.hpp internal/conversion/glushkov-automaton.hpp internal/conversion/nfa.hpp

C_DEBUG_FLAGS = -std=c++17 -O0 -DNDEBUG -g
C_BUILD_FLAGS =  -std=c++17 -O3 

make: $(SOURCE_FILES) $(MPC_FILES) $(CONVERSION_FILES) $(CHECK_FILES)
	g++ $(C_BUILD_FLAGS) $(SOURCE_FILES) $(MPC_FILES) $(CONVERSION_FILES) -o regexpWidth

debug: $(SOURCE_FILES) $(MPC_FILES) $(CONVERSION_FILES) $(CHECK_FILES)
	g++ $(C_DEBUG_FLAGS) $(SOURCE_FILES) $(MPC_FILES) $(CONVERSION_FILES) -o regexpWidth

clear:
	rm regexpWidth