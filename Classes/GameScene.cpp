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
	  map = TMXTiledMap::create("cnm.tmx");
	  // �ѵ�ͼ��ê���λ�ö�����Ϊԭ�㣬��������ʹ��ͼ�����½�����Ļ�����½Ƕ���
	//���õ�ͼ��ê��
	map->setAnchorPoint(Vec2::ZERO);
	//���õ�ͼλ��
	map->setPosition(0, 0);
	map->setScale(1.5f);
    addChild(map, 0);
	_collidable = map->getLayer("collidable");//����ϰ���
	_collidable->setVisible(false);//���ò��ɼ�
	//һ�����
	_player = Sprite::create("player_down_1.png");
	//�������ê��
	_player->setAnchorPoint(Vec2(0.5,0.3));
	// ����λ�ò����Ϊ��ͼ���ӽڵ�
	_player->setPosition(40, 40 );
	_player->setScale(0.8f);
	//�ڵ�Ч��ʵ�ֽ�������Ҫ������ڵ��������zOrderֵ�����ó�<2��������ҵ�zOrder��Ƴ�2���Ϳ���ʵ���ڵ�Ч���ˡ�											  
	map->addChild(_player, 2);
	//���ĸ�������ƶ�ͼ���뻺��
	_player_texture_left = CCTextureCache::sharedTextureCache()->addImage("player_left_1.png");
	_player_texture_right = CCTextureCache::sharedTextureCache()->addImage("player_right_1.png");
	_player_texture_up = CCTextureCache::sharedTextureCache()->addImage("player_up_1.png");
	_player_texture_down = CCTextureCache::sharedTextureCache()->addImage("player_down_1.png");
	// ���������¼�������
	auto keyBoardListener = EventListenerKeyboard::create();
	//���������£�map���������ֵ����Ϊtrue
	keyBoardListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event* event) {
		keys[code] = true;
		if (code != EventKeyboard::KeyCode::KEY_SPACE) {
			_player->stopAllActions();
			this->ForeverMove(code);
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
			this->ForeverMove(leftArrow);
		}
		else if (isKeyPressed(rightArrow)) {
			this->ForeverMove(rightArrow);
		}
		else if (isKeyPressed(upArrow)) {
			this->ForeverMove(upArrow);
		}
		else if (isKeyPressed(downArrow)) {
			this->ForeverMove(downArrow);
		}
		else {
			if ((EventKeyboard::KeyCode::KEY_LEFT_ARROW == code)) {
				_player->setTexture(_player_texture_left);
			}
			else if (EventKeyboard::KeyCode::KEY_RIGHT_ARROW == code) {
				_player->setTexture(_player_texture_right);
			}
			else if (EventKeyboard::KeyCode::KEY_UP_ARROW == code) {
				_player->setTexture(_player_texture_up);
			}
			else if (EventKeyboard::KeyCode::KEY_DOWN_ARROW == code) {
				_player->setTexture(_player_texture_down);
			}
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
	if ((isKeyPressed(space) && arrow)) {
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
	else if (isKeyPressed(space)) {
		keyPressedDuration(space);
	}
}


//ÿ֡����������������»���
void GameScene::update(float delta) {
	//�������λ��
	UpdatePosition(delta);
}


//���̰��º������
void GameScene::keyPressedDuration(EventKeyboard::KeyCode code) {
	int offsetX = 0, offsetY = 0;
	switch (code) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		offsetX -= 2;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		offsetX += 2;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		offsetY += 2;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		offsetY -= 2;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE: 
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
		map->addChild(pop, 1);
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
			animation->setDelayPerUnit(1.0f / 8.0f);
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
			for (int i = 0; i <= leftWaterLength; i++)
			{
				if (0==1)//ȱһ������
				{
					leftWaterLength = i;
					break;
				}
			}

			for (int i = 0; i <= rightWaterLength; i++)
				if (0==1)
				{
					rightWaterLength = i;
					break;
				}

			for (int i = 0; i <= upWaterLength; i++)
				if (0==1)
				{
					upWaterLength = i;
					break;
				}

			for (int i = 0; i <= downWaterLength; i++)
				if (0==1)
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
					map->addChild(sprite, 10);
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
					map->addChild(sprite, 10);
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
					map->addChild(sprite, 10);
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
					map->addChild(sprite, 10);
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



		});
		auto callFunc3 = CallFunc::create([=] {
			//���ݱ�ըʱ����ȡ��ͼ���ִ�ĵ�һ�������õ����ݲ�ɾ����
			auto pop = _popVector.at(0);
			map->removeChild(pop);
			_popVector.eraseObject(pop);
		});
		//����һ�����ж�������������->���ݼ�������vector->���ݱ�ը
		auto action = Sequence::create(callFunc1, _delayDelete, callFunc2, e,callFunc3,NULL);
		pop->runAction(action);
		break;
	}
		auto moveTo = MoveTo::create(0.06, _player->getPosition() + Vec2(offsetX, offsetY));
		_player->runAction(moveTo);
}
// ����Ļ����ת��ΪTileMap���꣬��ʱû��
Vec2 GameScene::tileCoordForPosition(Vec2 position)
{// CC_CONTENT_SCALE_FACTOR Retina����2�����򷵻�1
 // ���λ�õ�x���Ե�ͼ�Ŀ��õ����ǵ�ͼ����ĵڼ������ӣ�tile��
 // ��ͼ����㣺26[����] * 64[ͼ��Ŀ�] = 1680[��ͼ��]
 // ���羫���ڵ�x������640���������ڵ�ͼ�ĸ��Ӽ��㣺640[����λ��] / 64[ͼ��Ŀ�] = 10 [����]
	int x = (int)(position.x / (map->getTileSize().width / CC_CONTENT_SCALE_FACTOR()));
	// ���λ�õ�y���Ե�ͼ�ĸߣ��õ����ǵ�ͼ����ڼ������ӣ�tile����
	// ������Ϊcocos2d-x��y�ᣨ���½ǣ���TileMap��y�ᣨ���Ͻǣ����෴������ʹ�õ�ͼ�ĸ߶ȼ�ȥ���λ�õ�y
	float pointHeight = map->getTileSize().height / CC_CONTENT_SCALE_FACTOR();
	int y = (int)((map->getMapSize().height * pointHeight - position.y) / pointHeight);
	return Vec2(x,y);
}
//�������������
Vec2 GameScene::centerPositionForTileCoord(const cocos2d::Vec2 &TileCoord) {
	Size mapSize = map->getMapSize();//TileMap���������������
	Size tileSize =map->getTileSize();//ͼ���С
	int x = TileCoord.x * tileSize.width + tileSize.width / 2;
	int y = (mapSize.height - TileCoord.y)*tileSize.height - tileSize.height / 2;
	return Vec2(x, y);
}
void GameScene::ForeverMove(EventKeyboard::KeyCode code) {

	Animate* animate;
	std::string Name = "player";

	switch (code) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		animate = getAnimateByName(Name + "_left_", 0.1f, 6);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		animate = getAnimateByName(Name + "_right_", 0.1f, 6);
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		animate = getAnimateByName(Name + "_up_", 0.05f, 6);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		animate = getAnimateByName(Name + "_down_", 0.1f, 6);
		break;
	}
	//����һ������ �ظ�ִ�ж���
	auto repeatAnimate = RepeatForever::create(animate);
	_player->runAction(repeatAnimate);
}
//ͨ���������ֵõ���Ӧ�Ķ���
Animate * GameScene::getAnimateByName(std::string animName, float delay, int animNum)
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
