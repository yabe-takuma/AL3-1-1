#include "GameClear.h"
GameClear::GameClear() {}

GameClear::~GameClear(){/*delete mojisprite_;*/};

void GameClear::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	uint32_t textureTitle = TextureManager::Load("ゲームクリア.png");

	titlesprite_ =
	    Sprite::Create(textureTitle, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	// mojisprite_ = new MojiSprite();
	// mojisprite_->Initialize();
}

void GameClear::Update() {
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (Input::GetInstance()->GetJoystickStatePrevious(0, prevjoyState)) {
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X &&
			    !(prevjoyState.Gamepad.wButtons & XINPUT_GAMEPAD_X)) {
				isSceneEnd_ = true;
			} else if (
			    joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A &&
			    !(prevjoyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
				isTitleScene_ = true;
			}
		}
	}
}

void GameClear::Draw() {
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
	// if (mojisprite_ != nullptr) {

	//	mojisprite_->DrawUI();
	//}
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameClear::DrawUI() { titlesprite_->Draw(); }

void GameClear::Reset() { isSceneEnd_ = false;
	isTitleScene_ = false;
}
