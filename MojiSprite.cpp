#include "MojiSprite.h"
void MojiSprite::Initialize() { 
	uint32_t textureMoji = TextureManager::Load("moji.png");

	texturesprite_ = Sprite::Create(textureMoji, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f});




}
void MojiSprite::Update() {}

void MojiSprite::DrawUI() {
	texturesprite_->Draw();
}
