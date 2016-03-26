#include "GameOverScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

std::string g_winner;

static const std::string BACKGROUND_MENU_IMAGE_PATH = "background_menu.png";
static const std::string RESTART_BUTTON_NONCLICKED_IMAGE_PATH = "restart_nonclicked.png";
static const std::string RESTART_BUTTON_CLICKED_IMAGE_PATH = "restart_clicked.png";

using namespace cocostudio::timeline;

Scene* GameOverScene::createScene(std::string winner)
{
	g_winner = winner;
	auto scene = make_cc<Scene>();
	auto layer = make_cc<GameOverScene>();
	scene->addChild(layer);
	return scene;
}

bool GameOverScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create(BACKGROUND_MENU_IMAGE_PATH);
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));


	this->addChild(backgroundSprite);
	auto retryItem = MenuItemImage::create(RESTART_BUTTON_NONCLICKED_IMAGE_PATH, RESTART_BUTTON_CLICKED_IMAGE_PATH,
		CC_CALLBACK_1(GameOverScene::goToMainMenuScene, this));
	retryItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 45));

	auto menu = Menu::create(retryItem, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	auto currentScore = LabelTTF::create(g_winner.c_str(), "arial.TTF", visibleSize.height * 0.1);
	currentScore->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.5 + origin.y + 25));
	currentScore->setColor(Color3B(0, 255, 255));
	currentScore->enableShadow(Size(4, -4), 1.f, 10, true);
	this->addChild(currentScore);

	return true;
}

void GameOverScene::goToMainMenuScene(cocos2d::Ref *sender)
{
	auto scene = MainMenuScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}
