#include "Sprite.hpp"
#include "Logger.hpp"
#include "SpriteRenderer.hpp"
#include "Timer.h"

Sprite::Sprite()
{
}

/*
 position = center of sprite
 dimensions = width / height of sprite
*/
Sprite::Sprite(char* path, Vector2 position, Vector2 dimensions, int numberOfFrames)
{
	this->position = position;
	this->dimensions = dimensions;
	this->filename = path;
	angle = 180.f;

	this->animFrameWidth = dimensions.getX();
	sheetWidth = dimensions.getX() * numberOfFrames;
	animationPlaying = false;

	loadFromFile(path);
}


Sprite::~Sprite()
{
	g_pSpriteRenderer->removeSprite(this);
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

	glTranslatef(position.getX(), position.getY(), 0.f);
	glRotatef(angle, 0.f, 0.f, 1.f);
	glTranslatef(-position.getX(), -position.getY(), 0.f);

	float texCoordsFrameX[2];
	if (animationPlaying){
		texCoordsFrameX[0] = animations[indexOfActiveAnimation][indexOfActiveAnimationFrame] * animFrameWidth / sheetWidth;
		texCoordsFrameX[1] = texCoordsFrameX[0] + animFrameWidth / sheetWidth;

		animationTimer += g_pTimer->getDeltaTime();

		if (animationTimer > animationSpeed){
			indexOfActiveAnimationFrame++;
			animationTimer = 0.0f;
			if (indexOfActiveAnimationFrame >= animations[indexOfActiveAnimation].size()){
				animationPlaying = false;
				indexOfActiveAnimationFrame = 0;
			}
		
		}
		
	} else{
		texCoordsFrameX[0] = 0.0f;
		texCoordsFrameX[1] = animFrameWidth / sheetWidth;
	}

	glBegin(GL_QUADS);
		//top right
		glTexCoord2f(texCoordsFrameX[1], 1.f);
		glVertex2f(position.getX() + (dimensions.getX() / 2.f), position.getY() - (dimensions.getY() / 2.f));
		//bottom right
		glTexCoord2f(texCoordsFrameX[1], 0.f);
		glVertex2f(position.getX() + (dimensions.getX() / 2.f), position.getY() + (dimensions.getY() / 2.f));
		//bottom left
		glTexCoord2f(texCoordsFrameX[0], 0.f);
		glVertex2f(position.getX() - (dimensions.getX() / 2.f), position.getY() + (dimensions.getY() / 2.f));
		//top left
		glTexCoord2f(texCoordsFrameX[0], 1.f);
		glVertex2f(position.getX() - (dimensions.getX() / 2.f), position.getY() - (dimensions.getY() / 2.f));
	glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Sprite::addAnimation(std::vector<int> frames){
	animations.push_back(frames);
}

void Sprite::playAnimation(int index, float speed){
	indexOfActiveAnimation = index;
	animationSpeed = speed;
	animationPlaying = true;
	animationTimer = 0.0f;
	indexOfActiveAnimationFrame = 0;
}

bool Sprite::isPlayingAnimation(){
	return animationPlaying;
}

void Sprite::addAngle(float r)
{
	angle += r;
}

float Sprite::getAngle(){
	return angle;
}

void Sprite::setAngle(float a){
	this->angle = a;
}

void Sprite::setPosition(Vector2 newPos)
{
	position = newPos;
}

Vector2 Sprite::getPosition()
{
	return position;
}

std::string Sprite::getFilename()
{
	return filename;
}