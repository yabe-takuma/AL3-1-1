#pragma once
#include "WorldTransform.h"
#include "Model.h"
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
	/// 描画
	///</summary>

	void Draw(ViewProjection& viewProjection_);







	private:
	/// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;





};
