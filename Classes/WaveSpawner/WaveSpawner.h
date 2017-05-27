#pragma once

#include "EnemyData.h"
#include <vector>

class WaveSpawner
{
	std::vector<float> waveTimer;   // how each wave of enemies will stay in game
	std::vector<EnemyData> waveData;

public:
	WaveSpawner();
	~WaveSpawner();

	void Init();
	bool LoadFile(const char* filepath);
};