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
//解释类似于yourWorld.h，不再赘述
unsigned long long newDLC(const string name, const DLC d);
DLC getDLC(const unsigned long long id);
DLC getDLC(const string name);
unsigned long long getDLCId(const string name);
//自动加载一个DLC
bool load_a_DLC(const string name);