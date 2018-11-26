#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

template <typename Comparable>
class BinaryHeap{
public:
	explicit BinaryHeap( int capacity =0 ){currentSize=capacity; }
	explicit BinaryHeap( const vector<Comparable> & items ): array( items.size( ) + 10 ), currentSize{ items.size( )}{
		for( int i = 0; i < items.size( ); ++i )
			array[ i+1]= items[ i ];
		buildHeap( );
	}
	const Comparable & findMin( ) const;
	void insert( const Comparable & x ){
        if( currentSize == array.size( )-1)
            array.resize( array.size( ) * 2 );
        int hole = ++currentSize;
        Comparable copy = x;
        if(array.size()==0)array.push_back(move(copy));
        else array[ 0 ] = std::move( copy );
        for( ; x < array[ hole / 2 ]; hole /= 2 ){
            array[ hole ] = std::move( array[ hole / 2 ] );
        }
        array[ hole ] = std::move( array[ 0 ] );
	}
	//void insert( Comparable && x );
	bool isEmpty( ) const{
        return currentSize==0;
	}
	void deleteMin( ){
        if( isEmpty( ) )
            cout<<"Lista vacia"<<endl;

        array[ 1 ] = std::move( array[ currentSize-- ] );
        percolateDown( 1 );
    }

	void deleteMin( Comparable & minItem ){
            if(isEmpty()){cout<<"Lista vacia"<<endl;}
            minItem= std::move( array[ 1 ] );
            array[ 1 ] = std::move( array[ currentSize-- ] );
            percolateDown( 1 );

	}
	void makeEmpty( ){
        currentSize=0;
        array.clear();
	}
	void imprimir(){
		for (int i = 1; i <= currentSize; ++i)
		{
			cout<<array[i]<<" ";
		}
	}
private:
	int currentSize; // Number of elements in heap
	vector<Comparable> array; // The heap array

	void buildHeap( ){
		for( int i = currentSize / 2; i > 0; --i )
			percolateDown( i );
	}
	void percolateDown( int hole ){
		int child;
		Comparable tmp = std::move( array[ hole ] );
		for( ; hole * 2 <= currentSize; hole = child )
		{
			child = hole * 2;
			if( child != currentSize && array[ child +1]< array[ child ] )
				++child;
			if( array[ child ] < tmp )
				array[ hole ] = std::move( array[ child ] );
			else
				break;
		}
		array[ hole ] = std::move( tmp );
	}
};



int main(){
	BinaryHeap<int>B;
	B.insert(4);
	B.insert(3);
	B.insert(7);
	B.insert(9);
	B.insert(6);
	B.insert(1);

	B.imprimir();
    cout<<endl;
	B.deleteMin();

	B.imprimir();
	return 0;
}
