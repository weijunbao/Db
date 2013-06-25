#pragma once

enum BalanceRuleType
{
	BRT_NOT,//不需要balance
	BRT_Mandatory,//强制balance
	BRT_Condition//可以考虑balance
};
class BalanceRule
{
public:
	BalanceRule(void);
	~BalanceRule(void);
};

