#ifndef LIST_H_
#define LIST_H_
#include <string>
#include <sstream>

template <class T> class List;
/*----------------------Clase Link----------------------------*/
template <class T>
class Link { //Clase nodo
private:
	Link(T);// Constructor con un valor
	Link(T, Link<T>*); //Constructor con valor y apuntador
	Link(const Link<T>&); //Constructor para copiarlo

	T value;
	Link<T> *next;

	friend class List<T>; //friend permite a otras clases utilizar las funciones de su clase friend
};
/*-----------------------Métodos Link---------------------------------*/
template <class T>
Link<T>::Link(T val): value (val), next(0) {}

template <class T>
Link<T>::Link(T val, Link* nxt): value(val), next(nxt) {}

template <class T>
Link<T>::Link(const Link<T> &source):value(source.value),next(source.next) {}

/*------------------------Clase List-----------------------------*/

template <class T>
class List{
    public:

    List();
    List(const List<T>&);
    ~List();

    std::string toString() const;
    void insertion(T);
    void addFirst(T);
    bool empty()const;
    int search(T);
    void update(T,T);
    void deleteAt(T);
    void clear();
    
    
    private:
    Link<T> * head;
    int size;
};

/*---------------------------Métodos List----------------------------------*/

template <class T>
void List<T>::update(T index, T val)  {
    Link<T> *p;
    int auxc=0;
    p=head;
    while(auxc<index){
        p=p->next;
        auxc++;
    }
    p->value=val;
}

template <class T>
int List<T>::search(T val)  {
    	Link<T> *p;
        int auxc=0;
	p=head;
	while(p!=0){
		if (p->value==val){
			return auxc;
		}
        auxc++;
		p=p->next;
	}
	return -1;

}

template <class T>
void List<T>::deleteAt(T index)  {
    Link<T> *p,*q;
    int auxc=0;

    if (index==0){
        p=head;
	    head=p->next;
	    delete p;
	    size--;
        return;
    }
    
    p=head;
    while(auxc<index){
        q=p;
        p=p->next;
        auxc++;
    }
    q->next=p->next;
    delete p;
    size--;
    return;
}

template <class T>
void List<T>::addFirst(T val)  {
	Link <T> *newLink;
	newLink= new Link<T>(val);
	newLink->next = head;
	head=newLink;
	size++;
}

template <class T>
List<T>::List(){
	head=0;
	size=0;
}

template <class T>
void List<T>::clear() {
	Link<T> *p, *q;
	p=head;
	while(p!=0){
		q=p->next;
		delete p;
		p=q;
	}
	head = 0;
	size=0;
}

template <class T>
List<T>::~List() {clear();}

template <class T>
List<T>::List(const List<T> &source)  {
	Link<T> *p, *q;
	if (source.empty()){
		head=0;
		size=0;
	}else {
		p =source.head;
		head=new Link<T> (p->value);
		q=head;

		p=p->next;
		while(p!=0){
			q->next=new Link<T>(p->value);
			p=p->next;
			q=q->next;
		}
		size=source.size;
	}
}

template <class T>
void List<T>::insertion(T val){
    Link<T> *newLink;
	Link<T> *p;
	newLink= new Link<T>(val);
	if (empty()){
		addFirst(val);
		return;
	}
	p=head;
	while (p->next !=0){
		p=p->next;
	}
	newLink->next=0;
	p->next=newLink;
	size++;
}
template <class T>
bool List<T>::empty() const {
	return (head==0);
}


template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

#endif