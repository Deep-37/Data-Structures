#include<iostream>
using namespace std;

// node class
class Node{
public:
    int data;
    Node* next;
    // constructor
    Node(){};   
    Node(int value);
};

// Node constructor
Node::Node(int value){
    data = value;
    next = NULL;
}


// list class
class List{
private: 
    Node* start;
    Node* end;
public:
    //constructor
    List();
    List(int* elements, int n);

    // FUNCTIONS
    void print();
    void append(int element);
    void clear();
    int len();
    int count(int element);
    void extend(List &NewList);
    int index(int key);
    void pop();
    void remove(int element);
    void reverse();
};


List::List(){
    start = NULL;
    end = NULL;
}

// List with array constructer.
List::List(int* elements, int n){
    Node* newnode;
    start = NULL;
    end = NULL;
    for(int i = 0; i<n; i++){
        newnode = new Node(elements[i]);
        if(start == NULL)
        {
            start = newnode;
            end = start;
        }
        else{
            end->next = newnode;
            end = newnode;
        }
    }
}

//print Function
void List::print(){
    Node* temp = start;
    while(temp->next)
    {
        cout<<temp->data<<"->";
        temp = temp->next;
    }
    cout<<temp->data<<endl;
}

// Append Functiion
void List::append(int element){
    Node* newnode = new Node(element);
    if (start == NULL){
        start = end = newnode;
        return;
    }

    end->next = newnode;
    end = newnode;
}

// len function
int List::len(){
    if(start==NULL) return 0;

    Node* temp = start;
    int len = 0;
    while(temp){
        len++;
        temp=temp->next;
    }
    return len;
}

//pop Function
void List::pop(){
    Node* temp = start;
    while(1){
        if(temp->next==end){
            end = temp;
            temp = temp->next;
            end->next = NULL;
            delete temp;
            break;
        }
        else{
            temp = temp->next;
        }
    }
}

//remove function
void List::remove(int element){
    Node* t1 = start;
    Node* t2 = start;
    while(1){
        if(t1->next->data == element){
            t1 = t1->next;
            t2->next = t1->next;
            t1->next = NULL;
            delete t1;
            break;
        }
        else{
            t1 = t1->next;
            t2  = t2->next;
        }
    }
}

//clear function.
void List::clear(){
    end->next = NULL;
    while(start)
    {
        Node* temp = start;
        start = start->next;
        delete temp;
    }
}

//Index function
int List::index(int key){

    if(start==NULL)return -1;

    Node* temp = start;
    int index = 0;
    while(temp)
    {
        if(temp->data==key) return index;
        
        index++;
        temp = temp->next;
    }
    return -1;
}

//Count function
int List::count(int element){

    if(start==NULL) return 0;

    int count = 0;
    Node* temp = start;
    while(temp){
        count += (temp->data == element);
        temp=temp->next;
    }
    return count;
}

//extend function
void List::extend(List &L2){
    if(L2.len() == 0)return;
    Node* temp = L2.start;

    while(temp){
        this->append(temp->data);
        temp = temp->next;
    }

}

//reverse function
void List::reverse(){
    end = start;
    Node* prev = NULL;
    Node* current = start;
    Node* nextN = start->next;
    while(current){
        //NULL<-1->2->3->4->NULL to NULL<-1  2->3->4
        current->next = prev;

        // moving all pointers one node ahead.
        prev = current;
        current = nextN;
        if(current) nextN = current->next;
        else start = prev;
    }
}


int main()
{
    
}