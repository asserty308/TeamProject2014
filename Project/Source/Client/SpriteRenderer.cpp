#include "SpriteRenderer.hpp"
#include <SDL_opengl.h>
#include "Logger.hpp"


SpriteRenderer::SpriteRenderer()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	background[0] = nullptr;
	background[1] = nullptr;
}


SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::addSprite(Sprite *sprite)
{
	if (strcmp(sprite->getFilename().c_str(), "Sprites\\menu_background.png") == 0)
		background[0] = sprite;
	else if (strcmp(sprite->getFilename().c_str(), "Sprites\\new_background.png") == 0)
		background[1] = sprite;
	else
		sprites.push_back(sprite);
}

void SpriteRenderer::removeSprite(Sprite *sprite)
{
	sprites.erase(std::find(sprites.begin(), sprites.end(), sprite));
}

void SpriteRenderer::renderScene()
{
	if (background[0])
		background[0]->render();
	
	if (background[1])
		background[1]->render();

	for each(Sprite* s in sprites)
	{
		//g_pLogfile->fLog("Rendering sprite: \"%s\" @ %f/%f\n", s->getFilename().c_str(), s->getPosition().getX(), s->getPosition().getY());
		s->render();
	}
}

