#include "Attack.h"
#include "Projectile.h"
#include "HelloWorldScene.h"
#include "AudioManager.h"
#include "GameInputManager.h"

#define COCOS2D_DEBUG 1
Attack::Attack(string LaserImg) : chargeBarMaxValue(100), laserLifetime(3.f), LaserImgFile(LaserImg)
{
	InitLaser = false;
    chargeBarValue = 0;

    // create laser projectile
    LaserProjectile = new Projectile();
    LaserSprite = Sprite::create(LaserImg);

    // Laser as a powerup
    isLaserMode = false;
    laserTimer = 0.f;
}

Attack::~Attack()
{
}
void Attack::FireBasicBullet(string BulletImg, Vec2 SpawnPosition, float BulletSpeed, float LifeTime,bool isEnemy)
{
	Projectile* projectile = new Projectile();
	/*Sprite* ProjectileSprite =*/ projectile->InitBasicBullet(BulletImg, SpawnPosition, BulletSpeed, LifeTime, isEnemy);

    AudioManager::GetInstance()->PlaySoundEffect("Bullet");
}
void  Attack::FireLaserBullet(Vec2 SpawnPosition)
{
	if (!InitLaser)
	{
        //Projectile* projectile = new Projectile();
        LaserProjectile->SetLaserBullet(LaserSprite, SpawnPosition);
        this->InitLaser = true;

        AudioManager::GetInstance()->PlaySoundEffect("Laser");
        AudioManager::GetInstance()->PlaySoundEffect("LaserHum", true);
	}
	/*else
	{
		LaserSprite->setScaleX(LaserSprite->getScaleX() + LaserScaleX);
	}*/
}
void  Attack::StopFiringLaser(/*float LaserSpeed,float LifeTime*/)
{
    if (this->InitLaser) {
        this->InitLaser = false;
        //auto moveEvent = MoveBy::create(LifeTime, Vec2(1.f, 0.f) * LaserSpeed);
        //LaserSprite->runAction(moveEvent);

        //LaserSprite->removeFromParentAndCleanup(true);
        //LaserSprite = NULL;

        LaserSprite->setVisible(false);
        LaserSprite->getPhysicsBody()->setEnabled(false);

        AudioManager::GetInstance()->StopSoundEffect("LaserHum");
    }

}

void Attack::InitialiseLaser(Size size, Node* spriteNode)
{
    LaserProjectile->InitLaserBullet(LaserSprite, size, spriteNode);
}

void Attack::SetLaserMode(bool laserMode)
{
    isLaserMode = laserMode;
    if (!laserMode)
    {
        // reset timer
        laserTimer = 0.f;
    }
    
    auto scene = Director::getInstance()->getRunningScene();
    auto layer = scene->getChildByTag(999);
    HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);

    // if shoot key is held down already, set to fire laser
    if (GameInputManager::GetInstance()->IsKeyHeld("Shoot") || helloLayer->mainPlayer->IsTouchBegan())
    {
        if (laserMode)  // set to fire
            helloLayer->mainPlayer->FireLaser();
        else
            helloLayer->mainPlayer->StopFiringLaser();
    }
}

void Attack::UpdateLaserTimer(float dt)
{
    laserTimer += dt;
    if (laserTimer >= laserLifetime)    // end laser powerup
    {
        StopFiringLaser();
        isLaserMode = false;

        // reset timer
        laserTimer = 0.f;
    }
}

void Attack::LaserUpdate(float dt, float LaserScaleX,Vec2 PlayerPosition)
{
    if (InitLaser)
    {
        for (map<Entity*, Node*>::iterator it = EntityLaserDamageList.begin(); it != EntityLaserDamageList.end(); it++)
        {
            if (it->first == NULL) // this Entity was deleted already
            {
                EntityLaserDamageList.erase(it);
                break;
            }
            else
            {
                it->first->_hp -= 5000.f * dt;
                //if (it->first->_hp <= 0)    // Entity is killed
                if (it->first->IsDead())
                {
                    auto scene = Director::getInstance()->getRunningScene();
                    auto layer = scene->getChildByTag(999);
                    HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);

                    // if boss, set victory
                    if (it->first->_type == Entity::BCONSTRUCT) {
                        helloLayer->mainPlayer->SetWinGame(true);
                        helloLayer->GetGUI()->initEndScreen(helloLayer->mainPlayer, true);
                    }

                    helloLayer->waveSpawner->DestroyEnemy(it->second);

                    it->second->removeFromParentAndCleanup(true);
                    it->second = NULL;

                    EntityLaserDamageList.erase(it);

                    // add to score
                    helloLayer->mainPlayer->AddScore();
                    helloLayer->mainPlayer->AddScoreMultiplier(0.2);
                    helloLayer->GetGUI()->UpdateScoreMultiplierLabel(helloLayer->mainPlayer->GetScoreMultiplier());

                    break;
                }

            }
        }
        if (LaserSprite) {
            LaserSprite->setPosition(PlayerPosition);
          //  LaserSprite->getPhysicsBody()->onAdd();
        }
    }
}
bool  Attack::GetInitLaser()
{
	return InitLaser;
}
void  Attack::SetInitLaser(bool setlaser)
{
	this->InitLaser = setlaser;
}
Sprite* Attack::GetLaserSprite()
{
	return LaserSprite;
}
void Attack::SetLaserSprite(Sprite* laser)
{
	this->LaserSprite = laser;
}
void Attack::AddToLaserVector(Entity* entity, Node* node)
{
    bool NotInVector = true;
    for (map<Entity*, Node*>::iterator it = EntityLaserDamageList.begin(); it != EntityLaserDamageList.end(); it++)
    {
        if (it->first == entity)
        {
            NotInVector = false;
            break;
        }
    }
    if (NotInVector)
    {
        EntityLaserDamageList.insert(EntityLaserDamageList.begin(), std::pair<Entity*, Node*>(entity, node));
    }
}
void Attack::DeleteFromLaserVector(Entity* entity)
{
    int a = 0;
    for (map<Entity*, Node*>::iterator it = EntityLaserDamageList.begin(); it != EntityLaserDamageList.end(); it++)
    {
        if (it->first == entity)
        {
            EntityLaserDamageList.erase(it);
            break;
        }
        a++;
    }

}

// Special Attack Dash
void Attack::SetDashLinePoints(const std::vector<Vec2>& points)
{
    dashLinePoints = points;
}

void Attack::AddDashHitEntity(Entity* entity)
{
    dashEntitiesHit.push_back(entity);
}

bool Attack::HasDashHitEntity(Entity* entity)
{
    if (std::find(dashEntitiesHit.begin(), dashEntitiesHit.end(), entity) == dashEntitiesHit.end())
        return false;

    return true;
}

void Attack::ClearDashHitEntities()
{
    dashEntitiesHit.clear();
}

void Attack::IncreaseChargeBarValue(int value)
{
    SetChargeBarValue(chargeBarValue + value);
}

void Attack::ResetChargeBarValue()
{
    SetChargeBarValue(0);
}

void Attack::SetChargeBarValue(int value)
{
    chargeBarValue = value;
    if (chargeBarValue > chargeBarMaxValue)
        chargeBarValue = chargeBarMaxValue;
}