#include "WaveSpawner.h"
#include "BConstruct.h"
#include "HelloWorldScene.h"
#include "AudioManager.h"

#include <fstream>	
using std::string;
#define COCOS2D_DEBUG 1

WaveSpawner::WaveSpawner()
{

}

WaveSpawner::~WaveSpawner()
{
}

// written by JT
Entity* WaveSpawner::GetEntity(Node* node)
{
    CCLOG("Size; %d", enemy_list.size());

    int a = 0;
    for (auto enemyNode : enemy_list)
    {
        if (node == enemyNode->GetSprite())
        {
            return enemy_list[a];
        }
        a++;
    }
    return NULL;
}

void WaveSpawner::DestroyEnemy(Node* node)
{
    CCLOG("Size; %d", enemy_list.size());

	int a = 0;
	for (auto enemyNode : enemy_list)
	{
		if (node == enemyNode->GetSprite())
		{
            // remove its visibility
            //node->setVisible(false);

            // remove it from active enemy list

            // add it to inactive enemy list

			Entity* entity = enemy_list[a];
			
			enemy_list.erase(enemy_list.begin()+a);

			delete entity;
            entity = NULL;

			break;
		}
		a++;
	}
}
void WaveSpawner::Init()
{
	screen_height = 0;
	screen_width = 0;
	default_scale = Vec2(1600, 900);
	wavetimer = 0;
	currentwave = 1;
	wavetimer = 0;
	isspawned = false;
	isboss = false;
}

void WaveSpawner::SeteNode(Node* node)
{
	eNode = node;
}

void WaveSpawner::SpawnEnemy(EnemyData enemy)
{
	switch (enemy._type)
	{
	case (1) ://capule
	{
				  Capule* capule = new Capule;
				  capule->SetEntity(enemy);
				  capule->SettoSpawn();
				  enemy_list.push_back(capule);
				  eNode->addChild(capule->_eSprite, 1);
				  
	}break;
	case (2) ://platonic
	{
				  Platonic* platonic = new Platonic;
				  platonic->SetEntity(enemy);
				  platonic->SettoSpawn();
				  enemy_list.push_back(platonic);
				  eNode->addChild(platonic->_eSprite, 1);

	}break;
	default:
	{
			   Entity* entity = new Entity;
			   entity->SetEntity(enemy);
			   //entity->SetActive();
			   entity->SettoSpawn();
			   enemy_list.push_back(entity);
			   eNode->addChild(entity->_eSprite, 1);
			   
	}break;
	}






	//auto entity = Sprite::create(enemy._spriteFile);//single frame sprites for testing
	//	
	//this would be the ideaal way to set the animation/sprite but there is currently no string->animation conversion from the csv file
	//auto entity = Sprite::create();
	//AnimHandler::getInstance()->setAnimation(mainSprite, AnimHandler::CONSTRUCT_ACTIVEP2, true);
}

void WaveSpawner::SpawnInEnemy(Entity* enemy)
{
	enemy_list.push_back(enemy);
	eNode->addChild(enemy->_eSprite, 1);
}

void WaveSpawner::Run(float dt)
{
	wavetimer += dt;

	if (!isboss)
	{
		if (currentwave > waveTimer.size())//is this the finaal wave?
		{
			SpawnBoss();
			
            // play boss BGM
            AudioManager::GetInstance()->PlayBackgroundMusic("Boss");

			return;
		}

		if (!isspawned)
			SpawnCurrentWave();

		if (wavetimer > waveTimer.at(currentwave-1 ))
		{
			DespawnEnemies();
		}
		std::vector<Entity>::size_type size = enemy_list.size();
		for (std::vector<Entity>::size_type i = 0; i < size; ++i)
		{
			Entity*e = enemy_list[i];
			if (e->_waveNum == currentwave && e->_active)
			{
				e->DoAttack(dt);
					
			}e->_eSprite->getPhysicsBody()->onAdd();
		}
		//for (Entity* e : enemy_list)
		//{
		//	//if (!e->_active)//this should work when implemented
		//	//	continue;

		//	if (e->_waveNum == currentwave && e->_active)
		//		e->DoAttack(dt);
  //          else
  //              e->_eSprite->getPhysicsBody()->onAdd();

		//}
		//we need to add stuff to check if wave is dead later
	}
	else
	{
		std::vector<Entity>::size_type size = enemy_list.size();
		for (std::vector<Entity>::size_type i = 0; i < size; ++i)
		{
			Entity*e = enemy_list[i];
			if (e->_active)
			{
				e->DoAttack(dt);
				
			}e->_eSprite->getPhysicsBody()->onAdd();
        }
	}

}

void WaveSpawner::DespawnEnemies()
{
	//this is the node method. It works, but i dont know how to use it properly
	//Vector<Node*> enemies = eNode->getChildren();
	//Vector<Node*>::iterator Iterator;
	//for (Iterator = enemies.begin(); Iterator != enemies.end(); ++Iterator)
	//{
	//	auto mySprite = *Iterator;
	//	Sprite* entity = dynamic_cast<Sprite*>(mySprite);
	//	auto moveTo = MoveBy::create(3, Vec2(1000, 0));
	//	//auto moveTo = MoveTo::create(1, Vec2(entity->getPositionX() + 1000, entity->getPositionY()));
	//	entity->runAction(moveTo);
	//	// do something with this sprite.
	//}
	currentwave++;
	for (Entity* e : enemy_list)
	{
		//if (!e->_active)//this should work when implemented
		//	continue;

		if (e->_waveNum != currentwave)
		e->SettoDespawn();
	}
	isspawned = false;
	//enemy.active

}

void WaveSpawner::SpawnCurrentWave()
{
	log(currentwave);
	wavetimer = 0;
	for (EnemyData e : waveData)
	{
		if (e._waveNum != currentwave)
			continue;
		
		SpawnEnemy(e);
	}
	isspawned = true;
}

Vec2 StrToVec2(std::string data)
{
	// data is: (x.y)
	Vec2 value;

	std::stringstream vec2_data(data);
	string xVal, yVal;
	std::getline(vec2_data, xVal, '(');	// erase the opening bracket
	std::getline(vec2_data, xVal, '|');
	std::getline(vec2_data, yVal, ')');

	value.x = std::stof(xVal);
	value.y = std::stof(yVal);

	return value;
}

Vec2 WaveSpawner::ScreenToWorld(Vec2 pos)
{
	Vec2 result = Vec2(pos.x*screen_scaling.x, pos.y*screen_scaling.y);
	return result;
}

void WaveSpawner::ClearEnemies()
{
	//for (Entity* e : enemy_list)
	//{
	//	
	//		continue;

	//	e->_active = false;
	//	e->GetSprite()->removeFromParent();
	//}

	for (int i = enemy_list.size() - 1; i >= 0; i--)
	{
		if (enemy_list.at(i)->_type == Entity::BCONSTRUCT)
			continue;
		enemy_list.at(i)->GetSprite()->removeFromParent();
		enemy_list.erase(enemy_list.begin()+i);
	}

}

void WaveSpawner::SetScreenBoundaries(float h, float w)
{
	screen_height = h;
	screen_width = w;

	screen_scaling = Vec2((w/default_scale.x), (h / default_scale.y));

}

bool WaveSpawner::LoadFile(const char* file_path)
{
	std::ifstream fileStream(file_path, std::ios::binary);
	if (!fileStream.is_open()) {
		return false;
	}

	//=======================
	// COUNT NUMBER OF LINES
	//=======================
	//int numOfLines = 0;
	//
	//std::string line;
	//while (!fileStream.eof())
	//{
	//	std::getline(fileStream, line);
	//	if (line[0] == '#' || line == "")   // empty line OR comment
	//		continue;
	//
	//	++numOfLines;
	//}
	//
	//fileStream.clear();
	//fileStream.seekg(0, std::ios::beg);

	//================
	// READ FILE DATA
	//================
	bool firstLine = true;	// first line in CSV contains generic data not for EnemyData

	while (!fileStream.eof())
	{
		std::string thisLine;
		std::getline(fileStream, thisLine);

		if (thisLine == "" || thisLine[0] == '#')   // empty line OR comment
			continue;

		std::stringstream dataStream(thisLine);
		std::string data;
		if (firstLine)
		{
            for (std::getline(dataStream, data, ','); data != "\r" && data != "";) {
                waveTimer.push_back(std::stof(data));
                std::getline(dataStream, data, ',');
            }
			firstLine = false;
			continue;
		}

		EnemyData thisEnemyData;

		// first content is wave number
		std::getline(dataStream, data, ',');
		thisEnemyData._waveNum = std::stoi(data);

		// second content is sprite file name(changed to type with interger)
		std::getline(dataStream, data, ',');
		thisEnemyData._type = std::stoi(data);

		// third content is spawn position
		std::getline(dataStream, data, ',');
		thisEnemyData._spawnPos = ScreenToWorld(StrToVec2(data));

		// fourth content is first destination
		std::getline(dataStream, data, ',');
		thisEnemyData._destination = ScreenToWorld(StrToVec2(data));

		// fifth content is exit destination to leave the screen
		std::getline(dataStream, data, ',');
		thisEnemyData._exitDestination = ScreenToWorld(StrToVec2(data));

		// push into waveData vector
		waveData.push_back(thisEnemyData);
	}

	fileStream.close();

	return true;
}

void WaveSpawner::SpawnBoss()
{
	isboss = true;
	BConstruct* boss = new BConstruct;
	boss->spawner = this;
 	boss->SetData(screen_scaling.x);
 	boss->SettoSpawn();
	enemy_list.push_back(boss);
	eNode->addChild(boss->_eSprite, 1);
}
