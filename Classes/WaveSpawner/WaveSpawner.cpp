#include "WaveSpawner.h"
#include "Scenes/HelloWorldScene.h"
#include <fstream>
using std::string;

WaveSpawner::WaveSpawner()
{
}

WaveSpawner::~WaveSpawner()
{
}

void WaveSpawner::Init()
{
	wavetimer = 0;
	currentwave = 1;
	wavetimer = 0;
	isspawned = false;
}

void WaveSpawner::SeteNode(Node* node)
{
	eNode = node;
}

void WaveSpawner::SpawnEnemy(EnemyData enemy)
{
	Entity* entity = new Entity;
	entity->SetEntity(enemy);
	//entity->SetActive();
	entity->SettoSpawn();
	enemy_list.push_back(entity);
	eNode->addChild(entity->_eSprite, 1);
	//auto entity = Sprite::create(enemy._spriteFile);//single frame sprites for testing
	//	
	//this would be the ideaal way to set the animation/sprite but there is currently no string->animation conversion from the csv file
	//auto entity = Sprite::create();
	//AnimHandler::getInstance()->setAnimation(mainSprite, AnimHandler::CONSTRUCT_ACTIVEP2, true);
}

void WaveSpawner::Run(float dt)
{
	wavetimer += dt;
	if (currentwave == 0 && wavetimer >2)//level just started
	{
		currentwave = 1;
		wavetimer = 0;
		return;
	}
	if (!isspawned)
		SpawnCurrentWave();
	
	if (wavetimer > waveTimer.at(currentwave-1))
	{
		DespawnEnemies();
	}


	//we need to add stuff to check if wave is dead later





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
            for (std::getline(dataStream, data, ','); data != "\r";) {
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
		thisEnemyData._spawnPos = StrToVec2(data);

		// fourth content is first destination
		std::getline(dataStream, data, ',');
		thisEnemyData._destination = StrToVec2(data);

		// fifth content is exit destination to leave the screen
		std::getline(dataStream, data, ',');
		thisEnemyData._exitDestination = StrToVec2(data);

		// push into waveData vector
		waveData.push_back(thisEnemyData);
	}

	fileStream.close();

	return true;
}

