#pragma once

#include <SDL_ttf.h>
#include <string>

#include "Singleton.hpp"
#include "Vector2.hpp"

#define g_pFontRenderer FontRenderer::Get()

class FontRenderer : public Singleton<FontRenderer>
{
	private:
		TTF_Font *font;
		GLuint textureID;

	public:
		FontRenderer();
		~FontRenderer();

		void render(SDL_Renderer *renderer, std::string text, SDL_Color color);
		void drawText(std::string text, Vector2 pos, SDL_Color color);

		Vector2 getTextDimensions(std::string text);
};