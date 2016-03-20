#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "ball.h"

class CMainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    bool init() override;
    CREATE_FUNC(CMainScene);
private:
	void setPhysicsWorld(cocos2d::PhysicsWorld *world) { m_pSceneWorld = world; };
	bool onContactBegin(cocos2d::PhysicsContact &contact);
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void update(float dt);
private:
	CBall *m_pBall;
	CPaddle *m_pRedPaddle;
	CPaddle *m_pBluePaddle;
	int m_blueScores;
	int m_redScores;
	cocos2d::Label *m_pScoresLabel;
	cocos2d::Vec2 m_scores;
	cocos2d::PhysicsWorld *m_pSceneWorld;
	std::unordered_map<int, cocos2d::Node*> m_mouses;
};

#endif 
