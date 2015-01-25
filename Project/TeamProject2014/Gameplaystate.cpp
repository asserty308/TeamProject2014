#include "CollisionObserver.h"
#include "Gameplaystate.h"
#include "Game.hpp"
#include "MapParser.h"
#include "SpriteRenderer.hpp"
#include "FontRenderer.h"
#include "AudioController.hpp"

#include <sstream>

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

	char* serverInitPackage = client->getInitPackage();
	float playerSpawnFromServer[2];
	memcpy(playerSpawnFromServer, serverInitPackage, sizeof(float)* 2);
	Vector2 playerSpawn(playerSpawnFromServer[0], playerSpawnFromServer[1]);

	player = new Player(playerSpawn, Vector2(0.f, -1.f));
	netplayer = new Netplayer(playerSpawn, Vector2(0.0f, -1.0f));

	matchstate = SPAWN;
	matchCount = 0;
	scoreNetplayers.push_back(0);
	scorePlayer = 0;

	//initialize and play music
	//g_pAudioController->playMusic("Audio/Music/space2a.wav", true);
}

//TODO: Expand matchstructure to four players!
void Gameplaystate::update()
{
	g_pCollisionObserver->checkCollisionRoutine();
	//g_pAudioController->playSound();

	switch (matchstate){
	case(SPAWN) : {
		char* serverInitPackage = client->getInitPackage();
		float playerSpawnFromServer[2];
		memcpy(playerSpawnFromServer, serverInitPackage, sizeof(float)* 2);
		Vector2 playerSpawn(playerSpawnFromServer[0], playerSpawnFromServer[1]);

		player->setPosition(playerSpawn);
		player->reset();

		matchstate = MATCH;
	}break;
	case(MATCH) : {
		if (player){
			player->updatePosition(g_pTimer->getDeltaTime());
			player->update();

			if (player->getIsDead() || netplayer->getIsDead()){
				matchstate = MATCHOVER;
			}
		}

	}break;
	case(MATCHOVER) : {

		matchCount++;

		if (player->getIsDead()){
			for (int i = 0; i < scoreNetplayers.size(); i++){
				scoreNetplayers[i]++;
				break;
			}
		}

		if (netplayer->getIsDead()){
			scorePlayer++;
		}

		if (matchCount >= MATCHNUMBER){
			matchstate = GAMEOVER;
		} else {
			matchstate = SPAWN;
		}
	}break;
	case(GAMEOVER) : {					 
		break;
	}
	}

	handleConnection();
}

void Gameplaystate::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (matchstate){
	case(SPAWN) : 
	case(MATCHOVER) : 
	case(MATCH) : {
		if (map)
			map->render();

		if (player)
			player->render();

		if (netplayer){
			netplayer->render();
		}

		g_pSpriteRenderer->renderScene();
		renderScore();
	}break;
	case(GAMEOVER) : {
		std::string gameOverText = "Game Over! Thanks for playing!";
		SDL_Color color = { 255, 127, 0 };
		Vector2 textDimensions = g_pFontRenderer->getTextDimensions(gameOverText);
		Vector2 textPos((g_pGame->getWindowWidth() / 2) - (textDimensions.getX() / 2), (g_pGame->getWindowHeight() / 2) - (textDimensions.getY() / 2));
		g_pFontRenderer->drawText(gameOverText, textPos, color);
	}break;
	}
	
	
	
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

//Task: Send and receive required Information via client to and from server
void Gameplaystate::handleConnection(){
	Vector2 rocketPos, rocketForward;
	float isDead = player->getIsDead() ? 1.0f : 0.0f;

	if (player->rocketAlive()){
		rocketPos = player->getRocket()->getPosition();
		rocketForward = player->getRocket()->getForward();
	} else{
		rocketPos = Vector2(-100.0f, -100.0f);
		rocketForward = Vector2(0.0f, 0.0f);
	}

	float playerData[10] = { player->getPosition().getX(), player->getPosition().getY(),
		player->getForward().getX(), player->getForward().getY(),
		player->getSprite()->getAngle(),
		rocketPos.getX(), rocketPos.getY(),
		rocketForward.getX(), rocketForward.getY(), isDead };

	client->setPackage((char*)&playerData, sizeof(float)* 10);
	client->update();

	float allPlayerData[10];
	memcpy(allPlayerData, client->getReceivedPackage(), sizeof(float)* 10);

	Vector2 netPlayerPos(allPlayerData[0], allPlayerData[1]);
	Vector2 netPlayerForward(allPlayerData[2], allPlayerData[3]);
	float netPlayerAngle = allPlayerData[4];
	Vector2 netPlayerRocketPos(allPlayerData[5], allPlayerData[6]);
	Vector2 netPlayerRocketForward(allPlayerData[7], allPlayerData[8]);
	bool netPlayerIsDead = allPlayerData[9] > 0.0f ? true : false;

	float x = netPlayerRocketPos.getX();

	char* defaultTest = "???";
	if (memcmp(allPlayerData, defaultTest, sizeof(char) * 3) != 0){ //Check if sent data is no default memory. If it is, pass default values
		netplayer->update(netPlayerPos, netPlayerForward, netPlayerAngle, netPlayerRocketPos, netPlayerRocketForward, netPlayerIsDead);
	} else{
		netplayer->update(Vector2(-100.0f, -100.0f), Vector2(0.0f, -1.0f), 180.0f, Vector2(-100.0f, -100.0f), Vector2(0.0f, -1.0f), false);
	}
}

//Render playerscores
void Gameplaystate::renderScore(){
	std::stringstream scoreStream;
	scoreStream << scorePlayer;
	for (int i = 0; i < scoreNetplayers.size(); i++){
		scoreStream << "    " << scoreNetplayers[i];
	}

	SDL_Color color = { 255, 127, 0 };
	Vector2 textDimensions = g_pFontRenderer->getTextDimensions(scoreStream.str());
	Vector2 textPos((g_pGame->getWindowWidth() / 2) - (textDimensions.getX() / 2), 0.0f);
	g_pFontRenderer->drawText(scoreStream.str(), textPos, color);
}

