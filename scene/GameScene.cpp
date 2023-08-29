#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>
#include <fstream>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete debugCamera_;
	delete enemy_;
	delete modelSkydome_;
	for (EnemyBullet* bullet : enemybullets_) {
		delete bullet;
	}
	delete enemyhp_;
	delete enemyui_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("mario.jpg");

	model_ = Model::Create();
	viewProjection_.Initialize();
	debugCamera_ = new DebugCamera(1280, 720);
	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向の表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	//// 敵の生成
	// Enemy* enemy_ = new Enemy();

	//// 敵の初期化
	// const float kEnemySpeed = -0.1f;
	// Vector3 velocity_ = {0, 0, kEnemySpeed};

	// Vector3 position = {0, 0, 0};

	// enemy_->Initialize(model_, position, velocity_);

	skydome_ = new Skydome();

	// 3Dモデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	skydome_->Initialize(modelSkydome_);

	railcamera_ = new RailCamera();
	const float kCameraSpeed = 0.01f;
	 //const float kCameraRotateSpeed = 0.001f;
	Vector3 velocity = {0.0f, 0.0f, kCameraSpeed};

	railcamera_->Initialize(
	    velocity, railcamera_->GetWorldPosition(), railcamera_->GetWorldRotation());

	// 自キャラの生成
	player_ = new Player();
	// 自キャラとレールカメラの親子関係を結ぶ
	player_->SetParent(&railcamera_->GetWorldTransform());
	Vector3 PlayerPosition = {0.0f, 0.0f, 20.0f};
	player_->Initialize(model_, textureHandle_, PlayerPosition);
	Vector3 Position{0, 0, 0};
	//EnemyGeneration(Position);
	LoadEnemyPopData();

	// レティクルのテクスチャ
	TextureManager::Load("Reticle.jpg");

	Vector3 enemyhpposition_ = {0.0f, 18.0f, 50.0f};
	enemyhp_ = new EnemyHP();
	enemyhp_->Initialize(model_, enemyhpposition_);
	enemyhp_->SetParent(&railcamera_->GetWorldTransform());
	
	Vector3 enemyuiposition_ = {0.0f, 30.0f, 20.0f};
	enemyui_ = new EnemyUI();
	enemyui_->Initialize(model_, enemyuiposition_);

	Vector3 playerhpposition_ = {0.0f, -10.0f, 20.0f};
	playerhp_ = new PlayerHP();
	playerhp_->Initialize(model_, playerhpposition_);

	Vector3 playeruiposition_ = {-12.0f, -10.0f, 20.0f};
	playerui_ = new PlayerUI();
	playerui_->Initialize(model_, playeruiposition_);

	Vector3 limittimerposition_ = {10.0f, 0.0f, 20.0f};
	limittimer_ = new LimitTimer();
	limittimer_->Initialize(model_, limittimerposition_);

	Vector3 limittimeruiposition_ = {15.0f, 0.0f, 20.0f};
	limittimerui_ = new LImitTimerUI();
	limittimerui_->Initialize(model_, limittimeruiposition_);

}

void GameScene::Update() {
	debugCamera_->Update();
	// ビュープロジェクション行列の更新と転送
	viewProjection_.UpdateMatrix();

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		isDebugCameraAcctive_ = true;
	}
	if (isDebugCameraAcctive_) {

		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}
#endif

	viewProjection_.matView = railcamera_->GetViewProjection().matView;
	viewProjection_.matProjection = railcamera_->GetViewProjection().matProjection;

	// ビュープロジェクション行列の転送
	viewProjection_.TransferMatrix();

	if (railcamera_ != nullptr) {
		railcamera_->Update();
	}
	if (player_ != nullptr) {

		player_->Update(viewProjection_);
	}
	for (Enemy* enemy : enemys_) {
		if (enemy != nullptr) {
			enemy->Update();
		}
	}
	if (skydome_ != nullptr) {
		skydome_->Update();
	}

	if (enemyhp_ != nullptr) {

		enemyhp_->Update();
	}

	if (enemyui_ != nullptr) {

		enemyui_->Update();
	}

	if (playerhp_ != nullptr) {

		playerhp_->Update();
	}

	if (playerui_ != nullptr) {

		playerui_->Update();
	}

	if (limittimer_ != nullptr) {

		limittimer_->Update();
	}

	if (limittimerui_ != nullptr) {

		limittimerui_->Update();
	}

	for (EnemyBullet* bullet : enemybullets_) {
		bullet->Update();
	}
	
	CheckAllCollisions();

	// デスフラグの立った弾を削除
	enemybullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// デスフラグの立った弾を削除
	enemys_.remove_if([](Enemy* enemy) {
		if (enemy->IsDead()) {
			delete enemy;
			return true;
		}
		return false;
	});
	/*if (limittimer_->IsTimerLimit())
	{
		
	}*/
	/*if (player_->IsDead())
	{
		isSceneEnd_ = true;
	}*/

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
	for (Enemy* enemy : enemys_) {
		if (enemy != nullptr) {
			enemy->Draw(viewProjection_);
		}
	}
	if (player_ != nullptr) {

		player_->Draw(viewProjection_);
	}
	skydome_->Draw(viewProjection_);

	for (EnemyBullet* bullet : enemybullets_) {
		bullet->Draw(viewProjection_);
	}

	if (enemyhp_ != nullptr) {

		enemyhp_->Draw(viewProjection_);
	}

	if (enemyui_ != nullptr) {

		enemyui_->Draw(viewProjection_);
	}

	if (playerhp_ != nullptr) {

		playerhp_->Draw(viewProjection_);
	}

	if (playerui_ != nullptr) {

		playerui_->Draw(viewProjection_);
	}

	if (limittimer_ != nullptr) {

		limittimer_->Draw(viewProjection_);
	}

	if (limittimerui_ != nullptr) {

		limittimerui_->Draw(viewProjection_);
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

	player_->DrawUI();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}


void GameScene::EnemyGeneration(const Vector3& position) {
	// 敵の生成
	Enemy* enemy = new Enemy();

	// 敵の初期化
	const float kEnemySpeed = 0.01f;
	Vector3 velocity_ = {0, 0, kEnemySpeed};

	enemy->Initialize(model_, position, velocity_);
	enemy->SetGameScene(this);
	// 敵キャラに自キャラのアドレスを渡す
	enemy->SetPlayer(player_);

	enemys_.push_back(enemy);
}

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) {

	//  リストに登録する
	enemybullets_.push_back(enemyBullet);
}

void GameScene::CheckAllCollisions() {
	// 判定対象AをBの座標
	Vector3 posA, posB;

	// 自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	// 敵弾リストの取得
	// const std::list<EnemyBullet*>& enemyBullets = GetBullets();

	// const std::list<Enemy*>& enemys = GetEnemys();

#pragma region 自キャラと敵弾の当たり判定
	// 自キャラの座標
	posA = player_->GetWorldPosition();
	Vector3 radiusA, radiusB;

	// 自キャラと敵弾全ての当たり判定
	for (EnemyBullet* bullet : enemybullets_) {
		// 敵弾の座標

		posB = bullet->GetWorldPosition();
		radiusA = player_->GetWorldRadius();
		radiusB = bullet->GetWorldRadius();

		// 球と球の交差
		if (CollisionDot(posA, posB, radiusA, radiusB)) {
			// 自キャラの衝突時のコールバックを呼び出す
			player_->OnCollision();
			playerhp_->OnCollision();
			// 敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}

#pragma endregion

#pragma region 自弾と敵キャラの当たり判定

	// 敵キャラと自弾全ての当たり判定
	for (PlayerBullet* bullet : playerBullets) {
		for (Enemy* enemy : enemys_) {

			// 自弾の座標
			posA = bullet->GetWorldPosition();

			posB = enemy->GetWorldPosition();
			radiusB = enemy->GetWorldRadius();

			radiusA = bullet->GetWorldRadius();

			if (CollisionDot(posB, posA, radiusB, radiusA)) {

				// 自弾の衝突時のコールバックを呼び出す
				bullet->OnCollision();
				// 敵キャラの衝突時コールバックを呼び出す

				enemy->OnCollision();
				enemyhp_->OnCollision();
			}
		}
	}

#pragma endregion

#pragma region 自弾と敵弾の当たり判定

	// 敵弾と自弾全ての当たり判定
	for (PlayerBullet* playerbullet : playerBullets) {
		for (EnemyBullet* enemybullet : enemybullets_) {
			// 自弾の座標
			posA = playerbullet->GetWorldPosition();
			// 敵弾の座標
			posB = enemybullet->GetWorldPosition();

			radiusA = playerbullet->GetWorldRadius();
			radiusB = enemybullet->GetWorldRadius();

			if (CollisionDot(posA, posB, radiusA, radiusB)) {

				// 自弾の衝突時のコールバックを呼び出す
				playerbullet->OnCollision();
				// 敵弾の衝突時コールバックを呼び出す
				enemybullet->OnCollision();
			}
		}
	}
#pragma endregion
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
		if (word.find("POP") == 0) {
			// x座標
			getline(line_stream, word,',');
			float x = (float)std::atof(word.c_str());

			// y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			// z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			// 敵を発生させる
			EnemyGeneration(Vector3(x, y, z));
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
