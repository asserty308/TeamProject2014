#include "CollisionObserver.h"
#include "Gameplaystate.h"
#include "Game.hpp"
#include "MapParser.h"
#include "SpriteRenderer.hpp"
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

	float playerPos[2] = { player->getPosition().getX(), player->getPosition().getY() };

	client->setPackage((char*)&playerPos, sizeof(float) * 2);
	client->update();

	float allPlayerPositions[4];
	memcpy(allPlayerPositions, client->getReceivedPackage(), sizeof(float) * 4);

	Vector2 pos0(allPlayerPositions[0], allPlayerPositions[1]);
	Vector2 pos1(allPlayerPositions[2], allPlayerPositions[3]);

	Vector2 playerPosVec = Vector2(player->getPosition().getX(), player->getPosition().getY());

	float errorMargin = 1.0f;
	Vector2 netPlayerPos;

	if (std::abs(playerPosVec.getX() - pos0.getX()) < std::abs(playerPosVec.getX() - pos1.getX()) && 
		std::abs(playerPosVec.getY() - pos0.getY()) < std::abs(playerPosVec.getY() - pos1.getY())){
		netPlayerPos = pos1;
	} else{
		netPlayerPos = pos0;
	}

	netplayer->update(netPlayerPos);
}

void Gameplaystate::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (map)
		map->render();

	// temporary
	if (player)
		player->render();

	g_pSpriteRenderer->renderScene();
}

void Gameplaystate::quit()
{

}

void Gameplaystate::inputReceived(SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_p && key->type == SDL_KEYUP)
	{
		g_pGame->setState(g_pGame->getPauseState());

		//tmp location because init() is not called on state-changes
		g_pAudioController->playMusic("Audio/Music/science-0f-22mi.wav", true);
	}
}
