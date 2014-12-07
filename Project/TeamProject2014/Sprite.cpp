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
Sprite::Sprite(char* path, Vector2 position, Vector2 dimensions)
{
	this->position = position;
	this->dimensions = dimensions;
	angle = 180.f;

	spritePath = path;

	imgWidth = (int)dimensions.getX();
	imgHeight = (int)dimensions.getY();

	loadFromFile();
}


Sprite::~Sprite()
{
	SOIL_free_image_data(img);
}

void Sprite::loadFromFile()
{
	//textureID = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	img = SOIL_load_image(spritePath, &imgWidth, &imgHeight, 0, SOIL_LOAD_RGB);

	/*if (textureID == 0)
		g_pLogfile->fLog("SOIL loading error: %s", SOIL_last_result());*/

	if (img == NULL)
	{
		g_pLogfile->fLog("SOIL loading error: %s", SOIL_last_result());
		exit(EXIT_FAILURE);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	g_pSpriteRenderer->addSprite(this);
}

void Sprite::render()
{
	glColor3f(1.f, 1.f, 1.f);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_TEXTURE_2D);

	/*glColor3f(1.f, 1.f, 1.f);
	glBindTexture(GL_TEXTURE_2D, textureID);*/

	glPushMatrix();

	glTranslatef(position.getX(), position.getY(), 0.f);
	glRotatef(angle, 0.f, 0.f, 1.f);
	glTranslatef(-position.getX(), -position.getY(), 0.f);

	glBegin(GL_QUADS);
		//top right
		glTexCoord2f(1.f, 1.f);
		glVertex2f(position.getX() + (dimensions.getX() / 2.f), position.getY() - (dimensions.getY() / 2.f));
		//bottom right
		glTexCoord2f(1.f, 0.f);
		glVertex2f(position.getX() + (dimensions.getX() / 2.f), position.getY() + (dimensions.getY() / 2.f));
		//bottom left
		glTexCoord2f(0.f, 0.f);
		glVertex2f(position.getX() - (dimensions.getX() / 2.f), position.getY() + (dimensions.getY() / 2.f));
		//top left
		glTexCoord2f(0.f, 1.f);
		glVertex2f(position.getX() - (dimensions.getX() / 2.f), position.getY() - (dimensions.getY() / 2.f));
	glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Sprite::addAngle(float r)
{
	angle += r;
}

void Sprite::setPosition(Vector2 newPos)
{
	position = newPos;
}

Vector2 Sprite::getPosition()
{
	return position;
}