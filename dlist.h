#ifndef DLIST_H_
#define DLIST_H_
#include <string>
#include <sstream>

template <class T> class DList;

/* Clase DLink */
template <class T>
class DLink { // Clase nodo
private:
    T value;
    DLink<T> *previous;
    DLink<T> *next;

    DLink(T val) : value(val), previous(nullptr), next(nullptr) {}
    DLink(T val, DLink<T> *prev, DLink<T> *nxt) : value(val), previous(prev), next(nxt) {}
    DLink(const DLink<T> &source) : value(source.value), previous(source.previous), next(source.next) {}

    friend class DList<T>;
};

/* Clase DList */
template <class T>
class DList {
public:
    DList();
    DList(const DList<T> &);
    ~DList();

    std::string toStringForward() const;
    std::string toStringBackward() const;
    void insertion(T); //Método que agrega un objeto a la lista
    void addFirst(T); //Método que agrega un objeto al inicio de la lista
    bool empty() const; //Método que checa si esta vacio 
    int search(T); //Método para buscar un objeto y regresar el indice 
    void update(T, T); //Método para cambiar el valor de un objeto
    void deleteAt(T); //Método que borra un elemento 
    void clear(); //Método para vaciar un elemento 

private:
    DLink<T> *head;
    DLink<T> *tail;
    int size;

};

/* Métodos DList */
template <class T>
DList<T>::DList() : head(nullptr), tail(nullptr), size(0) {}

template <class T>
DList<T>::~DList() {
    clear();
}

template <class T>
bool DList<T>::empty() const {
    return (head == nullptr && tail == nullptr);
}

template <class T>
void DList<T>::update(T index, T val) {
    DLink<T> *p;
    int auxc = 0;
    p = head;
    while (auxc < index) {
        p = p->next;
        auxc++;
    }
    p->value = val;
}

template <class T>
int DList<T>::search(T val) {
    DLink<T> *p;
    int auxc = 0;
    p = head;
    while (p != nullptr) {
        if (p->value == val) {
            return auxc;
        }
        auxc++;
        p = p->next;
    }
    return -1;
}

template <class T>
void DList<T>::deleteAt(T index) {
    DLink<T> *p, *q;
    int auxc = 0;

    if (index == 0) {
        p = head;
        head = p->next;
        if (head != nullptr) {
            head->previous = nullptr;
        } else {
            tail = nullptr;
        }
        delete p;
    } else {
        p = head;
        while (auxc < index) {
            q = p;
            p = p->next;
            auxc++;
        }
        q->next = p->next;
        if (p->next != nullptr) {
            p->next->previous = q;
        } else {
            tail = q;
        }
        delete p;
    }
    size--;
}

template <class T>
void DList<T>::addFirst(T val) {
    DLink<T> *newDLink;
    newDLink = new DLink<T>(val);
    if (empty()) {
        newDLink->next = head;
        head = newDLink;
        tail = newDLink;
        size++;
    } else {
        newDLink->next = head;
        head->previous = newDLink;
        head = newDLink;
        size++;
    }
}

template <class T>
void DList<T>::clear() {
    DLink<T> *p, *q;
    p = head;
    while (p != nullptr) {
        q = p->next;
        delete p;
        p = q;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <class T>
DList<T>::DList(const DList<T> &source) {
    DLink<T> *p, *q;
    if (source.empty()) {
        size = 0;
        head = nullptr;
        tail = nullptr;
    } else {
        p = source.head;
        head = new DLink<T>(p->value);
        q = head;
        p = p->next;
        while (p != nullptr) {
            q->next = new DLink<T>(p->value, q, nullptr);
            p = p->next;
            q = q->next;
        }
        size = source.size;
    }
}

template <class T>
void DList<T>::insertion(T val) {
    DLink<T> *newDLink, *p;
    newDLink = new DLink<T>(val);
    if (empty()) {
        addFirst(val);
    } else {
        tail->next = newDLink;
        newDLink->previous = tail;
        tail = newDLink;
    }
    size++;
}

template <class T>
std::string DList<T>::toStringForward() const {
    std::stringstream aux;
    DLink<T> *p;
    p = head;
    aux << "[";
    while (p != nullptr) {
        aux << p->value;
        if (p->next != nullptr) {
            aux << ", ";
        }
        p = p->next;
    }
    aux << "]";
    return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward() const {
    std::stringstream aux;
    DLink<T> *p;
    p = tail;
    aux << "[";
    while (p != nullptr) {
        aux << p->value;
        if (p->previous != nullptr) {
            aux << ", ";
        }
        p = p->previous;
    }
    aux << "]";
    return aux.str();
}

#endif