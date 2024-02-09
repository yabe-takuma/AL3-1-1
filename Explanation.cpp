#include "Explanation.h"
#include <TextureManager.h>
#include"FakeBullet.h"
#include"Item.h"

void Explanation::Initialize() 
{
	texture_[0] = TextureManager::Load("内容説明1.png");

	sprite_[0] =
	    Sprite::Create(texture_[0], {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	texture_[1] = TextureManager::Load("内容説明2.png");

	sprite_[1] =
	    Sprite::Create(texture_[1], {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	texture_[2] = TextureManager::Load("内容説明3.png");

	sprite_[2] =
	    Sprite::Create(texture_[2], {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	texture_[3] = TextureManager::Load("内容説明4.png");

	sprite_[3] =
	    Sprite::Create(texture_[3], {640.0f, 500.0f}, uicolor_, {0.5f, 0.5f});

	texture_[4] = TextureManager::Load("内容説明5.png");

	sprite_[4] =
	    Sprite::Create(texture_[4], {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	texture_[5] = TextureManager::Load("内容説明6.png");

	sprite_[5] =
	    Sprite::Create(texture_[5], {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	texture_[6] = TextureManager::Load("内容説明7.png");

	sprite_[6] =
	    Sprite::Create(texture_[6], {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	input_=Input::GetInstance();

	counter_ = 1;

	isInput_ = false;
	timer_ = 0;
	istimer_ = false;

	isbulletOncollision_=false;
	Oncollisiontimer_ = 0;
	isInputFrag = false;
	isPowtimer_;

	lowalpha_ = 0.02f;
	uicolor_ = {1.0f, 1.0f, 1.0f, 1.0f};

}

void Explanation::Update() 
{ 
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A&&istimer_==false)
		{
			counter_ = counter_ + 1;
			istimer_ = true;
		}
	}
	if (istimer_)
	{
		timer_++;
	}
	if (timer_ >= 20)
	{
		timer_ = 0;
		istimer_ = false;
	}
	if (counter_ >= 5)
	{
		isInput_ = true;
	}
	//ImGui::Begin("Explanation");
	//ImGui::DragInt("counter", &counter_, 0.01f);
	//ImGui::DragInt("counter", &timer_, 0.01f);
	//ImGui::End();

	if (uicolor_.w >= 1.0f ) {
		isUi_ = false;
	} else if (uicolor_.w <= 0.0f ) {
		isUi_ = true;
	}
	
		
	

	if (isUi_) {
		uicolor_.w += lowalpha_;
		sprite_[3]->SetColor(uicolor_);
	} else if (isUi_ == false) {
		uicolor_.w -= lowalpha_;
		sprite_[3]->SetColor(uicolor_);
	}

}

void Explanation::PowExplanationUpdate() 
{ 
	if (item_->IsDead_())
	{
		isPowtimer_++;
	}
	if (isPowtimer_ >= 50)
	{
		isPowtimer_ = 51;
	}

}

void Explanation::DrawUI() 
{ 
	if (counter_ == 1) {

		sprite_[0]->Draw();
	} 
	if (counter_ == 2) {

		sprite_[1]->Draw();
	} 
	if (counter_ == 3) {

		sprite_[6]->Draw();
	} 
	if (counter_ == 4) {

		sprite_[2]->Draw();
	}

		sprite_[3]->Draw();
	
}

void Explanation::PowExplanationDraw() { 
if (item_->IsDead_()&&isPowtimer_<=50) {
		sprite_[5]->Draw();
	    }
}


