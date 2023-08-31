#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "PlayerBullet.h"
#include <list>
#include"Sprite.h"

///< summary>
/// 自キャラ
///</summary
class Player {
public:
	void Initialize(Model* model, uint32_t textureHandle, const Vector3& Position,Model* modelplayerbullet);

	///< summary>
	/// 更新
	///</summary>
	void Update(ViewProjection& viewProjection_);

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

	void Move();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 親となるワールドトランスフォームをセット
	/// </summary>
	/// <param name="parent">親となるワールドトランスフォーム</param>
	void SetParent(const WorldTransform* parent);

	/// <summary>
	/// UI描画
	/// </summary>
	void DrawUI();


	//スクリーン変換からワールド変換
	void ScreenWorldTransformation(ViewProjection& viewProjection);
	

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// ワールドradiusを取得
	Vector3 GetWorldRadius();

	//3DReticleのワールド座標を取得
	Vector3 GetWorldPosition3DReticle();

	// 弾リストを取得
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

	 bool IsDead() const { return isDead_; }

	 static const int HP = 5;

	 void HPInitialize();

	 const WorldTransform& GetWorldTransform3DReticle() { return worldTransform_; }

	private:
	/// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;

	Model* modelplayerbullet_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// キーボード入力
	Input* input_ = nullptr;

	////弾
	//PlayerBullet* bullet_ = nullptr;

	// 弾
	std::list<PlayerBullet*> bullets_;

	// 3Dレティクル用ワールドトランスフォーム
	WorldTransform worldTransform3DReticle_;

	bool isDead_ = false;

	int32_t hp_ = 0;

	// 2Dレティクル用スプライト
	Sprite* sprite2DReticle_ = nullptr;

	Vector2 SpritePosition;

};
