#include "stdafx.h"
#include "StateManager.h"

namespace menu{

StateManager::StateManager() : m_pActiveState(NULL)
{
}

StateManager::~StateManager()
{
}

void StateManager::OnKeyDown(SDL_KeyboardEvent& e)
{
	if (m_pActiveState)
		m_pActiveState->OnKeyDown(e);
}

void StateManager::OnKeyUp(SDL_KeyboardEvent& e)
{
	if (m_pActiveState)
		m_pActiveState->OnKeyUp(e);
}

void StateManager::OnChar(char* c)
{
	if (m_pActiveState)
		m_pActiveState->OnChar(c);
}

void StateManager::OnResize(int cx, int cy)
{
	if (m_pActiveState)
		m_pActiveState->OnResize(cx, cy);
}

void StateManager::Update(double dwCurrentTime)
{
	if (m_pActiveState)
		m_pActiveState->Update(dwCurrentTime);
}

void StateManager::Draw()
{
	if (m_pActiveState)
		m_pActiveState->Draw();
}

}//namespace menu