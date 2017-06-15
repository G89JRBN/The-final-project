#include "MapLayer.h"

bool MapLayer::init1(int a)
{
	_setMap = a;
	//��ʾ��ͼ
	if (_setMap == 1)
	{
		_map = TMXTiledMap::create("map1.tmx");
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 16; j++)
			{
					breakableBlocks[i][j] = breakableBlocks1[i][j];
			}
		}
	}
	else if (_setMap == 2)
	{
		_map = TMXTiledMap::create("map2.tmx");
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				breakableBlocks[i][j] = breakableBlocks2[i][j];
			}
		}
	}
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
	Vector<Action*> DestroyAction;//�ݻ�Ч����ʱ��������
	Vector<Sprite*> DestroySprite;
	for (int i = 0; i < 4; i++)
	{
		int m = _BubblePosition[i].x;
		int n = _BubblePosition[i].y;
		//�ĸ�����ı�ը��û�н����ͼ�һ���յľ���
		if (_boxbottom->getTileAt(_BubblePosition[i]) != nullptr && breakableBlocks[n][m] == 1)
		{
			breakableBlocks[n][m] = 0;
			Sprite* destroySprite = Sprite::create();
			destroySprite->setPosition(centerPositionForTileCoord(_BubblePosition[i]));
			destroySprite->setAnchorPoint(Vec2(0.5, 0.25));
			DestroySprite.pushBack(destroySprite);//�������������
			_map->addChild(destroySprite, 10);
			auto boomAnimation = Animation::create();
			for (unsigned i = 1; i <= 2; ++i)
			{
				boomAnimation->addSpriteFrameWithFile(StringUtils::format("Boom%d.png", i));
			}
			boomAnimation->setDelayPerUnit(1.0f / 8.0f);
			auto boomAnimate = Animate::create(boomAnimation);
			auto hideBoom = Hide::create();
			auto boomAction = Sequence::create(boomAnimate, hideBoom, NULL);
			DestroyAction.pushBack(boomAction);
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
	//�ݻ�Ч��
	while (DestroySprite.size()>0)
	{
		auto sprite = DestroySprite.at(0);
		auto action = DestroyAction.at(0);
		sprite->runAction(action);
		DestroySprite.eraseObject(sprite);
		DestroyAction.eraseObject(action);
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


void MapLayer::create_BlockVector(Vector<Sprite*>& _breakableBlockVector, Vector<SpriteGift*>& _giftVector)
{
	srand((int)time(NULL));
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			int m = (int)(100.0*rand() / RAND_MAX + 1);
			if (breakableBlocks[i][j] == 1)
			{
				Vec2 giftPosition = centerPositionForTileCoord(Vec2(j, i));
				auto test = Sprite::create();
				test->setAnchorPoint(Vec2(0.5, 0.5));
				test->setPosition(giftPosition);
				_breakableBlockVector.pushBack(test);
				this->addChild(test, 0);
				if (m <= 10)
				{//ҩˮ
					SpriteGift* Gift1 = SpriteGift::create("Gift1_1.png");
					Gift1->setAnchorPoint(Vec2(0.5, 0.5));
					Gift1->setPosition(giftPosition);
					_map->addChild(Gift1, 1);
					Gift1->setTag(GIFT1);
					_giftVector.pushBack(Gift1);
					auto animate = getAnimateByName("Gift1_", 0.1f, 3);
					auto repeatAnimate = RepeatForever::create(animate);
					Gift1->runAction(repeatAnimate);
				}
				else if (m >= 15 && m <= 25)
				{//Ь��
					SpriteGift* Gift2 = SpriteGift::create("Gift2_1.png");
					Gift2->setAnchorPoint(Vec2(0.5, 0.5));
					Gift2->setPosition(giftPosition);
					_map->addChild(Gift2, 1);
					Gift2->setTag(GIFT2);
					_giftVector.pushBack(Gift2);
					auto animate = getAnimateByName("Gift2_", 0.1f, 3);
					auto repeatAnimate = RepeatForever::create(animate);
					Gift2->runAction(repeatAnimate);
				}
				else if (m >= 30 && m <= 50)
				{//����
					SpriteGift* Gift3 = SpriteGift::create("Gift3_1.png");
					Gift3->setAnchorPoint(Vec2(0.5, 0.5));
					Gift3->setPosition(giftPosition);
					_map->addChild(Gift3, 1);
					Gift3->setTag(GIFT3);
					_giftVector.pushBack(Gift3);
					auto animate = getAnimateByName("Gift3_", 0.1f, 3);
					auto repeatAnimate = RepeatForever::create(animate);
					Gift3->runAction(repeatAnimate);
				}
			}
		}
	}
}
Animate * MapLayer::getAnimateByName(std::string animName, float delay, int animNum)
{
	// ����һ������
	Animation* animation = Animation::create();
	// ѭ���Ӿ���֡�����л�ȡ��ͼƬ�������Ӧ�ľ���֡��ɶ���
	for (unsigned int i = 1; i <= animNum; i++) {
		std::string frameName = animName;

		//�ڶ���֡���ƺ�������
		frameName.append(StringUtils::format("%d", i)).append(".png");
		animation->addSpriteFrameWithFile(frameName.c_str());
	}
	//���ö�����ʱ
	animation->setDelayPerUnit(delay);

	//�ڲ����궯��ʱ�ָ�����ʼ֡
	animation->setRestoreOriginalFrame(true);
	Animate* animate = Animate::create(animation);

	return animate;
}
