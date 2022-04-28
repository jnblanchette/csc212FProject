#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <array>
#include "B-Tree.h"

/*
 * Node Class Functions
*/

// Don't forget to change these constructors!
BTNode::BTNode(int new_degree,bool newleaf)
{
    
    min_degree = new_degree;
    
    leaf = newleaf;
   // std::pair<std::string, int> *key;
    
    node  = new std::pair<std::string,int> [2 * min_degree - 1]; 
    int nodeSIZE;
    
    //int nodesize = (sizeof(node)/sizeof(node[0]));
     // we have a node constructor but since each node is a vector of pairs the new vector of pairs is called node also
     // allows for the size of the new node to be 2 times the min_degree minus 1

    children = new BTNode *[2 * min_degree];
    // what is n doing ??? not sure 
    n = 0;
  
}

void BTNode::splitchild(int i, BTNode *y)
{

    BTNode *z = new BTNode(y->min_degree, y->leaf);
    z->n = min_degree - 1;
 
    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < min_degree - 1; j++)
    {
        z->node[j].first = y->node[j + min_degree].first;
    }
    // Copy the last t children of y to z
    if (y->leaf == false)
    {
        for (int j = 0; j < min_degree; j++)
        {
            z->children[j] = y->children[j + min_degree];
        }
    }
    
    // Reduce the number of keys in y
    y->n = min_degree - 1;

    for (int j = n; j >= i + 1; j--)
    {
        children[j + 1] = children[j];
    }
    // Link the new child to this node
    children[i + 1] = z;
    // A key of y will move to this node. Find the location of
    // new key and move all greater keys one space ahead
        for (int j = n-1; j >= i; j--)
         {
         node[j + 1].first = node[j].first;
         }
     // Copy the middle key of y to this node
    node[i].first = y->node[min_degree - 1].first; //maybe .first remember line 72 for this debugging tomorrow with TA's
    // Increment count of keys in this node
    n = n + 1;
    
    
}
void BTNode::traverse()
{
    // There are n keys and n+1 children, traverse through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child children[i].
        if (leaf == false){
            children[i]->traverse();
            std::cout << " " << node[i].first << std::endl;
        }
    }
    
    // Print the subtree rooted with last child

    if (leaf == false){

        children[i]->traverse();
    }

}
BTNode *BTNode::search(std::pair<std::string,int> searchword)
{
    //if  the first node is greater than and equal to searchword.first then increment counter
    int i = 0;

    std::cout<< n << " this is n" <<  std::endl;

    while (i < this->n && searchword.first > node[i].first)
    {
        i++;
    
    // If the found node is equal to searchword.first, return this node
    if (node[i].first == searchword.first)
    {
        return this;
    }
    // If node is not found here and this is a leaf node
    if (leaf == true)
    {
        return NULL;
    }

    }
    
        return children[i]->search(searchword);
    

    
}
void BTree::insert(std::pair<std::string,int> firstRoot)
{
    // trying to have temp search through and find the pointer to the key. dereference it.
    // if it finds the key. increment the counter aka the key.second
   // BTNode *temp = this->search(firstRoot);

   //BTNode *temp = this->search(firstRoot);
    
    
   /* if (temp != NULL)
    {
          std::cout << "I'M HERE PART 3000" << std::endl;

        for (int i = 0; i < temp->nodeSIZE - 1 ; i++)
        {
             
            if (temp->node[i].first == firstRoot.first)
            {
                temp->node[i].second += 1;
                
                std::cout << node[i].first << std::endl;
                std::cout << node[i].second << std::endl;
                return;
            }
            
        } 
        
    }
    */
  
  // if root is empty
    if(root == NULL)
    {

        root = new BTNode(min_degree, true);
       
        root->node[0].first = firstRoot.first;
         
        root->n = 1;
       // add a return  here to stop the code
        return;
    } 
    else{// if the root is not empty
      
        if (root->n == (2 * min_degree - 1)) // If root is full increase the height
        {
           
            BTNode *s = new BTNode(min_degree, false);
 
            // Make old root as child of new root
            s->children[0] = root;
 
            // Split the old root and move 1 key to the new root
            s->splitchild(0, root);
            // New root has two children now. 
             int i = 0;
            if (s->node[0].first < firstRoot.first){
            
             i++;
            
            s->children[i]->insertNonFull(firstRoot);
            
            // Change root
            root = s;
            }
        }
        else  {

            // If root is not full, call insertNonFull for root
            root->insertNonFull(firstRoot);
        }
    }

  
   }


void BTNode::insertNonFull(std::pair<std::string,int>firstRoot) {
    // Initialize index as index of rightmost element
    int i = n - 1;
        
    // If this is a leaf node
    if (leaf == true)
    {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && node[i].first > firstRoot.first)
        {
            node[i + 1].first = node[i].first;
            i--;
        }
         node[i + 1].first = firstRoot.first;
        n = n + 1;
    } else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && node[i].first > firstRoot.first)
        {
            i--;
        }
        // See if the found child is full
        if (children[i+1]->n == 2 * min_degree - 1)
        {
            // If the child is full, then split it
            splitchild(i + 1, children[i + 1]);
 
            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (node[i + 1].first < firstRoot.first)
            {
                i++;
            }
        }
        children[i + 1]->insertNonFull(firstRoot);
    
    }
}   

void BTree::ReadFile(std::string input_file_name)
{
    // Create the input filestream - opens the file & prepares it for reading
    std::ifstream file(input_file_name);
    // Creates a temporary vector to represent one row
    std::vector<std::string> new_row;
    // Temporary string to hold a single line of the file
    std::string str;
    
    // Reads all lines in the file, 1 at at time
    while (std::getline(file, str)) 
    {   
        // Keep reading a new line while there is
        // a blank line
           std::string chars = ("!?.'-;:)[(,]");


            str.erase(std::remove(str.begin(), str.end(),'\"'), str.end());
            
                str.erase(remove_if(str.begin(), str.end(),
                                [&chars](const char &c) {
                                    return chars.find(c) != std::string::npos;
                                }),
                                str.end());

           str.erase (std::remove_if(str.begin (), str.end (),::ispunct), str.end ());

            if (str == " ") continue;
            
            // Converts our string into a stringstream
                std::istringstream ss(str);
                std::string token;

                while (ss >> token )
                {
                int counter = 0;
                   std::pair<std::string,int> newword = std::make_pair(token,counter);
                   this->insert(newword);
                
                    
                }
             
               
            }
          
            }