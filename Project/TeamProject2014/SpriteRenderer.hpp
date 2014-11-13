#pragma once

#include <vector>
#include "Sprite.hpp"
#include "Singleton.hpp"

#define g_pSpriteRenderer SpriteRenderer::Get()

class SpriteRenderer : public Singleton<SpriteRenderer>
{
	private:
		std::vector<Sprite*> sprites;
		
	public:
		SpriteRenderer();
		~SpriteRenderer();

		void addSprite(Sprite *sprite);
		void removeSprite(Sprite *sprite);
		void renderScene();
};

