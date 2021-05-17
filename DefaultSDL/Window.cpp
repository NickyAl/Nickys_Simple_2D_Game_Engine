#include "Window.h"


SDL_Renderer* Window::renderer;

Window::Window() :
	title("NS2D Default Window") ,width(640), height(360), resolutionSetting(1.0f),
	closed(false), window(nullptr), openedSettings(false)
{}

Window::Window(const std::string& newTitle, int newWidth, int newHeight) :
	title(newTitle), width(newWidth), height(newHeight), resolutionSetting(1.0f),
	closed(false), window(nullptr)
{
	this->closed = !init();
}

Window::~Window()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	IMG_Quit();
	SDL_Quit();
}

bool Window::init()
{
	if (SDL_Init(SDL_INIT_VIDEO)) //ONLY VIDEO PORTION IF ADDING AUDIO MUST CHANGE
	{
		std::cerr << "Failed to init SDL.\n";
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG)) //png or jpg images
	{
		std::cerr << "Failed to init SDL_image\n";
		return false;
	}

	if (TTF_Init() == -1)
	{
		std::cerr << "Failed to init SDL_ttf\n";
		return false;
	}

	this->window = SDL_CreateWindow(this->title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		this->width, this->height, 0);

	if (this->window == nullptr)
	{
		std::cerr << "Failed to create window\n";
		return 0;
	}

	this->renderer = SDL_CreateRenderer(this->window, -1,
		SDL_RENDERER_ACCELERATED); //Can change to vsynced to cap the fps at 60

	if (renderer == nullptr)
	{
		std::cerr << "Failed to create renderer\n";
		return false;
	}

	return true;
}

void Window::pollEvents(SDL_Event& event)
{
	//std::cout << event.motion.x << " " << event.motion.y << "\n";
	switch (event.type)
	{
	case SDL_QUIT:
		this->closed = true;
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (event.motion.x > (640 * resolutionSetting) - (20 * resolutionSetting) && event.motion.y < 20 * resolutionSetting)
		{
			openedSettings = true;
		}

		if (openedSettings)
		{
			if (event.motion.y < 75)
			{

				resolutionSetting = 1.0f;
				openedSettings = false;
				closed = true;
			}
			else if (event.motion.y < 150)
			{
				resolutionSetting = 2.0f;
				openedSettings = false;
				closed = true;
			}
			else if (event.motion.y < 225)
			{
				resolutionSetting = 3.0f;
				openedSettings = false;
				closed = true;
			}
			else if (event.motion.y < 300)
			{
				resolutionSetting = 4.0f;
				openedSettings = false;
				closed = true;

			}
		}

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			this->closed = true;
			break;

		default:
			break;
		}

	default:
		break;
	}
}

void Window::clear() const
{
	SDL_RenderPresent(this->renderer);

	SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255); //renderer R G B Opacity
	SDL_RenderClear(this->renderer);
}
