#include "pop.h"


Animate* Pop::centerBoom1()
{
	// ��ʹ�þ���֡�����еľ��鴴��һ������������������
	auto animation = Animation::create();
	// ѭ���Ӿ���֡�����л�ȡ��ͼƬ�������Ӧ�ľ���֡��ɶ���
	for (int i = 1; i <= 3; i++) {
		animation->addSpriteFrameWithFileName(StringUtils::format("pop_%d.png", i));
	}
	// ���ö������ŵ����ԣ�3��/15֡
	animation->setDelayPerUnit(1.0f / 3.0f);
	// �þ�������ڶ���ִ�����ָ������״̬
	animation->setRestoreOriginalFrame(false);
	animation->setLoops(-1);//��ʾѭ������
	auto action = Animate::create(animation);
	return action;
}
Sequence* Pop::centerBoom2()
{
	// ��ʹ�þ���֡�����еľ��鴴��һ������������������
	auto animation = Animation::create();
	// ѭ���Ӿ���֡�����л�ȡ��ͼƬ�������Ӧ�ľ���֡��ɶ���
	for (int i = 4; i <= 7; i++) {
		animation->addSpriteFrameWithFileName(StringUtils::format("pop_%d.png", i));
	}
	// ���ö������ŵ����ԣ�3��/15֡
	animation->setDelayPerUnit(1.0f / 12.0f);
	// �þ�������ڶ���ִ�����ָ������״̬
	animation->setRestoreOriginalFrame(false);
	animation->setLoops(1);//��ʾѭ������
	auto animate = Animate::create(animation);
	auto hide = Hide::create();//����֮������
	auto action = Sequence::create(animate, hide, NULL);
	return action;
}

void Pop::destroy(int& power, Pop*& popx, Vector<Sprite*>& _breakableBlockVector, MapLayer*& map)
{
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
	leftWaterLength = power,
	rightWaterLength = power,
	upWaterLength = power,
	downWaterLength = power;

	//�ж�ˮ�������Ƕ���
	for (int i = 0; i < leftWaterLength; i++)
	{
		if (collide(Vec2(tileCoordForPosition(popx->getPosition()).x - i - 1, tileCoordForPosition(popx->getPosition()).y), POP,  _breakableBlockVector,map))//ȱһ������
		{
			leftWaterLength = i;
			break;
		}
	}

	for (int i = 0; i < rightWaterLength; i++)
		if (collide(Vec2(tileCoordForPosition(popx->getPosition()).x + i + 1, tileCoordForPosition(popx->getPosition()).y), POP, _breakableBlockVector, map))
		{
			rightWaterLength = i;
			break;
		}

	for (int i = 0; i < upWaterLength; i++)
		if (collide(Vec2(tileCoordForPosition(popx->getPosition()).x, tileCoordForPosition(popx->getPosition()).y - i - 1), POP, _breakableBlockVector, map))
		{
			upWaterLength = i;
			break;
		}

	for (int i = 0; i < downWaterLength; i++)
		if (collide(Vec2(tileCoordForPosition(popx->getPosition()).x, tileCoordForPosition(popx->getPosition()).y + i + 1), POP, _breakableBlockVector, map))
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
}
bool Pop::collide(Vec2 position, int type, Vector<Sprite*>& _breakableBlockVector, MapLayer*& map)
{
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

Vec2* Pop::setBubblePosition(int & power, Vec2 popPosition)
{
	Vec2 popPositionForTileMap = tileCoordForPosition(popPosition);
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
	return _BubblePosition;
}
