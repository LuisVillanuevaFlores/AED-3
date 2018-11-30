#include <iostream>
using namespace std;

struct nodo
{
	int fila;
	int columna;
	int valor;
	nodo *siguiente;
	nodo(){
		siguiente=NULL;
	}

};

class matrizsp
{
	nodo *inicio;
public:
	matrizsp(){inicio=NULL;}
	void insertar(int f,int c,int v){
		nodo *nuevo=new nodo;
		nuevo->fila=f;nuevo->columna=c;nuevo->valor=v;
		if(inicio==NULL){
			inicio=nuevo;
			return;
		}
		nodo *auxiliar=inicio;
		while(auxiliar!=NULL){
            if(auxiliar->fila==f && auxiliar->columna==c ){
                auxiliar->valor=v;
                //auxiliar=auxiliar->siguiente;
                return;
            }
            auxiliar=auxiliar->siguiente;



		}
		nodo *aux=inicio;
		while(aux->siguiente!=NULL){
			aux=aux->siguiente;

		}
		aux->siguiente=nuevo;

	}

	void imprimir(){
		nodo *auxfi=inicio;
		nodo *auxco=inicio;
		nodo* auxva=inicio;
		cout<<"FILAS: ";
		while(auxfi!=NULL){
			cout<<auxfi->fila<<" ";
			auxfi=auxfi->siguiente;
		}
		cout<<endl;
		cout<<"COLUMNAS: ";
		while(auxco!=NULL){
			cout<<auxco->columna<<" ";
			auxco=auxco->siguiente;

		}
		cout<<endl;
		cout<<"VALORES: ";
		while(auxva!=NULL){
			cout<<auxva->valor<<" ";
			auxva=auxva->siguiente;

		}
		cout<<endl;

	}
	matrizsp sumar(matrizsp A,matrizsp B){
		matrizsp C;
		nodo *aux1=A.inicio;
		nodo *aux2=B.inicio;
		while(aux1!=NULL){
			if(aux1->fila == aux2->fila && aux1->columna==aux2->columna ){
					C.insertar(aux1->fila,aux1->columna,aux1->valor+aux2->valor);
			}

			aux1=aux1->siguiente;
			aux2=aux2->siguiente;

		}
		return C;


	}




};

int main(){

matrizsp M,C;

int sparseMatric[4][5] =
    {
        {0 , 0 , 3 , 0 , 4 },
        {0 , 0 , 5 , 7 , 0 },
        {0 , 0 , 0 , 0 , 0 },
        {0 , 2 , 6 , 0 , 0 }
    };





  for(int i=0;i<4;i++){
  		for(int j=0;j<5;j++){
  			if(sparseMatric[i][j]!=0){
  				M.insertar(i,j,sparseMatric[i][j]);
  			}

  		}

  }

  M.imprimir();
  cout<<endl;
  C=M.sumar(M,M);
  C.imprimir();
  cout<<endl;
M.insertar(0,0,3);
M.imprimir();
cout<<endl;
M.insertar(0,0,5);
M.imprimir();
cout<<endl;
M.insertar(1,3,6);
M.imprimir();
  /*
  M.insertar(0,0,1);
  M.insertar(0,1,2);
   M.insertar(0,2,6);
  M.imprimir();
  M.insertar(0,0,6);
   M.insertar(0,1,3);
  cout<<endl;
  M.imprimir();
  */
 return 0;


}
