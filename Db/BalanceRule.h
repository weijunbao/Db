#pragma once

enum BalanceRuleType
{
	BRT_NOT,//����Ҫbalance
	BRT_Mandatory,//ǿ��balance
	BRT_Condition//���Կ���balance
};
class BalanceRule
{
public:
	BalanceRule(void);
	~BalanceRule(void);
};

