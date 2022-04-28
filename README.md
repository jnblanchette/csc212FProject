# CSC212 Final Project: B-Trees

##### **Rojeen Sindi, Nicolas Leffray, Jarrod Blanchette**


#

## What is a B-Tree?

A B-tree is a self-balancing tree data structure that maintains sorted data and allows searches, sequential access, insertions, and deletions in logarithmic time. The B-tree generalizes the binary search tree, allowing for nodes with more than two children. Unlike other self-balancing binary search trees, the B-Tree is well suited for storage systems that read and write relatively large blocks of data, such as databases and file systems.

## Project Description

Our project consists of using B-Trees to read in an input file. We are using .txt files of two different series of books from two seperate authors to search through the text and determine the overall word count, collegiate vs. elementary words and 

## How to Compile

We have three files. They are called B-Tree.cpp, main.cpp and B-Tree.h
You will need to save the .txt files of the books to your computer to utilize our code. 

To compile the code use:
``` g++ -std=c++11 main.cpp B-Tree.cpp -o btree```
 
To run the code use:
 ```./btree NameOfText.txt minDegree searchword```
 
 In place of NameOfText.txt you will use the name of the .txt file you wish to input.
 
 In place of minDegree you will use the minimum degree which represents the lower bound on the number of children a node in the B Tree can have (except for   the root)
 
 In place of searchword you will use the random word you wish to search. 
 
