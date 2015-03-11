#pragma once
#include "cocos2d.h"
class DataSingleton {
private:
	DataSingleton();
	DataSingleton(const DataSingleton& other);
	~DataSingleton();
	static DataSingleton inst;
public:
	static DataSingleton& getInstance() { return inst; }

	int nLevel;

	int nSpentTime;
	//std::string strSpentTime;
	
	int nSpentCount;

	// �ΰ��� -> ���â 
	bool bClear;
	int nStageRepeatCount;
	int nLeftLife;

	// ���â -> �������� ����
	int nCleardStage;
	bool bNewRanked;
};