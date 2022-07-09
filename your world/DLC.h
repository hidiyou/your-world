#pragma once
#include<string>
using namespace std;
struct DLC
{
	string name;
	string description;
	string version;
	int int_version = 0;
	bool valid = 0;
	bool isSystem = 0;
	unsigned long long id = 0;
	void* (*doc) (long long) = 0;
	void (*onLoad) (void*) = 0;
	void (*tick) () = 0;
	void (*onUnload)() = 0;
};
//解释类似于yourWorld.h，不再赘述
unsigned long long newDLC(const string name, const DLC d);
DLC getDLC(const unsigned long long id);
DLC getDLC(const string name);
unsigned long long getDLCId(const string name);
//自动加载一个DLC
bool load_a_DLC(const string name);
string supported_system_versions[] = { "T1","END" };