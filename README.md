# 42_ft_containers
Reproducing containers, but not the cool kind

# About
ft_containers is a project that aims to reproduce a selection of C++ Standard Template Library containers - namely stack, vector, set and map. Its learning goals mainly include template programming, iterators and algorithms.

For a brief overview, the following containers were implemented:
  * vector: a dynamically resizable random access array that supports automatic reallocation of memory
  * stack: a container adaptor on the vector container that limits functionality to those of a Last In, First Out stack
  * set: an associative container containing a sorted set of unique keys in a tree structure
  * map: an associative container containing a sorted set of key-value pairs with unique keys in a tree structure
    * both set and map are built on the same underlying tree structure and use a self-balancing Red-Black-Tree
    
 Also implemented were several functions from the \<utility\> header, including templates for comparsions, legographical compares, and the iterators used in the containers.
