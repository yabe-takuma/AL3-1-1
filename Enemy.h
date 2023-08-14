#pragma once
#include "Model.h"
#include "WorldTransform.h"
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
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection);


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



};