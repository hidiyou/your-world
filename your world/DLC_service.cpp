#include"DLC.h"
void* doc(bool _DLC, unsigned long long id)
{
	if (_DLC)
	{
		return getDLC(id).doc;
	}
	else
	{
		switch (id)
		{
		case 0:
			return doc;
			break;
		case 1:
			return getDLCId;
			break;
		case 2:
			return load_a_DLC;
			break;
		default:
			return NULL;
			break;
		}
	}
}