#include "CollisionObserver.h"
#include "Gameplaystate.h"
#include "Game.hpp"
#include "MapParser.h"
#include "SpriteRenderer.hpp"
#include "FontRenderer.h"
#include "AudioController.hpp"
#include "AudioFiles.hpp"

#include <sstream>

Gameplaystate::Gameplaystate() :
countdown(3)
{
	player = nullptr;
	map = nullptr;
	dbc = nullptr;

	//Just to make sure the Audiocontroller exists. Creating one during Gameplay causes Lags!
	g_pAudioController->stopMusic();
}

Gameplaystate::~Gameplaystate()
{
	delete player;
	delete map;

	for (Netplayer* n : netplayers){
		delete n;
		n = nullptr;
	}

	player = nullptr;
	map = nullptr;
	dbc = nullptr;
}

// TODO: hardcoded
float spawnPoints[2][2] = { { 100.f, 100.f }, { 750.f, 750.f } };

void Gameplaystate::init()
{
	client = g_pGame->getClient();

	map = MapParser::loadMap("Maps\\testmap2.xml");

	Vector2 playerSpawn(spawnPoints[spawnPoint][0], spawnPoints[spawnPoint][1]);
	player = new Player(playerSpawn, Vector2(0.f, -1.f));

	for (int i = 0; i < g_pGame->getNumberOfPlayers() - 1; i++){
		netplayers.push_back(new Netplayer(/*playerSpawn*/Vector2(500.f, 500.f), Vector2(0.0f, -1.0f)));
	}



	matchstate = SPAWN;
	matchCount = 0;

	for (int i = 0; i < g_pGame->getNumberOfPlayers() - 1; i++){
		scoreNetplayers.push_back(0);
	}

	scorePlayer = 0;

	//initialize and play music
	//g_pAudioController->playMusic(MusicFiles::THEME, true);
}

void Gameplaystate::sendOurStuffToServer()
{
	Vector2 rocketPos, rocketForward;
	float isDead = player->getIsDead() ? 1.0f : -1.0f;

	if (player->rocketAlive()){
		rocketPos = player->getRocket()->getPosition();
		rocketForward = player->getRocket()->getForward();
	}
	else{
		rocketPos = Vector2(-100.0f, -100.0f);
		rocketForward = Vector2(0.0f, 0.0f);
	}

	float playerData[10] = { player->getPosition().getX(), player->getPosition().getY(),
		player->getForward().getX(), player->getForward().getY(),
		player->getSprite()->getAngle(),
		rocketPos.getX(), rocketPos.getY(),
		rocketForward.getX(), rocketForward.getY(), isDead };

	client->sendToServer((char*)&playerData, sizeof(float)* 10);
}

void Gameplaystate::receivePacket(std::string packet)
{
	const char *cstr = packet.c_str();

	//size_t numberOfFloatsInBUFLEN = BUFLEN / sizeof(float);
	//float *allPlayerData = new float[(g_pGame->getNumberOfPlayers() - 1) * numberOfFloatsInBUFLEN];
	//memcpy(allPlayerData, cstr, sizeof(float)* (g_pGame->getNumberOfPlayers() - 1) * numberOfFloatsInBUFLEN);

	float *netPlayerData = new float[10];
	memcpy(netPlayerData, cstr, sizeof(float)* 10);

	//int offset = 0;
	//char* defaultTest = "???";

	for (int i = 0; i < g_pGame->getNumberOfPlayers() - 1; i++)
	{
		//offset = i * numberOfFloatsInBUFLEN;

		int offset = 0;

		Vector2 netPlayerPos(netPlayerData[offset + 0], netPlayerData[offset + 1]);
		Vector2 netPlayerForward(netPlayerData[offset + 2], netPlayerData[offset + 3]);
		float netPlayerAngle = netPlayerData[offset + 4];
		Vector2 netPlayerRocketPos(netPlayerData[offset + 5], netPlayerData[offset + 6]);
		Vector2 netPlayerRocketForward(netPlayerData[offset + 7], netPlayerData[offset + 8]);
		bool netPlayerIsDead = netPlayerData[offset + 9] > 0.0f ? true : false;

		if (netPlayerIsDead > 1.5f || netPlayerIsDead < -1.5f)
		{
			//g_pLogfile->fTextout("defaulting from %d", spawnPoint); NEVER HAPPENS
			netplayers[i]->update(Vector2(-100.0f, -100.0f), Vector2(0.0f, -1.0f), 180.0f, Vector2(-100.0f, -100.0f), Vector2(0.0f, -1.0f), false);
		}
		else
			netplayers[i]->update(netPlayerPos, netPlayerForward, netPlayerAngle, netPlayerRocketPos, netPlayerRocketForward, netPlayerIsDead);
	}

	delete[] netPlayerData;
}

//TODO: Expand matchstructure to four players!
void Gameplaystate::update()
{
	sendOurStuffToServer();
	client->update();

	g_pCollisionObserver->checkCollisionRoutine();

	Vector2 playerSpawn(spawnPoints[spawnPoint][0], spawnPoints[spawnPoint][1]);

	switch (matchstate)
	{
		case(SPAWN):
			player->setPosition(playerSpawn);
			player->reset();

			if (countdown.getState() == INITIALIZED)
				countdown.start();
			else if (countdown.getState() == FINISHED)
			{
				matchstate = MATCH;
				countdown.reset();
			}
		break;
		case(MATCH):
			if (player)
			{
				player->updatePosition(g_pTimer->getDeltaTime());
				player->update();

				int deadNetplayers = 0;
				for (Netplayer* n : netplayers)
				{
					if (n->getIsDead())
						deadNetplayers++;
				}

				//if every netplayer is dead and the player is alive OR every netplayer but one is dead and the player is also dead
				//the match is over
				if (deadNetplayers == g_pGame->getNumberOfPlayers() - 1 && !player->getIsDead() ||
					deadNetplayers == g_pGame->getNumberOfPlayers() - 2 && player->getIsDead())
				{
					//matchstate = MATCHOVER;
				}
			}
		break;
		case(MATCHOVER):
			matchCount++;

			if (!player->getIsDead())
				scorePlayer++;
			else
			{
				for (int i = 0; i < netplayers.size(); i++)
				{
					if (!netplayers[i]->getIsDead())
						scoreNetplayers[i]++;
				}
			}

			if (matchCount >= MATCHNUMBER)
				matchstate = GAMEOVER;
			else
				matchstate = SPAWN;
		break;
		case(GAMEOVER) :
		break;
	}

	countdown.run();
}

void Gameplaystate::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (matchstate)
	{
		case(SPAWN) :
		{
			if (countdown.getState() == RUNNING)
			{
				std::stringstream CountdownText;
				CountdownText << countdown.getCurrentCountdown();
				SDL_Color color = { 255, 127, 0 };
				Vector2 textDimensions = g_pFontRenderer->getTextDimensions(CountdownText.str());
				Vector2 textPos((g_pGame->getWindowWidth() / 2) - (textDimensions.getX() / 2), (g_pGame->getWindowHeight() / 2) - (textDimensions.getY() / 2));
				g_pFontRenderer->drawText(CountdownText.str(), textPos, color);
			}
		}
		break;
		case(MATCHOVER) :
		case(MATCH) :
		{
			if (map)
				map->render();

			if (player)
				player->render();

			for (Netplayer* n : netplayers)
				n->render();

			g_pSpriteRenderer->renderScene();
			renderScore();
		}
		break;
		case(GAMEOVER) :
		{
			std::string gameOverText = "Game Over! Thanks for playing!";
			SDL_Color color = { 255, 127, 0 };
			Vector2 textDimensions = g_pFontRenderer->getTextDimensions(gameOverText);
			Vector2 textPos((g_pGame->getWindowWidth() / 2) - (textDimensions.getX() / 2), (g_pGame->getWindowHeight() / 2) - (textDimensions.getY() / 2));
			g_pFontRenderer->drawText(gameOverText, textPos, color);
		}
		break;
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
		//g_pGame->setState(g_pGame->getPauseState());
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

