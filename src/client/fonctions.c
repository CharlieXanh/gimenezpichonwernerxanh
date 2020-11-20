#include "fonctions.h"

/* Fonction hello
 * Affiche "hello" suivi d'un retour à la ligne
 */
void hello(){
	printf("hello");
	printf("\n");
}

/* Fonction dispInt
 * Affiche le nombre entier donné en argument suivi d'un retour à la ligne
 */
void dispInt(int x){
	printf("%d\n",x);
}

/* Fonction parite
 * Teste si l'entier nommé a donné en argument est pair ou impair.
 * Affiche pair si a est pair, impair dans le cas contraire.
 */
void parite(int a){
	if(a%2 == 0){
		printf("pair\n");
	}
	else{
		printf("impair\n");
	}
}

/* Fonction sumN
 * Calcule la somme des N+1 premiers entiers (de 0 à N, entier donné en argument).
 * Renvoie le résultat.
 */
int sumN(int N){
	int i=0, sum=0;
	for(i=0;i<N;i++){
		sum = sum + i;
	}
	return sum;
}

/* Fonction signe
 */
void signe(int a){
	/*A COMPLETER*/
}

/* Fonction factorielle
 */
int fact(int N){
	/*A COMPLETER*/
}