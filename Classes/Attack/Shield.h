#ifndef SHIELD_H_
#define SHIELD_H_

#include "cocos2d.h"
#include <string>
#include "WaveSpawner/Entity.h"
using std::string;
using namespace cocos2d;

class Shield
{
private:

	Sprite* shieldSprite;	// this Shield's sprite
	Sprite* userSprite;	// the user of this Shield
    Vec2 spriteSize;    // size of this Shield sprite

	bool toBeDestroyed;	// to be destroyed because hit

	void InitShield(Sprite* userSprite);

	// for spawning / destroying outside of onContactBegin()
	static bool toSpawnShield;
	static Sprite* spawnUserSprite;
    static bool isSpawnUserPlayer;  // whether Shield is for Player (true) or Entity (false)

	static bool toDestroy;	// there is a Shield to destroy
    static bool isToDestroyPlayer;  // whether Shield to destroy is Player (true) or Entity (false)

public:

    static Shield* playerShield;
    static std::map<Entity*, Shield*> entityShieldsList;    // for enemies

	//Sprite* GetShieldSprite();
    void UpdatePosition();  // update shield's position to follow its user

	// function to call that checks whether a powerup should be spawned
    static void SpawnShield();  // this function checks whether it's for Player or Entity

    static void SetToSpawnShield(bool toSpawn) { toSpawnShield = toSpawn; } // set whether a Shield should be spawned
    static bool ToSpawnShield() { return toSpawnShield; }   // getter

	static void SetSpawnUser(Sprite* user, bool isPlayer)   // set the user for the Shield to be spawned
    {
        spawnUserSprite = user;
        isSpawnUserPlayer = isPlayer;
    }
    static Sprite* GetSpawnUser() { return spawnUserSprite; }   // getter

    // find in list of Shields, the Shield to be destroyed
    static void SetDestroyPlayerShield();
    static void SetDestroyEntityShield(Entity* entity);

    //void FindAndSetDestroy(Node* node);

	// static functions handling destruction of picked up powerups
	static void DestroyShield();
	static bool IsToDestroy();
};

#endif