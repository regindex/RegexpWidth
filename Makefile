SOURCE_FILES = main.cpp internal/graph/edge.cpp internal/graph/graph.cpp internal/partialOrder.cpp internal/verificator.hpp
MPC_FILES = internal/mpc.hpp internal/mpc/graph.cpp internal/mpc/naive.cpp internal/mpc/pflow.cpp
CONVERSION_FILES = 	internal/conversion/common.hpp internal/conversion/glushkov-automaton.hpp internal/conversion/nfa.hpp

EXECS = regexpWidth

C_FLAGS = -std=c++17 -O3 
make: $(SOURCE_FILES) $(MPC_FILES) $(CONVERSION_FILES)
	g++ $(C_FLAGS) $(SOURCE_FILES) $(MPC_FILES) $(CONVERSION_FILES) -o $(EXECS)

clean:
	rm -f $(EXECS)