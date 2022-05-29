#include "GameState.h"
#include "StateManager.h"

namespace menu{

CGameState::CGameState(StateManager* pManager)
  : m_pStateManager(pManager)
{
}

CGameState::~CGameState()
{
}

void CGameState::ChangeState(CGameState* pNewState)
{
	m_pStateManager->ChangeState(pNewState);
}

} // namespace menu