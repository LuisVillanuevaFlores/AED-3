#include <iostream>
#include <vector>
using namespace std;


template <class T>

class nodo
{
public:
	int fila;
	int columna;
	T valor;
	nodo<T>*pfila,*pcolumna;
	nodo(int fila= 0,int columna=0,T valor=0):fila(fila),columna(columna),valor(valor),pfila(NULL),pcolumna(NULL){};

};
template <class T>
class matriz_sparse{
public:
	vector<nodo<T>* >filas;
	vector<nodo<T>* >columnas;
	int nfilas;int ncolumnas;

	matriz_sparse(int f,int c){
		filas.resize(f);
		columnas.resize(c);
		nfilas=f;ncolumnas=c;
	}


	void put(int f,int c,T val){
		nodo<T>*nuevo=new nodo<T>(f,c,val);
		if(filas[f]==NULL){
			filas[f]=nuevo;
		}
		else{
			nodo<T> *aux=filas[f];
			nodo<T> *aux2=aux;
			while(aux!=NULL && c>aux->columna){
				aux2=aux;
				aux=aux->pfila;
			}
			if(aux==NULL){
            aux2->pfila=nuevo;}

            else if(aux==filas[f]){
            	nuevo->pfila=aux;
            	filas[f]=nuevo;
       		 }
			else{
				if(aux->columna==c){aux->valor=val;}
				else{
					aux2->pfila=nuevo;
					nuevo->pfila=aux;
				}
			}

		}
		if(columnas[c]==NULL){
			columnas[c]=nuevo;
		}
		else{
			nodo<T> *a=columnas[c];
			nodo<T> *a2=a;
			while(a!=NULL && f>a->fila){
				a2=a;
				a=a->pcolumna;
			}
			if(a==NULL){a2->pcolumna=nuevo;}
			else if(a==columnas[c]){
            	nuevo->pcolumna=a;
            	columnas[c]=nuevo;
       		 }
			else{
				if(a->fila==f){a->valor=val;}
				else{
					a2->pcolumna=nuevo;
					nuevo->pcolumna=a;
				}
			}

		}


	}

	void printfila(int f){
		nodo<T> *aux=filas[f];
		while(aux!=NULL){
			cout<<aux->valor<<" ";
			//cout<<aux->pfila<<"*";
			aux=aux->pfila;
		}
		cout<<endl;

    }
    void printcol(int c){
		nodo<T> *aux=columnas[c];
		while(aux!=NULL){
			cout<<aux->valor<<" ";
			aux=aux->pcolumna;
		}
		cout<<endl;
    }

    void makezero(int r,int c){

    	nodo<T>*nuevo=new nodo<T>(r,c,0);
		if(filas[r]==NULL){
			filas[r]=nuevo;
		}
		else{
			nodo<T> *aux=filas[r];
			nodo<T> *aux2=aux;
			while(aux!=NULL && c>aux->columna){
				aux2=aux;
				aux=aux->pfila;
			}
			if(aux==NULL){
            aux2->pfila=nuevo;}
			else{
				if(aux->columna==c){aux->valor=0;}
				else{
					aux2->pfila=nuevo;
					nuevo->pfila=aux;
				}
			}

		}
		if(columnas[c]==NULL){
			columnas[c]=nuevo;
		}
		else{
			nodo<T> *a=columnas[c];
			nodo<T> *a2=a;
			while(a!=NULL && r>a->fila){
				a2=a;
				a=a->pcolumna;
			}
			if(a==NULL){a2->pcolumna=nuevo;}
			else{
				if(a->fila==r){a->valor=0;}
				else{
					a2->pcolumna=nuevo;
					nuevo->pcolumna=a;
				}
			}

		}
	}

	bool iszero(int f,int c){
		nodo<T>*aux=filas[f];
		while(aux!=NULL && aux->columna!=c){
			aux=aux->pfila;
		}
		if(aux==NULL){return false;}
		if(aux->columna==c){
			if(aux->valor==0){return true;}
			return false;
		}
		nodo<T>*a=columnas[c];
		while(a!=NULL && a->fila!=f){
			a=a->pcolumna;
		}
		if(a==NULL){return false;}
		if(a->fila==f){
			if(a->valor==0){return true;}
			return false;
		}

	}

	T get( int f, int c ) {
		nodo<T>*aux=filas[f];
		while(aux!=NULL && aux->columna!=c){
			aux=aux->pfila;
		}
		if(aux==NULL){return -99999;}
		if(aux->columna==c){
			return aux->valor;
		}
		nodo<T>*a=columnas[c];
		while(a!=NULL && a->fila!=f){
			a=a->pcolumna;
		}
		if(a==NULL){return -999999;}
		if(a->fila==f){
			return a->valor;
		}


	}


	void prueba(){
		int a,b;
		for(int i=0;i<filas.size();i++){
			if(filas[i]!=NULL){
				a=i;
				break;
			}
		}
		cout<<a<<endl;
		for(int i=0;i<columnas.size();i++){
			if(columnas[i]!=NULL){
				b=i;
				break;
			}
		}

		cout<<b<<endl;



	}

	matriz_sparse<T> operator+( const matriz_sparse & rhs ) {
	nodo<T>*aux,*aux2;

    if(rhs.nfilas==nfilas&&rhs.ncolumnas==ncolumnas){
        matriz_sparse<T> temp(*this);
        for(int i=0;i<nfilas;i++){
            aux=temp.filas[i];
            aux2=rhs.filas[i];
            while(aux2!=NULL){
                //cout<<"i"<<i<<endl;
                if(aux==NULL||aux->columna>aux2->columna){
                    //cout<<"caso 1"<<endl;
                    temp.put(aux2->fila,aux2->columna,aux2->valor);
                    aux2=aux2->pfila;
                }
                else if(aux->columna==aux2->columna){
                    //cout<<"caso 2"<<endl;
                    aux->valor+=aux2->valor;
                    aux2=aux2->pfila;
                    aux=aux->pfila;

                }
                else if(aux->columna<aux2->columna){
                   //cout<<"caso 3"<<endl;
                    aux=aux->pfila;
                }
            }
        }
        return temp;
    }
    else
        cout<<"No se puede realizar la suma"<<endl;
}

	bool operator==( const matriz_sparse & rhs ) {
		nodo<T>*aux,*aux2;
		if(rhs.nfilas==nfilas&&rhs.ncolumnas==ncolumnas){
				//cout<<"A"<<endl;
				matriz_sparse<T> temp(*this);
				for(int i=0;i<nfilas;i++){
					//cout<<i<<endl;
					aux=temp.filas[i];
            		aux2=rhs.filas[i];	
            		
            		while(aux!=NULL&& aux2!=NULL){
            		if(aux->pfila!=NULL && aux2->pfila==NULL || aux->pfila==NULL && aux2->pfila!=NULL){return false;}
            		else if(aux->valor!=aux2->valor){
            		//cout<<"c"<<endl;
            		return false;}

            		else if(aux==NULL && aux2!=NULL){
            		//cout<<"d"<<endl;
            		return false;}

            		else if(aux->valor == aux2->valor){
            			//cout<<"e"<<endl;
            			aux=aux->pfila;
            			aux2=aux2->pfila;

            		}


				}
			}
				return true;


		}
		else{
			return false;

		}


	}






};

int main(){


	matriz_sparse<int> A(10,10);
	A.put(0,2,4);
	A.put(0,3,5);
	A.put(0,4,5);
	A.put(0,5,5);
	A.put(1,6,5);
	//A.put(0,5,5);


/*
	A.put(0,0,1);
	A.put(0,1,2);
	A.put(0,2,3);
	A.put(0,4,5);
	A.put(0,3,8);
	A.put(1,2,9);
	A.put(1,3,7);
	A.put(2,3,4);
*/
	matriz_sparse<int> B(10,10);

	B.put(0,2,4);
	B.put(0,3,5);
	B.put(0,4,5);
	B.put(0,5,5);
	B.put(1,6,5);
	//B.put(2,0,10);

	if(A==B){cout<<"true"<<endl;}
	else{cout<<"false"<<endl;}
	/*
	B.put(0,0,1);
	B.put(0,1,2);
	B.put(0,2,3);
	B.put(0,4,4);
	B.put(0,3,5);
	B.put(1,2,6);
	B.put(1,3,7);
	B.put(2,3,8);
*/
	/*
	matriz_sparse<int> c(10,10);
	c=A+B;
	c.printfila(0);
	c.printcol(0);
	*/




/*
	A.printfila(0);
	A.printfila(1);
	A.printfila(2);

	cout<<"-----------"<<endl;
	A.printcol(3);
    A.printcol(1);

    cout<<"-----------"<<endl;
    cout<<"v"<<endl;
    A.put(0,0,3);
    cout<<"t"<<endl;
    A.put(0,3,10);
  	cout<<"d"<<endl;
    A.put(2,3,20);
    A.printfila(0);
    A.printcol(3);
    cout<<"-----------"<<endl;

    A.makezero(0,3);
    A.printfila(0);

    cout<<"-----------"<<endl;
    cout<<A.iszero(0,3)<<endl;
    cout<<A.iszero(0,4)<<endl;
    cout<<A.iszero(20,6)<<endl;
	A.put(2,4,0);
	cout<<A.iszero(2,4)<<endl;
	cout<<"-----------"<<endl;
	cout<<A.get(0,0)<<endl;
	cout<<A.get(20,5)<<endl;
	cout<<A.get(1,3)<<endl;
	*/

}
