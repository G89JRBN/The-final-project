#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"
#include"Player.h"
#include"MapLayer.h"
USING_NS_CC;

enum Type
{
	PLAYER = 1,
	POP = 2
};
class GameScene : public cocos2d::Layer
{
public:
	//����Scene����
	static cocos2d::Scene* createScene();
	//init��������ɳ�ʼ������
	virtual bool init();
	// ����Ļ����ת��ΪTileMap����
	Vec2 tileCoordForPosition(Vec2 position);
   //�жϼ����Ƿ�ס
	bool isKeyPressed(EventKeyboard::KeyCode code);
	//�󷽸����������  
	Vec2 centerPositionForTileCoord(const cocos2d::Vec2 &TileCoord);
	//���̰��º������
	void keyPressedDuration(EventKeyboard::KeyCode code);
	//����λ��
	void UpdatePosition(float delta);
	/**
	*��player�ŵ�����Ϊê�㣬����������Ϊԭ��
	*�����˸����㣬ÿ�δ�����Ҫʹ�õĵ�
	*���м�⣬�����һ��Ҫ�����ϰ����ֹͣ������1���أ���ֹ��ס��
	*/
	void rightMove(int Move,int flag1,int flag2,int flag3);
	// �ص����º������ú���ÿһ֡�������
	void update(float delta);
	//ʹ��CREATE_FUNC�괴����ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�
	CREATE_FUNC(GameScene);
	//�ж��Ƿ�������ϰ���
	bool collide(Vec2 position,int type);
private:

	//���̰�����¼
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	MapLayer * map;  // ��ͼ
	Player* _player;  // ��Ҿ���
	Vector<Sprite* > _popVector;//���ݲ�
	Vector<Sprite*> _breakableBlockVector;//�ɱ�ը������
	int power = 2;//��������
	bool on_pop=false;
	//��¼�ϴ��ж�������������
	bool moveRecord[4] = { false,false,false,false };
	double move[4][2] = { { -2,0 },{ 2,0 },{ 0,2 },{ 0,-2 } };
};

#endif
