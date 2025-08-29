#include "a4_birthdayBST.hpp"
#include "a4_birthdaylib.hpp"

//private functions

//insert node recusrively by doing the following
BirthdayBSTreeNode*BirthdayBST::insertNode_rec(BirthdayBSTreeNode* node,
                                        Birthday* value){
    //if null, create anew node
    if (node == NULL){
        node = newNode(value);   
    } 
   
    else{ 
        //otherwise check if empty, if so create left node 
        //and connect it to parent
        if (compareBirthdaysByMD(node->value, value) > 0){

        node->left = insertNode_rec(node->left, value);
        node->left->parent = node;
        
    }
    //otherwise check if empty, if so create right node and
    //connect it to parent
    else {
        node->right = insertNode_rec(node->right, value);
        node->right->parent = node;
  
   
    }
    }
 return node;
 
    }

//remove the node by doing the following
 BirthdayBSTreeNode*BirthdayBST::removeNode_rec(BirthdayBSTreeNode* node,
                                        Birthday* value){

    if (node == NULL) 
    return node; //empty tree, do nothing, NULL is returned

    //find the node to remove
    if (node->value > value)
    removeNode_rec(node->left, value);

    else if (node->value < value){ 
    removeNode_rec(node->right, value);}

    else { //node is found
    if (node->left == NULL && node->right == NULL) { //node is a leaf
    delete node;
    return NULL;//let its caller update the child pointer to NULL
    } 

    else if (node->right == NULL) { //node has a single left child
    BirthdayBSTreeNode* lefty = node->left;
    delete node;
    return lefty; //let its caller update the child pointer so it's its child
    } 
    
    else if (node->left == NULL) { //node has a single right child
    BirthdayBSTreeNode* righty = node->right;
    delete node;
    return righty; //let its caller update the child pointer so it's its child
    } 
    
    else { //node has 2 children
    //see code on the right
    BirthdayBSTreeNode* minRightNode = minSuccessor(node->right);
    //copy the value from the minimum successor
    node->value = minRightNode->value;
    //move on to the right and remove this “duplicate”
    removeNode_rec(node->right, minRightNode->value);
    }
    }
    return node; //let its caller update the child pointer to “adopt” it
    }

//find the node by month day recusively
BirthdayBSTreeNode*BirthdayBST::findNodeByYMDN_rec(BirthdayBSTreeNode* node,
                                        short year, short month, short day,
                                   string name){
        //if null, do nothing
        if(node == nullptr){
            return NULL;
        }
        //else, check if there is a full match
        else if(node->value->year == year && 
        node->value->month == month &&
        node->value->day == day && 
        node->value->name.compare(name) == 0){
            return node;
        }
        //if not, check left and right node
        else{
            Birthday* comparing = create_Birthday(year,month,day,name, "NA");
            if(compareBirthdaysByMD(node->value, comparing) > 0){

               delete comparing;
               return findNodeByYMDN_rec(node->left,
                                        year, month, day, name);
            }

            else{
               delete comparing;
               return findNodeByYMDN_rec(node->right,
                                        year, month, day, name);
                    }
        }


    }

//find the node by month day
BirthdayBSTreeNode*BirthdayBST::findNodeByMD_rec(BirthdayBSTreeNode* node,
                                        short month, short day){
        //if empty, do nothing
        if(node == nullptr){
            return NULL;
        }

        //if ther is an exact match then return it
        else if(node->value->month == month &&
        node->value->day == day){
            return node;
        }

        //otherwise check left and right for a match
        else{
            Birthday* comparing = create_Birthday(0,month,day,"NA", "NA");
            if(compareBirthdaysByMD(node->value, comparing) > 0){
               delete comparing;
               return findNodeByMD_rec(node->left,
                                     month, day);
            }

            else{
               delete comparing;
               return findNodeByMD_rec(node->right,
                                        month, day);
                    }
        }

}

//print all nodes with matching month day
void BirthdayBST::printAllNodeWithMatchingMD_rec(BirthdayBSTreeNode* node, 
                                        ostream& os,
                                        short month, short day){
        //if null, do nothing
        if(findNodeByMD_rec(node, month, day) == NULL){
            return;
        }
        
        //otherwise, print the info
        else{
            os << node->value->year << "-" << node->value->month << "-";
            os << node->value->day << endl
            << node->value->name << endl << node->value->knownFor<<endl;
            os<<"====================================="<<endl;
            printAllNodeWithMatchingMD_rec(node->left,os, node->value->month, 
            node->value->day);
            printAllNodeWithMatchingMD_rec(node->right, os, 
            node->value->month, node->value->day);

            }
        }

                                        
        
 //print info recusrively       
void BirthdayBST::inOrderPrint_rec(BirthdayBSTreeNode* node, ostream& os){

    //if null do nothing
    if (node == nullptr){
        return;
    }  

    //otherwise go into each node and print the info inside
    else{
    inOrderPrint_rec(node->left, os);
    os<<"============================================"<<endl;
    os << node->value->year << "-" << node->value->month 
    << "-" << node->value->day << endl
    << node->value->name << endl << node->value->knownFor<<endl;
    inOrderPrint_rec(node->right, os);
    return;
    
    }

}


 //delete the tree recusrively    
void BirthdayBST::deleteTree_rec(BirthdayBSTreeNode* node){
    //if it is null do nothing
    if(node == NULL){
        return;
    }
    else{
        //otherwise go to the left, right, and value to delete all those
        deleteTree_rec(node->left);
        deleteTree_rec(node->right);
        delete_Birthday(node->value);
        //make sure to delete the node itself too so it isnt empty info
        delete node;
    }

}

 //create a new node       
BirthdayBSTreeNode* BirthdayBST:: newNode(Birthday* value){
    BirthdayBSTreeNode* noddy = new BirthdayBSTreeNode;
    //set all values to null so they can be filled up
    noddy->left = NULL;
    noddy->right = NULL;
    noddy->parent =NULL;
    noddy->value = value;
    //increment the size each time tyou have a new node then return the node
    size++;
    return noddy;

}

//minsuccesor is used to place the next node as the parent that was removed        
BirthdayBSTreeNode* BirthdayBST:: minSuccessor(BirthdayBSTreeNode* node){
    BirthdayBSTreeNode* smallestnode = node;

    //while it is not empty and the left node isnt empty, then set 
    //as the parent
    while (smallestnode != NULL && smallestnode->left != NULL) {
    smallestnode = smallestnode->left;
        }

    return smallestnode;
    }



//public functions

//creating constructor
BirthdayBST::BirthdayBST(){
    size = 0;
    root = NULL;
}

//getting size of tree
int BirthdayBST::getSize(){
    return size;
   
}

//inserting the node
void BirthdayBST::insertNode(Birthday* value){
        root = insertNode_rec(root,value);
        }

//removing the node 
Birthday* BirthdayBST::removeNode(Birthday* value){
    removeNode_rec(root,value);
    return 0;


}

//finding the node by it years,month,day,name
Birthday*BirthdayBST:: findNodeByYMDN(short year, short month, short day,
                                string name){

    //use recusrive function to see if there is a match
    BirthdayBSTreeNode* match = findNodeByYMDN_rec(root,year, 
    month,day,name);
    if(match == nullptr){
        return nullptr;
    }

    else{
        return match->value;
        }
    
    }

//finding the node by the month and day
Birthday* BirthdayBST:: findNodeByMD(short month, short day){

    //do the following, tell the user its not there but if there
    // is a found node print it, 
    BirthdayBSTreeNode* foundnode = findNodeByMD_rec(root,month,day);
    if(foundnode == nullptr){
        cout<< "No birthday on record "<<month<<"-"<<day<<endl;
        return nullptr;
    }
    else{
    
        if(foundnode != NULL){
            printAllNodeWithMatchingMD(foundnode->value->month, 
            foundnode->value->day,cout);

        }
    }
    return foundnode->value;
    
    
}


//print all the nodes with matching month, day, year, name
void BirthdayBST::printAllNodeWithMatchingMD(short month, short day, 
ostream& os){

    //if there is no match return, otherwise print it
   BirthdayBSTreeNode* matchinfo =  findNodeByMD_rec(root, month, day);
   if(matchinfo == NULL){
            os<<"No birthday on record: "<<month<<"-"<<day<<endl;
            return;
        }
    else{
        printAllNodeWithMatchingMD_rec(matchinfo, os,
                                        month, day);
       

    }
                                       
     }


//printing birthday info in order
void BirthdayBST::inOrderPrint(ostream& os){
    inOrderPrint_rec(root,os);

}

//destructor to delete the tree
BirthdayBST::~BirthdayBST(){
    deleteTree_rec(root);
}



