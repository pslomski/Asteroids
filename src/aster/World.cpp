#include <fstream>
#include "World.h"
#include "Sound.h"
#include "GameConsts.h"

World geWorld;

World::World()
{
    LARGE_INTEGER f;
    usePerfCounter_=QueryPerformanceFrequency(&f)!=0;
    frequency_=double(f.QuadPart);
    MusicVol=5;
    SoundVol=5;
    IsGameRunning=false;
    clipLeft=0;
    clipRight=GE_WORLD_WIDTH;
    clipBottom=0;
    clipTop=GE_WORLD_HEIGHT;
    scrWidth=GE_SCREEN_WIDTH;
    scrHeight=GE_SCREEN_HEIGHT;
//	counter.start();
}

World::~World()
{
}

PointF World::GetRandomPosAtEdge()
{
    PointF pt;
    int iSide=rand()%4;
    if(0==iSide){
        pt.x=geWorld.clipLeft;
        pt.y=rand()%int(geWorld.clipTop-geWorld.clipBottom);
    }
    else if(1==iSide){
        pt.x=geWorld.clipRight;
        pt.y=rand()%int(geWorld.clipTop-geWorld.clipBottom);
    }
    else if(2==iSide){
        pt.x=rand()%int(geWorld.clipRight-geWorld.clipLeft);
        pt.y=geWorld.clipBottom;
    }
    else{
        pt.x=rand()%int(geWorld.clipRight-geWorld.clipLeft);
        pt.y=geWorld.clipTop;
    }
    return pt;
}

void World::readSettings()
{
    std::ifstream inputFile("settings.dat");
    if(inputFile.fail()){
        MusicVol=5;
        SoundVol=5;
    }
    else{
        inputFile >> MusicVol >> SoundVol;
    }
    geMusic.SetVolume(0.1f*MusicVol);
    geSound.SetVolume(0.1f*SoundVol);
}

void World::saveSettings()
{
    // Create the file
    std::ofstream outputFile("settings.dat");
    if (outputFile.fail())
        return;
    
    outputFile << MusicVol << " " << SoundVol;
}

Float World::GetCurrentTime()
{
    if(usePerfCounter_){
        LARGE_INTEGER t;
        QueryPerformanceCounter(&t);
        return t.QuadPart/frequency_;
    }
    else{
        return GetTickCount()/1000.0;
    }
}
