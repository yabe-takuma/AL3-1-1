#pragma once
#include "Model.h"
#include <vector>
class BaseWall {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="models_">モデルデータ配列</param>
	virtual void Initialize(const std::vector<Model*>& models);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <sumamry>
	/// 描画
	/// </sumamry>
	/// <param name="viewProjection">ビュープロジェクション (参照渡し) </param>
	virtual void Draw(ViewProjection& viewProjection);

	/// <summary>
	/// ワールド変換データを取得
	/// </summary>
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

protected:
	// モデルデータ
	std::vector<Model*> models_;
	// ワールド変換データ
	WorldTransform worldTransform_;
};
