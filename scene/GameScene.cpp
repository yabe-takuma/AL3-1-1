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
	modelFighterBody_.reset(Model::CreateFromOBJ("Player2", true));
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("Player2L_arm", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("Player2R_arm", true));
	modelsord_.reset(Model::CreateFromOBJ("Sord", true));

	playerModels = {
	    modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),
	    modelFighterR_arm_.get(),modelsord_.get()};

	//自キャラの初期化
	player_->Initialize(playerModels);
	//天球の生成
	skydome_ = std::make_unique<Skydome>();
	modelskydome_.reset(Model::CreateFromOBJ("skydome", true));
	skydome_->Initialize(modelskydome_.get());
	//フィールドの生成
	ground_ = std::make_unique<Ground>();
	modelground_.reset(Model::CreateFromOBJ("ground2", true));
	ground_->Initialize(modelground_.get());

	debugCamera_ = std::make_unique<DebugCamera>(1280, 720);

	followcamera_ = std::make_unique<FollowCamera>();
	followcamera_->Initialize();
	followcamera_->SetTarget(&player_->GetWorldTransform());
	
	player_->SetViewProjection(&followcamera_->GetViewProjection());

	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize();
	enemy_->SetPlayer(player_);

	

	/*std::vector<Model*> wallModels = {
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
	};*/
	

	
	//LoadEnemyPopData();

	LoadWallPopData();

	breakwall_ = std::make_unique<BreakWall>();
	breakwall_->Initialize();
	breakwall_->SetPlayer(player_);

	fakewall_ = std::make_unique<FakeWall>();
	fakewall_->Initialize();


	modelitem_.reset(Model::CreateFromOBJ("Pow", true));
	item_ = std::make_unique<Item>();
	item_->Initialize(modelitem_.get());

	fakebullet_ = std::make_unique<FakeBullet>();
	modelfakebullet_.reset(Model::CreateFromOBJ("PlayerBullet", true));
	fakebullet_->Initialize(modelfakebullet_.get());
	player_->SetFakeBullet(fakebullet_.get());

		uint32_t textureTitle = TextureManager::Load("UI.png");

	uiSprite_.reset(
	    Sprite::Create(textureTitle, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}));

	uint32_t textureUi = TextureManager::Load("UI2.png");

	ui2Sprite_.reset(
	    Sprite::Create(textureUi, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}));

	ScoreInitialize();

	player_->SetItem(item_.get());

	explanation_ = std::make_unique<Explanation>();
	explanation_->Initialize();

	explanation_->SetFakeBullet(fakebullet_.get());
	explanation_->SetItem(item_.get());

	soundDataHandle_[0] = audio_->LoadWave("ゲーム中.wav");

	audio_->PlayWave(soundDataHandle_[0]);

	soundDataHandle_[1] = audio_->LoadWave("SE1.wav");

	soundDataHandle_[2] = audio_->LoadWave("SE2.wav");

	soundDataHandle_[3] = audio_->LoadWave("SE3.wav");

	uint32_t texturefead = TextureManager::Load("タイトル.png");
	Feadsprite_.reset (Sprite::Create(texturefead, pos_, {0.0f, 0.0f, 0.0f, 1.0f}, {0.5f, 0.5f}));

}

void GameScene::Update() { 

	if (pos_.y >= -360.0f) {
		easing_.time++;
		easing_.kAnimMaxtime = 50;
		/*	pos_.y += velocity_.y;
		    titlesprite_[1]->SetPosition(pos_);*/

		float frame = (float)easing_.time / easing_.kAnimMaxtime;
		float easeoutbounce = easeOutBounce(frame * frame);

		pos_.y -= easeoutbounce;
		Feadsprite_->SetPosition(pos_);
	}
	
		// デスフラグの立った弾を削除
	weakenemys_.remove_if([](std::unique_ptr<WeakEnemy>& weakenemys) {
		if (weakenemys->IsDead()) {
			
			
			return true;
		
		}
		return false;
	});

	if (player_->IsDead())
	{
		isGameOver_ = true;
	}
	
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
		
		// ビュープロジェクション行列の更新と転送
		//viewprojection_.UpdateMatrix();
	}
#endif
	viewprojection_.matView = followcamera_->GetViewProjection().matView;
	viewprojection_.matProjection = followcamera_->GetViewProjection().matProjection;

	viewprojection_.TransferMatrix();
	if (ground_ != nullptr) {
		ground_->Update();
	}
	for (const std::unique_ptr<Wall>& wall : walls_) {
		if (wall != nullptr) {
			wall->Update();
		}
	}
	if (followcamera_ != nullptr) {
		followcamera_->Update();
	}
	if (breakwall_ != nullptr) {
		breakwall_->Update();
	}
	if (fakewall_ != nullptr) {
		fakewall_->Update();
	}
	if (item_ != nullptr) {
		item_->Update();
	}
	if (fakebullet_ != nullptr) {
		fakebullet_->Update();
	}
	UpdateEnemyPopCommands();

	UpdateWallPopCommands();

	
	if (player_ != nullptr) {

		player_->Update();
	}
	CheckAllCollisions();
	if (explanation_->IsInput()) {
		
		if (skydome_ != nullptr) {
			skydome_->Update();
		}
		
		if (enemy_ != nullptr) {
			enemy_->Update();
		}
		
		

		for (const std::unique_ptr<WeakEnemy>& weakenemy : weakenemys_) {
			weakenemy->Update();
		}

		

		if (player_->IsClear()) {
			isGameClear_ = true;
		}
	}

	if (explanation_->IsInput() == false)
	{
		explanation_->Update();
	}

	explanation_->PowExplanationUpdate();

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
	//if (skydome_ != nullptr) {
	//	skydome_->Draw(viewprojection_);
	//}
	if (ground_ != nullptr){
	
		ground_->Draw(viewprojection_);
	}
	if (enemy_ != nullptr)
	{
		enemy_->Draw(viewprojection_);
	}
	for (const auto& wall : walls_) {
		
			wall->Draw(viewprojection_);
		
	}
	if (breakwall_ != nullptr)
	{
		breakwall_->Draw(viewprojection_);
	}
	if (fakewall_ != nullptr)
	{
		fakewall_->Draw(viewprojection_);
	}
	if (item_ != nullptr)
	{
		item_->Draw(viewprojection_);
	}
	
	for (const auto& weakenemy : weakenemys_) {
		weakenemy->Draw(viewprojection_);
	}
	if (fakebullet_ != nullptr)
	{
		fakebullet_->Draw(viewprojection_);
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

	DrawUI();

	if (explanation_->IsInput()==false)
	{
		explanation_->DrawUI();
	}

	explanation_->PowExplanationDraw();

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

	enemyPopCommands.clear();

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


void GameScene::CheckAllCollisions() {
	// 判定対象AをBの座標
	Vector3 posA, posB;

	// 自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	

	const std::list<std::unique_ptr<WeakEnemy>>& weakenemys = GetWeakEnemys();

#pragma region 自キャラと敵の当たり判定
	// 自キャラの座標
	posA = player_->GetWorldPosition();
	Vector3 radiusA, radiusB;

	// 自キャラと敵全ての当たり判定
	for (const std::unique_ptr<WeakEnemy>& weakenemy : weakenemys) {
		// 敵弾の座標

		posB = weakenemy->GetWorldPosition();
		radiusA = player_->GetWorldRadius();
		radiusB = weakenemy->GetWorldRadius();

		// 球と球の交差
		/*if (CollisionDot(posA, posB, radiusA, radiusB)&&player_->IsOnCollision()==false) {*/
			if (posA.x <= posB.x + radiusB.x && posB.x <= posA.x + radiusA.x &&
		                posA.y <= posB.y + radiusB.y && posB.y <= posA.y + radiusA.y &&
		                posA.z <= posB.z + radiusB.z && posB.z <= posA.z + radiusA.z ||
		            posA.x >= posB.x - radiusB.x && posB.x >= posA.x - radiusA.x &&
		                posA.y >= posB.y - radiusB.y && posB.y >= posA.y - radiusA.y &&
		        posA.z >= posB.z - radiusB.z && posB.z >= posA.z - radiusA.z &&
		        player_->IsOnCollision()) {
			isoncollision_ =0;
			// 自キャラの衝突時のコールバックを呼び出す
			player_->OnCollision();
			
			//playerhp_->OnCollision();
			// 敵弾の衝突時コールバックを呼び出す
			//weakenemy->OnCollision();
			}
			
	}

#pragma endregion

#pragma region 自弾と敵キャラの当たり判定

	// 敵キャラと自弾全ての当たり判定
	for (PlayerBullet* bullet : playerBullets) {
		for (const std::unique_ptr<WeakEnemy>& weakenemy : weakenemys) {

			// 自弾の座標
			posA = bullet->GetWorldPosition();

			posB = weakenemy->GetWorldPosition();
			radiusB = weakenemy->GetWorldRadius();

			radiusA = bullet->GetWorldRadius();

			if (CollisionDot(posB, posA, radiusB, radiusA)) {


				// 自弾の衝突時のコールバックを呼び出す
				bullet->OnCollision();
				// 敵キャラの衝突時コールバックを呼び出す

				weakenemy->OnCollision();

				/*if (weakenemy->IsExplosion() == false) {

					enemyhp_->OnCollision();
				}*/
				player_->Pow();
			}
		}
	}

#pragma endregion

#pragma region 自武器と敵の当たり判定

	

	// 武器と敵全ての当たり判定
	for (const std::unique_ptr<WeakEnemy>& weakenemy : weakenemys) {
		// 自弾の座標
		posA = player_->GetSordWorldPosition();
		// 敵弾の座標

		posB = weakenemy->GetWorldPosition();
		radiusA = player_->GetSordWorldRadius();
		radiusB = weakenemy->GetWorldRadius();

		// 球と球の交差
		if (CollisionDot(posA, posB, radiusA, radiusB)&&player_->IsSordAlive()) {
			// 自キャラの衝突時のコールバックを呼び出す
			//player_->OnCollision();
			// playerhp_->OnCollision();
			//  敵弾の衝突時コールバックを呼び出す
			weakenemy->OnCollision();

			player_->Pow();
			audio_->PlayWave(soundDataHandle_[1]);
		}
	}
#pragma endregion

	#pragma region 壊す壁と武器の当たり判定

	
			// 自弾の座標
			posA = player_->GetSordWorldPosition();
			// 敵弾の座標
			posB = breakwall_->GetWorldPosition();

			radiusA = player_->GetSordWorldRadius();
			radiusB = breakwall_->GetWorldRadius();

			if (CollisionDot(posA, posB, radiusA, radiusB)&&breakwall_->IsOnCollision()==false&&player_->IsSordAlive()) {
	       
				// 自弾の衝突時のコールバックを呼び出す
				//player_->OnCollision();
				// 敵弾の衝突時コールバックを呼び出す
				breakwall_->OnCollision();
		audio_->PlayWave(soundDataHandle_[1]);
			}
		
#pragma endregion
	
	#pragma region 壁と自機の当たり判定

		for (const std::unique_ptr<Wall>& wall : walls_) {
		        // 自弾の座標
		        posA = player_->GetWorldPosition();
		        // 敵弾の座標
		        posB = wall->GetWorldPosition();

		        radiusA = player_->GetWorldRadius();
		        radiusB = wall->GetWorldRadius();

		        // if (CollisionDot(posA, posB, radiusA, radiusB)) {
		        if (posA.x <= posB.x + radiusB.x && posB.x <= posA.x + radiusA.x &&
		                posA.y <= posB.y + radiusB.y && posB.y <= posA.y + radiusA.y &&
		                posA.z <= posB.z + radiusB.z && posB.z <= posA.z + radiusA.z ||
		            posA.x >= posB.x - radiusB.x && posB.x >= posA.x - radiusA.x &&
		                posA.y >= posB.y - radiusB.y && posB.y >= posA.y - radiusA.y &&
		                posA.z >= posB.z - radiusB.z && posB.z >= posA.z - radiusA.z &&
		                player_->IsOnCollision() == false) {

			// 自弾の衝突時のコールバックを呼び出す
			player_->OnCollision();
			// 敵弾の衝突時コールバックを呼び出す
			wall->OnCollision();
		        }
	        }
		
#pragma endregion

			#pragma region 壊す壁と自機の当たり判定

	       
		        // 自弾の座標
		        posA = player_->GetWorldPosition();
		        // 敵弾の座標
		        posB = breakwall_->GetWorldPosition();

		        radiusA = player_->GetWorldRadius();
		        radiusB = breakwall_->GetWorldRadius();

		        // if (CollisionDot(posA, posB, radiusA, radiusB)) {
		        if (posA.x <= posB.x + radiusB.x && posB.x <= posA.x + radiusA.x &&
		                posA.y <= posB.y + radiusB.y && posB.y <= posA.y + radiusA.y &&
		                posA.z <= posB.z + radiusB.z && posB.z <= posA.z + radiusA.z ||
		            posA.x >= posB.x - radiusB.x && posB.x >= posA.x - radiusA.x &&
		                posA.y >= posB.y - radiusB.y && posB.y >= posA.y - radiusA.y &&
		                posA.z >= posB.z - radiusB.z && posB.z >= posA.z - radiusA.z) {

			// 自弾の衝突時のコールバックを呼び出す
		        if (breakwall_->IsDead() == false) {
			player_->OnCollision2();
		        }
			// 敵弾の衝突時コールバックを呼び出す
			//breakwall_->OnCollision();
		        }
	        

#pragma endregion

				#pragma region 自機とアイテムの当たり判定

	            // 自弾の座標
	            posA = player_->GetWorldPosition();
	            // 敵弾の座標
	            posB = item_->GetWorldPosition();

	            radiusA = player_->GetWorldRadius();
	            radiusB = item_->GetWorldRadius();

	            // if (CollisionDot(posA, posB, radiusA, radiusB)) {
	            if (posA.x <= posB.x + radiusB.x && posB.x <= posA.x + radiusA.x &&
	                    posA.y <= posB.y + radiusB.y && posB.y <= posA.y + radiusA.y &&
	                    posA.z <= posB.z + radiusB.z && posB.z <= posA.z + radiusA.z ||
	                posA.x >= posB.x - radiusB.x && posB.x >= posA.x - radiusA.x &&
	                    posA.y >= posB.y - radiusB.y && posB.y >= posA.y - radiusA.y &&
	                    posA.z >= posB.z - radiusB.z && posB.z >= posA.z - radiusA.z) {

		    // 自弾の衝突時のコールバックを呼び出す
		    item_->OnCollision();
		    // 敵弾の衝突時コールバックを呼び出す
		    // breakwall_->OnCollision();

			audio_->PlayWave(soundDataHandle_[2]);
	            }

#pragma endregion

				#pragma region 自機とハンターの当たり判定

	            // 自弾の座標
	            posA = player_->GetWorldPosition();
	            // 敵弾の座標
	            posB = enemy_->GetWorldPosition();

	            radiusA = player_->GetWorldRadius();
	            radiusB = enemy_->GetWorldRadius();

	            // if (CollisionDot(posA, posB, radiusA, radiusB)) {
	            if (posA.x <= posB.x + radiusB.x && posB.x <= posA.x + radiusA.x &&
	                    posA.y <= posB.y + radiusB.y && posB.y <= posA.y + radiusA.y &&
	                    posA.z <= posB.z + radiusB.z && posB.z <= posA.z + radiusA.z ||
	                posA.x >= posB.x - radiusB.x && posB.x >= posA.x - radiusA.x &&
	                    posA.y >= posB.y - radiusB.y && posB.y >= posA.y - radiusA.y &&
	                    posA.z >= posB.z - radiusB.z && posB.z >= posA.z - radiusA.z&&enemy_->IsOnCollision()==false && player_->IsOnCollision() == false) {

		    // 自弾の衝突時のコールバックを呼び出す
		   player_->OnCollision();
		    // 敵弾の衝突時コールバックを呼び出す
		    enemy_->OnCollision();
	            }

#pragma endregion

				#pragma region 自弾と壊す壁の当たり判定
	            // 敵キャラと自弾全ての当たり判定
	            for (PlayerBullet* bullet : playerBullets) {
		    // 自弾の座標
		    posA = bullet->GetWorldPosition();
		    // 敵弾の座標
		    posB = breakwall_->GetWorldPosition();

		    radiusA = bullet->GetWorldRadius();
		    radiusB = breakwall_->GetWorldRadius();

		    // if (CollisionDot(posA, posB, radiusA, radiusB)) {
		    if (posA.x <= posB.x + radiusB.x && posB.x <= posA.x + radiusA.x &&
		            posA.y <= posB.y + radiusB.y && posB.y <= posA.y + radiusA.y &&
		            posA.z <= posB.z + radiusB.z && posB.z <= posA.z + radiusA.z ||
		        posA.x >= posB.x - radiusB.x && posB.x >= posA.x - radiusA.x &&
		            posA.y >= posB.y - radiusB.y && posB.y >= posA.y - radiusA.y &&
		            posA.z >= posB.z - radiusB.z && posB.z >= posA.z - radiusA.z &&
		            enemy_->IsOnCollision() == false && player_->IsOnCollision() == false) {

			// 自弾の衝突時のコールバックを呼び出す
			bullet->OnCollision();
			// 敵弾の衝突時コールバックを呼び出す
			breakwall_->OnCollision();

			audio_->PlayWave(soundDataHandle_[1]);
		    }
	            }

#pragma endregion

#pragma endregion

#pragma region 自弾とアイテムの弾の当たり判定
	            // 敵キャラと自弾全ての当たり判定
	         
		    // 自弾の座標
		    posA = player_->GetWorldPosition();
		    // 敵弾の座標
		    posB = fakebullet_->GetWorldPosition();

		    radiusA = player_->GetWorldRadius();
		    radiusB = fakebullet_->GetWorldRadius();

		    // if (CollisionDot(posA, posB, radiusA, radiusB)) {
		    if (posA.x <= posB.x + radiusB.x && posB.x <= posA.x + radiusA.x &&
		            posA.y <= posB.y + radiusB.y && posB.y <= posA.y + radiusA.y &&
		            posA.z <= posB.z + radiusB.z && posB.z <= posA.z + radiusA.z ||
		        posA.x >= posB.x - radiusB.x && posB.x >= posA.x - radiusA.x &&
		            posA.y >= posB.y - radiusB.y && posB.y >= posA.y - radiusA.y &&
		            posA.z >= posB.z - radiusB.z && posB.z >= posA.z - radiusA.z ) {

			// 自弾の衝突時のコールバックを呼び出す
		     fakebullet_->OnCollision();
		
			 audio_->PlayWave(soundDataHandle_[3]);
		    }
	            

#pragma endregion

}

void GameScene::WallGeneration(const Vector3& position, const Vector3& scale) {
	        // 敵の生成
	        Wall* wall = new Wall();
	       

	        wall->Initialize(position, scale);
	        wall->SetGameScene(this);

	        walls_.push_back(static_cast<std::unique_ptr<Wall>>(wall));
}

void GameScene::Reset() 
{ 
	isGameClear_ = false;
	isGameOver_ = false;
	
}

void GameScene::GameReset() 
{ 
	player_->Initialize(playerModels); 
			for (const std::unique_ptr<WeakEnemy>& weakenemy : weakenemys_) {
		     weakenemy->OnCollision();
	}
	LoadEnemyPopData();

	enemy_->Initialize();
	breakwall_->Initialize();
	fakebullet_->Initialize(modelfakebullet_.get());
	item_->Initialize(modelitem_.get());
	explanation_->Initialize();
}

void GameScene::DrawUI() { 
	if (fakebullet_->IsDead() == false) {
		     uiSprite_->Draw();
	}
	else if (fakebullet_->IsDead())
	{
		     ui2Sprite_->Draw();
	}
	if (player_->GetPow()==1||player_->GetPow()==11)
	{
		scoresprite_[0]->Draw();
	} else if (player_->GetPow() == 2 || player_->GetPow() == 12) {
		scoresprite_[1]->Draw();
	} else if (player_->GetPow() == 3 || player_->GetPow() == 13) {
		scoresprite_[2]->Draw();
	} else if (player_->GetPow() == 4 || player_->GetPow() == 14) {
		scoresprite_[3]->Draw();
	} else if (player_->GetPow() == 5 || player_->GetPow() == 15) {
		scoresprite_[4]->Draw();
	} else if (player_->GetPow() == 6 || player_->GetPow() == 16) {
		scoresprite_[5]->Draw();
	} else if (player_->GetPow() == 7 || player_->GetPow() == 17) {
		scoresprite_[6]->Draw();
	} else if (player_->GetPow() == 8 || player_->GetPow() == 18) {
		scoresprite_[7]->Draw();
	} else if (player_->GetPow() == 9 || player_->GetPow() == 19) {
		scoresprite_[8]->Draw();
	} else if (player_->GetPow() == 10 || player_->GetPow() == 20) {
		scoresprite_[9]->Draw();
	} 
	if (player_->GetPow() >= 10&&player_->GetPow() <= 19) {
		scoresprite_[10]->Draw();
	} else if (player_->GetPow() >= 20 &&player_->GetPow() <= 29) {
		scoresprite_[11]->Draw();
	}

	Feadsprite_->Draw();
}

void GameScene::ScoreInitialize() 
{ 
	scoretexture_[0] = TextureManager::Load("1.png"); 
	scoretexture_[1] = TextureManager::Load("2.png");
	scoretexture_[2] = TextureManager::Load("3.png");
	scoretexture_[3] = TextureManager::Load("4.png");
	scoretexture_[4] = TextureManager::Load("5.png");
	scoretexture_[5] = TextureManager::Load("6.png");
	scoretexture_[6] = TextureManager::Load("7.png");
	scoretexture_[7] = TextureManager::Load("8.png");
	scoretexture_[8] = TextureManager::Load("9.png");
	scoretexture_[9] = TextureManager::Load("0.png");
	scoresprite_[0].reset(
	    Sprite::Create(scoretexture_[0], {1200.0f, 54.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}));
	scoresprite_[1].reset(
	    Sprite::Create(scoretexture_[1], {1200.0f, 54.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}));
	scoresprite_[2].reset(
	    Sprite::Create(scoretexture_[2], {1200.0f, 54.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}));
	scoresprite_[3].reset(
	    Sprite::Create(scoretexture_[3], {1200.0f, 54.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}));
	scoresprite_[4].reset(
	    Sprite::Create(scoretexture_[4], {1200.0f, 54.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}));
	scoresprite_[5].reset(
	    Sprite::Create(scoretexture_[5], {1200.0f, 54.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}));
	scoresprite_[6].reset(
	    Sprite::Create(scoretexture_[6], {1200.0f, 54.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}));
	scoresprite_[7].reset(
	    Sprite::Create(scoretexture_[7], {1200.0f, 54.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}));
	scoresprite_[8].reset(
	    Sprite::Create(scoretexture_[8], {1200.0f, 54.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}));
	scoresprite_[9].reset(
	    Sprite::Create(scoretexture_[9], {1200.0f, 54.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}));
	scoresprite_[10].reset(
	    Sprite::Create(scoretexture_[0], {1170.0f, 54.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}));
	scoresprite_[11].reset(
	    Sprite::Create(scoretexture_[1], {1170.0f, 54.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}));
}

void GameScene::LoadWallPopData() 
{
	        // ファイルを開く
	        std::ifstream file2;
	        std::string filename2 = "Resources//wallPop.csv";
	        file2.open(filename2);
	        assert(file2.is_open());

	        // ファイルの内容を文字列ストリームにコピー
	        wallPopCommands << file2.rdbuf();

	        // ファイルを閉じる
	        file2.close();

}

void GameScene::UpdateWallPopCommands() 
{
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
	        std::string line2;

	        // コマンド実行ループ
	        while (getline(wallPopCommands, line2)) {
		        // 1行分の文字列をストリームに変換して解析しやすくなる
		        std::istringstream line_stream(line2);

		        std::string word2;
		        //,区切りで行の先頭文字列を取得
		        getline(line_stream, word2, ',');
		        //"//"から始まる行はコメント
		        if (word2.find("//") == 0) {
			// コメント行は飛ばす
			continue;
		        }
		        // POPコマンド
		        if (word2.find("SCALE") == 0) {
			// x座標
			getline(line_stream, word2, ',');
			scale_.x = (float)std::atof(word2.c_str());

			// y座標
			getline(line_stream, word2, ',');
			scale_.y = (float)std::atof(word2.c_str());

			// z座標
			getline(line_stream, word2, ',');
			scale_.z = (float)std::atof(word2.c_str());
		        }
		        // POPコマンド
		        if (word2.find("POP") == 0) {
			// x座標
			getline(line_stream, word2, ',');
			float x = (float)std::atof(word2.c_str());

			// y座標
			getline(line_stream, word2, ',');
			float y = (float)std::atof(word2.c_str());

			// z座標
			getline(line_stream, word2, ',');
			float z = (float)std::atof(word2.c_str());

			// 敵を発生させる
			WallGeneration(Vector3(x, y, z),scale_ );
		        }

		 //       // WAITコマンド
		 //       else if (word.find("WAIT") == 0) {
			//getline(line_stream, word, ',');

			//// 待ち時間
			//int32_t waitTime = atoi(word.c_str());

			//// 待機開始
			//iswait = true;
			//waitTimer = waitTime;

			//// コマンドループを抜ける
			//break;
		 //       }
	        }
}

float GameScene::easeOutBounce(float x) {
	        const float n1 = 7.5625f;
	        const float d1 = 2.75f;

	        if (x < 1 / d1) {
		        return n1 * x * x;
	        } else if (x < 2 / d1) {
		        return n1 * (x -= 1.5f / d1) * x + 0.75f;
	        } else if (x < 2.5f / d1) {
		        return n1 * (x -= 2.25f / d1) * x + 0.9375f;
	        } else {
		        return n1 * (x -= 2.625f / d1) * x + 0.984375f;
	        }
}

