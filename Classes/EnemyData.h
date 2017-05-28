#pragma once

#include <string>
#include "cocos2d.h"

using namespace cocos2d;
//using std::string;

struct EnemyData
{
	int _waveNum;
	int _type;
	Vec2 _spawnPos;
	Vec2 _destination;
	Vec2 _exitDestination;

	// Behaviour
};