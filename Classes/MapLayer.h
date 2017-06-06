/**
* �ڲ���TMXTiledMap������ͨ��getMap����
* Ŀǰֻ֧��Ĭ�ϵ�ͼ�������������ӵ�ͼѡ����
* ͨ��boom����ʵ�����ݱ�ը���ͼ�Ľ���
* judge_collide�����ж��ض�λ���Ƿ����ϰ���
* create_BlockVector���������ϰ�������
*/
#ifndef _MAP_LAYER_
#define _MAP_LAYER

#include "cocos2d.h"
#include "SpriteGift.h"

USING_NS_CC;


enum Type
{
	PLAYER = 1,
	POP = 2,
	GIFT1 = 3,
	GIFT2 = 4,
	GIFT3 = 5
};

class MapLayer :public Layer
{
public:
	virtual bool init();
	TMXTiledMap* getMap() { return _map; }
	bool boom(Vec2 _BubblePosition[]);
	bool judge_collide(Vec2 position);
	//�󷽸����������  
	Vec2 centerPositionForTileCoord(const cocos2d::Vec2 &TileCoord);

	//��breakable��block�Ϸ�һ������ �����Ϳ��Է�����ײ
	void create_BlockVector(Vector<Sprite*> &_breakableBlockVector, Vector<SpriteGift*>& _giftVector);
	CREATE_FUNC(MapLayer);
private:
	TMXTiledMap* _map;  // ��ͼ
	TMXLayer* _collidable;  // �ϰ���
	TMXLayer* _boxbottom;//�ײ�
	Vector<TMXLayer*> _layerNames;//������
	int breakableBlocks[12][16] = {
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
};
#endif