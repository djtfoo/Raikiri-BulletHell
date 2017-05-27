#include "WaveSpawner.h"
#include <fstream>

WaveSpawner::WaveSpawner()
{
}

WaveSpawner::~WaveSpawner()
{
}

void WaveSpawner::Init()
{

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