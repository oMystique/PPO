#include "paddle.h"
#include "HelloWorldScene.h"

USING_NS_CC;

CPaddle::CPaddle(void)
{
}

CPaddle::~CPaddle(void)
{
}

Rect CPaddle::getRect()
{
	auto s = getTexture()->getContentSize();
	return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

CPaddle* CPaddle::createWithTexture(Texture2D* aTexture)
{
	CPaddle* pPaddle = new (std::nothrow) CPaddle();
	pPaddle->initWithTexture(aTexture);
	pPaddle->autorelease();

	return pPaddle;
}

bool CPaddle::initWithTexture(Texture2D* aTexture)
{
	if (Sprite::initWithTexture(aTexture))
	{
		Sprite::setScale(0.35f);
		spriteBody = PhysicsBody::createCircle(getContentSize().width / 2, PhysicsMaterial(600, 0.5f, 600));
		spriteBody->setMass(100.f);
		spriteBody->setTag(128);
		setPhysicsBody(spriteBody);
	}

	return true;
}

void CPaddle::onEnter()
{
	Sprite::onEnter();
}

void CPaddle::onExit()
{
	Sprite::onExit();
}
