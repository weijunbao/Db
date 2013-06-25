#pragma once

template<typename T>
class DList
{
public:
	template<typename T>
	class DListNode{
	private:
		T curNode;
		DListNode<T>* nextNode;
		DListNode<T>* preNode;
	public:
		DListNode<T>(void){}
		DListNode<T>(T t){
			this->curNode=t;
		}
		~DListNode<T>(void){}
	};

	DList(void):head(NULL),tail(NULL),count(0){

	}
	
	~DList(void){
	}
public:
	int insert(T t){
		if(head==NULL){
			head=new DListNode(t);
			tail=head;
			this->count+=1;
		}
		else{
			tail->nextNode=new DListNode(t);
			tail=tail->nextNode;
			this->count+=1;
		}
		return 1;
	}
	int remove(int index){
		int middle=count/2;
		if(middle > index){
		
		}
		else{
		
		}
		return 1;
	}
	int search(T t){
		DListNode<T> node=head;
		int i=1;
		while(node!=NULL)
		{
			i+=1;
			if(node.curNode==t){
				return i;
			}
		}
		return 1;
	}
	int getCount(void){
		return this->count;
	}
private:
	DListNode<T>* head;
	DListNode<T>* tail;
	int count;
};