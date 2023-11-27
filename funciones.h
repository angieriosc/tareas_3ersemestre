#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <iostream>
#include <sstream> //para el uso de strngstream y aux 
#include <string>
using namespace std;

class Funciones{

public: 
  //Constuctor inicial
  Funciones(){};

  // Metodos miembros de la clase
  long sumaIterativa(int);
  long sumaRecursiva(int);
  long sumaDirecta(int);
};


long Funciones:: sumaIterativa(int n) {
	long acum = 0;
	for (int i = 1; i <= n; i++) {
		acum += i;
	}
	return acum;
}

long Funciones:: sumaRecursiva(int n) {
	if (n==0){
		return 0;
	} 
    else {
        if (n <= 1) {
		    return 1;
	    } else {
		    return n + sumaRecursiva(n - 1);
	     }
    }
}
//Para realizar la función de suma directa se utiliza una formula matemática.
long Funciones:: sumaDirecta(int n) {
    return n * (n + 1) / 2;
}

#endif /* FUNCIONES_H_ */