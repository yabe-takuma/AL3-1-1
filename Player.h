#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "PlayerBullet.h"
#include <list>

///< summary>
/// 自キャラ
///</summary
class Player {
public:
	void Initialize(Model* model, uint32_t textureHandle);

	///< summary>
	/// 更新
	///</summary>
	void Update();

	///< summary>
	/// 攻撃
	///  </summary>
	void Attack();


	///< summary>
	/// 描画
	///</summary>
	void Draw(ViewProjection& viewProjection_);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();





	private:
	/// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// キーボード入力
	Input* input_ = nullptr;

	////弾
	//PlayerBullet* bullet_ = nullptr;

	// 弾
	std::list<PlayerBullet*> bullets_;

};
