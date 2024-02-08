#include "GameOverScene.h"

GameOverScene::GameOverScene() {}

GameOverScene::~GameOverScene(){

};

void GameOverScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	uint32_t textureTitle = TextureManager::Load("ゲームオーバー.png");

	titlesprite_ =
	    Sprite::Create(textureTitle, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	pos_ = {640.0f, 360.0f};

	color_ = {0.0f, 0.0f, 0.0f, 1.0f};

	uint32_t texturefead = TextureManager::Load("タイトル.png");
	Feadsprite_ = Sprite::Create(texturefead, pos_, color_, {0.5f, 0.5f});
}

void GameOverScene::Update() {

	if (isFead_[0] == false && isFead_[1]==false) {
		color_.w -= 0.005f;
		Feadsprite_->SetColor(color_);
	}

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (Input::GetInstance()->GetJoystickStatePrevious(0, prevjoyState)) {
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A &&
			    !(prevjoyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
				isFead_[0] = true;
			}
			else if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X &&
			    !(prevjoyState.Gamepad.wButtons & XINPUT_GAMEPAD_X)) {
				isFead_[1] = true;
			}
		}
	}
	if (isFead_[0]) {
		color_.w += 0.005f;
		Feadsprite_->SetColor(color_);
		if (color_.w >= 1.0f) {
			isSceneEnd_ = true;
			isFead_[0] = false;
		}
	} 
	if (isFead_[1]) {
		color_.w += 0.005f;
		Feadsprite_->SetColor(color_);
		if (color_.w >= 1.0f) {
			isGameScene_ = true;
			isFead_[1] = false;
		}
	}
}

void GameOverScene::Draw() {
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

void GameOverScene::DrawUI() { titlesprite_->Draw();
	Feadsprite_->Draw();
}

void GameOverScene::Reset() { isSceneEnd_ = false; 
isGameScene_ = false;
	color_ = {0.0f, 0.0f, 0.0f, 1.0f};
Feadsprite_->SetColor(color_);
}
