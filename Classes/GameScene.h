#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"
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
	// ����Ļ����ת��ΪTileMap���꣬��ʱû��
	Vec2 tileCoordForPosition(Vec2 position);
   //�жϼ����Ƿ�ס
	bool isKeyPressed(EventKeyboard::KeyCode code);
	//�󷽸����������  
	Vec2 centerPositionForTileCoord(const cocos2d::Vec2 &TileCoord);
	//������Զִ���������
	void ForeverMove(EventKeyboard::KeyCode code);
	//���̰��º������
	void keyPressedDuration(EventKeyboard::KeyCode code);
	//����λ��
	void UpdatePosition(float delta);
	//ͨ���������ֵõ���Ӧ�Ķ���
	Animate* getAnimateByName(std::string animName, float delay, int animNum);
	/**
	*��player�ŵ�����Ϊê�㣬����������Ϊԭ��
	*�����˸����㣬ÿ�δ�����Ҫʹ�õĵ�
	*���м�⣬�����һ��Ҫ�����ϰ����ֹͣ������1���أ���ֹ��ס��
	*/
	void rightMove(int offsetX,int offsetY,int flag1,int flag2,int flag3);
	// �ص����º������ú���ÿһ֡�������
	void update(float delta);
	//ʹ��CREATE_FUNC�괴����ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�
	CREATE_FUNC(GameScene);
	///�ж��Ƿ�������ϰ���
	bool collide(Vec2 position,int type);
private:

	//���̰�����¼
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	TMXTiledMap* map;  // ��ͼ
	Sprite* _player;  // ��Ҿ���
	TMXLayer* _collidable;  // �ϰ���
	TMXLayer* _boxbottom;//�ײ�
	Vector<TMXLayer*> _layerNames;//������
	Vector<Sprite* > _popVector;//���ݲ�
	Vector<Sprite*> _breakableBlockVector;//�ɱ�ը������
	int power = 2;//��������
	//�����ҡ��ϡ��µľ�̬ͼƬ�������Ӧ�����ƶ�ʱ���ô���ͼ�����滻
	CCTexture2D *_player_texture_left;
	CCTexture2D *_player_texture_right;
	CCTexture2D *_player_texture_up;
	CCTexture2D *_player_texture_down;
};

#endif
