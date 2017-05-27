#include "WaveSpawner.h"
#include <fstream>
#include "HelloWorldScene.h"

WaveSpawner::WaveSpawner()
{
}

WaveSpawner::~WaveSpawner()
{
}

void WaveSpawner::Init()
{
	wavetimer = 0;
	//eNode= Node::create();
	//auto scene = Director::getInstance()->getRunningScene();
	//auto layer = scene->getChildByTag(999);
	//HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
	//helloLayer->addChild(eNode, 2);

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

	auto entity = Sprite::create(enemy._spriteFile);//single frame sprites for testing
		eNode->addChild(entity, 1);
	//this would be the ideaal way to set the animation/sprite but there is currently no string->animation conversion from the csv file
	//auto entity = Sprite::create();
	//AnimHandler::getInstance()->setAnimation(mainSprite, AnimHandler::CONSTRUCT_ACTIVEP2, true);

	entity->setAnchorPoint(Vec2::ZERO);
	entity->setPosition(enemy._spawnPos.x,enemy._spawnPos.y);
	

	auto moveTo = MoveTo::create(1, enemy._destination);
	entity->runAction(moveTo);//simple moveto
	//entity->runAction(CCSequence::create(moveTo,moveTo));//this is for the attack state




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
	
	if (wavetimer > 5)
	{
		DespawnEnemies();
			//maybe some delay
		currentwave++;
	}
	//if (wavetimer > )

	//we need to add stuff to check if wave is dead later





}

void WaveSpawner::DespawnEnemies()
{
	Vector<Node*> enemies = eNode->getChildren();

	Vector<Node*>::iterator Iterator;
	for (Iterator = enemies.begin(); Iterator != enemies.end(); ++Iterator)
	{
		auto mySprite = *Iterator;
		Sprite* entity = dynamic_cast<Sprite*>(mySprite);


		auto moveTo = MoveBy::create(3, Vec2(1000, 0));
		//auto moveTo = MoveTo::create(1, Vec2(entity->getPositionX() + 1000, entity->getPositionY()));
		entity->runAction(moveTo);
		// do something with this sprite.
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

		// second content is sprite file name
		std::getline(dataStream, data, ',');
		thisEnemyData._spriteFile = data + ".png";

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

