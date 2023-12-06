# Progetto-AlgorithmOverMassiveData
 
# Width of a Regexp
This is a software to compute the width of a given Regexp, it works as follows:

1. Compute the Glushkov automaton of the input Regexp
2. Compute the partial preoder of the Glushkov automaton <cite>[1]</cite>
3. Compute the chain decomposition of partial preorder <cite>[2]</cite>


# Usage

```
Usage: ./regexpWidth
```
The regexp it's taken from the standard input stream

Supported operators for the regexp: ()+?|* 

There is a set of optional flags:
```
-chain FILE         It stores the chain decomposition of the 
                    partial preorder in the file specified in
                    the the following format:     
                        -in the first line we have the number of chains
                        -in the following lines we have the chains

-partial FILE       It will store the partial preorder as Hasse
                    diagram in the following format:
                        -in the first line we have the number nodes
                         and number of edges
                        -in the following lines we have the edges
                        
-gl FILE            It will save the Glushkov automaton in 
                    the specified file as a dot format file.

-quotient FILE      It will store the quotient graph obtained 
                    by collapsing the equivalent class defined 
                    by the partial preorder as a dot format file

-verificator        It checks if the algorithm works correctly 
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

It also prints some statistics about the Partial order, the Glushkov automaton and the quotient graph:

* The width of the partial order
* The number of edges of the Glushkov automaton
* The number of nodes of the Glushkov automaton
* The number of nodes of the quotient graph

# Usage

### Dowload
```
git clone https://github.com/regindex/RegexpWidth
```
### Compile
```
make
```
### Run on Example Data

```
./regexpWidth
(a*(ab))+((b*)|a*)*
```

Output:
```
Regexp length: 19
+ symbols quantity: 1
? symbols quantity: 0
| symbols quantity: 1
* symbols quantity: 4
--------------------------------
Width: 3
Glushkov_edges: 12
Glushkov_nodes: 6
Quotient_graph_nodes: 6
```
### Implementation

* [Riccardo Maso](https://github.com/RiccardoMaso)
## References

- [1] Nicola Cotummaxio, Graphs can be succinctly indexed for pattern matching in O(|E|2+|V|5/2) time: https://ieeexplore.ieee.org/document/9810716
- [2] PerformanceMPC repository: https://github.com/algbio/PerformanceMPC/tree/main


### Funding
This project has received funding from the European Research Council (ERC) under the European Union’s Horizon Europe research and innovation programme, project REGINDEX, grant agreement No 101039208
