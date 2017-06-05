#include "MapLayer.h"
bool MapLayer::init()
{
	//��ʾ��ͼ
	_map = TMXTiledMap::create("Map.tmx");
	// �ѵ�ͼ��ê���λ�ö�����Ϊԭ�㣬��������ʹ��ͼ�����½�����Ļ�����½Ƕ���
	//���õ�ͼ��ê��
	_map->setAnchorPoint(Vec2::ZERO);
	//���õ�ͼλ��
	_map->setPosition(0, 0);
	this->addChild(_map,0);
	// ��ȡ�ϰ��㣬�������ϰ��㲻�ɼ�
	_collidable = _map->getLayer("collidable");
	_collidable->setVisible(false);
	_boxbottom = _map->getLayer("boxbottom");
	_layerNames.pushBack(_map->getLayer("boxtop"));
	_layerNames.pushBack(_map->getLayer("housetop"));
	return true;
}

bool MapLayer::boom(Vec2 _BubblePosition[])
{
	Sprite* Up;//��ը����ϰ벿��
	int _GID[4];//GID
	Sprite* emptySprite = Sprite::create();//�վ���
	emptySprite->setPosition(Vec2(-1, -1));
	Vector<Sprite*> _erasePopvector;//��ʱ���ݻٽ�������
	for (int i = 0; i < 4; i++)
	{
		//�ĸ�����ı�ը��û�н����ͼ�һ���յľ���
		if (_boxbottom->getTileAt(_BubblePosition[i]) != nullptr)
		{
			_erasePopvector.pushBack(_boxbottom->getTileAt(_BubblePosition[i]));
		}
		else
		{
			_erasePopvector.pushBack(emptySprite);
		}

		_GID[i] = _boxbottom->getTileGIDAt(_BubblePosition[i]);
		//����Ҫ������Ϊ���ɼ�
		if (_GID[i])
		{
			_erasePopvector.at(i)->setVisible(false);//�°벿��
			Value properties = (_map->getPropertiesForGID(_GID[i]));
			ValueMap valuemap = properties.asValueMap();
			std::string value = valuemap.at("breakable").asString();
			if (value == "true")
			{
				Up = _layerNames.at(0)->getTileAt(_BubblePosition[i] + Vec2(0, -1));//�ϰ벿��
				Up->setVisible(false);
			}
		}
	}
	_erasePopvector.clear();
	return true;
}
bool MapLayer::judge_collide(Vec2 position)
{
	//ʹ��tileGid������ȡTileMap����ϵ���GID��GID�ǡ�ȫ��Ψһ��ʾ��
	int tileGid = _collidable->getTileGIDAt(position);
	if (tileGid)
	{
		Value properties = (_map->getPropertiesForGID(tileGid));
		ValueMap valueMap = properties.asValueMap();
		//����ValueMap������п���ײ���壬ֱ�ӷ���
		std::string value = valueMap.at("collidable").asString();
		if (value.compare("true") == 0)
		{
			return 1;
		}
	}
	return false;
}



void MapLayer::create_BlockVector(Vector<Sprite*>& _breakableBlockVector)
{
	int breakableBlocks[13][17] = {
		//0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //0
		{ 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0 }, //1
		{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0 }, //2
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 }, //3
		{ 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0 }, //4
		{ 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0 }, //5
		{ 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0 }, //6
		{ 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0 }, //7
		{ 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0 }, //8
		{ 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0 }, //9
		{ 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 }, //10
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //11 
	};
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			if (breakableBlocks[i][j] == 1)
			{
				auto test = Sprite::create();
				test->setAnchorPoint(Vec2(0.5, 0.5));
				test->setPosition(centerPositionForTileCoord(Vec2(j, i)));
				_breakableBlockVector.pushBack(test);
				this->addChild(test, 5);
			}
		}
	}
}
Vec2 MapLayer::centerPositionForTileCoord(const cocos2d::Vec2 &TileCoord) {
	Size mapSize = _map->getMapSize();//TileMap���������������
	Size tileSize = _map->getTileSize();//ͼ���С
	int x = TileCoord.x * tileSize.width + tileSize.width / 2;
	int y = (mapSize.height - TileCoord.y)*tileSize.height - tileSize.height / 2;
	return Vec2(x, y);
}
