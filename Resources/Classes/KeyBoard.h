/**
*ʹ��keyBoardDirection����־��ǰ����ָ��
*startKb���������̼�����
*/

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include"cocos2d.h"
USING_NS_CC;

typedef enum
{
	keyBoard_left,
	keyBoard_right,
	keyBoard_up,
	keyBoard_down,
	keyBoard_stand,
	keyBoard_space
}KBDirection;

class KeyBoard : public Layer
{
public:
	CREATE_FUNC(KeyBoard);
	void startKB();
	void stopKB();
	int keyBoardDirection;
	int mulPressed;
	virtual bool init();
private:
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
};

#endif