#include <SDL_opengl.h>
#include "AudioFiles.hpp"
#include "Logger.hpp"
#include "InputObserver.h"
#include "CollisionObserver.h"
#include "Player.hpp"
#include "Timer.h"
#include "Game.hpp"
#include "SpriteRenderer.hpp"
#include "CircleBoundingBox.h"
#include "AudioController.hpp"
#include "MathUtil.h"

const float Player::TOP_SPEED = 70.f;
const float Player::ACCELERATION = 120.f;
const float Player::TURN_SPEED = 188.f;

Player::Player(Vector2 position, Vector2 forward) : TransformCollidable(position, forward, Vector2(0.0f, 0.0f))
{
	isThrustKeyDown = isLeftKeyDown = isRightKeyDown = isFirePressed = fireLock = false;
	
	g_pInputObserver->addListener(this);
	g_pCollisionObserver->addListener(this);

	boundingBox = new CircleBoundingBox(position, 30.0f);

	//create sprite
	sprite = new Sprite("Sprites\\new_fighter_sheet.png", position, Vector2(80.f, 80.f), 4);
	std::vector<int> idleAnimation;
	idleAnimation.push_back(0);
	sprite->addAnimation(idleAnimation);
	std::vector<int> thrustingAnimation;
	thrustingAnimation.push_back(1);
	thrustingAnimation.push_back(2);
	thrustingAnimation.push_back(3);
	sprite->addAnimation(thrustingAnimation);

	rocket = nullptr;

	isDead = false;

	//g_pAudioController->addSound("Audio/Sounds/spaceship-ambience.wav");
}

Player::~Player()
{
	//g_pAudioController->removeSound("Audio/Sounds/spaceship-ambience.wav");
	g_pCollisionObserver->removeListener(this);

	delete sprite;
	delete boundingBox;

	sprite = nullptr;
	boundingBox = nullptr;
}

void Player::inputReceived(SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_w)
		isThrustKeyDown = (key->type == SDL_KEYDOWN);
	else if (key->keysym.sym == SDLK_a)
		isLeftKeyDown = (key->type == SDL_KEYDOWN);
	else if (key->keysym.sym == SDLK_d)
		isRightKeyDown = (key->type == SDL_KEYDOWN);
	else if (key->keysym.sym == SDLK_SPACE){
		isFirePressed = (key->type == SDL_KEYDOWN);
		if (key->type == SDL_KEYUP){
			fireLock = false;
		}
	}
}

void Player::CollisionDetected(TransformCollidable *other, Vector2 penetration){
	if (other == rocket){
		return;
	}

	if (std::strcmp(other->getTag().c_str(), "netRocket") == 0){
		die();
	}

	velocity += penetration * -1 * 15.0f;
}

void Player::update()
{
	if (rocket == nullptr || !rocket->getControllable())
	// only control the player if there is no rocket or it's not controlled
	{
		if (isThrustKeyDown)
		{
			setAcceleration(forward * ACCELERATION);
			
			if (sprite->getAnimationIndex() != 1)
			{
				sprite->playAnimation(1, 0.05f, true);
				g_pAudioController->playSound(SoundFiles::BOOST, true);
			}
		}
		else
		{
			setAcceleration(Vector2(0.0f, 0.0f));

			if (sprite->getAnimationIndex() != 0)
			{
				sprite->playAnimation(0, 0.05f, true);
				g_pAudioController->stopSoundByFile(SoundFiles::BOOST);
			}
		}

		if (isLeftKeyDown && !isRightKeyDown)
		{
			rotate(-TURN_SPEED * g_pTimer->getDeltaTime());
			sprite->addAngle(-TURN_SPEED * g_pTimer->getDeltaTime());
		}
		else if (isRightKeyDown && !isLeftKeyDown)
		{
			rotate(TURN_SPEED * g_pTimer->getDeltaTime());
			sprite->addAngle(TURN_SPEED * g_pTimer->getDeltaTime());
		}
	}

	handleRocket();

	if (velocity.getLength() > TOP_SPEED)
	// cap max speed if we are going to fast
	{
		velocity.normalize();
		velocity = velocity * TOP_SPEED;
	}

	if (!isDead){
		float playerRadius = dynamic_cast<CircleBoundingBox*> (boundingBox)->getRadius();

		if (getPosition().getX() < playerRadius)
		{
			position.setX(playerRadius);
			velocity.setX(-velocity.getX() * .25f);
		} else if (getPosition().getX() > g_pGame->getWindowWidth() - playerRadius)
		{
			position.setX(g_pGame->getWindowWidth() - playerRadius);
			velocity.setX(-velocity.getX() * .25f);
		}

		if (getPosition().getY() < playerRadius)
		{
			position.setY(playerRadius);
			velocity.setY(-velocity.getY() *.25f);
		} else if (getPosition().getY() > g_pGame->getWindowHeight() - playerRadius)
		{
			position.setY(g_pGame->getWindowHeight() - playerRadius);
			velocity.setY(-velocity.getY() *.25f);
		}
	}

	//set sprite position to player position
	sprite->setPosition(position);
}

void Player::handleRocket()
{
	if (isFirePressed && rocket == nullptr && !fireLock)
	{
		fireLock = true;
		rocket = new Rocket(this, getPosition(), getForward());
		rocket->setTag("rocket");
		//rocket->setVelocity(getVelocity() * 2.f);
	}
	else if (rocket != nullptr)
	{
		//if rocket is on screen, let it fly until it's out of screen
		if (rocket->getPosition().getX() > 0.f && rocket->getPosition().getX() < g_pGame->getWindowWidth() &&
			rocket->getPosition().getY() < g_pGame->getWindowHeight() && rocket->getPosition().getY() > 0.f)
			rocket->update();
		else
		{
 			delete rocket;
			rocket = nullptr;
		}
	}
}

void Player::rocketDestroyed(){
	if (rocket){
		delete rocket;
		rocket = nullptr;
	}
}

bool Player::rocketAlive(){
	if (rocket){
		return true;
	} else{
		return false;
	}
}

void Player::die(){
	isDead = true;
	setPosition(Vector2(-500.0, -500.0));
	g_pInputObserver->removeListener(this);

	//TODO: Do something more.....sophisticated? 
}

void Player::reset(){
	isDead = false;

	this->acceleration = this->velocity = Vector2(0.0f, 0.0f);

	Vector2 lookAtVector = Vector2(g_pGame->getWindowWidth() / 2 - position.getX(), g_pGame->getWindowHeight() / 2 - position.getY());
	lookAtVector.normalize();
	this->forward = lookAtVector;
	sprite->setAngle(angleFromVector<float>(forward));

	if (!g_pInputObserver->isListening(this)){
		g_pInputObserver->addListener(this);
	}
}

bool Player::getIsDead(){
	return isDead;
}

Rocket* Player::getRocket(){
	return rocket;
}

Sprite* Player::getSprite(){
	return this->sprite;
}