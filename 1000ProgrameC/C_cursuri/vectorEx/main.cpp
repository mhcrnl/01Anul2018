#include <iostream>

using namespace std;

void AfisareVector(int arg[], int numarElemente){
    for(int i=0; i<numarElemente; i++){
        cout << arg[i] << ' ';
    }
}

int main()
{
    cout << " Hello world! Vector " << endl;
    //Declararea unui vector (array) initializat cu valori de tip int
    int vectorInt[] = { 1,2,3,4,5,6,7,8,9,10};
    cout << "Elementul de pe pozitia vectorInt[0] este: " << vectorInt[0] <<endl;
    cout << "Elementul de pe pozitia vectorInt[9] este: " << vectorInt[9] <<endl;
    //Afisarea unui vector cu n elemente
    int n = 10 ; //numarul de elemente din vector
    for(int i =0; i<n;i++){
        cout << vectorInt[i] << ' ';
    }
    cout << endl;
    //Afisarea unui vector cu o functie
    AfisareVector(vectorInt, 10);

    return 0;
}
