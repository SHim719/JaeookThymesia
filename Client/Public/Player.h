#pragma once

#include "Character.h"
#include "Player_Enums.h"

BEGIN(Client)

class CPlayer final : public CCharacter
{
private:
	enum PLAYER_WEAPON { SABER, DAGGER, CLAW_L, CLAW_R, WEAPON_END};

private:
	CPlayer(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CPlayer(const CPlayer& rhs);
	virtual ~CPlayer() = default;

public:
	HRESULT Initialize_Prototype()		override;
	HRESULT Initialize(void* pArg)		override;
	void Tick(_float fTimeDelta)		override;
	void LateTick(_float fTimeDelta)	override;
	HRESULT Render()					override;

private:
	void Bind_KeyFrames()	override;

private:
	class CPlayerStat*	m_pStats = { nullptr };
public:
	CPlayerStat* Get_PlayerStat() const { 
		return m_pStats; }

private:
	class CWeapon* m_Weapons[WEAPON_END] = {};

private:
	void Update_AttackDesc(const ATTACKDESC& Desc);

	void Active_Weapons();
	void InActive_Weapons();
	void Active_Claw();
	void InActive_Claw();

private:
	CTransform*		m_pTargetTransform = { nullptr };
	_bool			m_bLockOn = { false };
	_bool			m_bCanParry = { true };

public:
	void Toggle_LockOn(CTransform* pTargetTransform = nullptr);
	_bool Is_LockOn() const { return m_bLockOn; }
	void Enable_Parry() { m_bCanParry = true; }
	void Disable_Parry() { m_bCanParry = false; }

private:
	HRESULT Ready_Components();
	HRESULT Ready_States();
	HRESULT Ready_Weapons();

public:
	static CPlayer* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END