#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <fstream>

GameScene::GameScene() {}

GameScene::~GameScene() { delete player_; }

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	model_.reset(Model::CreateFromOBJ("Player",true));

	textureHandle_ = TextureManager::Load("sample.png");

	viewprojection_.Initialize();

	//自キャラの生成
	player_ =new Player();
	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm", true));

	// 自キャラモデル
	std::vector<Model*> playerModels = {
	    modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),
	    modelFighterR_arm_.get()};

	//自キャラの初期化
	player_->Initialize(playerModels);
	//天球の生成
	skydome_ = std::make_unique<Skydome>();
	modelskydome_.reset(Model::CreateFromOBJ("skydome", true));
	skydome_->Initialize(modelskydome_.get());
	//フィールドの生成
	ground_ = std::make_unique<Ground>();
	modelground_.reset(Model::CreateFromOBJ("ground", true));
	ground_->Initialize(modelground_.get());

	debugCamera_ = std::make_unique<DebugCamera>(1280, 720);

	followcamera_ = std::make_unique<FollowCamera>();
	followcamera_->Initialize();
	followcamera_->SetTarget(&player_->GetWorldTransform());
	
	player_->SetViewProjection(&followcamera_->GetViewProjection());

	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize();
	enemy_->SetPlayer(player_);

	wall_ = std::make_unique<Wall>();
	modelwall_.reset (Model::Create());

	std::vector<Model*> wallModels = {
		modelwall_.get(), modelwall_.get(), 
		modelwall_.get(), modelwall_.get(), 
		modelwall_.get(), modelwall_.get(), 
		modelwall_.get(), modelwall_.get(), 
		modelwall_.get(), modelwall_.get(),
		modelwall_.get(), modelwall_.get(), 
		modelwall_.get(), modelwall_.get(), 
		modelwall_.get(), modelwall_.get(),
		modelwall_.get(), modelwall_.get(), 
		modelwall_.get(), modelwall_.get(),
	    modelwall_.get(), modelwall_.get(), 
		modelwall_.get(), modelwall_.get(), 
		modelwall_.get(), modelwall_.get(), 
		modelwall_.get(), modelwall_.get(), 
		modelwall_.get(), modelwall_.get(),
	    modelwall_.get(), modelwall_.get(), 
		modelwall_.get(), modelwall_.get(), 
	    modelwall_.get()
	};
	
	wall_->Initialize(wallModels);
	
	LoadEnemyPopData();

}

void GameScene::Update() { 
	

	debugCamera_->Update();
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		isDebugCameraAcctive_ = true;
	}
	if (isDebugCameraAcctive_) {

		viewprojection_.matView = debugCamera_->GetViewProjection().matView;
		viewprojection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewprojection_.TransferMatrix();
	} else {
		viewprojection_.matView = followcamera_->GetViewProjection().matView;
		viewprojection_.matProjection = followcamera_->GetViewProjection().matProjection;

		viewprojection_.TransferMatrix();
		// ビュープロジェクション行列の更新と転送
		//viewprojection_.UpdateMatrix();
	}
#endif

	if (followcamera_ != nullptr) {
		followcamera_->Update();
	}

	if (player_ != nullptr) {

		player_->Update();
	}
	if (skydome_ != nullptr) {
		skydome_->Update();
	}
	if (ground_ != nullptr) {
		ground_->Update();
	}
	if (enemy_ != nullptr)
	{
		enemy_->Update();
	}
	if (wall_ != nullptr)
	{
		wall_->Update();
	}

		for (const std::unique_ptr<WeakEnemy>& weakenemy : weakenemys_) {
		weakenemy->Update();
	}

	UpdateEnemyPopCommands();

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	if (player_ != nullptr) {

		player_->Draw(viewprojection_);
	}
	if (skydome_ != nullptr) {
		skydome_->Draw(viewprojection_);
	}
	if (ground_ != nullptr){
	
		ground_->Draw(viewprojection_);
	}
	if (enemy_ != nullptr)
	{
		enemy_->Draw(viewprojection_);
	}
	if (wall_ != nullptr)
	{
		wall_->Draw(viewprojection_);
	}
	
	for (const auto& weakenemy : weakenemys_) {
		weakenemy->Draw(viewprojection_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::EnemyGeneration(const Vector3& position, const Vector3& velocity) {
	// 敵の生成
	WeakEnemy* weakenemy = new WeakEnemy();

	

	weakenemy->Initialize(position,velocity);
	weakenemy->SetGameScene(this);


	weakenemys_.push_back(static_cast <std::unique_ptr<WeakEnemy>>(weakenemy));
}


void GameScene::LoadEnemyPopData() {

	// ファイルを開く
	std::ifstream file;
	std::string filename = "Resources//enemyPop.csv";
	file.open(filename);
	assert(file.is_open());

	// ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();

	// ファイルを閉じる
	file.close();
}

void GameScene::UpdateEnemyPopCommands() {
	bool iswait = false;
	int32_t waitTimer = 0;



	// 待機処理
	if (iswait) {
		waitTimer--;
		if (waitTimer <= 0) {
			// 待機完了
			iswait = false;
		}
		return;
	}
	// 1行分の文字列を入れる変数
	std::string line;

	// コマンド実行ループ
	while (getline(enemyPopCommands, line)) {
		// 1行分の文字列をストリームに変換して解析しやすくなる
		std::istringstream line_stream(line);

		std::string word;
		//,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');
		//"//"から始まる行はコメント
		if (word.find("//") == 0) {
			// コメント行は飛ばす
			continue;
		}
		// POPコマンド
		if (word.find("SPEED") == 0) {
			// x座標
			getline(line_stream, word, ',');
			 velocity_.x = (float)std::atof(word.c_str());

			// y座標
			getline(line_stream, word, ',');
			 velocity_.y = (float)std::atof(word.c_str());

			// z座標
			getline(line_stream, word, ',');
			 velocity_.z = (float)std::atof(word.c_str());
		
			
		}
			// POPコマンド
			 if (word.find("POP") == 0) {
				// x座標
				getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str());

				// y座標
				getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str());

				// z座標
				getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());

				// 敵を発生させる
				EnemyGeneration(Vector3(x, y, z), velocity_);
			}
		

		// WAITコマンド
		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			// 待ち時間
			int32_t waitTime = atoi(word.c_str());

			// 待機開始
			iswait = true;
			waitTimer = waitTime;

			// コマンドループを抜ける
			break;
		}
	}
}


