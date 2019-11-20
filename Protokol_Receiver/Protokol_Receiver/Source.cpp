// STRING VECTOR EXAMPLE 
// CPP program to illustrate 
// Implementation of begin() function 
#include <iostream> 
#include <string> 
#include <vector> 
using namespace std;

int r(vector<int> v1, int n);//Claus: dette beh�ves ikke
int r(vector<int> v1, int n) {

	//Claus: .begin() bruges til at finde begyndelsen p� en vektor .end() bruges til at finde enden af en vektor
	// using begin() to print vektor 
	for (auto it = v1.begin(); //Claus: it bliver til en adresse til vektorens begyndelse
		it != v1.end(); ++it) //Claus: mens it ikke er n�et til slutningen af vektoren; incrementeres pointeren
		cout << ' ' << *it; //Claus: it bliver derefrenceret og bliver til v�rdien der er i adressen, og bliver printet ud.
	//Claus: alternativ kan man bruge v1[0] for at f� den f�rste v�rdi i vektoren (i stedet for at f� adressen til den f�rste v�rdi (aka. en pointer))
	//Claus: .size(); kan bruges til at finde hvor mange elementer der er i vektoren (aka. st�rrelsen)
};

//Claus: for at definere en funktion skal man skrive f�lgende
//returnType navnP�Funktion(type argument1, type argument2){
//whatever funktionen nu skal g�re
//}

//Claus: altid skriv main til sidst, det g�r det hele lidt nemmere
int main()
{
	
	cout << "it works" << endl;
	return 0;
}
