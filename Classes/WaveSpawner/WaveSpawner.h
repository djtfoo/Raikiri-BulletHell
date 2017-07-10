#pragma once
#include "Entity.h"
#include "Enemy\Capule.h"
#include "Enemy\Platonic.h"

#include <vector>

class WaveSpawner
{
	std::vector<float> waveTimer;   // how each wave of enemies will stay in game
	std::vector<EnemyData> waveData;
	std::vector<Entity*> enemy_list;//need to implement recycling for this




public:
	WaveSpawner();
	~WaveSpawner();
	void SeteNode(Node* node);

	void SpawnBoss();
	void SpawnCurrentWave();
	void SpawnEnemy(EnemyData enemy);
	void SpawnInEnemy(Entity* enemy);
	void DespawnEnemies();
	void Run(float dt);
	void DestroyEnemy(Node* node);

	void Init();
	bool LoadFile(const char* filepath);

	Node*  eNode;
	float wavetimer;
	int currentwave;
	bool isspawned,isboss;
};