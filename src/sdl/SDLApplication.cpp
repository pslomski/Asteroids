#include "Exception.h"
#include "SDLApplication.h"
#include "SDLWindow.h"
#include "engine/Tools.h"
#include "engine/World.h"
#include "engine/Sound.h"

bool SDLApplication::fQuit = false;

void SDLApplication::Init()
{
	geWorld.ReadSettings();

	/*Initialize SDL library*/
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw SDLException("SDL library initialization failed");

	/* Initialize the TTF library */
	if (TTF_Init() < 0)
		throw SDLException("Couldn't initialize TTF");

	/*Initialize sound*/
	geSound.Open();
	geMusic.Open();

	/*Create window*/
	geWorld.scrHeight = std::min(geWorld.scrHeight, int(0.80 * GetSystemMetrics(SM_CYSCREEN)));
	geWorld.scrWidth = geWorld.scrHeight;
	fPtrWnd = SDLWindow::Create(geWorld.scrWidth, geWorld.scrHeight);
	if (fPtrWnd == NULL)
		throw std::runtime_error("Main window could not be created");
}

void SDLApplication::Cleanup()
{
	SDLWindow::Destroy(fPtrWnd);
	geMusic.Close();
	geSound.Close();
	TTF_Quit();
	SDL_Quit();
}

int GetVRefersh()
{
	constexpr int DEFAULT_VREFRESH = 60;
	SDL_DisplayMode mode;
	if (SDL_GetCurrentDisplayMode(0, &mode) == 0) {
		return mode.refresh_rate;
	}
	else
		return DEFAULT_VREFRESH;
}

void SDLApplication::Run()
{
	geWorld.ReadSettings();
	geWorld.scrHeight = std::min(geWorld.scrHeight, int(0.80 * GetSystemMetrics(SM_CYSCREEN)));
	geWorld.scrWidth = geWorld.scrHeight;
	int VRefresh = GetVRefersh();
	Float FRAME_TIME = (1000.0 / VRefresh);
	DWORD Sleep = int(FRAME_TIME) - 1;
	Float dt = 0.0; // czas od ostatniej aktualizacji
	Float lastUpdateTime = geWorld.GetCurrentTime();
	Float accumulator = 0.0;
	const Float TIME_STEP = 1.0 / VRefresh; // krok czasowy, a zarazem czas trwania ramki fizyki w sekundach;
											   // tutaj czas trwania jednego cyklu odswiezania ekranu
	const Float MAX_ACCUMULATED_TIME = 1.0; // maksymalny czas zgromadzony w pojedynczym

	SDL_Event e;
	while (!fQuit) {
		while (SDL_PollEvent(&e)) {
			OnEvent(&e);
		}
		dt = geWorld.GetCurrentTime() - lastUpdateTime;	//obliczenie czasu od ostatniej klatki
		lastUpdateTime += dt;
		dt = std::max((Float)0, dt);//upewniamy sie, ze dt >= 0
		accumulator += dt;
		accumulator = CLAMP(accumulator, 0.0, MAX_ACCUMULATED_TIME);
		bool bUpdate = false;
		while (accumulator > TIME_STEP) {
			geWorld.dt = TIME_STEP;
			fPtrWnd->Update(TIME_STEP);
			accumulator -= TIME_STEP;
			bUpdate = true;
		}
		geWorld.interp = accumulator / TIME_STEP;
		fPtrWnd->Draw();
	}
}

void SDLApplication::OnEvent(SDL_Event* e)
{
	switch (e->type) {
	case SDL_QUIT:
		QuitApp();
		break;
	default:
		fPtrWnd->OnEvent(e);
	}
}