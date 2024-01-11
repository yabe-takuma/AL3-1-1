#pragma once
#include"Sprite.h"
#include"Input.h"
#include <Xinput.h>
#include"ImGuiManager.h"

class FakeBullet;

class Item;

class Explanation {
public:
	void Initialize();

	void Update();

	void PowExplanationUpdate();

	void DrawUI();

	void PowExplanationDraw();

	bool IsInput() const { return isInput_; }

	bool IsBulletOncollision() const { return isbulletOncollision_; }

	void SetFakeBullet(FakeBullet* fakebullet) { fakebullet_ = fakebullet; }

	void SetItem(Item* item) { item_ = item; }

	private:
	

	Sprite* sprite_[7];
	uint32_t texture_[7];

	int32_t counter_;

	XINPUT_STATE joyState;

	Input* input_ = nullptr;

	bool isInput_;

	int32_t timer_;

	bool istimer_;

	bool isbulletOncollision_;

	FakeBullet* fakebullet_ = nullptr;

	int32_t Oncollisiontimer_;

	bool isInputFrag = false;

	Item* item_ = nullptr;

	int32_t isPowtimer_;

};
