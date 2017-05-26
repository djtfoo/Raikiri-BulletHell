#pragma once

#include "EnemyData.h"
#include <vector>

class WaveSpawner
{
	float enemyLifetime;	// how long an enemy will stay in game before it starts to leave
	std::vector<EnemyData> waveData;

public:
	WaveSpawner();
	~WaveSpawner();

	void Init();
	bool LoadFile(const char* filepath);
};