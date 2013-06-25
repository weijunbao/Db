#pragma once
#include "commonType.h"
#include "Page.h"
#include "Db.h"
#include "BalanceRule.h"

struct BtreeCursor 
{
	public:
		int level;
		PageNo page;
		PageNo pPage;
	public:
		void set(int level,PageNo page,PageNo pPage){
			this->level=level;this->page=page;this->pPage=pPage;
		}
		bool isValid(){
			return level < 1;
		}
	};

enum OpType{
	OP_INSERT=0,
	OP_UPDATE,
	OP_DELETE
};

class Btree :
	public NonCopyable
{
public:
	Btree(void);
	~Btree(void);
public:
	BtreeCursor search(Value key);
	int insert(const Value key,const Value value);
	int update(const Value key,const Value value);
	int remove(Value key);
private:
	int split(PLeafPage pPage);
	int split(PIndexPage pPage);
	int remove(PPage pPage,const Value key);
	int merge(PPage pPage,int index);
	int balance(PPage parentPage,int index);
	void balance(PPage parentPage,PPage curPage,int index,OpType opType);
	BalanceRuleType trybalance(PPage parentPage,PPage curPage,int index);
	void traverse(void (*callback)(Value v));//±éÀú
private:
	Db* db;
};