#pragma once

#include "EnemyData.h"
#include <vector>

class WaveSpawner
{
	std::vector<float> waveTimer;   // how each wave of enemies will stay in game
	std::vector<EnemyData> waveData;
	std::vector<Sprite*> enemy_list;
public:
	WaveSpawner();
	~WaveSpawner();
	void SeteNode(Node* node);

	void SpawnCurrentWave();
	void SpawnEnemy(EnemyData enemy);
	void DespawnEnemies();
	void Run(float dt);


	void Init();
	bool LoadFile(const char* filepath);

	Node*  eNode;
	float wavetimer;
	int currentwave;
	bool isspawned;
};