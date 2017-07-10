#ifndef POWERUP_H_
#define POWERUP_H_

#include "cocos2d.h"
#include <string>
using std::string;
using namespace cocos2d;
class Powerup
{
public:
	enum POWERUP_TYPE
	{
		POWERUP_LIVES,
		POWERUP_BULLETS,
		POWERUP_MISSILE,
		POWERUP_SHIELD,
		POWERUPS_TOTAL
	};

private:

	Sprite* powerupSprite;
	POWERUP_TYPE powerupType;

	void InitPowerup(POWERUP_TYPE type, Vec2 SpawnPosition);

	static bool toSpawnPowerup;
	static Vec2 spawnPosition;

public:

	//static std::vector<Powerup> powerups;
	static std::map<int, Powerup*> powerupsList;
	static int powerupSpawnCount;

	Sprite* GetPowerupSprite();
	POWERUP_TYPE GetPowerupType();

	// function to call that checks whether a powerup should be spawned
	static bool CheckSpawnPowerup();	// check whether to spawn is true
	static void RandomSpawnPowerup();	// randomly spawn 1 powerup

	static bool ToSpawnPowerup() { return toSpawnPowerup; }
	static Vec2 GetSpawnPos() { return spawnPosition; }
	static void SetToSpawnPowerup(bool toSpawn) { toSpawnPowerup = toSpawn; }
	static void SetSpawnPos(Vec2 spawnPos) { spawnPosition = spawnPos; }

	void Pickup();	// apply effect and play SFX

	// functions to begin & handle magnetism
};

#endif