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
		POWERUP_LASER,
		POWERUPS_TOTAL
	};

private:

	Sprite* powerupSprite;
	POWERUP_TYPE powerupType;

	bool toBeDestroyed;	// to be destroyed because picked up

	void InitPowerup(POWERUP_TYPE type, const Vec2& SpawnPosition);
    void DestroySelf(); // to destroy self automatically when it leaves screen

	static bool toSpawnPowerup;
	static Vec2 spawnPosition;

	static bool toDestroy;	// there is a Powerup to destroy

public:

	//static std::vector<Powerup> powerups;
	static std::vector<Powerup*> powerupsList;

	Sprite* GetPowerupSprite();
	POWERUP_TYPE GetPowerupType();

	// function to call that checks whether a powerup should be spawned
	static bool CheckSpawnPowerup();	// check against RNG whether should spawn or not
	static void RandomSpawnPowerup();	// randomly spawn 1 powerup

	static bool ToSpawnPowerup() { return toSpawnPowerup; }
	static Vec2 GetSpawnPos() { return spawnPosition; }
	static void SetToSpawnPowerup(bool toSpawn) { toSpawnPowerup = toSpawn; }
	static void SetSpawnPos(const Vec2& spawnPos) { spawnPosition = spawnPos; }

	// functions to handle magnetism & pickup
	static void FindAndBeginPickup(Node* node, const Vec2& pos);
	void BeginPickup(const Vec2& pos);
	void ApplyPowerupEffect();	// apply effect and play SFX

	// static functions handling destruction of picked up powerups
	static void DestroyPickedups();
	static bool IsToDestroy();
};

#endif