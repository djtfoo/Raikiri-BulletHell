#ifndef ATTACK_H_
#define ATTACK_H_


#include <string>
#include <map>
#include "cocos2d.h"
#include "Projectile.h"
#include "WaveSpawner\Entity.h"
using std::string;
using std::map;
using namespace cocos2d;

class Attack
{


private:
    string BulletImg;

    map<Entity*, Node*> EntityLaserDamageList;

    Projectile* LaserProjectile;
    Sprite* LaserSprite;
    bool InitLaser;

    std::vector<Vec2> dashLinePoints;   // for special attack
    std::vector<Entity*> dashEntitiesHit;

    int chargeBarValue;
    const int chargeBarMaxValue;

    void SetChargeBarValue(int value);

    // Laser as a powerup
    bool isLaserMode;
    float laserTimer;
    const float laserLifetime;

public:
    Attack(string LaserImg);
    ~Attack();

    bool IsLaserMode() { return isLaserMode; }
    void SetLaserMode(bool laserMode);
    void UpdateLaserTimer(float dt);

    bool IsChargeBarMax()
    {
        return (chargeBarValue == chargeBarMaxValue);
    }
    float GetChargeBarPercentage()
    {
        return (float)chargeBarValue / (float)chargeBarMaxValue;
    }

    void IncreaseChargeBarValue(int value);
    void ResetChargeBarValue();

    void SetDashLinePoints(const std::vector<Vec2>& points);
    void AddDashHitEntity(Entity* entity);
    bool HasDashHitEntity(Entity* entity);
    void ClearDashHitEntities();

	void FireBasicBullet(string BulletImg, Vec2 SpawnPosition, float BulletSpeed, float LifeTime,bool isEnemy);
	void FireLaserBullet(Vec2 SpawnPosition);
	void StopFiringLaser(/*float LaserSpeed, float LifeTime*/);
	
    void InitialiseLaser(Size size, Node* spriteNode);
    void LaserUpdate(float dt, float LaserScaleX, Vec2 PlayerPosition);
	bool GetInitLaser();
	void SetInitLaser(bool setlaser);

	Sprite* GetLaserSprite();
	void SetLaserSprite(Sprite* laser);

    void AddToLaserVector(Entity* entity, Node* node);
    void DeleteFromLaserVector(Entity* entity);
};




#endif