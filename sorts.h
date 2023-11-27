//Angélica Ríos CUentas
#ifndef SORTS_H
#define SORTS_H

#include <vector>
#include <algorithm>
using namespace std;

template<typename T>

//Se crea clase sorts con los metodos a realizar
class Sorts {
private:
    void swap(vector<T>&, int, int);
    void copyArray(vector<T>&, vector<T>&, int , int);
    void mergeSplit(vector<T>&, vector<T>&, int , int);
    void mergeArray(vector<T>&, vector<T>&, int, int, int);
public:
    Sorts() {};
    vector<T> ordenaMerge(vector<T>&);
    vector<T> ordenaSeleccion(vector<T>& );
    vector<T> ordenaBurbuja(vector<T>& );
    int busqSecuencial(vector<T>, int);
    int busqBinaria(vector<T> , int );

};

template <class T>
void Sorts<T>::swap(vector<T> &vec, int i, int j) {
	T aux = vec[i];
	vec[i] = vec[j];
	vec[j] = aux;
}

template <class T>
vector<T> Sorts<T>::ordenaSeleccion(vector<T> &vec){
	int min;
	for (int j = 0; j < vec.size() - 1; j++) {
		min = j;
		for (int i = vec.size() - 1; i >= j; i--) {
			if (vec[i] < vec[min]) {
				min = i;
			}
		}
		if (min != j) {
			swap(vec, j, min);
		}
	}
	return vec;
}


template <class T>
vector<T> Sorts<T>::ordenaBurbuja(vector<T>& vec){
    for(int i = vec.size() - 1; i > 0 ; i--){
        for(int j = 0; j < i; j++ ){
            if(vec[j] > vec[j+1]){
                swap(vec, j,j+1);
            }
        }
    }
	return vec;
}

template <class T>
void Sorts<T>::copyArray(vector<T> &A, vector<T> &B, int low, int high){
    for(int i = low; i <= high; i++ ){
        A[i] = B[i];
    }
}

template <class T>
void Sorts<T>::mergeArray(vector<T> &A, vector<T> &B, int low, int mid, int high){
    int i = low, k = low, j = mid + 1;

    while(i <= mid && j <= high){
        if(A[i] < A[j]){
            B[k] = A[i];
            i++;
        }else{
            B[k] = A[j];
            j++;
        }
        k++;
    }
    if(i > mid){
        for(; j <= high ; j++){
            B[k++] = A[j];
        }
    }else{
        for(; i <= mid ; i++){
            B[k++] = A[i];
        }
    }

}

template <class T>
void Sorts<T>::mergeSplit(vector<T> &A, vector<T> &B, int low, int high){
    int mid;

    if((high - low) < 1){
        return;
    }
    mid = (high + low) / 2;
    mergeSplit(A,B,low,mid);
    mergeSplit(A,B,mid+1,high);
    mergeArray(A,B,low,mid,high);
    copyArray(A,B,low,high);
}

template<class T>
vector<T> Sorts<T>::ordenaMerge(vector<T> &vec){
    vector<T> tmp(vec.size());

    mergeSplit(vec,tmp,0,vec.size()-1);
	return vec;
}

template <class T>
int Sorts<T>::busqSecuencial(vector<T> arr,int val){

    for(int j = 0; j < arr.size(); j++){
        if(arr[j] == val){
            return j;
        }
    }
    return -1;
}

template <class T>
int Sorts<T>::busqBinaria(vector<T> arr, int val){
    int low = 0; 
    int high = arr.size() - 1;

    while(low <= high){
        int mid = (high + low) / 2;
        if(arr[mid] == val){
            return mid;
        }
        if(arr[mid] < val){
            low = mid + 1;
        }else{
            high = mid - 1;
        }
    }
    return -1;
}

#endif