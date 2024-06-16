#pragma once

#include "Character.h"

BEGIN(Client)

class CEnemy abstract : public CCharacter
{
protected:
	CEnemy(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CEnemy(const CEnemy& rhs);
	virtual ~CEnemy() = default;

protected:
	static CGameObject* s_pTarget;

public:
	static void Set_Target(CGameObject* pTarget) {
		s_pTarget = pTarget;
	}

	static CGameObject* Get_Target() {
		return s_pTarget;
	}

protected:
	_bool m_bLookTarget = { true };
	_bool m_bKeyFrameAnimChanged = { false };

public:
	void Enable_LookTarget() {
		m_bLookTarget = true;
	}
	void Disable_LookTarget() {
		m_bLookTarget = false;
	}

public:
	void Free() override;
};

END