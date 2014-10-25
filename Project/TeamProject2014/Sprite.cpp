#include "Sprite.hpp"
#include "Logger.hpp"
#include "SpriteRenderer.hpp"

Sprite::Sprite()
{
}

/*
 position = center of sprite
 dimensions = width / height of sprite
*/
Sprite::Sprite(const char* path, Vector2 position, Vector2 dimensions)
{
	this->position = position;
	this->dimensions = dimensions;
	loadFromFile(path);
}


Sprite::~Sprite()
{
}

void Sprite::loadFromFile(const char* path)
{
	textureID = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (textureID == 0)
		g_pLogfile->fLog("SOIL loading error: %s", SOIL_last_result());

	g_pSpriteRenderer->addSprite(this);
}

void Sprite::render()
{
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.f, 1.f, 1.f);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glPushMatrix();

	glBegin(GL_QUADS);
		//top right
		glTexCoord2f(1.f, 1.f);
		glVertex2f(position.getX() + dimensions.getX() / 2, position.getY() + dimensions.getY() / 2);
		//bottom right
		glTexCoord2f(1.f, 0.f);
		glVertex2f(position.getX() + dimensions.getX() / 2, position.getY() - dimensions.getY() / 2);
		//bottom left
		glTexCoord2f(0.f, 0.f);
		glVertex2f(dimensions.getX() - dimensions.getX() / 2, position.getY() - dimensions.getY() / 2);
		//top left
		glTexCoord2f(0.f, 1.f);
		glVertex2f(dimensions.getX() - dimensions.getX() / 2, position.getY() + dimensions.getY() / 2);
	glEnd();

	glPopMatrix();

	/*glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glTranslatef(0.5f, 0.5f, 0.f);
	glRotatef(90.f, 0.f, 0.f, 0.5f);
	glTranslatef(-0.5f, -0.5f, 0.f);
	glMatrixMode(GL_MODELVIEW);*/

	glDisable(GL_TEXTURE_2D);
}