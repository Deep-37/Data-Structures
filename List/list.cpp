#include<iostream>
#include<stdexcept>
using namespace std;

// node class
class Node{
public:
    int data;
    Node* next;
    // constructor
    Node(){};   
    Node(int value);

    friend ostream& operator<<(ostream &out, Node& obj){

        out << obj.data;
        return out;
    }
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
    void insert(int index, int element);
    void clear();
    int len();
    int count(int element);
    void extend(List &NewList);
    int index(int key);
    void pop();
    void remove(int element);
    void reverse();
    void sort();

    //operator overload
    Node& operator[](int index);
    List& operator+(List& l2);

    friend ostream& operator<<(ostream& out, List& obj){
        if(obj.start==NULL){
            out<<"[]"<<endl;
            return out;
        }
        Node* temp = obj.start;
        out <<"[";
        while(temp->next){
            out<<*temp<<", ";
            temp = temp->next;
        }        
        out<<*temp<<"]"<<endl;
        return out;
    
    }

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

// insert function
void List::insert(int index, int element){
        
    if(index == 0){
        Node* newnode = new Node(element);
        newnode->next = start;
        start = newnode;
    }
    else if(index<(this->len())){
        
        Node* newnode = new Node(element);
        Node* temp = start;
        int i=0;
        while(i<index-1){
            temp = temp->next;
            i++;
        }
        newnode->next = temp->next;
        temp->next = newnode;

    }
    // 0 1 2 3 4 5 6
    // 1 2 3 4 5
    else{
        this->append(element);
    }
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

    if(start==NULL)
    throw std::length_error("List is empty");

    Node* temp = start;
    int index = 0;
    while(temp)
    {
        if(temp->data==key) return index;
        
        index++;
        temp = temp->next;
    }
    throw std::invalid_argument("Invalid Index");
    
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

//sort function
void List::sort(){
    if(start == NULL) return;

    Node *temp;

    int n = len(), tmp;

    for (int i = 0; i < n - 1; i++)
    {
        temp = start;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (temp->data > temp->next->data)
            {
                tmp = temp->data;
                temp->data = temp->next->data;
                temp->next->data = tmp;
            }
            temp = temp->next;
        }
    }
}

//[]operator overloading 
Node& List::operator[](int index){
    int length = this->len();
    if(index>=length){
        throw std::out_of_range("invalid index");
    }
    Node* temp = start;
    for(int i=0;i<index;i++){
        temp =temp->next;
    }
    return *temp;
}

//+operator overloading
List& List::operator+(List& l2){
    List *L3 = new List();
    Node* temp1 = this->start;
    while(temp1){
        (*L3).append(temp1->data);
        temp1 = temp1->next;
    }
    temp1 = l2.start;
    while(temp1){
        (*L3).append(temp1->data);
        temp1 = temp1->next;
    }
    return *L3;
}


int main()
{
    int a[] = {1,2,3,4,5};
    List L1(a,5);
    L1.insert(100,12);
    L1.print();
    try{
        cout<<L1.index(-1);
    }
    catch(const std::exception& e){
        std::cerr<<e.what()<<"\n";
    }
    cout<<L1+L1;
    cout<<L1;
}