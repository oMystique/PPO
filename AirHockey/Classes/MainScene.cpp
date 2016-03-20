#include "MainScene.h"
#include "GameOverScene.h"
#include <string>
#include <sstream>

namespace std
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream ss;
		ss << n;
		return ss.str();
	}
}

USING_NS_CC;

static const std::string BACKGROUND_IMAGE_PATH = "background.png";
static const std::string BLUE_PADDLE_IMAGE_PATH = "blue_player.png";
static const std::string RED_PADDLE_IMAGE_PATH = "red_player.png";
static const std::string BALL_IMAGE_PATH = "ball_1.png";

Scene* CMainScene::createScene()
{
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setGravity(Vec2(0.f, 0.f));
    auto layer = CMainScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);
    return scene;
}

bool CMainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0, 0.5f, 0));
	edgeBody->setDynamic(false);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);
	addChild(edgeNode);

	auto centerLineBody = PhysicsBody::createBox(Size(5, visibleSize.height));
	centerLineBody->setDynamic(false);
	centerLineBody->setContactTestBitmask(0xFFFFFFFF);
	auto centerLineNode = Node::create();
	centerLineNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	centerLineNode->setPhysicsBody(centerLineBody);
	addChild(centerLineNode);

	auto backGroundSprite = cocos2d::Sprite::create(BACKGROUND_IMAGE_PATH);
	backGroundSprite->setPosition(cocos2d::Vec2(visibleSize / 2) + origin);
	this->addChild(backGroundSprite);

	Texture2D *pBluePaddleTexture = cocos2d::Director::getInstance()->getTextureCache()->addImage(BLUE_PADDLE_IMAGE_PATH);
	Texture2D *pRedPaddleTexture = cocos2d::Director::getInstance()->getTextureCache()->addImage(RED_PADDLE_IMAGE_PATH);

	m_pBluePaddle = CPaddle::createWithTexture(pBluePaddleTexture);
	m_pBluePaddle->setPosition(Vec2(origin.x + visibleSize.width / 2 + 100,
		origin.y + visibleSize.height - m_pBluePaddle->getContentSize().height - 50));
	m_pBluePaddle->setTag(128);
	addChild(m_pBluePaddle);

	m_pRedPaddle = CPaddle::createWithTexture(pRedPaddleTexture);
	m_pRedPaddle->setPosition((Vec2(origin.x + visibleSize.width / 2 - 100,
		origin.y + visibleSize.height - m_pRedPaddle->getContentSize().height + 50)));
	m_pRedPaddle->setTag(128);
	addChild(m_pRedPaddle);

	m_pBall = CBall::ballWithTexture(cocos2d::Director::getInstance()->getTextureCache()->addImage(BALL_IMAGE_PATH));
	m_pBall->setPosition(Vec2(visibleSize / 2) + origin);
	m_pBall->setTag(100);
	addChild(m_pBall);
	auto rotateBy = RotateBy::create(0.1f, 80.f);
	auto pRepeatRotate = cocos2d::RepeatForever::create(rotateBy);
	m_pBall->runAction(pRepeatRotate);

	auto redGateBody = PhysicsBody::createBox(Size(5, visibleSize.height / 3));
	redGateBody->setDynamic(false);
	redGateBody->setContactTestBitmask(true);
	redGateBody->setContactTestBitmask(RED_GATE_CONTACT_BITMASK);
	redGateBody->setCollisionBitmask(RED_GATE_CONTACT_BITMASK);
	auto redGateNode = Node::create();
	redGateNode->setPosition(Point(0 + origin.x, visibleSize.height / 2 + origin.y));
	redGateNode->setPhysicsBody(redGateBody);
	addChild(redGateNode);

	auto blueGateBody = PhysicsBody::createBox(Size(5, visibleSize.height / 3));
	blueGateBody->setDynamic(false);
	blueGateBody->setContactTestBitmask(true);
	blueGateBody->setContactTestBitmask(BLUE_GATE_CONTACT_BITMASK);
	blueGateBody->setCollisionBitmask(BLUE_GATE_CONTACT_BITMASK);
	auto blueGateNode = Node::create();
	blueGateNode->setPosition(Point(visibleSize.width - origin.x, visibleSize.height / 2 + origin.y));
	blueGateNode->setPhysicsBody(blueGateBody);
	addChild(blueGateNode);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CMainScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(CMainScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(CMainScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(CMainScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	

	m_scores = { 0, 0 };
	m_pScoresLabel = Label::createWithTTF(std::to_string(static_cast<int>(m_scores.x)) + " - " +
		std::to_string(static_cast<int>(m_scores.y)), "arial.ttf", visibleSize.height * 0.15);
	m_pScoresLabel->setColor(Color3B::WHITE);
	m_pScoresLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height - origin.y - 50));
	this->addChild(m_pScoresLabel, 10000);

	this->scheduleUpdate();

	return true;
}

bool CMainScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();
	if (((BALL_COLLISION_BITMASK == a->getCollisionBitmask()) &&
		(RED_GATE_CONTACT_BITMASK == b->getCollisionBitmask())) ||
		((BALL_COLLISION_BITMASK == b->getCollisionBitmask()) &&
		(RED_GATE_CONTACT_BITMASK == a->getCollisionBitmask())))
	{
		m_scores.y += 1;
		m_pBall->ballIsMoving(false);
		m_pScoresLabel->setString(std::to_string(static_cast<int>(m_scores.x)) + " - " +
			std::to_string(static_cast<int>(m_scores.y)));
		return true;
	}
	else if (((BALL_COLLISION_BITMASK == a->getCollisionBitmask()) &&
		(BLUE_GATE_CONTACT_BITMASK == b->getCollisionBitmask())) ||
		((BALL_COLLISION_BITMASK == b->getCollisionBitmask()) &&
			(BLUE_GATE_CONTACT_BITMASK == a->getCollisionBitmask())))
	{
		m_scores.x += 1;
		m_pScoresLabel->setString(std::to_string(static_cast<int>(m_scores.x)) + " - " +
			std::to_string(static_cast<int>(m_scores.y)));
		m_pBall->ballIsMoving(false);
		return true;
	}
	return false;
}

bool CMainScene::onTouchBegan(Touch* touch, Event* event)
{
	auto location = touch->getLocation();
	auto arr = m_pSceneWorld->getShapes(location);

	PhysicsBody* body = nullptr;
	for (auto& obj : arr)
	{
		if ((obj->getBody()->getTag() & 128) != 0)
		{
			body = obj->getBody();
		}
	}

	if (body != nullptr)
	{
		Node* pMouse = Node::create();
		auto physicsBody = PhysicsBody::create(PHYSICS_INFINITY, PHYSICS_INFINITY);
		physicsBody->setDynamic(false);
		pMouse->addComponent(physicsBody);
		pMouse->setPosition(location);
		this->addChild(pMouse);
		PhysicsJointPin* joint = PhysicsJointPin::construct(physicsBody, body, location);
		joint->setMaxForce(5000.0f * body->getMass());
		m_pSceneWorld->addJoint(joint);
		m_mouses.insert(std::make_pair(touch->getID(), pMouse));
		return true;
	}

	return false;
}

void CMainScene::onTouchMoved(Touch* touch, Event* event)
{
	auto it = m_mouses.find(touch->getID());

	if (it != m_mouses.end())
	{
		it->second->setPosition(touch->getLocation());
	}
}

void CMainScene::onTouchEnded(Touch* touch, Event* event)
{
	auto it = m_mouses.find(touch->getID());

	if (it != m_mouses.end())
	{
		this->removeChild(it->second);
		m_mouses.erase(it);
	}
}

void CMainScene::update(float dt)
{
	m_pBall->ballAction();
	if ((m_scores.x >= 6) || (m_scores.y >= 6))
	{
		Scene *pScene;
		if (m_scores.x >= 6)
		{
			pScene = GameOverScene::createScene("RED WIN");
		}
		else
		{
			pScene = GameOverScene::createScene("BLUE WIN");
		}
		Director::getInstance()->replaceScene(TransitionFade::create(0.1f, pScene));
	}
}