# 欢迎游玩Your World

## 介绍

这是一个无论从开发角度，还是从游玩角度都高度自由的游戏。

## 开发环境

VS2022 + EasyX_20220610

## 安装游戏

## 方法1

在发行版中下载.zip然后解压

## 安装DLC

将DLC文件夹拷贝进gameData/DLC文件夹中，并将这个文件夹的名字添加到DLC.txt中（1行1个）

## 卸载DLC

将在gameData/DLC中的对应文件夹删除，并在DLC.txt中删除

## 卸载游戏

直接删除即可，Your World 不会在游戏目录以外生成任何文件

# DOC表

|编号|描述|函数声明|
|----|----|----|
|0|doc函数（毛用没有）|void* doc(bool _DLC, unsigned long long id);
|1|获取DLC的ID|unsigned long long getDLCId(const string name);
|2|自动加载DLC的函数|bool load_a_DLC(const string name);