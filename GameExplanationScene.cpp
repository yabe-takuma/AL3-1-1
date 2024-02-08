#include "GameExplanationScene.h"

GameExplanationScene::GameExplanationScene() {}

GameExplanationScene::~GameExplanationScene(){

};

void GameExplanationScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	uint32_t textureTitle = TextureManager::Load("ゲーム説明.png");

	titlesprite_ =
	    Sprite::Create(textureTitle, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	pos_ = {640.0f, 360.0f};

	uint32_t texturefead = TextureManager::Load("タイトル.png");
	Feadsprite_=Sprite::Create(texturefead, pos_, {0.0f, 0.0f, 0.0f, 1.0f}, {0.5f, 0.5f});
}

void GameExplanationScene::Update() {
	if (pos_.y >= -360.0f) {
		easing_.time++;
		easing_.kAnimMaxtime = 50;
		/*	pos_.y += velocity_.y;
		    titlesprite_[1]->SetPosition(pos_);*/

		float frame = (float)easing_.time / easing_.kAnimMaxtime;
		float easeoutbounce = easeOutBounce(frame * frame);

		pos_.y -= easeoutbounce;
		Feadsprite_->SetPosition(pos_);
	}
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (Input::GetInstance()->GetJoystickStatePrevious(0, prevjoyState)) {
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A &&
			    !(prevjoyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
				isFead_ = true;
				easing_.time = 0;
			}
		}
	}
	if (isFead_) {
		
		easing_.kAnimMaxtime = 50;
		/*	pos_.y += velocity_.y;
		    titlesprite_[1]->SetPosition(pos_);*/
		easing_.time++;
		float frame = (float)easing_.time / easing_.kAnimMaxtime;
		float easeoutbounce = easeOutBounce(frame * frame);

		pos_.y += easeoutbounce;
		Feadsprite_->SetPosition(pos_);
		if (pos_.y >= 355.0f) {
			isFead_ = false;
			isSceneEnd_ = true;
		}
	}
}

void GameExplanationScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	DrawUI();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameExplanationScene::DrawUI() { titlesprite_->Draw();
	Feadsprite_->Draw();
}

void GameExplanationScene::Reset() { isSceneEnd_ = false;
	pos_ = {640.0f, 360.0f};
	Feadsprite_->SetPosition(pos_);
	
	easing_.time = 0;
	
}

float GameExplanationScene::easeOutBounce(float x) {
	const float n1 = 7.5625f;
	const float d1 = 2.75f;

	if (x < 1 / d1) {
		return n1 * x * x;
	} else if (x < 2 / d1) {
		return n1 * (x -= 1.5f / d1) * x + 0.75f;
	} else if (x < 2.5f / d1) {
		return n1 * (x -= 2.25f / d1) * x + 0.9375f;
	} else {
		return n1 * (x -= 2.625f / d1) * x + 0.984375f;
	}
}