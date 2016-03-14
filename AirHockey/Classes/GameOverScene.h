#pragma once
#include "resources.h"


class GameOverScene : public cocos2d::Layer
{
public:
	CREATE_FUNC(GameOverScene);
	GameOverScene() = default;
	~GameOverScene() = default;

	static cocos2d::Scene* createScene(std::string winner);
private:
	void goToMainMenuScene(cocos2d::Ref *sender);
	bool init() override;
};
