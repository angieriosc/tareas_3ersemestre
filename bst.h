#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include "bst.h"

template <class T> class BST;

template <class T>
class Node {
private:
    T value;
    Node<T>* left;
    Node<T>* right;


public:
    Node(T);
    Node(T, Node<T>*, Node<T>*);
    void add(T);
    bool find(T);
    void remove(T);
    void removeChilds();
    void inorder(std::stringstream&) const;
    void preorder(std::stringstream&) const;
    Node<T> *successor();
    void removeChildren();
    void postorder(std::stringstream &) const;
    void levelbylevel(std::stringstream&) const;

    friend class BST<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(nullptr), right(nullptr) {}

template <class T>
Node<T>::Node(T val, Node<T>* le, Node<T>* ri) : value(val), left(le), right(ri) {}

template <class T>
void Node<T>::add(T val) {
    if (val < value) {
        if (left != nullptr) {
            left->add(val);
        } else {
            left = new Node<T>(val);
        }
    } else if (val > value) {
        if (right != nullptr) {
            right->add(val);
        } else {
            right = new Node<T>(val);
        }
    }
}

template <class T>
bool Node<T>::find(T val) {
    if (val == value) {
        return true;
    } else if (val < value && left != nullptr) {
        return left->find(val);
    } else if (val > value && right != nullptr) {
        return right->find(val);
    }
    return false;
}

template <class T>
Node<T>* Node<T>::successor() {
    Node<T>* le = left;
    Node<T>* ri = right;

    if (left == nullptr) {
        if (right != nullptr) {
            right = nullptr;
        }
        return ri;
    }

    if (left->right == nullptr) {
        left = left->left;
        le->left = nullptr;
        return le;
    }

    Node<T>* parent = left;
    Node<T>* child = left->right;
    while (child->right != nullptr) {
        parent = child;
        child = child->right;
    }
    parent->right = child->left;
    child->left = nullptr;
    return child;
}

template <class T>
void Node<T>::remove(T val) {
    Node<T>* succ;
    Node<T>* old;

    if (val < value && left != nullptr) {
        if (left->value == val) {
            old = left;
            succ = left->successor();
            if (succ != nullptr) {
                succ->left = old->left;
                succ->right = old->right;
            }
            left = succ;
            delete old;
        } else {
            left->remove(val);
        }
    } else if (val > value && right != nullptr) {
        if (right->value == val) {
            old = right;
            succ = right->successor();
            if (succ != nullptr) {
                succ->left = old->left;
                succ->right = old->right;
            }
            right = succ;
            delete old;
        } else {
            right->remove(val);
        }
    }
}

template <class T>
void Node<T>::removeChildren() {
    if (left != nullptr) {
        left->removeChildren();
        delete left;
        left = nullptr;
    }
    if (right != nullptr) {
        right->removeChildren();
        delete right;
        right = nullptr;
    }
}

template <class T>
void Node<T>::inorder(std::stringstream& aux) const {
    if (left != nullptr) {
        left->inorder(aux);
    }
    if (aux.tellp() != 1) {
        aux << " ";
    }
    aux << value;
    if (right != nullptr) {
        right->inorder(aux);
    }
}

template <class T>
void Node<T>::preorder(std::stringstream& aux) const {
    aux << value;
    if (left != nullptr) {
        aux << " ";
        left->preorder(aux);
    }
    if (right != nullptr) {
        aux << " ";
        right->preorder(aux);
    }
}

template <class T>
void Node<T>::postorder(std::stringstream& aux) const {
    if (left != nullptr) {
        left->postorder(aux);
        aux << " ";
    }
    if (right != nullptr) {
        right->postorder(aux);
        aux << " ";
    }
    aux << value;
}

template <class T>
void Node<T>::levelbylevel(std::stringstream& aux) const {
    std::queue<Node<T>*> nodesQueue;
    nodesQueue.push(const_cast<Node<T>*>(this)); // Agregar el nodo raíz a la cola

    while (!nodesQueue.empty()) {
        Node<T>* current = nodesQueue.front();
        nodesQueue.pop();
        if (aux.tellp() != 1){
            aux << " ";
        }
        aux << current->value; // Imprimir el valor del nodo actual

        // Agregar los nodos hijos a la cola si existen
        if (current->left != nullptr) {
            nodesQueue.push(current->left);
        }
        if (current->right != nullptr) {
            nodesQueue.push(current->right);
        }
    }
}



template <class T>
class BST {
private:
    Node<T>* root;
    int heightAux(Node<T>* node) const;
    void ancestorsAux(Node<T>* node, T val, std::stringstream& result) const;
    int whatLevelAmIAux(Node<T>* node, T val, int level) const;

public:
    BST();
    ~BST();
    bool empty() const;
    void add(T val);
    bool find(T val) const;
    void remove(T val);
    void removeAll();
    std::string inorder() const;
    std::string preorder() const;
    std::string postorder() const;
    std::string levelByLevel() const;
    std::string visit();
    int height() const;
    std::string ancestors(T val) const;
    int whatlevelamI(T val) const;
};

template <class T>
BST<T>::BST() : root(nullptr) {}

template <class T>
BST<T>::~BST() {
    removeAll();
}

template <class T>
bool BST<T>::empty() const {
    return (root == nullptr);
}

template <class T>
void BST<T>::add(T val) {
    if (root != nullptr) {
        if (!root->find(val)) {
            root->add(val);
        }
    } else {
        root = new Node<T>(val);
    }
}

template <class T>
void BST<T>::remove(T val) {
    if (root != nullptr) {
        if (val == root->value) {
            Node<T>* succ = root->successor();
            if (succ != nullptr) {
                succ->left = root->left;
                succ->right = root->right;
            }
            delete root;
            root = succ;
        } else {
            root->remove(val);
        }
    }
}

template <class T>
void BST<T>::removeAll() {
    if (root != nullptr) {
        root->removeChildren();
    }
    delete root;
    root = nullptr;
}

template <class T>
bool BST<T>::find(T val) const {
    if (root != nullptr) {
        return root->find(val);
    }
    return false;
}

template <class T>
std::string BST<T>::inorder() const {
    std::stringstream aux;
    aux << "[";
    if (!empty()) {
        root->inorder(aux);
    }
    aux << "]";
    return aux.str();
}

template <class T>
std::string BST<T>::preorder() const {
    std::stringstream aux;
    aux << "[";
    if (!empty()) {
        root->preorder(aux);
    }
    aux << "]";
    return aux.str();
}

template <class T>
std::string BST<T>::postorder() const {
    std::stringstream aux;
    aux << "[";
    if (!empty()) {
        root->postorder(aux);
    }
    aux << "]";
    return aux.str();
}

template <class T>
std::string BST<T>::levelByLevel() const {
    std::stringstream aux;
    aux << "[";
    if (!empty()) {
        root->levelbylevel(aux);
    }
    aux << "]";
    return aux.str();
}

template <class T>
std::string BST<T>::visit(){
    std::stringstream result;
    result << preorder();
    result << "\n";
    result << inorder();
    result << "\n";
    result << postorder();
    result << "\n";
    result << levelByLevel();
    return result.str();

}


template <class T>
int BST<T>::height() const {
    return heightAux(root);
}

template <class T>
int BST<T>::heightAux(Node<T>* node) const {
    if (node == nullptr) {
        return 0;
    } else {
        int leftHeight = heightAux(node->left);
        int rightHeight = heightAux(node->right);
        return std::max(leftHeight, rightHeight) + 1;
    }
}

template <class T>
std::string BST<T>::ancestors(T val) const {
    std::stringstream result;
    result << "[";
    ancestorsAux(root, val, result);
    result << "]";
    return result.str();
}

template <class T>
void BST<T>::ancestorsAux(Node<T>* node, T val, std::stringstream& result) const {
    if (node == nullptr) {
        result <<"[]";
    }

    if (node->find(val)) {
        if (node->value != val) {
            if (result.tellp() != 1){
                result << " ";
            }
            result << node->value;

        }
        if (val < node->value) {
            ancestorsAux(node->left, val, result);
        } else if (val > node->value) {
            ancestorsAux(node->right, val, result);
        }
    }
}

template <class T>
int BST<T>::whatlevelamI(T val) const {
    return whatLevelAmIAux(root, val, 1);
}

template <class T>
int BST<T>::whatLevelAmIAux(Node<T>* node, T val, int level) const {
    if (node == nullptr) {
        return 0;
    }

    if (node->value == val) {
        return level;
    } else if (val < node->value) {
        return whatLevelAmIAux(node->left, val, level + 1);
    } else {
        return whatLevelAmIAux(node->right, val, level + 1);
    }
}

#endif /* BST_H_ */
