#include "TitleScene.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene(){

};

void TitleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	uint32_t textureTitle = TextureManager::Load("タイトル.png");
	

pos_[0] = {640.0f, -360.0f};
	pos_[1] = {1920.0f, 360.0f};
	velocity_[0] = {0.0f, 0.5f};
	velocity_[1] = {0.5f, 0.0f};

	color_ = {0.0f, 0.0f, 0.0f, 1.0f};

	titlesprite_[0] = Sprite::Create(
	    textureTitle, {pos_[1].x, pos_[1].y}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	titlesprite_[1] = Sprite::Create(textureTitle, {pos_[0].x, pos_[0].y}, color_, {0.5f, 0.5f});

	titlesprite_[2] = Sprite::Create(textureTitle, {640.0f, 360.0f}, color_, {0.5f, 0.5f});
	
	
}

void TitleScene::Update() {
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (Input::GetInstance()->GetJoystickStatePrevious(0, prevjoyState)) {
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A&&
				    !(prevjoyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
				isSceneEnd_ = true;
			
			}
		}
	}

	if (isFead_) {
		easing_[0].kAnimMaxtime = 50;
		/*	pos_.y += velocity_.y;
		    titlesprite_[1]->SetPosition(pos_);*/
		easing_[0].time++;
		float frame = (float)easing_[0].time / easing_[0].kAnimMaxtime;
		float easeoutbounce = easeOutBounce(frame * frame);

		pos_[0].y += easeoutbounce;
		titlesprite_[1]->SetPosition(pos_[0]);
		if (pos_[0].y >= 355.0f) {
			isFead_ = false;
			isSceneEnd_ = true;
		}
	}

	// if (easing_.time >= 50) {
	if (pos_[1].x >= 640.0f) {
		easing_[1].time++;
		easing_[1].kAnimMaxtime = 50;
		/*	pos_.y += velocity_.y;
		    titlesprite_[1]->SetPosition(pos_);*/

		float frame2 = (float)easing_[1].time / easing_[1].kAnimMaxtime;
		float easeoutbounce2 = easeOutBounce(frame2 * frame2);

		pos_[1].x -= easeoutbounce2;
		titlesprite_[0]->SetPosition(pos_[1]);
	}
	

}

void TitleScene::Draw() {
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

void TitleScene::DrawUI() { titlesprite_->Draw();
	

}

void TitleScene::Reset() { isSceneEnd_ = false; }

float TitleScene::easeOutBounce(float x) {
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
