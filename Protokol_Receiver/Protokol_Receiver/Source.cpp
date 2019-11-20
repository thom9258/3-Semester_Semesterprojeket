// STRING VECTOR EXAMPLE 
// CPP program to illustrate 
// Implementation of begin() function 
#include <iostream> 
#include <string> 
#include <vector> 
using namespace std;

int r(vector<int> v1, int n);//Claus: dette behøves ikke
int r(vector<int> v1, int n) {

	//Claus: .begin() bruges til at finde begyndelsen på en vektor .end() bruges til at finde enden af en vektor
	// using begin() to print vektor 
	for (auto it = v1.begin(); //Claus: it bliver til en adresse til vektorens begyndelse
		it != v1.end(); ++it) //Claus: mens it ikke er nået til slutningen af vektoren; incrementeres pointeren
		cout << ' ' << *it; //Claus: it bliver derefrenceret og bliver til værdien der er i adressen, og bliver printet ud.
	//Claus: alternativ kan man bruge v1[0] for at få den første værdi i vektoren (i stedet for at få adressen til den første værdi (aka. en pointer))
	//Claus: .size(); kan bruges til at finde hvor mange elementer der er i vektoren (aka. størrelsen)
};

//Claus: for at definere en funktion skal man skrive følgende
//returnType navnPåFunktion(type argument1, type argument2){
//whatever funktionen nu skal gøre
//}

//Claus: altid skriv main til sidst, det gør det hele lidt nemmere
int main()
{
	
	cout << "it works" << endl;
	return 0;
}
