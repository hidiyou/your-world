#include<vector>
#include<map>
#include<fstream>
#include"DLC.h"
#include"yourWorld.h"

using namespace std;

vector<DLC*> DLCs;
unsigned long long COD = 1;
map<string, unsigned long long> DLC_Map;
unsigned long long newDLC(const string name,const DLC d)
{
	DLC* D = new DLC;
	*D=d;
	if (DLC_Map[name] != 0)
	{
		DLCs[DLC_Map[name]] = D;
		return DLC_Map[name];
	}
	DLCs.push_back(D);
	DLC_Map[name] = COD++;
	return DLC_Map[name];
}
DLC getDLC(const unsigned long long id)
{
	if (DLCs.size() >= id)
		return *DLCs[id - 1];
	return *DLCs[0];//找不到，返回一个空的DLC
}
DLC getDLC(const string name)
{
	if (DLC_Map[name] != 0)
	{
		return getDLC(DLC_Map[name]);
	}
	return *DLCs[0];
}
unsigned long long getDLCId(const string name)
{
	return DLC_Map[name];
}
bool load_a_DLC(const string name)
{
	fstream fio;
	if (name == "system")
	{
		fio.open("gameData/system/system.json");
		return 1;
	}
	else
	{
		if (existsTest("gameData/DLC/" + name + "/" + name + ".json"))
		{
			fio.open("gameData/DLC/" + name + "/" + name + ".json");
		}
		else
		{
			putError(name + "无法加载");
			return 0;
		}
	}
	return 1;
}