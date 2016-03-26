#pragma once

#include "MainScene.h"


class MainMenuScene : public cocos2d::Layer
{
public:
	MainMenuScene() = default;
	~MainMenuScene() = default;
	CREATE_FUNC(MainMenuScene);
	static cocos2d::Scene* createScene();
	bool init() override;
private:
	void goToGameScene(cocos2d::Ref *sender);
};
