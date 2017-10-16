#include "Util.h"
#include "random"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
USING_NS_CC;

static float scalex;
static float scaley;
static float characterScale = 1;
static Size frameSize;
static std::vector<monsterData> _monstersData;

void Util::setSw(float s)
{
	scalex = s;
}

float Util::getSw()
{
	return scalex;
}
void Util::setSh(float s)
{
	scaley = s;
}

float Util::getSh()
{
	return scaley;
}
Size Util::getScreenSize()
{
	return frameSize;
}
void Util::setScreenSize(Size s)
{
	frameSize = s;
}
int Util::getRandom(int x, int y)
{
	auto rand = RandomHelper();
	return rand.random_int(x, y);
}

bool Util::initMonsters()
{
	bool bret = false;

	rapidjson::Document doc;
	ssize_t size = 0;
	unsigned char *pBytes = NULL;

	do
	{
		pBytes = cocos2d::FileUtils::getInstance()->getFileData("data/monsters.json", "r", &size);

		CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);

		std::string load_str((const char*)pBytes, size);

		CC_SAFE_DELETE_ARRAY(pBytes);

		doc.Parse<0>(load_str.c_str());

		CC_BREAK_IF(doc.HasParseError());
		CC_BREAK_IF(!doc.IsArray());

		monsterData data;

		for (rapidjson::SizeType i = 0; i < doc.Size(); i++)
		{
			const rapidjson::Value &p = doc[i];
			if (p.HasMember("id"))
			{
				data.id = p["id"].GetInt();
			}
			if (p.HasMember("name"))
			{
				data.name = p["name"].GetString();
			}
			if (p.HasMember("hpUpper"))
			{
				data.hpUpper = (float)p["hpUpper"].GetDouble();
			}
			if (p.HasMember("speed"))
			{
				data.speed = (float)p["speed"].GetDouble();
			}
			if (p.HasMember("damage"))
			{
				data.damage = (float)p["damage"].GetDouble();
			}
			if (p.HasMember("damageAvg"))
			{
				data.damageAvg = (float)p["damageAvg"].GetDouble();
			}
			if (p.HasMember("score"))
			{
				data.score = (float)p["score"].GetDouble();
			}			
			if (p.HasMember("dropPercent"))
			{
				data.dropPercent = (float)p["dropPercent"].GetDouble();
			}
			_monstersData.push_back(data);
		}

		bret = true;
	} while (0);

	return bret;
}

std::vector<monsterData> Util::getMonsterData()
{
	return _monstersData;
}

//1 医疗包(20) 2 加速(10) 3 升级弹药(3) 4 多重射击(3) 5 护盾(3) 6 怪物静止(5) 7 手雷(10) 8 地雷(10) 9 无敌(1)  -1金币(35)
int Util::getRandomProps()
{
	int i = getRandom(1, 100);

	if (0 < i && i <= 20)
	{
		return 0;
	}
	else if (20 < i && i <= 30)
	{
		return 1;
	}
	else if (30 < i && i <= 33)
	{
		return 2;
	}
	else if (33 < i && i <= 36)
	{
		return 2;
	}
	else if (36 < i && i <= 39)
	{
		return 2;
	}
	else if (39 < i && i <= 44)
	{
		return 4;
	}
	else if (44 < i && i <= 54)
	{
		return 4;
	}
	else if (54 < i && i <= 64)
	{
		return 4;
	}
	else if (64 < i && i <= 65)
	{
		return 4;
	}
	else
	{
		return -1;
	}
}