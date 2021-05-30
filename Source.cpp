#include <iostream>

using namespace std;

template <typename T>
class SortedStacklessBST;
// BST Node Class 
template <typename T>
class TNode {
	T data;
	TNode * left;
	TNode * right;
	TNode * nextInOrder;
public:
	//TNode constructor
	TNode() {
		left = nullptr;
		right = nullptr;
		nextInOrder = nullptr;
	}
	//TNode Parameterized Constructor 
	TNode(T d) {
		data = d;
		left = nullptr;
		right = nullptr;
		nextInOrder = nullptr;
	}
	//TNode Copy Constructor
	TNode(TNode <T> & obj) {
		data = obj.data;
		left = obj.left;
		right = obj.right;
		nextInOrder = obj.nextInOrder;
	}
	//Destructor
	~TNode() {
		
	}

	friend class SortedStacklessBST<T>;
};

//BST Class
template <typename T>
class SortedStacklessBST {
	TNode <T> * root;
	bool IsSuccessor;
public:
	//Default Constructor
	SortedStacklessBST() {
		root = nullptr;
		IsSuccessor = true;
	}
	//BST copy constructor
	SortedStacklessBST(SortedStacklessBST <T> & obj) {
		IsSuccessor = obj.IsSuccessor;
		root = nullptr;
		copy(root,obj.root);
		// inorderPrintKeys();
	}
	//Function to Deepcopy the Contents.... it is used in Copy constructor and assignment operator
	//it is using insert function as well because deep copy is required
	  void copy(TNode <T> * &ro,TNode <T> * temp) {
		  if (temp == nullptr)
			  ro = nullptr;
		  else{	
			insert(temp->data);
			copy(ro->left, temp->left);
			copy(ro->right, temp->right);
		  }
	}
	//Wrapper function of Insert
	void insert(T d) {
		insert(d, root);
	}
	//Data variables to be used in Insert Function
	TNode<T> *maxleft = new TNode<T>(-5);
	TNode<T> *minright = new TNode<T>(100000);
	TNode<T> *maxm = new TNode<T>(0);
	
	//Function to Insert the data element in BST iteratively
	void insert(T d, TNode <T> * & r) {
		TNode<T> *curr = r;
		TNode<T> *curr2 = r;
		TNode<T> *parent = nullptr;
		TNode<T> * prev = nullptr;
		if (root == nullptr){
			TNode <T> * temp = new TNode <T>;
			temp->data = d;
			r = temp;
			return;
		}//Finding the Node where insertion is to be done
		while (curr != nullptr) {
			parent = curr;
			if (d < curr->data)
				curr = curr->left;
			else
				curr = curr->right;
			if (d == parent->data) {
				curr = nullptr;
			}
		}
		while (curr2 != parent && curr2 != nullptr) {
			prev = curr2;
			if (d < curr2->data)
				curr2 = curr2->left;
			else 
				curr2 = curr2->right;
		}//Insertion Cases
		if (d == parent->data) {
			cout << "Element Already exits in BST!!" << endl;
			return;
		}
		else if (d < parent->data) {
			TNode <T> * temp = new TNode <T>;
			temp->data = d;
			parent->left = temp;
			temp->nextInOrder = parent;
			//Setting the values of NextInOrder
			if (d > maxleft->data && d<root->data) { 
				maxleft = temp;
			}
			if (d < minright->data && d > root->data) {
				minright = temp;
			}
				root->nextInOrder = minright;
				maxleft->nextInOrder = root;
			if (parent->data > temp->data && prev!=nullptr)
			   prev->nextInOrder = temp;
		}
		else if(d>parent->data) {
			TNode <T> * temp = new TNode <T>;
			temp->data = d;
			parent->right = temp;
			parent->nextInOrder = temp;
			temp->nextInOrder = r->right;
			//Setting the values of NextInOrder
			if (d < minright->data && d > root->data) {
				minright = temp;
			}
			if (d > maxleft->data && d<root->data) {
				maxleft = temp;
			}
			if (maxm->data < d) {
				maxm = temp;
				maxm->nextInOrder = nullptr;
			}
			maxleft->nextInOrder = root;
		}

			Setting_Successor();
	}
	//Function to set the NextInOrder pointer in BST to be used in the Remove Function
	void Setting_Successor() {
		if (IsSuccessor == true) {
			root->nextInOrder = Successor(root->data);
			TNode <T>* temp = getMin();
			while (temp) {
				temp->nextInOrder = Successor(temp->data);
				temp = temp->nextInOrder;
			}
		}
		else {
			root->nextInOrder = Successor(root->data);
			TNode<T>* temp = getMax();
			while (temp) {
				temp->nextInOrder = Successor(temp->data);
				temp = temp->nextInOrder;
			}
		}
	}
	//Helper funtion for setting nextinorder... used in Setting_Successor
	TNode<T>*Successor(T d) {
		if (IsSuccessor == true)
			return Successortrue(root, d);
		else
			return Successorfalse(root, d);
	}
	//Helper Function for Setting the nextinorder if Issuccessor is equal to true... used in Setting_Successor 
	TNode<T>*Successortrue(TNode<T>* temp, T d) {
		TNode<T>*r = temp;
		T x = temp->data;
		int f = 0;
		//comparing the data in nodes to arrange the nextinorder pointer
		while (temp) {
			if (temp && temp->data > d && temp->data < r->data) {
				r = temp;
				f = 1;
			}
			if (temp && x < d && temp->data > d && temp->data > r->data) {
				r = temp;
				f = 1;
			}
			if (temp && x == d && temp->data > d && temp->data > r->data) {
				r = temp;
				f = 1;
			}
			else if (temp && d == temp->data) {
				temp = temp->right;
			}
			else if (temp && d > temp->data) {
				temp = temp->right;
			}
			else if (temp && d < temp->data) {
				temp = temp->left;
			}
		}
		if (getMax()->data == d)
			return nullptr;
		else
			return r;
	}
	//Helper Function for Setting the nextinorder if Issuccessor is False... used in Setting_Successor
	TNode<T>*Successorfalse(TNode<T>* temp, T d) {
		TNode<T>*r = new TNode<T>;
		r->data = 0;
		T x = temp->data;
		//comparing the data in nodes to arrange the nextinorder pointer
		while (temp) {
			if (temp && (temp->data < d) && (temp->data > r->data)) {
				r = temp;
			}
			else if (temp && d == temp->data) {
				temp = temp->left;
			}
			else if (temp && d > temp->data) {
				temp = temp->right;
			}
			else if (temp && d < temp->data) {
				temp = temp->left;
			}
		}
		if (r->data == 0)
			return nullptr;
		else
			return r;
	}
	TNode <T> * dummy = new TNode<T>;
	//Function to get the Node of maximum element of the BST
	TNode <T> * getMax() {
		TNode <T> * temp2 = root->right;
		TNode <T> * & max = dummy;
		while (temp2 != nullptr) {
			max = temp2;
			temp2 = temp2->right;
		}
		return max;
	}
	//Function to get the Node of minimum element of the BST
	TNode <T> * getMin() {
		TNode <T> * temp2 = root->left;
		TNode <T> * & min = dummy;
		while (temp2) {
			min = temp2;
			temp2 = temp2->left;
		}
		return min;
	}
	//Function to get the Node of minimum element of the any root Node
	TNode <T> * getMin(TNode <T> * temp) {
		TNode <T> * temp2 = temp;
		TNode <T> * & min = dummy;
		while (temp2) {
			min = temp2;
			temp2 = temp2->left;
		}
		return min;
	}
	//Function to get the Node of maximum element of any root Node
	TNode <T> * get_Max(TNode <T> * temp) {
		TNode <T> * temp2 = temp;
		TNode <T> * & max = dummy;
		while (temp2 != nullptr) {
			max = temp2;
			temp2 = temp2->right;
		}
		return max;
	}
    //Wrapper Function to Print the elements of BST 
	void inorderPrintKeys() {
		if (root != nullptr) {
			if (IsSuccessor == true)
				PrintR(getMin());
			else
				PrintR(getMax());
		}
			cout << endl;
	}
	//Funtion to Print the elements of BST
	void PrintR(TNode <T> * temp) {
		while (temp != nullptr){
			cout << temp->data << " ";
			temp = temp->nextInOrder;
		}
	}
	//Function to get the Maximum element value of BST
	T getMax(TNode <T> * & temp) {
		if (temp->right != nullptr) {
			T max;
			bool flag = false;
			TNode <T> * & temp2 = temp->right;
			while (temp2) {
				flag = true;
				max = temp2->data;
				temp2 = temp2->right;
			}
			if (flag == true)
				return max;
			else
				return -1;
		}
	}
    //Wrapper Function to remove the element from the BST
	void Remove(T d) {
		Remove(d, root);
	}
	//Function to remove the element from the BST Recursively
	void Remove(T val, TNode<T>*& temp) {
		if (temp == nullptr) {
			//
		}//Cases of Deletion
		else if (val == temp->data) {
			TNode<T>* trash = nullptr;
			if (temp->left == nullptr && temp->right == nullptr) {
				trash = temp;
				temp = nullptr;
			}
			else if (temp->left != nullptr && temp->right == nullptr) {
				trash = temp;
				temp = temp->left;
			}
			else if (temp->left == nullptr && temp->right != nullptr) {
				trash = temp;
				temp = temp->right;
			}
			else { //if both the left and right child are not nullptr 
				TNode<T>*& minNode = FindMin(temp->right); 
				temp->data = minNode->data;
				Remove(minNode->data, minNode);
			}
			if (trash != nullptr) {
				delete trash;
				cout << "Deleted!!" << endl;
			}
			//updating the values of the nextinorder pointer
			if(root!=nullptr)
			Setting_Successor();
		}
		else if (val < temp->data) {
			Remove(val, temp->left);
		}
		else {
			Remove(val, temp->right);
		}
	}
	//Function to Find the Minimum element Node 
	TNode<T> *& FindMin(TNode<T>*& temp) {
		if (temp == nullptr) {
		}
		else if (temp->left == nullptr) {
			return temp;
		}
		else {
			return this->FindMin(temp->left);
		}
	}
	//Wrapper Function to Search the element in BST
	bool search(T d) {
		return search(d, root);
	}
	//Function to Search the element in the BST iteratively
	bool search(T d, TNode <T> * temp) {
		bool flag = false;
		while (temp != nullptr) {
			if (d==temp->data) {
				flag = true;
				cout << d <<" Found in Tree! " << endl;
				return true;
			}
			if (d < temp->data)
				temp=temp->left;
			else {
				temp=temp->right;
			}
		}
		if (flag == false) {
			cout << d << " Not Found in Tree! " << endl;
		}
		return false;
	}
	//Wrapper Function to Print the Elements between the given low to high range
	void Print(T Low, T High) {
		if (IsSuccessor == true)
			Print(Low, High, getMin());
		else
		Print(Low, High, getMax());
	}
	//Function to Print the Elements between the given low to high range iterativey
	void Print(T Low, T High, TNode <T> * temp) {
		while (temp != nullptr) {
			if (temp->data >= Low && temp->data <= High) {
				cout << temp->data << " ";
			}
			temp = temp->nextInOrder;
		}
		cout << endl;
	}
	//Wrapper Function to Reverse the NextInOrder pointer in the BST
	void ReverseOrder() {
		if (IsSuccessor == true)
			IsSuccessor = false;
		else
			IsSuccessor = true;
		if (root != nullptr) {
			if (IsSuccessor == false)
				reverse(getMin(root->left));
			else
				reverse(get_Max(root->right));
			cout << "Reversed!!" << endl;
		}
	}
	//Function to Reverse the NextInOrder pointer in the BST Recursively
	TNode<T>* reverse(TNode<T>* temp)	{
		if (temp == nullptr)
			return nullptr;
		if (temp->nextInOrder == nullptr) {
			root->nextInOrder = temp;
			return temp;
		}
		TNode<T>* temp1 = reverse(temp->nextInOrder);
		temp1->nextInOrder = temp;
		temp->nextInOrder = nullptr;
		return temp;
	}
	//Funtion to Print the Structure of the BST 
	void printstruct(TNode<T> *temp, int blanks, int & count){  
		if (temp == nullptr)
			return; 
		blanks += count;
		printstruct(temp->right, blanks,count);
		cout << endl;
		for (int i = count; i < blanks; i++)
			cout << " ";
		cout << temp->data <<"-";  
		printstruct(temp->left, blanks, count);
	}
	//Wrapper Funtion to Print the Structure of the BST
	void printstruct(){
		int count = 5;
		printstruct(root, 0, count);
		cout << endl;
	}
	//Assignment Operator using DeepCopy function to Assign
	SortedStacklessBST <T> & operator = (const SortedStacklessBST <T> & obj) {
		if (root != nullptr) {
			destructor(root);
		}
		IsSuccessor = obj.IsSuccessor;
		copy(root, obj.root);
		return *this;
	}
	//Function to Check whether the BST leafs are on same level or not...Recursively
	bool Isbalance(TNode<T> *temp, int level, int & leaf2){ 
		if (temp == nullptr) 
			return true; 
		if (temp->left == nullptr && temp->right == nullptr){
			if (leaf2 == 0){
				leaf2 = level; 
				return true;
			}
			return (level == leaf2);
		} 
		//calculating using number of levels 
		return (Isbalance(temp->left, level + 1, leaf2) && Isbalance(temp->right, level + 1, leaf2));
	}
	//Wrapper Function to Check whether the BST leafs are on same level or not
	bool Isbalance(){
		int level = 0, leaf2 = 0;
		bool flag = Isbalance(root, level, leaf2);
		if (flag == true && root != nullptr)
			cout << "Leafs are at the same level!!" << endl;
		else 
			cout<< "Leafs are not at the same level!!" << endl;
		return flag;
	}
	//Function to be used in Destructor to Delete the complete BST....iteratively
	void destructor(TNode <T> * temp) {
		while (temp != nullptr) {
			TNode <T> * temp2 = temp;
			temp = temp->nextInOrder;
			delete temp2;
		}
		root = nullptr;
	}
	//Destructor
	~SortedStacklessBST() {
		if (IsSuccessor == true)
			destructor(getMin());
		else
			destructor(getMax());
	}

};
//Function to print the menu
void menu() {

	cout << "---------------- Binary Search Tree -----------------" << endl;
	cout << "Press 1 to Insert Element" << endl;
	cout << "Press 2 to Remove Element" << endl;
	cout << "Press 3 to Search Element" << endl;
	cout << "Press 4 to Reverse Tree" << endl;
	cout << "Press 5 to Print BST" << endl;
	cout << "Press 6 to Print element from Low to High elements" << endl;
	cout << "Press 7 to Check if Leafs are Balance" << endl;
	cout << "Press 8 to Copy BST into Another" << endl;
	cout << "Press 9 to Print BST Structure" << endl;
	cout << "Press E to Exit" << endl;
}

int main() {
	char opt = 0;
	SortedStacklessBST<int> tree;
	while (opt != 'e' || opt != 'E') {
		menu();
		cout << "Enter the option to select: " << endl;
		cin >> opt;
		if (opt == '1') {
			int el;
			cout << "Enter the Element to Insert: " << endl;
			cin >> el;
			tree.insert(el);
		}
		if (opt == '2') {
			int el;
			cout << "Enter the Element to Remove: " << endl;
			cin >> el;
			tree.Remove(el);
		}
		if (opt == '3') {
			int el;
			cout << "Enter the Element to Search: " << endl;
			cin >> el;
			tree.search(el);
		}
		if (opt == '4') {
			tree.ReverseOrder();
		}
		if (opt == '5') {
			cout << "Tree: ";
			tree.inorderPrintKeys();
		}
		if (opt == '6') {
			int low;
			int high;
			cout << "Enter Lower Element: " << endl;
			cin >> low;
			cout << "Enter High Element: " << endl;
			cin >> high;
			tree.Print(low, high);
		}
		if (opt == '7') {
			tree.Isbalance();
		}
		if (opt == '8') {
			SortedStacklessBST<int> tree1 = tree;
			cout << "Tree2: ";
			tree1.inorderPrintKeys();
		}
		if (opt == '9') {
			tree.printstruct();
		}
		if (opt == 'e' || opt == 'E') {
			cout << "Exited!" << endl;
			break;
		}
	}
	
	/*
	tree.insert(500);
	tree.insert(1000);
	tree.insert(1);
	tree.insert(600);
	tree.insert(700);
	tree.insert(10);
	tree.insert(30);
	tree.insert(9000);
	tree.insert(50000);
	tree.insert(20);
	tree.insert(800);
	tree.insert(35);
	tree.insert(8000);
	tree.insert(3);
	tree.insert(40);
	tree.insert(44);
	cout << "Tree: ";
	tree.inorderPrintKeys();
	tree.Remove(600);
	tree.Remove(10);
	tree.Remove(1000);
	tree.inorderPrintKeys();
	tree.search(700);
	tree.Print(50, 900);
	tree.ReverseOrder();
	tree.inorderPrintKeys();

	SortedStacklessBST<int> tree1(tree);
	tree1.Remove(10);
	tree1.Remove(500);
	tree1.Remove(9000);
	tree1.inorderPrintKeys();

	SortedStacklessBST<int> tree2 = tree1;
	tree2.inorderPrintKeys();
	tree = tree2;
	tree.inorderPrintKeys();
	tree.Isbalance();
	cout<< endl;*/
	return 0;
}