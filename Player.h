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
	void Initialize(Model* model, uint32_t textureHandle, const Vector3& Position);

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

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 親となるワールドトランスフォームをセット
	/// </summary>
	/// <param name="parent">親となるワールドトランスフォーム</param>
	void SetParent(const WorldTransform* parent);

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// ワールドradiusを取得
	Vector3 GetWorldRadius();

	// 弾リストを取得
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

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
