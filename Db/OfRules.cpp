#include "OfRules.h"
#include <assert.h>

OfRules::OfRules(void)
{
}


OfRules::~OfRules(void)
{
}

bool MandatoryOfRules::isOf(PDB pDb,PPage pPage,Row* row)
{
	DataRow* dataRow=NULL;
	assert(pPage);
	assert(row);

	dataRow=dynamic_cast<DataRow*>(row);
	assert(dataRow);

	if(dataRow->getVSize() > pDb->getPageSize() / 2){
		return true;
	}
	return false;
}

