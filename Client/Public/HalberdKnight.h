#pragma once

#include "Enemy.h"
#include "HalberdKnight_Enums.h"

BEGIN(Client)

class CHalberdKnight final : public CEnemy
{
public:
	enum HALBEREDKNIGHT_WEAPON { SPEAR, WEAPON_END };

private:
	CHalberdKnight(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CHalberdKnight(const CHalberdKnight& rhs);
	virtual ~CHalberdKnight() = default;

private:
	HRESULT Initialize_Prototype()		override;
	HRESULT Initialize(void* pArg)		override;
	void Tick(_float fTimeDelta)		override;
	void LateTick(_float fTimeDelta)	override;
	HRESULT Render()					override;

	void Bind_KeyFrames()				override;

private:
	_float	m_fRotRate = { 8.f };

private:
	void Percept_Target() override;
	void SetState_Death()	override;

	_bool Is_Death() override {
		return m_iState == (_uint)HalberdKnight_State::State_Death;
	}

	_bool Is_Stunned() override {
		return m_iState == (_uint)HalberdKnight_State::State_Stunned_Loop;
	}

private:
	HRESULT Ready_Components(void* pArg);
	HRESULT Ready_States();
	HRESULT Ready_Weapon();
	HRESULT Ready_Stats();
	HRESULT Ready_UI();

public:
	static CHalberdKnight* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CGameObject* Clone(void* pArg) override;
	void Free() override;
};

END