#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include"EnemyBullet.h"
#include"EnemyHP.h"
#include<list>

class Player;

// GameSceneの前方宣言(苦肉の策)
class GameScene;

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

	void ExplorionInitialize();

	void ExplorionUpdate();

	// ワールド座標を取得
	Vector3 GetWorldPosition();
	// ワールドradiusを取得
	Vector3 GetWorldRadius();

	bool IsDead() const { return isDead_; }

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	// 発射間隔
	static const int kFireInterval_ = 60;

	static const int HP_ = 3;

	void HPInitialize();

	bool IsExplosion() const { return isexplosion_; }


	static const int kExplosionInterval_ = 20;

	

	private:
	// ワールド変換データ
	WorldTransform worldTransform_;



	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	uint32_t textureHandle2_ = 0u;

	Model* modelenemy_ = nullptr;
	

	// 速度
	Vector3 velocity_;
	// フェーズ
	Phase phase_ = phase_;
	//弾
	EnemyBullet* bullet_ = nullptr;
	//// 敵弾
	//std::list<EnemyBullet*> bullets_;
	// 発射タイマー
	int32_t kFireTimer_ = 0;

	int32_t kExplosionTimer_ = 0;

	Player* player_ = nullptr;

	GameScene* gameScene_ = nullptr;

	// デスフラグ
	bool isDead_ = false;

	int32_t hp_ = 0;

	EnemyHP* enemyhp_ = nullptr;

	bool isexplosion_ = false;

	
};

