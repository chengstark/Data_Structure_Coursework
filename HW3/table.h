#ifndef table_h_
#define table_h_

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cassert>
#include <vector>

using namespace std;

template <class T> class Table {
public:
	typedef unsigned int size_type;
	// CONSTRUCTORS, ASSIGNMNENT OPERATOR, & DESTRUCTOR
	Table(size_type row_, size_type col_, const T& val){this -> create(row_, col_, val);}
	Table(const Table<T>& t) {copy(t);}
	Table& operator=(const Table& t);
	~Table(){this -> deletstuff();}


	void set(size_type row_, size_type col_, const T& val);
	T get(size_type row_, size_type col_) const;
	void push_back_row(const vector<T>& vec);
	void push_back_column(const vector<T>& vec);
	void pop_back_row();
	void pop_back_column();
	size_type numRows() const {return row;}
	size_type numColumns() const {return col;}
	void print();


private:
	void copy(const Table& t);
	void create(size_type row_, size_type col_, const T& val);
	void deletstuff();

	T** data;
	size_type row;
	size_type col;
	size_type size;
};

template <class T> void Table<T>::create(size_type row_, size_type col_,  const T& val){
	data = new T*[row_];
	for(size_type i = 0; i< row_; i++){
		data[i] = new T[col_];
		for(size_type j=0; j<col_;j++){
			data[i][j] = val;
		}
	}
	row = row_;
	col = col_;
	size = row_*col_;
}

template <class T> void Table<T>::copy(const Table<T>& t){
	if(t.numRows()>0 && t.numColumns()>0){
		row = t.numRows();
		col = t.numColumns();
		size = row*col;
		// deletstuff();
		data = new T*[row];
		for(size_type i=0;i<row;i++){
			data[i] = new T[col];
		}
		for(size_type i =0;i<row;i++){
			for(size_type j=0;j<col;j++){
				data[i][j] = t.get(i, j);
			}
		}
	}
	else{
		cerr<<"Cannot copy an empty table!"<<endl;
		exit(1);
	}
}

template <class T> void Table<T>::deletstuff(){
	for(size_type i = 0;i<row;i++){
		delete[] data[i];
	}
	delete[] data;
}

template <class T> Table<T>& Table<T>::operator=(const Table<T>& t){
	if (this != &t) {
	    deletstuff();
	    copy(t);
	}
  return *this;

}

template <class T> void Table<T>::set(size_type row_, size_type col_, const T& val){
	data[row_][col_] = val;
}

template <class T> T Table<T>::get(size_type row_, size_type col_) const{
	return data[row_][col_];
}

template <class T> void Table<T>::push_back_row(const vector<T>& vec){
	if(vec.size()!=col){
		cerr<<"None consistence row length!"<<endl;
		exit(1);
	}
	T** tmp = new T*[row+1];
	for(size_type i = 0; i< row; i++){
		tmp[i] = data[i];
	}
	tmp[row] = new T[col];
	for(size_type i= 0;i<col;i++){
		tmp[row][i] = vec[i];
	}
	delete[] data;
	data = tmp;
	row = row+1;
	size = row*col;
}


template <class T> void Table<T>::push_back_column(const vector<T>& vec){
	if(vec.size()!=row){
		cerr<<"None consistence col length!"<<endl;
		exit(1);
	}
	for(size_type i=0;i<row;i++){
		T* tmp = new T[col+1];
		for(size_type j=0;j<col;j++){
			tmp[j] = data[i][j];
		}
		tmp[col] = vec[i];
		delete[] data[i];
		data[i] = tmp;
	}
	col = col+1;
	size = row*col;
}


template <class T> void Table<T>::pop_back_row(){
	T** tmp = new T*[row-1];
	for(size_type i=0;i<(row-1);i++){
		tmp[i] = data[i];
	}
	delete[] data[row-1];
	delete[] data;
	data = tmp;
	row = row - 1;
	size = row*col;
}


template <class T> void Table<T>::pop_back_column(){
	for(size_type i=0;i<row;i++){
		T* tmp = new T[col-1];
		for(size_type j = 0;j< (col-1);j++){
			tmp[j] = data[i][j];
		}
		delete[] data[i];
		data[i] = tmp;
	}
	col = col - 1;
	size = row*col;
}

template <class T> void Table<T>::print(){
	for(size_type i=0; i<row ;i++){
		for (size_type j = 0; j < col; j++){
			cout<<" "<<data[i][j];
		}
		cout<<endl;
	}
}

#endif