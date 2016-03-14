#pragma once
#include "resources.h"

class CPaddle : public cocos2d::Sprite
{
private:
	cocos2d::PhysicsBody *spriteBody;
public:
	CPaddle();
	~CPaddle(void);
	static CPaddle *createWithTexture(cocos2d::Texture2D* aTexture);
private:
	cocos2d::Rect getRect();
	void onEnter() override;
	void onExit() override;
	bool initWithTexture(cocos2d::Texture2D* aTexture) override;
};