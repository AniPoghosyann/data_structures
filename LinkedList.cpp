#include<iostream>
using namespace std;
/*
 * Template Node class
 * NodeType represents the data type of key and value
 */

template <class t>
class Node{
public:
        t value; //value stored
        Node<t>* prev = nullptr; // pointer to previous node
        Node<t>* next = nullptr; // pointer to next node
	//constructor to initialize key and value
        Node(t b){
                value = b;
        }
};
/*
 * Linked List class (templated)
 */

template <class type>
class LinkedList{
private:
        Node<type>* head = nullptr; // pointer to head
        Node<type>* tail = nullptr; // pointer to tail
        int count = 0;
public:
        void push_back(type b){
                Node<type>* temp =new Node(b);
                if(head==nullptr){
                         head = temp;
                         tail = temp;
                }else{
                        temp->prev = tail;
                        tail->next = temp;
                        tail = temp;
                }
                count++;
        }

        void pop_back(){
                tail = tail->prev;
                delete tail->next;
                tail->next = nullptr;
                count--;
	}

 void print(){
                for(Node<type>* k=head; k!=nullptr; k=k->next){
                        cout<<"value: "<<k->value<<endl;
                }
        }
        ~LinkedList(){
                while(head!=nullptr){
                        Node<type>* i = head->next;
                        delete head;
                        head = i;
                }
        }
        LinkedList(){
        count++;
        }
        LinkedList(LinkedList& x){
                for(Node<type>* k=x.head;k!=nullptr; k=k->next){
                        push_back(k->value);
                }
        }



        LinkedList&  operator=(const LinkedList& x){
                if(head==nullptr){
                        for(Node<type>* k=x.head; k!=nullptr; k=k->next){

                                push_back(k->value);
                        }
                }else{
                        for(Node<type>*k=head; k!=nullptr;k=k->next){
                                        Node<type>* i = k;
                                        delete i;
                        }
                        for(Node<type>* k=x.head; k!=nullptr; k=k->next){
                                push_back(k->value);
                        }
                }
                return *this;
        }
 friend ostream& operator<<(ostream& tpel, LinkedList& x){
                tpel<<"-------opertor's<< call-"<<endl;
                for(Node<type>* k=x.head; k!=nullptr; k=k->next){
                        tpel<<"Value:    "<<k->value<<endl;
                }
                return tpel;
        }

        friend istream& operator>>(istream& nerm, LinkedList& x){
                bool b = true;
                type value;
                while(b){
                        cout<<"value:    "<<endl;
                        nerm>>value;
                        x.push_back(value);
                        bool a = true;
                        while(a){
                                cout<<"do you want to continue? 1. yes 0.no"<<endl;
                                int y;
                                nerm>>y;
                                if(y==1){
                                        b = true;
                                        a = false;
                                }else if(y==0){
                                        b = false;
                                        a = false;
                                }else{
                                        cout<<"wrong number, try again"<<endl;
                                        a = true;
                                        b = true;
                                }
                        }
                }

                return nerm;
        }

LinkedList<type>& operator++(){
                cout<<"Prefix operator"<<endl;
                for(Node<type>* i=head; i!=nullptr;i=i->next){
                        i->value = i->value+1;
                }
                return *this;
        }
        LinkedList<type> operator ++(int a){
                cout<<"postfix operator"<<endl;
                LinkedList<type> b = *this;
                for(Node<type>* i=head; i!=nullptr; i=i->next){
                        i->value = i->value+1;
                }
                return b;
        }

        LinkedList<type>& operator--(){
                cout<<"Prefix operator"<<endl;
                for(Node<type>* i=head; i!=nullptr;i=i->next){
                        i->value = i->value-1;
                }
                return *this;
        }
         LinkedList<type> operator --(int a){
                cout<<"postfix operator"<<endl;
                LinkedList<type> b = *this;
                for(Node<type>* i=head; i!=nullptr; i=i->next){
                        i->value = i->value-1;
                }
                return b;

        }
 type operator[](int index){
                cout<<"operator []  "<<endl;
                if(index<0 or index>count){
                        int a = 777;
                        throw a;
                }
                cout<<"----1''''''"<<endl;
                Node<type>* x = head;
                cout<<"x:  "<<x->value<<endl;
                for(int i=0; i<index; i++){
                        cout<<"inside for "<<endl;
                        x = x->next;
                }

                cout<<"--after for--"<<endl;
                return x->value;
        }



};
int main()
{
        try{
                LinkedList<int> a; //LInkedList()
                a.push_back(12);
                a.push_back(34);
                a.push_back(5);
                a.push_back(45);
                a.push_back(78);
                a.push_back(78);
                a.push_back(78);
                a.push_back(78);
                a.push_back(78);
                a.pop_back();
                a.pop_back();
                a.print();
		int k = a[2];
                cout<<"k="<<k<<endl;
                int h =a[90];
                cout<<"h = "<<h<<endl;
        }catch(int q){
                if(q==777){
                        cout<<"out: number not found"<<endl;
                }
        }
return 0;
}
