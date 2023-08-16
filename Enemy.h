#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include"EnemyBullet.h"
#include<list>

class Player;



///< summary>
/// 敵
/// </summary>
class Enemy {
public:

	enum class Phase {
		Approach, // 接近する
		Leave,    // 離脱する
	};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	///< summary>
	/// 更新
	/// </summary>
	void Update();

	///< summary>
	/// 接近フェーズ
	/// </summary>
	void Approach();
	///< summary>
	/// 離脱フェーズ
	/// </summary>
	void Leave();

	///< summary>
	/// 攻撃
	///</summary>
	void Fire();


	///< summary>
	/// デストラクタ
	///</summary>
	~Enemy();

	///< summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	/// 接近フェーズ初期化
	void ApproachInitialize();

	void ApproachUpdate();

	void SetPlayer(Player* player) { player_ = player; }

	// ワールド座標を取得
	Vector3 GetWorldPosition();
	// ワールドradiusを取得
	Vector3 GetWorldRadius();

    // 弾リストを取得
	const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }

	// 発射間隔
	static const int kFireInterval_ = 60;

	private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// 速度
	Vector3 velocity_;
	// フェーズ
	Phase phase_ = phase_;
	//弾
	EnemyBullet* bullet_ = nullptr;
	// 敵弾
	std::list<EnemyBullet*> bullets_;
	// 発射タイマー
	int32_t kFireTimer_ = 0;

	Player* player_ = nullptr;


};

