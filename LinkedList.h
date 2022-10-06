#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <string>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node{
public:
  string val;
  Node* next;
};
/*
Node* swap(Node* firstNode, Node* secondNode){
  Node* temp = secondNode->next;
  secondNode->next = firstNode;
  firstNode->next = temp;

  return secondNode;
}*/

class LinkedList{
private:
  Node* head;
  int size;
public:
  LinkedList() : head(nullptr), size(0) {}
  ~LinkedList();

  void add(string);
  void addBegin(string);
  void add_by_index(int index, string content);
  void remove(string key);
  void sort_by_alpha();
  void sort_by_length(); 

  // bool isDuplicate(string);
  // Node* isDuplicate(Node*, string);
  bool isHere(string, string);
  string const toString();
  

//test functions
  int getSize();
  void print();
};

LinkedList::~LinkedList(){
  Node* curr = head;
  
  while (curr != nullptr){
    Node* temp = curr;
    curr = curr->next;
    delete temp;
  }
}

void LinkedList::add(string val){
  Node* curr = head;
  //create new node
  Node* newNode = new Node;
  newNode->val = val;
  newNode->next = nullptr;
  
  if (curr == nullptr){
    head = newNode;
    size++;
  }
  else{
    //traverse the list til the end 

    Node* temp = head;
    if (temp->val == val){ return; }
  
    while (temp->next != nullptr && temp->val != val){
      temp = temp->next;
    }
    if (temp->next == nullptr && temp->val == val){
      return;
    }
    //Node* temp = head;
    
    while (temp->next != nullptr ){
      temp = temp->next;
    }
    
    temp->next = newNode;
    size++;
  }
}

/*
bool LinkedList::isDuplicate(string val){
  if (head == nullptr){ return false; }
  
  Node* where = isDuplicate(head, val);

  if (where->val == val){
    return true;
  }
  return false;
}

Node* LinkedList::isDuplicate(Node* _head, string val){
  Node* temp = _head;
  if (temp->val == val){ return temp; }
  
  while (temp->next != nullptr && temp->val != val){
    temp = temp->next;
  }
  if (temp->next == nullptr && temp->val == val){
    return temp;
  }
  return temp;
}*/

void LinkedList::addBegin(string val){
  //create new node
  Node* newNode = new Node;
  newNode->val = val;
  newNode->next = nullptr;
  
  if (head == nullptr){
    head = newNode;
    size++;
  }
  else{
    Node* temp = head;
    if (temp->val == val){ return; }
  
    while (temp->next != nullptr && temp->val != val){
      temp = temp->next;
    }
    if (temp->val == val){return;}
    else if (temp->next == nullptr && temp->val == val){
      return;
    }
    
    newNode->next = head;
    head = newNode;
    size++;
  }
}
//Add (0) [contents]
void LinkedList::add_by_index(int index, string content){
  if (index > size){
    return;
  }
  //adding in beginning
  else if (index == 0){
    addBegin(content);
  }
  else if (index <= size){
    Node* newNode = new Node;
    newNode->val = content;
    
    Node* temp = head;
    while (temp->next != nullptr && temp->val != content){
      temp = temp->next;
    }
    if (temp->val == content){return;}


    Node* curr = head, *prev = nullptr;
    for (int i = 0; i < index; i++){
      prev = curr;
      curr = curr->next;
    }
    
    newNode->next = prev->next;
    prev->next = newNode;
    size++;
  } 
}

// void DLL::insertAt(int index, string sentence) {
//   if (index > sizeLL)
//     return;

//   if (index == 0)
//     Push(sentence); //begin
//   else if (index == sizeLL)
//     Append(sentence); //end
//   else {
//     Node *new_node = new Node;
//     new_node->data = sentence;
//     Node *curr = head;
//     Node *prev = nullptr;
//     int i = 0;
//     while (i != index) {
//       prev = curr;
//       curr = curr->next;
//       i++;
//     }
//     new_node->next = prev->next;
//     prev->next = new_node;

//     sizeLL++;
//   }
// }

// bool DLL::duplicateFound(string sentence) {

//   if (isEmpty())
//     return false;
  
//   Node *dupe = duplicateFound(head, sentence);

//   if (dupe->data == sentence)
//     return true;

//   return false;
// }



void LinkedList::sort_by_alpha(){
  Node* curr = head;

  if (curr == nullptr){ return; }
  
  for (int i = 0; i < size; i++){
    while (curr->next != nullptr){
      if (curr->val > curr->next->val){
        string temp = curr->val;
        curr->val = curr->next->val;
        curr->next->val = temp;
      }
      curr = curr->next;
    }
    curr = head;
  }
}

  
void LinkedList::sort_by_length(){
  Node* curr = head;

  if (curr == nullptr){ return; }
  
  for (int i = 0; i < size; i++){
    while (curr->next != nullptr){
      if (curr->val.size() > curr->next->val.size()){
        string temp = curr->val;
        curr->val = curr->next->val;
        curr->next->val = temp;
      }
      curr = curr->next;
    }
    curr = head;
  }
}

bool LinkedList::isHere(string key, string inEachNode){
  size_t pos = inEachNode.find(key);
  if (pos != string::npos){
    return true;
  }
  return false;
}

void LinkedList::remove(string key){
  if (size == 0) { return; }
  Node* curr = head, *prev = nullptr;
  //if LL has 1 node
  if (curr->next == nullptr) {
    if (isHere(key, curr->val) == true){
      head = nullptr;
      delete curr;
      size--;
      
    }
  }
  else{ // if LL has more than 1 node
    if (isHere(key, curr->val) == true){
      Node* temp = curr;
      curr = curr->next;
      delete temp;

      head = curr;
      size--;
      remove(key);
      return;      
    }
    else{
      prev = curr;
      curr = curr->next;

      //traverse LL
      while(curr->next != nullptr){
        if (isHere(key, curr->val)){
          Node* temp = curr;

          prev->next = curr->next;
          curr = curr->next;
          delete temp;

          size--;
          remove(key);
          return;
        }
        else{
          prev = curr;
          curr = curr->next;
        }
      }
      if (isHere(key, curr->val) == true){
        prev->next = nullptr;
        delete curr;
        size--;
        remove(key);
      }
    }
  }/*
  if (isHere())


  
  if (isHere(key, head->val) == true){
    Node* temp = head;
    head = head->next;

    delete temp;
    size--;
  }
  
  while (curr != nullptr) {
    if (isHere(key, curr->val) == true){
      prev->next = curr->next;
      delete curr;
			curr = prev->next;
      size--;
    }
    else{ prev = curr; }
    curr = curr->next;
  }*/
}



string const LinkedList::toString() {
  Node* curr = head;
  string listAsString = "";
  
  while (curr != nullptr) {
    listAsString += curr->val + "\n";
    curr = curr->next;
  }
  return listAsString;
}
  


//test functions
void LinkedList::print(){
  Node* curr = head;

  while (curr != nullptr){
    cout << curr->val << endl;
    curr = curr->next;
  }
}
int LinkedList::getSize(){
  return size;
}

#endif 