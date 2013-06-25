#include "commonType.h"

NonCopyable::NonCopyable(void)
{

}

NonCopyable::NonCopyable(const NonCopyable& )
{

}

NonCopyable& NonCopyable::operator=(const NonCopyable& )
{
	return *this;
}