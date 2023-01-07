/*
 Project 5:  myMap 
 File name: mymap.h Author: Arij Khan  NetId: akhan342  Course: CS 251
 System: Visual Studio
*/
#pragma once

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

template<typename keyType, typename valueType>
class mymap {
 private:
    struct NODE {
        keyType key;  // used to build BST
        valueType value;  // stored data for the map
        NODE* left;  // links to left child
        NODE* right;  // links to right child
        int nL;  // number of nodes in left subtree
        int nR;  // number of nodes in right subtree
        bool isThreaded;
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of key/value pairs in the mymap

    //
    // iterator:
    // This iterator is used so that mymap will work with a foreach loop.
    //
    struct iterator {
     private:
        NODE* curr;  // points to current in-order node for begin/end

     public:
        iterator(NODE* node) {
            curr = node;
        }

        keyType operator *() {
            return curr -> key;
        }

        bool operator ==(const iterator& rhs) {
            return curr == rhs.curr;
        }

        bool operator !=(const iterator& rhs) {
            return curr != rhs.curr;
        }

        bool isDefault() {
            return !curr;
        }

        //
        // operator++:
        // O(logN)
        //Advances curr to the next in-order node
        iterator operator++() {
            
            if(curr == nullptr)
            {
                return iterator(curr); 
            }
            
            if(curr->isThreaded == true)
            {
                curr = curr->right;
                return iterator(curr);  //return 
            }
            else if(curr->isThreaded == false)
            {
                
                curr = curr->right; 
                while(curr->left != nullptr) //traversr to the left until left is null
                {
                    curr = curr->left; 
                }
                return iterator(curr); //return 
            }

        }
    };


    void recursiveEqual(const mymap& other, NODE* currRoot)
     {
        if(currRoot == nullptr)
        {
            return; 
        }
        put(currRoot->key, currRoot->value); //insert root 
        recursiveEqual(other, currRoot->left); //recursively move to the left side of the tree
        if(currRoot->isThreaded == false)//if node isn't a threaded node then move and pass in the right most node
        {
            recursiveEqual(other, currRoot->right); 
        }
     }
 //clears the map when clear is called
void recursiveFunctionPostOrder(NODE* node)
    {
        if(node == nullptr)
        {
            return; 
        }
        else
        {
            recursiveFunctionPostOrder(node->left); //move to the left of the tree 
            if(node->isThreaded == false)
            {
            recursiveFunctionPostOrder(node->right); //if node is not threaded move to the right of the tree
            }
            //set right/left ptr to null
            node->left = nullptr; 
            node->right = nullptr; 
            delete node; //delete node
            size--; //decrement size
        }
    }
//A helper function that checks if node is balanced or not
    //EX: NODE: 2
    //left of 2 is 1
    //Right of 2 is 4
    //max is 4 <= 2*1(min) + 1 = false 
    //isValidator should return false  
    bool isValidator(NODE *curr)
    {
            return(max(curr->nL,curr->nR) <=  2 * min(curr->nL,curr->nR) + 1);
    }
    //sorts the nodes in the map in a vector from left of tree to right of tree
   void sortNodes(vector<NODE*> &bstNodes, NODE* tempRoot)
    {
       
        if(tempRoot == nullptr)
        {
            return;
        }
        else
        {
            sortNodes(bstNodes, tempRoot->left); //move to the left 
            bstNodes.push_back(tempRoot); 

            if(tempRoot->isThreaded == false)
            {
                sortNodes(bstNodes, tempRoot->right);
            }
        }

    
    }

    void funcToBalance(NODE* violatorParent, vector<NODE*> bstNodes, int low, int high)
    {
        int mid = (low + high) / 2; //calculate mid
        //set mid index values right and left to point to null
        bstNodes[mid]->right = nullptr;
        bstNodes[mid]->left = nullptr;
        bstNodes[mid]->nL = 0;
        bstNodes[mid]->nR = 0;
        // cout << violatorParent->key << " Violator Parent KEY" << endl; 
        // cout << bstNodes[mid]->key <<" mid " << endl; 
        if (high < low) //base case
        {
            return; 
        }
        if(violatorParent == nullptr)
        {
            root = bstNodes[mid]; 
        }
        //if mid index value is less than the parent, mid value goes to the left of the parent 
        else if(bstNodes[mid]->key < violatorParent->key)
        {
            violatorParent->left = bstNodes[mid]; //assign the parents left to mid value
            bstNodes[mid]->isThreaded = true; //set isThreaded to true
            bstNodes[mid]->right = violatorParent; //mid values right points to the violator parent 
            cout << violatorParent->key <<"Parent" << endl; 
             cout << bstNodes[mid]->right->key << "PARENT RIGHT" <<  endl;                                             
        }

      
        //if mid index value is greater than the parent, mid value goes to the right of the parent 
        else
        {
            bstNodes[mid]->right = violatorParent->right; //violatorParents right is null
            bstNodes[mid]->isThreaded = true; 
            violatorParent->right = bstNodes[mid]; //point violatorParent right to mid value in vector 
            violatorParent->isThreaded = false;  
            

            //  n->right = prev->right; //point nodes right to prev right 
            // n->isThreaded = true; 
            // prev->right = n; //set prev right to point to new node created 
            // prev->isThreaded = false; //prev dosen't have a thread now
        }
        if(violatorParent != nullptr)
        {
         cout << violatorParent->key << " ViolatorParent" << endl;
         if(violatorParent->right != nullptr) 
         {
        cout << violatorParent->right->key << " Is Right of violator " << endl;
         }
         if(violatorParent->left != nullptr) 
         {
        cout << violatorParent->left->key << " Is left of violator" << endl; 
         }
        }
        //based off the indexes high and low, we can calculate how many nodes are to the left and right of the mids value 
        bstNodes[mid]->nL = mid - low; 
        bstNodes[mid]->nR = high - mid;
        
        violatorParent = bstNodes[mid]; //set parent to mid value, since mid will change 
        funcToBalance(violatorParent, bstNodes, low, mid - 1); //if travering thru the left, change highs index value to mid - 1
        funcToBalance(violatorParent, bstNodes, mid + 1, high); //if travering thru the right, change low index value to mid + 1

    }

    
 public:
    //
    // default constructor:
    //
    // Creates an empty mymap.
    // Time complexity: O(1)
    //
    mymap() {

        root = nullptr; //initialize root to null
        size = 0; //set size to zero 

    }

    //
    // copy constructor:
    //
    // Constructs a new mymap which is a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    mymap(const mymap& other) {
         root = nullptr; 
         size = 0; 
         recursiveEqual(other, other.root); //calls helper function
    }

     

    //
    // operator=:
    //
    // Clears "this" mymap and then makes a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    mymap& operator=(const mymap& other) {

        clear(); //clears the map
        recursiveEqual(other, other.root); //pass in the empty tree/root of the non empty tree
        return *this;  // TODO: Update this return.
    }
    
    

    // clear:
    //
    // Frees the memory associated with the mymap; can be used for testing.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    void clear() {
    
        recursiveFunctionPostOrder(this->root); //pass in root to helper function
        this->root = nullptr; //set root ptr to null after clearing map
    
    }

    //
    // destructor:
    //
    // Frees the memory associated with the mymap.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    ~mymap() {

        clear(); 
        this->root = nullptr; 

        // TODO: write this function.


    }

    //
    // put:
    //
    // Inserts the key/value into the threaded, self-balancing BST based on
    // the key.
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-tree that needs to be re-balanced.
    // Space complexity: O(1)
    //
    void put(keyType key, valueType value) {

        NODE *prev = nullptr;
        NODE *curr = root;
        
        
        while (curr != nullptr)
        {
            if (key == curr->key)
            {
                curr->value = value; 
                return;
                
            }
            else if (key < curr->key) //(key < curr->key && isCounter == false)
            {
                prev = curr;
                //curr->nl++; 
                curr = curr->left; // move curr to the left
            }
            else
            {
                prev = curr;
                if(curr->isThreaded) 
                {
                    curr = nullptr; 
                }
                else
                {
                    curr = curr->right; // move curr to the right
                    //curr->nr++; 
                }
            }
        } // end while loop...
        NODE *n = new NODE();
        n->key = key;
        n->value = value;
        n->left = nullptr;
        n->right = nullptr;
        

        // curr = n;

        // if bst is empty
        if (prev == nullptr)
        {
            this->root = n;
            
        }
        else if (key < prev->key)
        {

            prev->left = n;
            n->isThreaded = true; //set isThread to true 
            n->right = prev; 

            
        }
        else //(key > prev->key)
        {
            
            n->right = prev->right; //point nodes right to prev right 
            n->isThreaded = true; 
            prev->right = n; //set prev right to point to new node created 
            prev->isThreaded = false; //prev dosen't have a thread now

          
        }
     
        size++;

    }

    

//Function is used to check insert in nodes into the map and check for any violation that occurs
// while inserting in nodes passed in
    // void copyPut(keyType key, valueType value) {

    //     NODE* prev = nullptr;
    //     NODE* curr = root;
    //     NODE* validator = nullptr; //points to the violator node in the tree
    //     NODE* validatorParent = nullptr; //points to the violators parent node
    //     bool isFlagged = false; //if there is a same key that is being passed in then set the flag to true and it won't increment
    //     //the nL and nR of that current node if we are inserting 
    //     //first while loop is used to check if any same nodes are being passed in
    //     while (curr != nullptr)
    //     {
    //         if (key == curr->key)
    //         {
    //             isFlagged = true; //if duplicate key being passed in then set flag to true 
    //             curr->value = value; //set the value of curr to the same node 
    //             return;
                
    //         }
    //         else if (key < curr->key) 
    //         {
    //             prev = curr; //set ptev to curr before moving curr
    //             curr = curr->left; // move curr to the left
    //         }
    //         else
    //         {
    //             prev = curr;
    //             if(curr->isThreaded) 
    //             {
    //                 curr = nullptr; //set curr to null if there is a thread 
    //             }
    //             else
    //             {
    //                 curr = curr->right; // move curr to the right 
    //             }
    //         }
    //     } 
    //     //reset prev and curr
    //     prev = nullptr;
    //     curr = root;
    //     //second while loop checks to see where key should be inserted in the map and checks to see if there is any
    //     //violation of that current node or not using the formula
    //     while (curr != nullptr)
    //     {
    //         //if keys already exist in the map, then replace its value with value being passed in
    //         if (key == curr->key)
    //         {
    //             curr->value = value;  
    //             return; 
                
    //         }
    //         else if (key < curr->key) //if key is less than current key, then key goes to the left of current key
    //         {
    //             //if no dupicates
    //             if(!isFlagged)
    //             {
                    
    //                 curr->nL++; //increment curr nl
                    
    //                 if(validator == nullptr && isValidator(curr) == false)
    //                 {
    //                     validator = curr; //curr is the violator if true 
    //                     validatorParent = prev; //set violator parent 
    //                 }

    //             }
    //             prev = curr; //set prev to curr before moving curr
    //             curr = curr->left; // move curr to the left
    //         }
    //         else //if key is greater than curr->key
    //         {
    //             if(!isFlagged)
    //             {
    //                 curr->nR++; //increment curr right 
    //                 if(validator == nullptr && isValidator(curr) == false)
    //                 {
    //                     validator = curr;
    //                     validatorParent = prev; ///set violator parent 
    //                 }
    //             }
    //             prev = curr;
    //             if(curr->isThreaded) 
    //             {
    //                 curr = nullptr; 
    //             }
    //             else
    //             {
    //                 curr = curr->right; // move curr to the right
    //             }
    //         }
    //     } // end while loop...
    //     //create new node 
    //     NODE *n = new NODE();
    //     n->key = key;//set key for new node
    //     n->value = value; //set value for new node 
    //     n->left = nullptr; //set node left to null
    //     n->right = nullptr; //set node right to null
        

    //     // if bst is empty
    //     if (prev == nullptr)
    //     {
    //         this->root = n;
            
    //     }
    //     else if (key < prev->key) //if key is less than prev key, then new node goes to the left of prev
    //     {

    //         prev->left = n; 
    //         n->isThreaded = true; //set isThread to true 
    //         n->right = prev; //set new nodes right to prev

            
    //     }
    //     else 
    //     {
            
    //         n->right = prev->right; //point nodes right to prev right 
    //         n->isThreaded = true; 
    //         prev->right = n; //set prev right to point to new node created 
    //         prev->isThreaded = false; //prev dosen't have a thread now
          
    //     }
        

    //     size++; //node is added, increment size 
        
    //    vector<NODE*> bstNodes; //vector that will hold the violator node and nodes after it 
    //    //check to see if there is violator node in map or not 
    //    if(validator != nullptr)
    //    {
    //     // vector<NODE*> bstNodes;
    //     cout << "Hello" << endl; 
    //     cout << "Violator KEY:" << validator->key << endl; 
    //     cout << "# of nodes on the left of the violator : " << validator->nL << endl; 
    //     cout << "# of nodes on the right of the violator: " << validator->nR << endl; 
       
    //     if(validator->left != nullptr )
    //     {
    //         cout << "Left Key: " << validator->left->key << endl; 
    //     }
        
    //     cout << "Right Key: " << validator->right->key << endl; 
    //      sortNodes(bstNodes, validator); //populates the vector with the violator and its children from descending order 
    //      int low = 0; 
    //      int high = bstNodes.size() - 1; //size of the vector - 1(index starts at 0)
    //     if(validatorParent != nullptr && validatorParent->key < bstNodes[(low+high) / 2]->key)
    //     {
    //         validatorParent->right = nullptr; 
    //     }
    //     else if(validatorParent != nullptr && validatorParent->key > bstNodes[(low+high) / 2]->key)
    //     {
    //         validatorParent->left = nullptr; 
    //     }
    //     if(validatorParent == nullptr)
    //     {
    //         root = bstNodes[(high+low) / 2]; 
    //     }
    //     funcToBalance(validatorParent, bstNodes, low, high); //helper function that will balance the sub-tree of where the violator occurs 
    //   if(bstNodes[bstNodes.size() - 1]->right != nullptr)
    //     {
    //         //cout << "VilatorParent: " << bstNodes->key << endl; 
    //     cout << bstNodes[bstNodes.size() - 1]->key <<" 1 " <<bstNodes[bstNodes.size() - 1]->right->key << "MID RIGHT" << endl; 
       
    //     }
    //     if(bstNodes[bstNodes.size() - 1]->left != nullptr)
    //     {
    //         cout << bstNodes[bstNodes.size() - 1]->key <<" 1 " <<bstNodes[bstNodes.size() - 1]->left->key << endl; 
    //     }
    //     if(bstNodes[0]->right != nullptr){
    //         cout << bstNodes[0]->key << " 2 " <<bstNodes[0]->right->key << endl; 

    //     }
    //      if(bstNodes[0]->left != nullptr){
    //         cout <<bstNodes[0]->key << " 2 " <<bstNodes[0]->left->key << endl; 
    //     }
    //      if(bstNodes[1]->right != nullptr){
    //         cout <<bstNodes[1]->key << " 3 " <<bstNodes[1]->right->key << endl; 
    //     }
    //      if(bstNodes[1]->left != nullptr){
    //         cout << bstNodes[1]->key <<" 3 " <<bstNodes[1]->left->key << endl; 
    //     }

   
    //    }
       
    //   if(bstNodes.size() != 0)
    //   {
    //     cout << "Vector Output: " << endl; 
    //     for(int i = 0; i < bstNodes.size(); i++)
    //     {
    //         cout << bstNodes.at(i)->key << endl; 
    //     }
    //     cout << "Vector SIZE: " << bstNodes.size() << endl; 
    //   }

        
    // }

    

    //
    // contains:
    // Returns true if the key is in mymap, return false if not.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //function checks if key is in the map, if it is return true, if not return false
    bool contains(keyType key) {
        NODE* curr = root;

        while (curr != nullptr)
        {
          
            if (key == curr->key)
            {
                return true; //key is found in the map 
            }
            else if (key < curr->key)
            { 
                curr = curr->left; // move curr to the left
            }
            else
            {
                if(curr->isThreaded == false)
                {
                    curr = curr->right; // move curr to the right
                }
                else
                {
                    return false; 
                }
            }
          
        }
        
        return false;  
    }

    //
    // get:
    //
    // Returns the value for the given key; if the key is not found, the
    // default value, valueType(), is returned (but not added to mymap).
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //function checks if key is in the map, if it not found then just returns the default value 
    valueType get(keyType key) {

        NODE* curr = root;

        while (curr != nullptr)
        {
          
            if (key == curr->key)
            {
                return curr->value; //key is found in the map, then return the value of that key
            }
            else if (key < curr->key)
            { 
                curr = curr->left; // move curr to the left
            }
            else
            {
                if(curr->isThreaded == false)
                {
                    curr = curr->right; // move curr to the right
                }
                else
                {
                    return false; 
                }
            }
          
        }
 
        return valueType();  // returns the default value type 
    }

    //
    // operator[]:
    //
    // Returns the value for the given key; if the key is not found,
    // the default value, valueType(), is returned (and the resulting new
    // key/value pair is inserted into the map). 
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-trees that need to be re-balanced.
    // Space complexity: O(1)
    //
    valueType operator[](keyType key) {
        NODE* curr = root;

        while (curr != nullptr)
        {
          
            if (key == curr->key)
            {
                return curr->value; //key is found in the map 
            }
            else if (key < curr->key)
            { 
                curr = curr->left; // move curr to the left
            }
            else
            {
                curr = curr->right; // move curr to the right
            }
          
        }

        put(key, valueType()); //if key is not found, then insert it into the tree
 
        return valueType(); 

        
    }

    //
    // Size:
    //
    // Returns the # of key/value pairs in the mymap, 0 if empty.
    // O(1)
    //
    int Size() {

        return size;  //returns the size 
    }

    //
    // begin:
    //
    // returns an iterator to the first in order NODE.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //gets the first node in the map
    iterator begin() {
        NODE* curr = root; //set curr to the root
        while(curr != nullptr)
        {
            curr = curr->left; //move to the left
        }

        return iterator(curr); 
    }

    //
    // end:
    //
    // returns an iterator to the last in order NODE.
    // this function is given to you.
    // 
    // Time Complexity: O(1)
    //
    iterator end() {
        return iterator(nullptr);
    }

    
    
 void _recursiveFunctionToString(NODE *node, stringstream &output) 
    {
   

        if (node == nullptr)
        {
            return;
        }
        else
        {
            // in-order traversal
            _recursiveFunctionToString(node->left, output); //recursively move node to the left 
            output << "key: " << node->key << " value: " << node->value << endl; //output the key and value 
             if(node->isThreaded == false) //if nodeThread is false 
             {
                _recursiveFunctionToString(node->right, output); //recursively move node to the right 
             }
        }
    }


    // toString:
    //
    // Returns a string of the entire mymap, in order.
    // Format for 8/80, 15/150, 20/200:
    // "key: 8 value: 80\nkey: 15 value: 150\nkey: 20 value: 200\n
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST

    //returns a string of the entire map in order
    string toString() {

        string str =  ""; 
        stringstream s; 
        _recursiveFunctionToString(root, s);//call helper toString function

        str = s.str(); 
        return str; 

    }
    void _recursiveFunctionToVector(vector<pair<keyType, valueType> > &vector, NODE* node)
    {
        if(node == nullptr)
        {
            return;
        }
        else
        {
            _recursiveFunctionToVector(vector, node->left); //move node to the left 
            vector.push_back(make_pair(node->key, node->value)); //insert the node inside the vector
            //if node dosent have a thread then move node to the right
            if(node->isThreaded == false)
            {
                _recursiveFunctionToVector(vector, node->right); //recusively call the function again and move to the right 
            }
        }
    }

    //
    // toVector:
    //
    // Returns a vector of the entire map, in order.  For 8/80, 15/150, 20/200:
    // {{8, 80}, {15, 150}, {20, 200}}
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    //vector that holds all nodes in order 
    vector<pair<keyType, valueType> > toVector() {
        vector<pair<keyType, valueType> > vector; 
        
        _recursiveFunctionToVector(vector, root); //calls helper function for toVector 
    
        return vector;  //return vector 
    }

   void _recursiveFunctionCheckBalance(NODE* node, stringstream &output)
    {
        if (node == nullptr)
        {
            return;
        }
        else
        {
            output << "Key: " << node->key << " nL: " << node->nL << " nR:" << node->nR << endl; //ouputs the key, nL, and nR of the node
            _recursiveFunctionCheckBalance(node->left, output); //recusive function that passes node to the left 
            if(node->isThreaded == false)
            {
            _recursiveFunctionCheckBalance(node->right, output);//recursive function that passes node to the right
            }

             
        }
    }

    //
    // checkBalance:
    //
    // Returns a string of mymap that verifies that the tree is properly
    // balanced.  For example, if keys: 1, 2, 3 are inserted in that order,
    // function should return a string in this format (in pre-order):
    // "key: 2, nL: 1, nR: 1\nkey: 1, nL: 0, nR: 0\nkey: 3, nL: 0, nR: 0\n";
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    //function checks if tree is balcanced or not
    string checkBalance() {

        string str =  ""; 
        stringstream s;
        _recursiveFunctionCheckBalance(root, s); //calls helper checkBalance function 
         str = s.str(); 
        return str;
    }
};
