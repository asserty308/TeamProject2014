#include <SDL.h>
#include <SDL_opengl.h>

#include "FontRenderer.h"
#include "Logger.hpp"

FontRenderer::FontRenderer()
{
	std::string fontFilename = "font.ttf";
	int pointSize = 28;

	if (TTF_Init() < 0)
		g_pLogfile->fLog("SDL_ttf could not be initialized: %s", TTF_GetError());

	font = TTF_OpenFont(fontFilename.c_str(), pointSize);

	if (!font)
		g_pLogfile->fLog("Failed to load font '%s': %s", fontFilename, TTF_GetError());

	glGenTextures(1, &textureID);
}

FontRenderer::~FontRenderer()
{
	if (font)
	{
		TTF_CloseFont(font);
		font = nullptr;
	}

	TTF_Quit();
}

void FontRenderer::drawText(std::string text, SDL_Color color)
{
	// convert RGB color to BGR
	int swap = color.r;
	color.r = color.b;
	color.b = swap;

	SDL_Surface *sText = TTF_RenderUTF8_Blended(font, text.c_str(), color);

	if (!sText)
	{
		g_pLogfile->fLog("Unable to render text surface: %s", SDL_GetError());
		return;
	}

	SDL_Rect area = { 0, 0, sText->w, sText->h };

	SDL_Surface *temp = SDL_CreateRGBSurface(0, sText->w, sText->h, 32, 0, 0, 0, 0);

	if (!temp)
	{
		g_pLogfile->fLog("Unable to create text surface: %s", SDL_GetError());
		return;
	}

	SDL_BlitSurface(sText, &area, temp, NULL);
	
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sText->w, sText->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, temp->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex3f(0, 0, 0);
		glTexCoord2d(1, 0); glVertex3f(0 + sText->w, 0, 0);
		glTexCoord2d(1, 1); glVertex3f(0 + sText->w, 0 + sText->h, 0);
		glTexCoord2d(0, 1); glVertex3f(0, 0 + sText->h, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	SDL_FreeSurface(sText);
	SDL_FreeSurface(temp);
}