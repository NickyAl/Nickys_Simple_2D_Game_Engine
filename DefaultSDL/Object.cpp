#include "Object.h"


Object::Object() : Rect(), hasCollision(false)//, animFrames(0)
{
}

Object::Object(float w, float h, float x, float y, uint8_t r, uint8_t g, uint8_t b, uint8_t a, bool collsn) :
	Rect(w, h, x, y, r, g, b, a), hasCollision(collsn)//, animFrames(0)
{
}

Object::Object(float w, float h, float x, float y, const std::string& image_path, bool collsn) :
	Rect(w, h, x, y, 255, 255, 255, 255), hasCollision(collsn)//, animFrames(0)
{
	auto surface = IMG_Load(image_path.c_str()); //c_str converts it to a construct pointer
	//auto says the type is SDL_Surface but once I change it from auto to SDL_Surface it breaks
	if (!surface)
	{
		std::cerr << "Failed to create surface\n";
	}

	this->texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
	if (!this->texture)
	{
		std::cerr << "Failed to create texture\n";
	}

	SDL_FreeSurface(surface);
}

Object::Object(float w, float h, float x, float y, SDL_Texture* texture, bool collsn) : Rect(w, h, x, y, texture), hasCollision(collsn)//, animFrames(0)
{
}

Object::~Object()
{
	SDL_DestroyTexture(this->texture);
}

//SDL_Texture* Object::LoadTexture(const std::string& filepath)
//{
//	SDL_Texture* newTexture = nullptr;
//
//	SDL_Surface* loadedSurf = IMG_Load(filepath.c_str());
//
//	if (loadedSurf == nullptr)
//	{
//		std::cerr << "Failed to load pawn texture\n";
//	}
//	else
//	{
//		newTexture = SDL_CreateTextureFromSurface(Window::renderer, loadedSurf);
//		if (newTexture == nullptr)
//		{
//			std::cerr << "Failed to create texture for pawn\n";
//		}
//		SDL_FreeSurface(loadedSurf);
//	}
//
//	return newTexture;
//}

//void Object::loadAnim(const std::string& filepath, short int frames)
//{
//	this->animFrames = frames;
//	std::string path;
//
//	for (int i = 0; i < frames; i++)
//	{
//		path = filepath;
//		path += std::to_string(i);
//		path += ".png";
//
//		animation.push_back(LoadTexture(path));	
//	}
//}

//void Object::updateSprite(float tpf, float cooldown)
//{
//	static float timer = 0;
//	static short int frame = 0;
//
//	int divider = (int) (1000 * cooldown);
//
//	timer += tpf;
//
//	if (timer > cooldown)
//	{
//		int check = (int) timer * 1000;
//		if (check / divider > 1)
//		{
//			frame += check / divider;
//		}
//		else
//			frame++;
//		timer = 0;
//	}
//
//	if (frame >= this->animFrames)
//		frame = 0;
//	
//	setTexture(this->animation[frame]);
//}
