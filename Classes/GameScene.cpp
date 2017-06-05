#include "GameScene.h"
USING_NS_CC;
Scene* GameScene::createScene()
{
	// ����һ����������
	auto scene = Scene::create();
	// ���������
	auto layer = GameScene::create();
	// ������Ϊ�ӽڵ���ӵ�����
	scene->addChild(layer);
	// ���س�������
	return scene;
}

bool GameScene::init()
{

	if (!Layer::init())
	{
		return false;
	}
	// ��ôӴ��ڴ�С
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//��ʾ��ͼ
	  map = MapLayer::create();
	  map->setScale(1.5f);
    addChild(map, 0);

	//һ�����
	auto objects = (map->getMap())->getObjectGroup("Object");
	ValueMap mapPlayer = objects->getObject("player");
	int x = mapPlayer.at("x").asInt();
	int y = mapPlayer.at("y").asInt();
	_player =Player::create();
	// ����λ�ò����Ϊ��ͼ���ӽڵ�
	_player->setPosition(x, y);
	_player->setAnchorPoint(_player->getAnchorPoint() + Vec2(0, -0.5));
	map->getMap()->addChild(_player, 4);

	map->create_BlockVector(_breakableBlockVector, _giftVector);
	// ���������¼�������
	auto keyBoardListener = EventListenerKeyboard::create();
	//���������£�map���������ֵ����Ϊtrue
	keyBoardListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event* event) {
		keys[code] = true;
		if (code != EventKeyboard::KeyCode::KEY_SPACE) {
			_player->stopAllActions();
			_player->ForeverMove(code);
		}
	};
	//�������ɿ���map���������ֵ����Ϊfalse
	keyBoardListener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event* event) {
		keys[code] = false;
		_player->stopAllActions();
		auto
			leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW,
			rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
			upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW,
			downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW,
			space = EventKeyboard::KeyCode::KEY_SPACE;
		if (isKeyPressed(leftArrow)) {
			_player->ForeverMove(leftArrow);
		}
		else if (isKeyPressed(rightArrow))
		{
			_player->ForeverMove(rightArrow);
		}
		else if (isKeyPressed(upArrow))
		{
			_player->ForeverMove(upArrow);
		}
		else if (isKeyPressed(downArrow))
		{
			_player->ForeverMove(downArrow);
		}
		else {
			_player->StandMove(code);
		}
	};
	// ��Ӧ�����¼�����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
	// ��Ϸ��ѭ��,ÿ֡�����õĺ���
	this->scheduleUpdate();
	return true;
}



//�жϼ����Ƿ�ס
bool GameScene::isKeyPressed(EventKeyboard::KeyCode code) {
	return keys[code];
}
//�������λ��
void GameScene::UpdatePosition(float delta) {
	//�ĸ������
	auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW,
		rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
		upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW,
		downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW,
	space = EventKeyboard::KeyCode::KEY_SPACE;

	int arrow = isKeyPressed(leftArrow) + isKeyPressed(rightArrow) + isKeyPressed(upArrow) + isKeyPressed(downArrow);

	//ͬʱ���·�����Ϳո����Ҳ�ɷ���һ��ˮ��
	if ((isKeyPressed(space) && arrow)||(isKeyPressed(space))) {
		keyPressedDuration(space);
		keys[space] = false;
	}

	//���·����������ƶ�
	if (isKeyPressed(leftArrow)) {
		keyPressedDuration(leftArrow);
	}
	else if (isKeyPressed(rightArrow)) {
		keyPressedDuration(rightArrow);
	}
	else if (isKeyPressed(upArrow)) {
		keyPressedDuration(upArrow);
	}
	else if (isKeyPressed(downArrow)) {
		keyPressedDuration(downArrow);
	}
}


//ÿ֡����������������»���
void GameScene::update(float delta) {
	//�������λ��
	UpdatePosition(delta);
	//�ж��Ƿ���������
	giftcollide(delta);
}


//���̰��º������
void GameScene::keyPressedDuration(EventKeyboard::KeyCode code) {
	int Move=4;
	switch (code) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		Move=0;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		Move = 1;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		Move = 2;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		Move = 3;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		if (_popVector.size() < popMax)
		{
			//���λ��
			Vec2 _tilePlayer = tileCoordForPosition(_player->getPosition());
			Vec2 _popPosition = centerPositionForTileCoord(_tilePlayer);

			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("popo.plist");

			//����һ�������ڸ��ӵ�����
			Sprite* pop = Sprite::createWithSpriteFrameName("pop_1.png");
			pop->setAnchorPoint(Vec2(0.5, 0.5));
			pop->setPosition(_popPosition);
			pop->setScale(0.9f);
			_popVector.pushBack(pop);
			//�������ݵ�zorder
			map->getMap()->addChild(pop, 1);
			//�����ݱ�����vector�����ݱ�ը����ʱ
			DelayTime * _delayDelete = DelayTime::create(3.0f);
			DelayTime *e = DelayTime::create(0.5f);
			auto callFunc1 = CallFunc::create([=] {

				// ��ʹ�þ���֡�����еľ��鴴��һ������������������
				auto animation = Animation::create();
				// ѭ���Ӿ���֡�����л�ȡ��ͼƬ�������Ӧ�ľ���֡��ɶ���
				for (int i = 1; i <= 3; i++) {
					std::string szName = StringUtils::format("pop_%d.png", i);
					// ������ͼƬ���Ϊ����֡��������֡��
					animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szName));
				}
				// ���ö������ŵ����ԣ�3��/15֡
				animation->setDelayPerUnit(1.0f / 3.0f);
				// �þ�������ڶ���ִ�����ָ������״̬
				animation->setRestoreOriginalFrame(false);
				animation->setLoops(-1);//��ʾѭ������
				auto animate = Animate::create(animation);
				pop->runAction(animate);
			});
			auto callFunc2 = CallFunc::create([=] {
				// ��ʹ�þ���֡�����еľ��鴴��һ������������������
				auto animation = Animation::create();
				// ѭ���Ӿ���֡�����л�ȡ��ͼƬ�������Ӧ�ľ���֡��ɶ���
				for (int i = 4; i <= 7; i++) {
					std::string szName = StringUtils::format("pop_%d.png", i);
					// ������ͼƬ���Ϊ����֡��������֡��
					animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szName));
				}
				// ���ö������ŵ����ԣ�3��/15֡
				animation->setDelayPerUnit(1.0f / 12.0f);
				// �þ�������ڶ���ִ�����ָ������״̬
				animation->setRestoreOriginalFrame(false);
				animation->setLoops(1);//��ʾѭ������
				auto animate = Animate::create(animation);
				auto hide = Hide::create();//����֮������
				auto action = Sequence::create(animate, hide, NULL);
				auto popx = _popVector.at(0);//��õ�һ������
				Vec2 popPosition = popx->getPosition();
				popx->runAction(action);
				//��ʱ��������
				Vector<Action*> leftAction;
				Vector<Action*> rightAction;
				Vector<Action*>	upAction;
				Vector<Action*> downAction;
				//��ʱ��������
				Vector<Sprite*> leftSprite;
				Vector<Sprite*> rightSprite;
				Vector<Sprite*> upSprite;
				Vector<Sprite*> downSprite;
				//ˮ������
				int leftWaterLength = power,
					rightWaterLength = power,
					upWaterLength = power,
					downWaterLength = power;

				//�ж�ˮ�������Ƕ���
				for (int i = 0; i < leftWaterLength; i++)
				{
					if (collide(Vec2(tileCoordForPosition(popx->getPosition()).x - i - 1, tileCoordForPosition(popx->getPosition()).y), POP))//ȱһ������
					{
						leftWaterLength = i;
						break;
					}
				}

				for (int i = 0; i < rightWaterLength; i++)
					if (collide(Vec2(tileCoordForPosition(popx->getPosition()).x + i +1, tileCoordForPosition(popx->getPosition()).y), POP))
					{
						rightWaterLength = i;
						break;
					}

				for (int i = 0; i < upWaterLength; i++)
					if (collide(Vec2(tileCoordForPosition(popx->getPosition()).x, tileCoordForPosition(popx->getPosition()).y - i - 1), POP))
					{
						upWaterLength = i;
						break;
					}

				for (int i = 0; i < downWaterLength; i++)
					if (collide(Vec2(tileCoordForPosition(popx->getPosition()).x, tileCoordForPosition(popx->getPosition()).y + i + 1), POP))
					{
						downWaterLength = i;
						break;
					}
				//ˮ������Ч��
				if (rightWaterLength != 0)
				{
					for (int i = 1; i <= rightWaterLength; i++)
					{
						auto sprite = Sprite::create();
						sprite->setPosition(Vec2(popx->getPositionX() + 40 * i, popx->getPositionY()));
						rightSprite.pushBack(sprite);//�������������
						map->getMap()->addChild(sprite, 10);
						if (rightWaterLength != i)//ˮ���м�Ķ���
						{
							auto animation = Animation::create();
							for (int j = 1; j <= 4; ++j)
								animation->addSpriteFrameWithFileName(StringUtils::format("Explosion_right_%d.png", j));
							animation->setDelayPerUnit(0.1f);
							auto animate = Animate::create(animation);
							auto hide = Hide::create();
							auto delay = DelayTime::create(0.f);
							auto action = Sequence::create(delay, animate, hide, NULL);
							rightAction.pushBack(action);
						}
						else {//ˮ��β���Ķ���
							auto animation = Animation::create();
							for (int j = 1; j <= 4; j++)
								animation->addSpriteFrameWithFileName(StringUtils::format("Explosion_right_0%d.png", j));
							animation->setDelayPerUnit(0.1f);
							auto animate = Animate::create(animation);
							auto hide = Hide::create();
							auto delay = DelayTime::create(0.f);
							auto action = Sequence::create(delay, animate, hide, NULL);
							rightAction.pushBack(action);
						}
					}
				}

				if (leftWaterLength != 0)
				{
					for (int i = 1; i <= leftWaterLength; i++)
					{
						auto sprite = Sprite::create();
						sprite->setPosition(Vec2(popx->getPositionX() - 40 * i, popx->getPositionY()));
						leftSprite.pushBack(sprite);//�������������
						map->getMap()->addChild(sprite, 10);
						if (leftWaterLength != i)//ˮ���м�Ķ���
						{
							auto animation = Animation::create();
							for (int j = 1; j <= 4; j++)
								animation->addSpriteFrameWithFileName(StringUtils::format("Explosion_left_%d.png", j));
							animation->setDelayPerUnit(0.1f);
							auto animate = Animate::create(animation);
							auto hide = Hide::create();
							auto delay = DelayTime::create(0.f);
							auto action = Sequence::create(delay, animate, hide, NULL);
							leftAction.pushBack(action);
						}
						else {//ˮ��β���Ķ���
							auto animation = Animation::create();
							for (int j = 1; j <= 4; j++)
								animation->addSpriteFrameWithFileName(StringUtils::format("Explosion_left_0%d.png", j));
							animation->setDelayPerUnit(0.1f);
							auto animate = Animate::create(animation);
							auto hide = Hide::create();
							auto delay = DelayTime::create(0.f);
							auto action = Sequence::create(delay, animate, hide, NULL);
							leftAction.pushBack(action);
						}
					}
				}
				if (upWaterLength != 0)
				{
					for (int i = 1; i <= upWaterLength; i++)
					{
						auto sprite = Sprite::create();
						sprite->setPosition(Vec2(popx->getPositionX(), popx->getPositionY() + 40 * i));
						upSprite.pushBack(sprite);//�������������
						map->getMap()->addChild(sprite, 10);
						if (upWaterLength != i)//ˮ���м�Ķ���
						{
							auto animation = Animation::create();
							for (int j = 1; j <= 4; j++)
								animation->addSpriteFrameWithFileName(StringUtils::format("Explosion_up_%d.png", j));
							animation->setDelayPerUnit(0.1f);
							auto animate = Animate::create(animation);
							auto hide = Hide::create();
							auto delay = DelayTime::create(0.f);
							auto action = Sequence::create(delay, animate, hide, NULL);
							upAction.pushBack(action);
						}
						else {//ˮ��β���Ķ���
							auto animation = Animation::create();
							for (int j = 1; j <= 4; j++)
								animation->addSpriteFrameWithFileName(StringUtils::format("Explosion_up_0%d.png", j));
							animation->setDelayPerUnit(0.1f);
							auto animate = Animate::create(animation);
							auto hide = Hide::create();
							auto delay = DelayTime::create(0.f);
							auto action = Sequence::create(delay, animate, hide, NULL);
							upAction.pushBack(action);
						}
					}
				}
				if (downWaterLength != 0)
				{
					for (int i = 1; i <= downWaterLength; i++)
					{
						auto sprite = Sprite::create();
						sprite->setPosition(Vec2(popx->getPositionX(), popx->getPositionY() - 40 * i));
						downSprite.pushBack(sprite);//�������������
						map->getMap()->addChild(sprite, 10);
						if (downWaterLength != i)//ˮ���м�Ķ���
						{
							auto animation = Animation::create();
							for (int j = 1; j <= 4; j++)
								animation->addSpriteFrameWithFileName(StringUtils::format("Explosion_down_%d.png", j));
							animation->setDelayPerUnit(0.1f);
							auto animate = Animate::create(animation);
							auto hide = Hide::create();
							auto delay = DelayTime::create(0.f);
							auto action = Sequence::create(delay, animate, hide, NULL);
							downAction.pushBack(action);
						}
						else {//ˮ��β���Ķ���
							auto animation = Animation::create();
							for (int j = 1; j <= 4; j++)
								animation->addSpriteFrameWithFileName(StringUtils::format("Explosion_down_0%d.png", j));
							animation->setDelayPerUnit(0.1f);
							auto animate = Animate::create(animation);
							auto hide = Hide::create();
							auto delay = DelayTime::create(0.f);
							auto action = Sequence::create(delay, animate, hide, NULL);
							downAction.pushBack(action);
						}
					}
				}

				//ִ�����ж�������������ɾ��
				while (rightWaterLength != 0 && rightSprite.size()>0)
				{
					auto sprite = rightSprite.at(0);
					auto action = rightAction.at(0);
					sprite->runAction(action);
					rightSprite.eraseObject(sprite);
					rightAction.eraseObject(action);
				}

				while (leftWaterLength != 0 && leftSprite.size()>0)
				{
					auto sprite = leftSprite.at(0);
					auto action = leftAction.at(0);
					sprite->runAction(action);
					leftSprite.eraseObject(sprite);
						leftAction.eraseObject(action);
				}

				while (upWaterLength != 0 && upSprite.size()>0)
				{
					auto sprite = upSprite.at(0);
					auto action = upAction.at(0);
					sprite->runAction(action);
					upSprite.eraseObject(sprite);
					upAction.eraseObject(action);
				}

				while (downWaterLength != 0 && downSprite.size()>0)
				{
					auto sprite = downSprite.at(0);
					auto action = downAction.at(0);
					sprite->runAction(action);
					downSprite.eraseObject(sprite);
					downAction.eraseObject(action);
				}
				//����λ��
				Vec2 popPositionForTileMap = tileCoordForPosition(popPosition);

				Vec2 _BubblePosition[4];
				//�ĸ���ըλ��
				if (leftWaterLength == power)
				{
					_BubblePosition[0] = popPositionForTileMap - Vec2(leftWaterLength, 0);
				}
				else
				{
					_BubblePosition[0] = popPositionForTileMap - Vec2(leftWaterLength + 1, 0);
				}
				if (rightWaterLength == power)
				{
					_BubblePosition[1] = popPositionForTileMap + Vec2(rightWaterLength, 0);
				}
				else
				{
					_BubblePosition[1] = popPositionForTileMap + Vec2(rightWaterLength + 1, 0);
				}
				if (upWaterLength == power)
				{
					_BubblePosition[2] = popPositionForTileMap - Vec2(0, upWaterLength);
				}
				else
				{
					_BubblePosition[2] = popPositionForTileMap - Vec2(0, upWaterLength + 1);
				}
				if (downWaterLength == power)
				{
					_BubblePosition[3] = popPositionForTileMap + Vec2(0, downWaterLength);
				}
				else
				{
					_BubblePosition[3] = popPositionForTileMap + Vec2(0, downWaterLength + 1);
				}
				map->boom(_BubblePosition);
			});
			auto callFunc3 = CallFunc::create([=] {
				//���ݱ�ըʱ����ȡ��ͼ���ִ�ĵ�һ�������õ����ݲ�ɾ����
				auto pop = _popVector.at(0);
				map->removeChild(pop);
				_popVector.eraseObject(pop);
			});
			//����һ�����ж�������������->���ݼ�������vector->���ݱ�ը
			auto action = Sequence::create(callFunc1, _delayDelete, callFunc2, e, callFunc3, NULL);
			pop->runAction(action);
		}
		
		break;
	}
	//��ʼ�ж��Ƿ�ײǽ
	if (Move != 4)
	{
		if (Move == 0)
			rightMove(Move, 2, 2, 6);
		if (Move == 1)
			rightMove(Move, 3, 3, 7);
		if (Move == 2)
			rightMove(Move, 1, 4, 5);
		if (Move == 3)
			rightMove(Move, 0, 6, 7);
	}
}

void GameScene::rightMove(int Move,int flag1,int flag2,int flag3)
{
	move[0][0] = -(2 + addSpeed);
	move[1][0] = 2 + addSpeed;
	move[2][1] = 2 + addSpeed;
	move[3][1] = -(2 + addSpeed);
	auto destination = _player->getPosition() + Vec2(move[Move][0], move[Move][1]);
	auto moveTo = MoveTo::create(0.01, destination);
	auto tmp=tileCoordForPosition(destination);     //����ʹ��
	auto delt=15;
	//�ж��Ƿ���������
	auto now= tileCoordForPosition(_player->getPosition());
	if (!_popVector.empty()&&now != tileCoordForPosition(_popVector.at(_popVector.size() - 1)->getPosition()))
		on_pop = false;
	else
		on_pop = true;
	Vec2 tileCoord[8];//0 ��,1 ��, 2 ��, 3 �� ,4 ����, 5 ����, 6 ����, 7 ����
	tileCoord[0] = tileCoordForPosition(destination + Vec2(0, -3));
	tileCoord[1] = tileCoordForPosition(destination + Vec2(0, 2*delt));
	tileCoord[2] = tileCoordForPosition(destination + Vec2(-delt, delt));
	tileCoord[3] = tileCoordForPosition(destination + Vec2(delt, delt));
	tileCoord[4] = tileCoordForPosition(destination + Vec2(-delt, 2*delt));
	tileCoord[5] = tileCoordForPosition(destination + Vec2(delt, 2*delt));
	tileCoord[6] = tileCoordForPosition(destination + Vec2(-delt, -3)); 
	tileCoord[7] = tileCoordForPosition(destination + Vec2(delt, -3));
	if (!collide(tileCoord[flag1], PLAYER) && !collide(tileCoord[flag2], PLAYER) && !collide(tileCoord[flag3], PLAYER))
	{
		for (int i = 0; i < 4; i++)
		{
			moveRecord[i] = false;
		}
		_player->runAction(moveTo);
	}
	else
	{
		if (!moveRecord[Move])
		{
			auto destination = _player->getPosition() + Vec2(-move[Move][0], -move[Move][1]);
			auto moveTo = MoveTo::create(0.01, destination);
			_player->runAction(moveTo);
		}
		for (int i = 0; i < 4; i++)
		{
			moveRecord[i] = false;
		}
		moveRecord[Move] = true;
	}
}
Vec2 GameScene::centerPositionForTileCoord(const cocos2d::Vec2 &TileCoord) {
	Size mapSize = (map->getMap())->getMapSize();//TileMap���������������
	Size tileSize = (map->getMap())->getTileSize();//ͼ���С
	int x = TileCoord.x * tileSize.width + tileSize.width / 2;
	int y = (mapSize.height - TileCoord.y)*tileSize.height - tileSize.height / 2;
	return Vec2(x, y);
}

bool GameScene::collide(Vec2 position,int type)
{
	//����Ҳ���ϰ���
	int pop_size;
	if (on_pop)
		pop_size = _popVector.size() - 1;
	else
		pop_size = _popVector.size();
	for (int i = 0; i < pop_size; i++) {
		Vec2 popPosition = _popVector.at(i)->getPosition();
		Vec2 popPositionForTileMap = tileCoordForPosition(popPosition);
		if (position == popPositionForTileMap && type == PLAYER) {
			return true;
		}
	}
	//����Ƿ��ը
	for (int i = 0; i < _breakableBlockVector.size(); i++)
	{

		Vec2 popPosition = _breakableBlockVector.at(i)->getPosition();
		Sprite* erase = _breakableBlockVector.at(i);
		Vec2 popPositionForTileMap = tileCoordForPosition(popPosition);
		if (position == popPositionForTileMap)
		{
			if (type == POP)
				_breakableBlockVector.eraseObject(erase);
			return true;
		}
	}
	//ʹ��tileGid������ȡTileMap����ϵ���GID��GID�ǡ�ȫ��Ψһ��ʾ��
	if (map->judge_collide(position))
		return 1;
	return 0;
}
void GameScene::giftcollide(float delta)
{
	Vec2 playerposition = _player->getPosition();
	Vec2 playerPositionForTileMap = tileCoordForPosition(playerposition);
	for (int i = 0; i < _giftVector.size(); i++)
	{
		
		Vec2 giftPosition = _giftVector.at(i)->getPosition();
		Vec2 giftPositionForTileMap = tileCoordForPosition(giftPosition);
		SpriteGift* erase = _giftVector.at(i);
		if (playerPositionForTileMap == giftPositionForTileMap)
		{
			if (erase->getTag() == GIFT1)
			{
				power++;
			}
			else if (erase->getTag() == GIFT2)
			{
				addSpeed = 0.2 + addSpeed;
			}
			else if (erase->getTag() == GIFT3)
			{
				popMax++;
			}
			map->getMap()->removeChild(erase);
			_giftVector.eraseObject(erase);
		}
	}
}


// ����Ļ����ת��ΪTileMap���꣬��ʱû��
Vec2 GameScene::tileCoordForPosition(Vec2 position)
{// CC_CONTENT_SCALE_FACTOR Retina����2�����򷵻�1
 // ���λ�õ�x���Ե�ͼ�Ŀ��õ����ǵ�ͼ����ĵڼ������ӣ�tile��
 // ��ͼ����㣺26[����] * 64[ͼ��Ŀ�] = 1680[��ͼ��]
 // ���羫���ڵ�x������640���������ڵ�ͼ�ĸ��Ӽ��㣺640[����λ��] / 64[ͼ��Ŀ�] = 10 [����]
	int x = (int)(position.x / ((map->getMap())->getTileSize().width / CC_CONTENT_SCALE_FACTOR()));
	// ���λ�õ�y���Ե�ͼ�ĸߣ��õ����ǵ�ͼ����ڼ������ӣ�tile����
	// ������Ϊcocos2d-x��y�ᣨ���½ǣ���TileMap��y�ᣨ���Ͻǣ����෴������ʹ�õ�ͼ�ĸ߶ȼ�ȥ���λ�õ�y
	float pointHeight = (map->getMap())->getTileSize().height / CC_CONTENT_SCALE_FACTOR();
	int y = (int)(((map->getMap())->getMapSize().height * pointHeight - position.y) / pointHeight);
	return Vec2(x,y);
}

