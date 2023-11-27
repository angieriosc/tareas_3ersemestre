
// Nombre: splay.h
// Autor: Angélica Ríos Cuentas
// Fecha: 06/11/2023.
// Tarea que muestra el conocimiento de un Splay Tree



#ifndef SplayTree_H
#define SplayTree_H

#include <string>
#include <sstream>
#include <iostream>

template <class T> class SplayTree;

template <class T>
class Node {
private:
	T value;
	Node *left, *right, *parent;

	Node<T>* succesor();
	Node<T>* rot_right(Node<T>*);
	Node<T>* rot_left(Node<T>*);

public:
	Node(T);
	Node(T, Node<T>*, Node<T>* ,Node<T>*);
	Node<T>* add(T); //agregar nodo
	Node<T>* find(T); //encontrar nodo
	Node<T>* remove(T); //eliminar nodo
	void removeChilds();
	void inorder(std::stringstream&) const; 
	void print_tree(std::stringstream&) const; 
	void preorder(std::stringstream&) const;
	Node<T>* splay(Node<T>*, Node<T>*); //función splay

	friend class SplayTree<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0), parent(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, Node<T> *p)
	: value(val), left(le), right(ri), parent(p) {}

template <class T>
Node<T>* Node<T>::add(T val) {
    if (val < value) {
        if (left == nullptr) {
            left = new Node<T>(val, nullptr, nullptr, this);
            return left;
        } else {
            return left->add(val);
        }
    } else {
        if (right == nullptr) {
            right = new Node<T>(val, nullptr, nullptr, this);
            return right;
        } else {
            return right->add(val);
        }
    }
}

template <class T>
Node<T>* Node<T>::find(T val) {
	if (val == value) {
		return this;
	} else if (val < value) {
		if (left != 0) {
			return left->find(val);
		} else {
			return this;
		}
	} else if (val > value) {
		if (right != 0) {
			return right->find(val);
		} else {
			return this;
		}
	}
	return 0;
}

template <class T>
Node<T>* Node<T>::succesor() {
	Node<T> *le, *ri;

	le = left;
	ri = right;

	if (right->left == 0) {
		right = right->right;
		ri->right = 0;
		return ri;
	}

	Node<T> *parent, *child;
	parent = right;
	child = right->left;
	while (child->left != 0) {
		parent = child;
		child = child->left;
	}
	parent->left = child->right;
	child->right = 0;
	return child;
}

template <class T>
Node<T>* Node<T>::remove(T val) {
	if (val < value) {
		if (left == nullptr)
			return this;
		left = left->remove(val);
	} else if (val > value) {
		if (right == nullptr)
			return this;
		right = right->remove(val);
	} else {
		if (left == nullptr) {
			Node<T>* temp = right;
			delete this;
			return temp;
		} else if (right == nullptr) {
			Node<T>* temp = left;
			delete this;
			return temp;
		}

		Node<T>* temp = right;
		while (temp->left != nullptr) {
			temp = temp->left;
		}
		value = temp->value;
		right = right->remove(temp->value);
	}
	return this;
}

template <class T>
void Node<T>::removeChilds() {
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* x){
	Node<T> *y = x->left;
	x->left = y->right;
	if(y->right)
		y->right->parent = x;
	y->right = x;
	y->parent = x->parent;
	x->parent = y;
	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::rot_left(Node<T>* x){
	Node<T> *y = x->right;
	x->right = y->left;
	if(y->left)
		y->left->parent = x;
	y->left = x;
	y->parent = x->parent;
	x->parent = y;
	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
	while(x->parent != 0){

		if(x->parent->value == root->value){
			if(x->parent->left && x->parent->left->value == x->value){
				rot_right(x->parent);
			}else{
				rot_left(x->parent);
			}
		}else{
			Node<T>*p = x->parent; // parent
			Node<T>*g = p->parent; // granparent
			if(p->left && g->left &&
				x->value == p->left->value && p->value == g->left->value){
				rot_right(g);
				rot_right(p);
			}else if(p->right && g->right &&
				x->value == p->right->value && p->value == g->right->value){
				rot_left(g);
				rot_left(p);
			}else	if(p->left && g->right &&
				x->value == p->left->value && p->value == g->right->value){
				rot_right(p);
				rot_left(g);
			}else{
				rot_left(p);
				rot_right(g);
			}
		}
	}
	return x;
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void Node<T>::print_tree(std::stringstream &aux) const {
	if (parent != 0){
		aux << "\n node " << value;
		aux << " parent " << parent->value;
	}else
		aux << "\n root " << value;
	if (left != 0)
		aux << " left " << left->value;
	if (right != 0)
		aux << " right " << right->value;
	aux << "\n";

	if (left != 0) {
		left->print_tree(aux);
	}
	if (right != 0) {
		right->print_tree(aux);
	}
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
class SplayTree {
private:
	Node<T> *root;

public:
	SplayTree();
	~SplayTree();
	bool empty() const;
	void add(T);
	bool find(T);
	void remove(T);
	void removeAll();
	Node<T>* getRoot() {return &root;}
	std::string inorder() const;
	std::string print_tree() const;
	std::string preorder() const;
};

template <class T>
SplayTree<T>::SplayTree() : root(0) {}

template <class T>
SplayTree<T>::~SplayTree() {
	removeAll();
}

template <class T>
bool SplayTree<T>::empty() const {
	return (root == 0);
}

template<class T>
void SplayTree<T>::add(T val) {
	if (root != 0) {
		Node<T>* added = root->add(val);
		root = root->splay(root,added);
	} else {
		root = new Node<T>(val);
	}
}

template <class T>
void SplayTree<T>::remove(T val) {
    if (root != nullptr) {
        Node<T>* nodeToRemove = root->find(val);
        if (nodeToRemove != nullptr) {
            if (nodeToRemove->left != nullptr && nodeToRemove->right != nullptr) {
                Node<T>* succ = nodeToRemove->succesor();
                nodeToRemove->value = succ->value;
                nodeToRemove = succ;
            }
			Node<T>* parent = nodeToRemove->parent;
            Node<T>* child = (nodeToRemove->left != nullptr) ? nodeToRemove->left : nodeToRemove->right;

            if (nodeToRemove->parent != nullptr) {
                if (nodeToRemove == nodeToRemove->parent->left) {
                    nodeToRemove->parent->left = child;
                } else {
                    nodeToRemove->parent->right = child;
                }
                if (child != nullptr) {
                    child->parent = nodeToRemove->parent;
                }
                Node<T>* newRoot = nodeToRemove->splay(root, parent); // Llama a splay a través de nodeToRemove
                root = newRoot;
            } else {
                root = child;
                if (child != nullptr) {
                    child->parent = nullptr;
                }
            }
            delete nodeToRemove;
        }
    }
}


template <class T>
void SplayTree<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

template <class T>
bool SplayTree<T>::find(T val){
	if (root != 0) {
		Node<T>* found = root->find(val);
		root = root->splay(root,found);
		return (root->value == val);
	} else {
		return false;
	}
}

template <class T>
std::string SplayTree<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string SplayTree<T>::print_tree() const {
	std::stringstream aux;

	aux << "\n ================================ ";
	if (!empty()) {
		root->print_tree(aux);
	}
	aux << " ================================ \n";
	return aux.str();
}



template <class T>
std::string SplayTree<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

#endif