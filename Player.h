#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include"Input.h"
#include<WinApp.h>
#include <Sprite.h>
#include"ImGuiManager.h"
class Player {
public:

	~Player();

	void Initialize(Model* model, uint32_t textureHandle);

	void Update(ViewProjection& viewProjection);

	void Draw(ViewProjection& viewProjection);

	void ScreenWorldTransformation(ViewProjection& viewProjection);

	void Attack();

	/// <summary>
	/// UI描画
	/// </summary>
	void DrawUI();

	Vector3 GetWorldPosition3DReticle();

	Vector3 GetWorldPosition();

	private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_=nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//キーボード入力
	Input* input_ = nullptr;

	// 速度
	Vector3 velocity_;

	// 3Dレティクル用ワールドトランスフォーム
	WorldTransform worldTransform3DReticle_;

	// 2Dレティクル用スプライト
	Sprite* sprite2DReticle_ = nullptr;

	Vector2 SpritePosition;

};
