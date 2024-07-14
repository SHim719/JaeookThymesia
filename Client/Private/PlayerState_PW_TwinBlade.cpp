#include "PlayerState_PW_TwinBlade.h"

CPlayerState_PW_TwinBlade::CPlayerState_PW_TwinBlade(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CPlayerState_Base(pDevice, pContext)
{
}

HRESULT CPlayerState_PW_TwinBlade::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_PossibleStates = { PlayerState::State_Attack, PlayerState::State_ChargeStart, PlayerState::State_Avoid, PlayerState::State_Parry };

	return S_OK;
}

void CPlayerState_PW_TwinBlade::OnState_Start(void* pArg)
{
	Reset_AttackIdx();

	m_pPlayer->Set_CanNextState(false);
	m_pPlayer->Set_Stanced(true);
	m_pPlayer->Set_Active_DefaultWeapons(false);
	m_pPlayer->Set_Active_Claws(false);

	m_pPlayer->Set_Active_Weapon(CPlayer::PW_TWINBLADE_L, true);
	m_pPlayer->Set_Active_Weapon(CPlayer::PW_TWINBLADE_R, true);

	m_pPlayer->Update_AttackDesc();

	m_pModel->Change_Animation(Corvus_PW_TwinSwords_1);
}

void CPlayerState_PW_TwinBlade::Update(_float fTimeDelta)
{
	m_pOwnerTransform->Move_Root(m_pModel->Get_DeltaRootPos(), m_pNavigation);
}

void CPlayerState_PW_TwinBlade::Late_Update(_float fTimeDelta)
{
	if (m_pModel->Is_AnimComplete())
		m_pPlayer->Change_State((_uint)PlayerState::State_Idle);

	PlayerState ePlayerState = Decide_State();
	if (PlayerState::State_End != ePlayerState)
		m_pPlayer->Change_State((_uint)ePlayerState);

}

void CPlayerState_PW_TwinBlade::OnState_End()
{
	m_pPlayer->Set_Stanced(false);
	m_pPlayer->Set_Active_DefaultWeapons(true);

	m_pPlayer->Set_Active_Weapon(CPlayer::PW_TWINBLADE_L, false);
	m_pPlayer->Set_Active_Weapon(CPlayer::PW_TWINBLADE_R, false);

	m_pPlayer->Set_Active_WeaponCollider(CPlayer::PW_TWINBLADE_L, false);
	m_pPlayer->Set_Active_WeaponCollider(CPlayer::PW_TWINBLADE_R, false);
}

void CPlayerState_PW_TwinBlade::Init_AttackDesc()
{
	m_AttackDescs.reserve(7);

	ATTACKDESC AtkDesc = m_pPlayerStats->Get_PlagueAttackDesc();
	AtkDesc.iDamage = AtkDesc.iPlagueDamage;

	m_AttackDescs.emplace_back(CPlayer::PW_TWINBLADE_L, AtkDesc);
	m_AttackDescs.emplace_back(CPlayer::PW_TWINBLADE_R, AtkDesc);
	m_AttackDescs.emplace_back(CPlayer::PW_TWINBLADE_R, AtkDesc);
	m_AttackDescs.emplace_back(CPlayer::PW_TWINBLADE_L, AtkDesc);
	m_AttackDescs.emplace_back(CPlayer::PW_TWINBLADE_R, AtkDesc);
	m_AttackDescs.emplace_back(CPlayer::PW_TWINBLADE_L, AtkDesc);
	m_AttackDescs.emplace_back(CPlayer::PW_TWINBLADE_R, AtkDesc);

}



CPlayerState_PW_TwinBlade* CPlayerState_PW_TwinBlade::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, void* pArg)
{
	CPlayerState_PW_TwinBlade* pInstance = new CPlayerState_PW_TwinBlade(pDevice, pContext);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Created : CPlayerState_PW_TwinBlade"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPlayerState_PW_TwinBlade::Free()
{
	__super::Free();
}