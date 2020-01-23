#pragma once

#include "Types.h"

class World {
private:
	bool usePerfCounter_;
	double frequency_;
	DWORD timePrev_;
	DWORD time_;
	void SetTime(DWORD in_Time) {
		timePrev_ = time_;
		time_ = in_Time;
	};
public:
	World(void);
	virtual ~World(void);

	int MusicVol;
	int SoundVol;
	bool IsGameRunning;
	Float dt;//krok czasu pomiedzy  wywolaniami GetTimeDelta
	Float interp;//wspczynnik interpolacji ruchu
	int scrWidth;//szerokosc ekranu w pixelach
	int scrHeight;//wysokosc ekranu w pixelach
	//granice obszaru gry
	Float clipLeft, clipRight;
	Float clipBottom, clipTop;
	Float getWidth() {
		return clipRight - clipLeft;
	}
	Float GetHeight() {
		return clipTop - clipBottom;
	}
	PointF GetCenter() {
		return PointF(
			(clipRight + clipLeft) / 2.0,
			(clipTop + clipBottom) / 2.0
		);
	}
	PointF GetRandomPosAtEdge(void);
	DWORD GetTicks(void) {
		return time_;
	}
	Float GetCurrentTime();
	void ReadSettings(void);
	void SaveSettings(void);
};

extern World geWorld;