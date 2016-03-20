#include "ball.h"

USING_NS_CC;

CBall::CBall(void)
{
}

CBall::~CBall(void)
{
}

CBall* CBall::ballWithTexture(Texture2D* aTexture)
{
	CBall* pBall = new (std::nothrow) CBall();
	pBall->initWithTexture(aTexture);
	pBall->autorelease();
	return pBall;
}


bool CBall::initWithTexture(Texture2D* aTexture)
{
	if (Sprite::initWithTexture(aTexture))
	{
		m_visibleSize = Director::getInstance()->getVisibleSize();
		m_origin = Director::getInstance()->getVisibleOrigin();
		Sprite::setScale(0.6f);
		m_pSpriteBody = PhysicsBody::createCircle(getContentSize().width / 2, PhysicsMaterial(1.f, 1.3f, 1.f));
		m_pSpriteBody->setCollisionBitmask(1);
		m_pSpriteBody->setContactTestBitmask(true);
		m_pSpriteBody->setContactTestBitmask(BALL_COLLISION_BITMASK);
		m_pSpriteBody->setCollisionBitmask(BALL_COLLISION_BITMASK);
		m_pSpriteBody->setMass(20);
		setPhysicsBody(m_pSpriteBody);
	}

	return true;
}

void CBall::ballAction()
{
	if (!m_isMoving)
	{
		setPosition(Vec2(m_visibleSize / 2) + m_origin);
		m_pSpriteBody->setVelocity(Vec2(0, 0));
		m_isMoving = true;
	}
}

void CBall::ballIsMoving(bool isMoving)
{
	m_isMoving = isMoving;
}