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
        int count = 0; // Number of elements in the list
public:
 	 	/*
     	* Add a new element at the end of the list
     	*/
        void push_back(type b){
            	Node<type>* temp =new Node(b);
                if(head==nullptr){
					// List is empty
                    head = temp;
                    tail = temp;
                }else{
					// Attach to the end
                    temp->prev = tail;
                    tail->next = temp;
                    tail = temp;
                }
                count++;
        }
	 	/*
     	* Remove the last element from the list
     	*/
    	void pop_back(){
        	tail = tail->prev;
        	delete tail->next;
        	tail->next = nullptr;
        	count--;
		}
		/*
     	* Print all values in the list
     	*/
	 	void print(){
        	    for(Node<type>* k=head; k!=nullptr; k=k->next){
            	    cout<<"value: "<<k->value<<endl;
            	}
    	}
		/*
     	* Destructor
     	* Frees all dynamically allocated nodes
     	*/
		~LinkedList(){
            while(head!=nullptr){
                Node<type>* i = head->next;
                delete head;
				head = i;
        	}
        }

		/*
     	* Default constructor
     	*/
        LinkedList(){
        	count++;
        }

		/*
     	* Copy constructor
     	* Creates a deep copy of another LinkedList
     	*/
        LinkedList(LinkedList& x){
                for(Node<type>* k=x.head;k!=nullptr; k=k->next){
                        push_back(k->value);
                }
        }

		/*
     	* Assignment operator overload
     	* Handles deep copy and self-assignment
     	*/
        LinkedList&  operator=(const LinkedList& x){
                if(head==nullptr){
					// If current list is empty
        			for(Node<type>* k=x.head; k!=nullptr; k=k->next){
                         push_back(k->value);
                     }
                }else{
					// Delete existing nodes
                    for(Node<type>*k=head; k!=nullptr;k=k->next){
                         Node<type>* i = k;
                         delete i;
                    }
					// Copy new nodes
                    for(Node<type>* k=x.head; k!=nullptr; k=k->next){
                         push_back(k->value);
                    }
                }
                return *this;
        }
		
		/*
     	* Output stream operator <<
     	* Allows printing the list using cout
     	*/
 		friend ostream& operator<<(ostream& tpel, LinkedList& x){
                tpel<<"-------opertor's<< call-"<<endl;
                for(Node<type>* k=x.head; k!=nullptr; k=k->next){
                        tpel<<"Value:    "<<k->value<<endl;
                }
                return tpel;
        }
    	
		/*
     	* Input stream operator >>
     	* Allows user-driven input into the list
     	*/
        friend istream& operator>>(istream& input, LinkedList& x){
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
                         input>>y;
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

                return input;
        }
		/*
	    * Prefix increment operator (++list)
	    * Increments all values by 1
	    */
		LinkedList<type>& operator++(){
                cout<<"Prefix operator"<<endl;
                for(Node<type>* i=head; i!=nullptr;i=i->next){
                        i->value = i->value+1;
                }
                return *this;
        }

		/*
     	* Postfix increment operator (list++)
     	* Returns old list, then increments values
     	*/
        LinkedList<type> operator ++(int a){
                cout<<"postfix operator"<<endl;
                LinkedList<type> b = *this;
                for(Node<type>* i=head; i!=nullptr; i=i->next){
                        i->value = i->value+1;
                }
                return b;
        }
		
		/*
     	* Prefix decrement operator (--list)
     	*/
        LinkedList<type>& operator--(){
            cout<<"Prefix operator"<<endl;
            for(Node<type>* i=head; i!=nullptr;i=i->next){
                i->value = i->value-1;
            }
            return *this;
        }

		/*
     	* Postfix decrement operator (list--)
    	*/
        LinkedList<type> operator --(int a){
            cout<<"postfix operator"<<endl;
            LinkedList<type> b = *this;
            for(Node<type>* i=head; i!=nullptr; i=i->next){
                i->value = i->value-1;
            }
            return b;

        }

		/*
     	* Subscript operator []
     	* Access element by index
    	* Throws exception if index is invalid
     	*/
 		type operator[](int index){
            cout<<"operator []  "<<endl;
            if(index<0 or index>count){
                int a = 777;// Custom error code
                throw a;
            }
            cout<<"----1''''''"<<endl;
            Node<type>* x = head;
            cout<<"x:  "<<x->value<<endl;
            for(int i=0; i<index; i++){
                x = x->next;
			}
            return x->value;
        }
};

/*
 * =========================
 * Main Function
 * =========================
 * Demonstrates usage of the LinkedList class
 */
int main() {
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
