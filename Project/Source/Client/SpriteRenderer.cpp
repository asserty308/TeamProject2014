#include "SpriteRenderer.hpp"
#include <SDL_opengl.h>
#include "Logger.hpp"


SpriteRenderer::SpriteRenderer()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::addSprite(Sprite *sprite)
{
	sprites.push_back(sprite);
}

void SpriteRenderer::removeSprite(Sprite *sprite)
{
	sprites.erase(std::find(sprites.begin(), sprites.end(), sprite));
}

void SpriteRenderer::renderScene()
{
	for each (Sprite *s in sprites)
	{
		g_pLogfile->fLog("Rendering sprite: \"%s\" @ %f/%f\n", s->getFilename().c_str(), s->getPosition().getX(), s->getPosition().getY());
		s->render();
	}

}

