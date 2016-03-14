#pragma once
#include "paddle.h"

class CBall : public cocos2d::Sprite
{
public:
	CBall();
	~CBall();
	static CBall* ballWithTexture(cocos2d::Texture2D* aTexture);
	void ballAction();
	void ballIsMoving(bool isMoving);
private:
	bool initWithTexture(cocos2d::Texture2D* aTexture) override;
private:
	bool m_isMoving;
	cocos2d::Size m_visibleSize;
	cocos2d::Vec2 m_origin;
	cocos2d::PhysicsBody *m_pSpriteBody;
};