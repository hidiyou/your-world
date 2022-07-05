#pragma once
#include<string>
using namespace std;
struct DLC
{
	string name = NULL;
	string description = NULL;
	bool isSystem = NULL;
	unsigned long long id = NULL;
	void* (*doc) (long long) = NULL;
	void (*onLoad) (void*) = NULL;
	void (*tick) () = NULL;
	void (*onUnload)() = NULL;
};
//����������yourWorld.h������׸��
unsigned long long newDLC(const string name, const DLC d);
DLC getDLC(const unsigned long long id);
DLC getDLC(const string name);
unsigned long long getDLCId(const string name);
//�Զ�����һ��DLC
bool load_a_DLC(const string name);