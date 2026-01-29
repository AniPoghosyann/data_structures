#include<iostream>
using namespace std;
/*
 * Template Node class
 * NodeType represents the data type of key and value
 */
template <class NodeType>
class Node{
        public:
                NodeType value;  //value stored
                NodeType key;    //key used for BFT ordering
                Node<NodeType>* right = nullptr;  //pointer to right child
                Node<NodeType>* left = nullptr;   //pointer to left child
                Node<NodeType>* parent = nullptr; //pointer to parent node
                //constructor to initialize key and value
                Node(NodeType a, NodeType b){
                        key = a;
                        value = b;

                }
};

/*
 * Binary Search Tree class (templated)
 */
template <class T>
class BinarySearchTree{
        private:
                Node<T>* root = nullptr; // pointer to root of the tree
        public:

                // check if the tree is empty
                bool isEmpty(){
                        return root==nullptr;
                }
                /*
                 * Recursively checks if the key exists  in the tree
                 */

 		bool findKey(T tiv, Node<T>* k){
                        if(k==nullptr){
                                return false;     // key not found
                        }else if(tiv==k->key){
                                return true;      // key found
                        }else if(tiv<k->key){
                                return findKey(tiv, k->left);  // search left subtree
                        }else{
                                return findKey(tiv,k->right);  // search right subtree
                        }
                        return false;
                }
                /*
                 *  Recursive insert helper
		 */

   		void insert(T a, T b, Node<T>* k){
                        cout<<"-------------in insert function--------"<<endl;
                        if(root==nullptr){
                                root = new Node(a, b); // create root
                        }else if(a<k->key){
                                cout<<"----if key is smaller------"<<endl;
                                if(k->left==nullptr){
                                        k->left = new Node(a, b); // insert as left child
                                        k->left->parent = k;

                                }else{
                                        insert(a,b, k->left); // continue recursion
                                }

                        }else if(a>k->key){
                                cout<<"------------if key is bigger----------"<<endl;
                                if(k->right==nullptr){
                                        k->right = new Node(a, b); // insert as right child
                                        k->right->parent = k;
                                }else{
                                        insert(a, b, k->right);
                                }
                        }else{
                                cout<<"----------in else (insert)"<<endl;
                                k->value=b;
                        }

                }
                /*
                 * Finds and returns pointer to node with given key
                 */

		 Node<T>* findPointer(T tiv, Node<T>* k){
                        if(k==nullptr){
                                return nullptr;
                        }else if(tiv==k->key){
                                return k;
                        }else if(tiv<k->key){
                                return findPointer(tiv, k->left);
                        }else{
                                return findPointer(tiv, k->right);
                        }
                        return findPointer(tiv, k->right);
                }

                /*
                 * Removes a node by key
                 */
 		 void remove(T x){
                        cout<<"--------in remove function------------"<<endl;
                        auto k = findPointer(x, root);
                        if(k==nullptr){
                                return;
                        }
                        if(k->left != nullptr){
                                cout<<"-------------------if k->left is not nullptr"<<endl;
                                auto i = k->left;
                                for(; i->right!=nullptr; i=i->right){}
                                k->key = i->key;
                                k->value = i->value;
                                if(i->left != nullptr){
                                        i->left->parent = i->parent;
                                }
                                if(i->parent->right == i){
                                        i->parent->right = i->left;
                                }else{
                                        i->parent->left = i->left;
                                }

                                if(i->left != nullptr){
                                        i->left->parent = i->parent;
                                }

                                i->parent->right = nullptr;
                                delete i;
                         }else if( k->right!=nullptr){
                                 cout<<"-------------------if k->right is not nullptr"<<endl;
                                 auto i = k->right;
                                 for(; i->left!=nullptr; i=i->left){
                                        cout<<"i=>key=="<<i->key<<endl;
                                }
                                k->key = i->key;
                                k->value = i->value;
                                if(i->right != nullptr){
                                        i->right->parent = i->parent;
                                }
                                if(i->parent->left == i){
                                        i->parent->left = i->right;
				}else{
                                        i->parent->right = i->right;
                                }

                                if(i->right != nullptr){
                                        i->right->parent = i->parent;
                                }

                                i->parent->left = nullptr;
                                delete i;
                           }else{
                                 cout<<"----------------------else so right and left are null"<<endl;
                                 if(x<k->parent->key){
                                         cout<<"--------if x<k->parent->key"<<endl;
                                         k->parent->left = nullptr;
                                         cout<<"-----------after "<<endl;
                                         delete k;
                                         cout<<"-----after delete"<<endl;
                                 }else if(x>k->parent->key){

                                         k->parent->right = nullptr;
                                         delete k;
                                 }

                        }
                        cout<<"---after else case ---"<<endl;

                }


                /*
                 * Public insert function
                 */

 		void insert(T a, T b){
                        if(!findKey(a, root)){
                                insert(a, b, root);
                        }

                }

                /*
                 * Recursive print helper
                 */
                void print(Node<T>* k){
                        if(k!=nullptr){
                                print(k->left);
                                cout<<"key: "<<k->key<<"  value: "<<k->value<<endl;
                                print(k->right);
                        }
                        cout<<"---print functions end---"<<endl;
                }

                /*
                 * Public print function
                 */
                void print (){
                        print(root);

                }
                 /*
                  * Deletes all nodes (postorder cleanup)
                  */
                void clean(Node<T>* k){
                        cout<<"++++++++++++++in clean"<<endl;
                        if(k!=nullptr){
                                cout<<"if k is not null"<<endl;
                                clean(k->left);
                                cout<<"recursion for left"<<endl;
                                clean(k->right);
                                cout<<"recursion for right"<<endl;
                                delete k;
                        }
                }


		 // Destructor
                ~BinarySearchTree(){
                        cout<<"in destructor"<<endl;
                        clean(root);
                }
                // Default constructor
                BinarySearchTree(){
                }

                /*
                 * Deep copy helper
                 */
                Node<T>* copy(Node<T>* a){
                        if(a!=nullptr){
                                auto k = new Node(a->key,a->value);
                                k->left = copy(a->left);
                                k->right = copy(a->right);
                                return k;
                        }else{
                                return nullptr;
                        }

                }

                // Copy constructor
                BinarySearchTree(BinarySearchTree& x){
                        root = copy(x.root);
                }

                // Assignment operator
                BinarySearchTree& operator=(BinarySearchTree& x){
                       if(root==nullptr){
                               root = copy(x.root);
                               return *this;
                       }else{
                                clean(root);
                                root = nullptr;
                                root = copy(x.root);
                       }
                       return *this;



		}

                // Output operator
                friend ostream& operator<<(ostream& tpel, BinarySearchTree& x){
                                tpel<<"------BinerySearchTree's operator<< call ------"<<endl;
                                x.print(x.root);
                                return tpel;
                }

                // Input operator
                friend istream& operator>>(istream& nerm, BinarySearchTree& x){
                        bool b = true;
                        T val;
                        T k;
                        while(b){
                                cout<<"key:  "<<endl;
                                nerm>>k;
                                cout<<"value:   "<<endl;
                                nerm>>val;
                                x.insert(k, val);
                                bool a = true;
                                int x;
                                while(a){
                                        cout<<"do you want to continue? 1.yes 0.no"<<endl;
                                        nerm>>x;
                                        if(x==1){
                                                b = true;
                                                a = false;
                                        }else if(x==0){
                                                b = false;
                                                a = false;
                                        }else{
                                                cout<<"wrong number try again"<<endl;
                                                a = true;
                                                b = true;
                                        }
                                }
                        }
                        return nerm;

  }



};
int main(){
        BinarySearchTree<int> a;
        a.insert(12,100);
        a.insert(13,50);
        a.insert(54,250);
        a.insert(345,40);
        a.insert(45,75);
        a.insert(35,200);
        a.insert(31,300);
        a.insert(3,30);
        a.insert(5,70);
        cout<<"------------------------0----------------"<<endl;
        a.insert(99, 350);
        cout<<"-----------------------1----------------"<<endl;
        a.remove(99);
        cout<<"---after remove----"<<endl;
        a.print();
        cout<<"---after print()----"<<endl;

        cout<<"-----------------------"<<endl;
        BinarySearchTree<string> e;
        e.insert("a","b");
        e.insert("d","s");
        e.insert("b","a");
        e.insert("s","q");
        e.insert("k","h");
        e.insert("l","g");
        e.insert("n","g");
        e.insert("a","f");
        cout<<e<<endl;

        cout<<a<<endl;
        BinarySearchTree<int> b = a;
        cout<<b<<endl;
	BinarySearchTree<string> x;
        cin>>x;
        x.print();

        cout<<x<<endl;

        return 0;
}
