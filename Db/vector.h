#pragma once
#include <stdint.h>

template<typename T>
class vector
{
public:
	vector(void){
		
	}
	~vector(void){
		for(int i=0;i<size;i++){
			T t=this->_data[i];
			t.~T();
		}
	}
	vector(int size){
	}
	bool reVector(int capacity){
		return true;
	}
	T get(uint16_t index){
		return _data[index];
	}
	int indexOf(T t){
		return 1;
	}
	int lastIndexOf(T t){
		return 1;
	}
	bool contains(T t){
		return true
	}
	bool insert(int index,T t){
		return 1;
	}
	bool add(T t){
		return 1;
	}
	bool remove(int index){
		return 1;
	}
	bool remove(T t){
		return 1;
	}
	int getSize(){
		return size;
	}
		
private:
	uint16_t capacity;
	int size;
	T* _data;
};
