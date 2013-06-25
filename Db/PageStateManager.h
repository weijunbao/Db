#pragma once
#include "PageState.h"
#include "Page.h"
class PageState;
class PageStateManager
{
public:
	PageStateManager(void);
	~PageStateManager(void);
public:
	PageState* getPageState(PageNo);
};

