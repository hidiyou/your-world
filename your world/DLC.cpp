#include<vector>
#include<map>
#include<fstream>
#include"DLC.h"
#include"yourWorld.h"
#include <sstream>
#include"cJSON.h"

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
	stringstream buffer;
	fstream fio;
	if (name == "system")
	{
		fio.open("gameData/system/system.json");
		buffer << fio.rdbuf();
		string tmp(buffer.str());
		cJSON* json = NULL;
		json = cJSON_Parse(tmp.c_str());
		if (json == NULL)
		{
			putError("system 无法加载，游戏无法运行！！");
			Sleep(1000);
			exit(1);
		}
		cJSON* LV = NULL;
		LV = cJSON_GetObjectItem(json, "loader_version");
		int sysLV = LV->valueint;
		if (sysLV != loaderVersion)
		{
			putError("system版本错误，游戏无法运行");
		}
		LV = cJSON_GetObjectItem(json, "system_version");
		string SV = LV->valuestring;
#pragma warning(disable : 6385)
//问题已确认
		for (int i = 0; supported_system_versions[i] != "END"; ++i)
		{

		}
#pragma warning(default : 6385)
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