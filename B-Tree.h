
#include <iostream>
#include <iomanip>
#include <ostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include<array>

#ifndef NULL
#define NULL 0x00
#endif
// Defines MAX
// When used, MAX(a,b) will be replaced with ((a > b) ? a : b)
#ifndef MAX
#define MAX(a,b) ((a > b) ? a : b)
#endif

class BTNode
{
    private:
  
    

    public:
        //initializing node as a pointer to an array of pairs
        std::pair<std::string, int> *node; 
       
         int min_degree; 
        bool leaf;
        BTNode **children;
        //number of elements in the node
        int n; 
        BTNode(int min_degree2,bool leaf);
        
        void splitchild(int i, BTNode *y);
        void traverse();
        void insertNonFull(std::pair<std::string,int> firstRoot);    
       
        BTNode *search(std::pair<std::string,int> firstRoot);
        

    friend class BTree;
};

class BTree
{
    private:
       
    
        
    public:
        
        BTNode *root;
        int value;
        bool leaf;
        int height(BTNode* root);
        BTNode *temp ;
        //initializing node as a pointer to an array of pairs
        std::pair<std::string, int> *node; 
        int min_degree;
        //constructor initials the tree to zero
        BTree(int min_degree2)
        {
            root = NULL;
            min_degree = min_degree2;
        };
        
        void traverse(){ if (root!= NULL) root->traverse();}
        
        void ReadFile(std::string input_file_name);        
        BTNode *search(std::pair<std::string,int> firstRoot)
        { 
            return (root == NULL)? NULL : root->search(firstRoot); 
        }
        void insert(std::pair<std::string,int> firstRoot);
        
};

