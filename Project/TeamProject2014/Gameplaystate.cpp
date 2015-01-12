#include "CollisionObserver.h"
#include "Gameplaystate.h"
#include "Game.hpp"
#include "MapParser.h"
#include "SpriteRenderer.hpp"
#include "FontRenderer.h"
#include "AudioController.hpp"

Gameplaystate::Gameplaystate()
{
	client = nullptr;
	player = nullptr;
	map = nullptr;
	dbc = nullptr;
}

Gameplaystate::~Gameplaystate()
{
	delete client;
	delete player;
	delete netplayer;
	delete map;

	player = nullptr;
	netplayer = nullptr;
	map = nullptr;
	dbc = nullptr;
}

void Gameplaystate::init()
{
	client = new Client();

	map = MapParser::loadMap("testmap.xml");

	Vector2 playerSpawn(g_pGame->getWindowWidth() / 2, g_pGame->getWindowHeight() / 2);

	if (map)
		playerSpawn = map->getPlayerSpawn();

	player = new Player(playerSpawn, Vector2(0.f, -1.f));

	netplayer = new Netplayer(playerSpawn, Vector2(0.0f, -1.0f));

	//initialize and play music
	//g_pAudioController->playMusic("Audio/Music/space2a.wav", true);
}

void Gameplaystate::update()
{
	g_pCollisionObserver->checkCollisionRoutine();

	//play all sounds currently active
	g_pAudioController->playSound();

	if (player){
		player->updatePosition(g_pTimer->getDeltaTime());
		player->update();
	}

	
	Vector2 rocketPos, rocketForward;

	if (player->rocketAlive()){
		rocketPos = player->getRocket()->getPosition();
		rocketForward = player->getRocket()->getForward();
	} else{
		rocketPos = Vector2(-100.0f, -100.0f);
		rocketForward = Vector2(0.0f, 0.0f);
	}
	
	float playerData[9] = { player->getPosition().getX(), player->getPosition().getY(), 
							player->getForward().getX(), player->getForward().getY(), 
							player->getSprite()->getAngle(),
							rocketPos.getX(), rocketPos.getY(),
							rocketForward.getX(), rocketForward.getY()};

	client->setPackage((char*)&playerData, sizeof(float) * 9);
	client->update();

	float allPlayerData[9];
	memcpy(allPlayerData, client->getReceivedPackage(), sizeof(float) * 9);

	Vector2 netPlayerPos(allPlayerData[0], allPlayerData[1]);
	Vector2 netPlayerForward(allPlayerData[2], allPlayerData[3]);
	float netPlayerAngle = allPlayerData[4];
	Vector2 netPlayerRocketPos(allPlayerData[5], allPlayerData[6]);
	Vector2 netPlayerRocketForward(allPlayerData[7], allPlayerData[8]);

	float x = netPlayerRocketPos.getX();

	netplayer->update(netPlayerPos, netPlayerForward, netPlayerAngle, netPlayerRocketPos, netPlayerRocketForward);
}

void Gameplaystate::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (map)
		map->render();

	if (player)
		player->render();

	if (netplayer){
		netplayer->render();
	}

	g_pSpriteRenderer->renderScene();

	SDL_Color color = { 255, 127, 0 };
	g_pFontRenderer->drawText("Hello World", color);
}

void Gameplaystate::quit()
{

}

void Gameplaystate::inputReceived(SDL_KeyboardEvent *key)
{
	//enter pause state
	if (key->keysym.sym == SDLK_p && key->type == SDL_KEYUP)
	{
		g_pGame->setState(g_pGame->getPauseState());

		//tmp location because init() is not called on state-changes
		g_pAudioController->playMusic("Audio/Music/science-0f-22mi.wav", true);
	}
}
