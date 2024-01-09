# RegexpWidth (Work In Progess)
This is a software to compute the width of a given Regexp, it works as follows:

1. Compute the Glushkov automaton of the input Regexp
2. Compute the colex partial preoder of the Glushkov automaton <cite>[1]</cite>
3. Compute the chain decomposition of the colex partial preorder <cite>[2]</cite>

NOTICE: This repository is a work in progress and contains some bugs that are currently being addressed.

The regexp is read from the standard input stream and should be written all in a single line

Supported regexp operators: ()+?|*
The operators have the following syntax:
- "+": is a unary operator, specifies that the preceding character or group of characters 
must appear one or more times.
- "?": is a unary operator, specifies that the preceding character or group of characters is 
optional. It matches either zero or one occurrence of the preceding element.
- "|": is a binary operator. It functions as a logical OR, allowing you to match either the 
pattern on the left-hand side of the | or the pattern on the right-hand side.
- "*": is a unary operator. It specifies that the preceding character or group of characters 
can occur zero or more times. 

Optional flags:
```
-chain FILE         Store the chain decomposition of the 
                    partial preorder in the file specified in
                    the the following format:     
                        -in the first line we have the number of chains
                        -in the following lines we have the chains

-partial FILE       Store the partial preorder as a Hasse
                    diagram in the following format:
                        -in the first line we have the number of nodes
                         and number of edges
                        -in the following lines we have the edges
                        
-gl FILE            Save the Glushkov automaton in 
                    the specified file as a dot format file.

-quotient FILE      Store the quotient graph obtained 
                    by collapsing the equivalent class defined 
                    by the partial preorder as a dot format file

-verificator        Check if the algorithm works correctly 
                    and if the given order is partial and 
                    co-lexicographic.
```


### Requirements

This tool requires:
* A modern C++17 compiler.

### Output 

This tool prints some statistics about the regexp:

* The regex length
* The number of times the symbol "+" appears in the regexp.
* The number of times the symbol "?" appears in the regexp.
* The number of times the symbol "|" appears in the regexp.
* The number of times the symbol "*" appears in the regexp. 

It also prints some statistics about the colex Partial order, the Glushkov automaton and the quotient graph:

* The width of the partial order
* The number of nodes and edges of the Glushkov automaton
* The number of nodes and edges of the quotient graph

# Usage

### Download
```
git clone https://github.com/regindex/RegexpWidth
```
### Compile
```
make
```
### Run on Example Data

```
echo "(a*(ab))+((b*)|a*)*" | ./regexpWidth
```

Output:
```
Regexp length: 19
+ symbols occurrences: 1
? symbols occurrences: 0
| symbols occurrences: 1
* symbols occurrences: 4
--------------------------------
Width: 3
Glushkov_nodes: 6
Glushkov_edges: 13
Quotient_graph_nodes: 6
Quotient_graph_edges: 13
```
### Implementation

* [Riccardo Maso](https://github.com/RiccardoMaso)
## References

- [1] Nicola Cotumaccio, Graphs can be succinctly indexed for pattern matching in O(|E|2+|V|5/2) time: https://ieeexplore.ieee.org/document/9810716
- [2] PerformanceMPC repository: https://github.com/algbio/PerformanceMPC/tree/main


### Funding
This project has received funding from the European Research Council (ERC) under the European Union’s Horizon Europe research and innovation programme, project REGINDEX, grant agreement No 101039208
