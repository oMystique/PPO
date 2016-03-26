#pragma once
#include "cocos2d.h"

#define BALL_COLLISION_BITMASK 0x000001
#define RED_GATE_CONTACT_BITMASK 0x000002
#define BLUE_GATE_CONTACT_BITMASK 0x000003

static const float BACKGROUND_SPRITE_SCALE = 0.44f;


template <class T, class ...TArgs>
T *make_cc(TArgs&&... args)
{
	T *ret = new (std::nothrow) T;
	if (ret && ret->init(std::forward<TArgs>(args)...)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}

template <class T, class ...TArgs>
cocos2d::Scene *make_scene(TArgs&&... args)
{
	auto scene = cocos2d::Scene::create();
	auto layer = make_cc<T>(std::forward<TArgs>(args)...);
	scene->addChild(layer);

	return scene;
}