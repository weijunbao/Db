#pragma once
#include "commonType.h"
#include "Page.h"
#include "Db.h"

class OfRules:
	public Object
{
public:
	OfRules(void);
	~OfRules(void);
	 virtual bool isOf(PDB pDb,PPage,Row*)=0;
};

/*ǿ�ƵĹ���*/
class MandatoryOfRules :
	public OfRules{
public:
	MandatoryOfRules(){}
	~MandatoryOfRules(){}
	bool isOf(PDB pDb,PPage,Row*);
};