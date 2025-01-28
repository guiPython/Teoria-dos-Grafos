# Graphs Theory UFABC
UFABC 2023-Q3 Graphs Theory Exercises

The repository uses a library written in C by professors Maycon Sambinelli and Carla Negri Lintzmayer, and the exercises were solved using it as a base.
Some modifications were made to make it easier to manipulate digraphs and weighted graphs, they are:

- Addition of the weight attribute for every edge, when the information is not relevant this attribute was initialized with value 1
- Addition of a function that adds edges taking into account the direction (digraphs)

With the modifications, the implementations in both adjacency matrix and linked list were modified to support the addition of weights. In the case of the matrix, 
each position indicates the weight of the edge. If it is 0, it means that we do not have the edge.
In the case of linked list, the weight attribute was added to each node.

The exercises have the original texts and the input and output cases, in case you need to test
there are compilation commands in the Makefile that generate the binary.
