#include "Wall.h"
#include<cassert>
#include"GameScene.h"


void Wall::Initialize(Vector3 position, Vector3 scale) {

	model_ = Model::Create();


	worldTransform_.scale_ = scale;

		worldTransform_.translation_ = position;

	worldTransform_.Initialize();

	/*BaseWall::Initialize(models);
	
	worldTransform_[0].translation_ = {3.0f, 0.0f, -20.0f};
	worldTransform_[0].scale_ = {35.5f, 20.0f, 1.0f};

	worldTransform_[1].translation_ = {20.4f, 0.0f, -59.2f};
	worldTransform_[1].scale_ = {1.0f, 20.0f, 20.2f};

	worldTransform_[2].translation_ = {-10.0f, 0.0f, -59.2f};
	worldTransform_[2].scale_ = {1.0f, 20.0f, 20.2f};

	worldTransform_[3].translation_ = {6.0f, 0.0f, -79.9f};
	worldTransform_[3].scale_ = {15.9f, 20.0f, 1.0f};

	worldTransform_[4].translation_ = {-31.7f, 0.0f, -39.3f};
	worldTransform_[4].scale_ = {22.7f, 20.0f, 1.0f};

	worldTransform_[5].translation_ = {42.1f, 0.0f, -40.0f};
	worldTransform_[5].scale_ = {22.7f, 20.0f, 1.0f};

	worldTransform_[6].translation_ = {-51.5f, 0.0f, 40.4f};
	worldTransform_[6].scale_ = {2.9f, 20.0f, 78.9f};

	worldTransform_[7].translation_ = {63.9f, 0.0f, -30.7f};
	worldTransform_[7].scale_ = {1.0f, 20.0f, 10.2f};

	worldTransform_[8].translation_ = {3.0f, 0.0f, 10.0f};
	worldTransform_[8].scale_ = {35.0f, 20.0f, 1.0f};

	worldTransform_[9].translation_ = {38.8f, 0.0f, 50.4f};
	worldTransform_[9].scale_ = {1.0f, 20.0f, 40.1f};
	
	
	worldTransform_[10].translation_ = {63.8f, 0.0f, 19.9f};
	worldTransform_[10].scale_ = {3.8f, 20.0f, 20.9f};

	worldTransform_[11].translation_ = {80.7f, 0.0f, -0.3f};
	worldTransform_[11].scale_ = {20.6f, 20.0f, 7.8f};

	worldTransform_[12].translation_ = {76.8f, 0.0f, -21.5f};
	worldTransform_[12].scale_ = {12.0f, 20.0f, 1.0f};

	worldTransform_[13].translation_ = {89.7f, 0.0f, -29.8f};
	worldTransform_[13].scale_ = {1.0f, 20.0f, 9.3f};

	worldTransform_[14].translation_ = {102.0f, 0.0f, -39.0f};
	worldTransform_[14].scale_ = {1.0f, 20.0f, 57.3f};

	worldTransform_[15].translation_ = {76.3f, 0.0f, -39.9f};
	worldTransform_[15].scale_ = {14.4f, 20.0f, 1.0f};

	worldTransform_[16].translation_ = {59.2f, 0.0f, -63.6f};
	worldTransform_[16].scale_ = {1.0f, 20.0f, 22.6f};

	worldTransform_[17].translation_ = {81.4f, 0.0f, -85.0f};
	worldTransform_[17].scale_ = {22.0f, 20.0f, 1.0f};

	worldTransform_[18].translation_ = {71.4f, 0.0f, 49.6f};
	worldTransform_[18].scale_ = {8.1f, 20.0f, 1.0f};

	worldTransform_[19].translation_ = {80.0f, 0.0f, 34.0f};
	worldTransform_[19].scale_ = {1.0f, 20.0f, 16.5f};
	
	
	worldTransform_[20].translation_ = {92.7f, 0.0f, 18.6f};
	worldTransform_[20].scale_ = {13.7f, 20.0f, 12.4f};

	worldTransform_[21].translation_ = {105.8f, 0.0f, 47.1f};
	worldTransform_[21].scale_ = {1.0f, 20.0f, 27.7f};

	worldTransform_[22].translation_ = {85.0f, 0.0f, 74.7f};
	worldTransform_[22].scale_ = {21.0f, 20.0f, 1.0f};

	worldTransform_[23].translation_ = {62.2f, 0.0f, 97.0f};
	worldTransform_[23].scale_ = {2.1f, 20.0f, 23.2f};

	worldTransform_[24].translation_ = {38.4f, 0.0f, 119.2f};
	worldTransform_[24].scale_ = {23.0f, 20.0f, 1.0f};

	worldTransform_[25].translation_ = {-31.0f, 0.0f, 26.3f};
	worldTransform_[25].scale_ = {1.0f, 20.0f, 15.5f};

	worldTransform_[26].translation_ = {-6.4f, 0.0f, 40.8f};
	worldTransform_[26].scale_ = {23.7f, 20.0f, 1.0f};

	worldTransform_[27].translation_ = {-8.3f, 0.0f, 54.9f};
	worldTransform_[27].scale_ = {1.0f, 20.0f, 13.5f};

	worldTransform_[28].translation_ = {-19.1f, 0.0f, 67.3f};
	worldTransform_[28].scale_ = {11.6f, 20.0f, 1.0f};

	worldTransform_[29].translation_ = {-29.7f, 0.0f, 81.2f};
	worldTransform_[29].scale_ = {1.0f, 20.0f, 14.7f};

	
	worldTransform_[30].translation_ = {23.8f, 0.0f, 93.0f};
	worldTransform_[30].scale_ = {15.9f, 20.0f, 2.6f};

	worldTransform_[31].translation_ = {-17.5f, 0.0f, 94.8f};
	worldTransform_[31].scale_ = {11.6f, 20.0f, 1.0f};

	worldTransform_[32].translation_ = {-26.3f, 0.0f, 117.9f};
	worldTransform_[32].scale_ = {23.0f, 20.0f, 1.0f};

	worldTransform_[33].translation_ = {16.9f, 0.0f, 55.0f};
	worldTransform_[33].scale_ = {1.0f, 20.0f, 15.2f};

	worldTransform_[34].translation_ = {26.0f, 20.5f, 13.0f};
	worldTransform_[34].scale_ = {82.0f, 1.0f, 113.0f};
	*/


	textureHandle_ = TextureManager::Load("wall.png");
	

	/*for (int i = 0; i < 35; i++) {
		worldTransform_[i].Initialize();
	}*/
	
}

void Wall::Update() {
	worldTransform_.UpdateMatrix();
	/*BaseWall::Update();
	for (int i = 0; i < 35; i++) {
		worldTransform_[i].UpdateMatrix();
	}*/
	
	ImGui::Begin("Wall");
	 ImGui::DragFloat3("position", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	//ImGui::DragFloat3("position0", &worldTransform_[0].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale0", &worldTransform_[0].scale_.x, 0.1f);
	//ImGui::DragFloat3("position1", &worldTransform_[1].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale1", &worldTransform_[1].scale_.x, 0.1f);
	//ImGui::DragFloat3("position2", &worldTransform_[2].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale2", &worldTransform_[2].scale_.x, 0.1f);
	//ImGui::DragFloat3("position3", &worldTransform_[3].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale3", &worldTransform_[3].scale_.x, 0.1f);
	//ImGui::DragFloat3("position4", &worldTransform_[4].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale4", &worldTransform_[4].scale_.x, 0.1f);
	//ImGui::DragFloat3("position5", &worldTransform_[5].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale5", &worldTransform_[5].scale_.x, 0.1f);
	//ImGui::DragFloat3("position6", &worldTransform_[6].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale6", &worldTransform_[6].scale_.x, 0.1f);
	//ImGui::DragFloat3("position7", &worldTransform_[7].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale7", &worldTransform_[7].scale_.x, 0.1f);
	//ImGui::DragFloat3("position8", &worldTransform_[8].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale8", &worldTransform_[8].scale_.x, 0.1f);
	//ImGui::DragFloat3("position9", &worldTransform_[9].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale9", &worldTransform_[9].scale_.x, 0.1f);


	//ImGui::DragFloat3("position10", &worldTransform_[10].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale10", &worldTransform_[10].scale_.x, 0.1f);
	//ImGui::DragFloat3("position11", &worldTransform_[11].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale11", &worldTransform_[11].scale_.x, 0.1f);
	//ImGui::DragFloat3("position12", &worldTransform_[12].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale12", &worldTransform_[12].scale_.x, 0.1f);
	//ImGui::DragFloat3("position13", &worldTransform_[13].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale13", &worldTransform_[13].scale_.x, 0.1f);
	//ImGui::DragFloat3("position14", &worldTransform_[14].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale14", &worldTransform_[14].scale_.x, 0.1f);
	//ImGui::DragFloat3("position15", &worldTransform_[15].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale15", &worldTransform_[15].scale_.x, 0.1f);
	//ImGui::DragFloat3("position16", &worldTransform_[16].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale16", &worldTransform_[16].scale_.x, 0.1f);
	//ImGui::DragFloat3("position17", &worldTransform_[17].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale17", &worldTransform_[17].scale_.x, 0.1f);
	//ImGui::DragFloat3("position18", &worldTransform_[18].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale18", &worldTransform_[18].scale_.x, 0.1f);
	//ImGui::DragFloat3("position19", &worldTransform_[19].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale19", &worldTransform_[19].scale_.x, 0.1f);


	//ImGui::DragFloat3("position20", &worldTransform_[20].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale20", &worldTransform_[20].scale_.x, 0.1f);
	//ImGui::DragFloat3("position21", &worldTransform_[21].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale21", &worldTransform_[21].scale_.x, 0.1f);
	//ImGui::DragFloat3("position22", &worldTransform_[22].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale22", &worldTransform_[22].scale_.x, 0.1f);
	//ImGui::DragFloat3("position23", &worldTransform_[23].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale23", &worldTransform_[23].scale_.x, 0.1f);
	//ImGui::DragFloat3("position24", &worldTransform_[24].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale24", &worldTransform_[24].scale_.x, 0.1f);
	//ImGui::DragFloat3("position25", &worldTransform_[25].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale25", &worldTransform_[25].scale_.x, 0.1f);
	//ImGui::DragFloat3("position26", &worldTransform_[26].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale26", &worldTransform_[26].scale_.x, 0.1f);
	//ImGui::DragFloat3("position27", &worldTransform_[27].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale27", &worldTransform_[27].scale_.x, 0.1f);
	//ImGui::DragFloat3("position28", &worldTransform_[28].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale28", &worldTransform_[28].scale_.x, 0.1f);
	//ImGui::DragFloat3("position29", &worldTransform_[29].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale29", &worldTransform_[29].scale_.x, 0.1f);

	//ImGui::DragFloat3("position30", &worldTransform_[30].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale30", &worldTransform_[30].scale_.x, 0.1f);
	//ImGui::DragFloat3("position31", &worldTransform_[31].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale31", &worldTransform_[31].scale_.x, 0.1f);
	//ImGui::DragFloat3("position32", &worldTransform_[32].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale32", &worldTransform_[32].scale_.x, 0.1f);
	//ImGui::DragFloat3("position33", &worldTransform_[33].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale33", &worldTransform_[33].scale_.x, 0.1f);
	//ImGui::DragFloat3("position34", &worldTransform_[34].translation_.x, 0.1f);
	//ImGui::DragFloat3("scale34", &worldTransform_[34].scale_.x, 0.1f);
	ImGui::End();

	
}

void Wall::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	/*models_[0]->Draw(worldTransform_[0], viewProjection, textureHandle_);
	models_[1]->Draw(worldTransform_[1], viewProjection, textureHandle_);
	models_[2]->Draw(worldTransform_[2], viewProjection, textureHandle_);
	models_[3]->Draw(worldTransform_[3], viewProjection, textureHandle_);
	models_[4]->Draw(worldTransform_[4], viewProjection, textureHandle_);
	models_[5]->Draw(worldTransform_[5], viewProjection, textureHandle_);
	models_[6]->Draw(worldTransform_[6], viewProjection, textureHandle_);
	models_[7]->Draw(worldTransform_[7], viewProjection, textureHandle_);
	models_[8]->Draw(worldTransform_[8], viewProjection, textureHandle_);
	models_[9]->Draw(worldTransform_[9], viewProjection, textureHandle_);
	models_[10]->Draw(worldTransform_[10], viewProjection, textureHandle_);
	models_[11]->Draw(worldTransform_[11], viewProjection, textureHandle_);
	models_[12]->Draw(worldTransform_[12], viewProjection, textureHandle_);
	models_[13]->Draw(worldTransform_[13], viewProjection, textureHandle_);
	models_[14]->Draw(worldTransform_[14], viewProjection, textureHandle_);
	models_[15]->Draw(worldTransform_[15], viewProjection, textureHandle_);
	models_[16]->Draw(worldTransform_[16], viewProjection, textureHandle_);
	models_[17]->Draw(worldTransform_[17], viewProjection, textureHandle_);
	models_[18]->Draw(worldTransform_[18], viewProjection, textureHandle_);
	models_[19]->Draw(worldTransform_[19], viewProjection, textureHandle_);
	models_[20]->Draw(worldTransform_[20], viewProjection, textureHandle_);
	models_[21]->Draw(worldTransform_[21], viewProjection, textureHandle_);
	models_[22]->Draw(worldTransform_[22], viewProjection, textureHandle_);
	models_[23]->Draw(worldTransform_[23], viewProjection, textureHandle_);
	models_[24]->Draw(worldTransform_[24], viewProjection, textureHandle_);
	models_[25]->Draw(worldTransform_[25], viewProjection, textureHandle_);
	models_[26]->Draw(worldTransform_[26], viewProjection, textureHandle_);
	models_[27]->Draw(worldTransform_[27], viewProjection, textureHandle_);
	models_[28]->Draw(worldTransform_[28], viewProjection, textureHandle_);
	models_[29]->Draw(worldTransform_[29], viewProjection, textureHandle_);
	models_[30]->Draw(worldTransform_[30], viewProjection, textureHandle_);
	models_[31]->Draw(worldTransform_[31], viewProjection, textureHandle_);
	models_[32]->Draw(worldTransform_[32], viewProjection, textureHandle_);
	models_[33]->Draw(worldTransform_[33], viewProjection, textureHandle_);
	models_[34]->Draw(worldTransform_[34], viewProjection, textureHandle_);*/
}

void Wall::OnCollision() {}

Vector3 Wall::GetWorldPosition() { 
// ワールド座標を入れる変数
	Vector3 worldPos;

		// ワールド行列の平行移動成分を取得(ワールド座標)
		worldPos.x = worldTransform_.matWorld_.m[3][0];
		worldPos.y = worldTransform_.matWorld_.m[3][1];
		worldPos.z = worldTransform_.matWorld_.m[3][2];
	

	return worldPos;
}

Vector3 Wall::GetWorldRadius() { 
Vector3 worldRadius;


		worldRadius.x = worldTransform_.scale_.x;
		worldRadius.y = worldTransform_.scale_.y;
		worldRadius.z = worldTransform_.scale_.z;

	return worldRadius;
}
	
