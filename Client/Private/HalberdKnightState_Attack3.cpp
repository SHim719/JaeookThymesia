#include "HalberdKnightState_Attack3.h"

#include "Player.h"

CHalberdKnightState_Attack3::CHalberdKnightState_Attack3(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CHalberdKnightState_Base(pDevice, pContext)
{
}

HRESULT CHalberdKnightState_Attack3::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	Init_AttackDesc();

	return S_OK;
}

void CHalberdKnightState_Attack3::OnState_Start(void* pArg)
{
	Reset_AttackIdx();

	m_pHalberdKnight->Set_Stanced(true);
	m_pHalberdKnight->Set_LookTarget(true);
	m_pHalberdKnight->Update_AttackDesc();

	m_pModel->Change_Animation(HArmorLV1_Halberds_ComboC01);
}

void CHalberdKnightState_Attack3::Update(_float fTimeDelta)
{
	if (false == m_pHalberdKnight->Is_CollPlayer())
		m_pOwnerTransform->Move_Root(m_pModel->Get_DeltaRootPos(), m_pNavigation);
}

void CHalberdKnightState_Attack3::Late_Update(_float fTimeDelta)
{
	if (m_pModel->Is_AnimComplete())
		Decide_State();
}

void CHalberdKnightState_Attack3::OnState_End()
{

}

void CHalberdKnightState_Attack3::Init_AttackDesc()
{
	m_AttackDescs.reserve(1);

	ATTACKDESC AttackDesc;
	AttackDesc.iDamage = 40;
	AttackDesc.eEnemyAttackType = NORMAL;
	AttackDesc.pAttacker = m_pHalberdKnight;

	m_AttackDescs.emplace_back(CHalberdKnight::SPEAR, AttackDesc);

	AttackDesc.eEnemyAttackType = NORMAL;

	m_AttackDescs.emplace_back(CHalberdKnight::SPEAR, AttackDesc);

	AttackDesc.iDamage = 60;
	AttackDesc.eEnemyAttackType = BIG_HIT;

	m_AttackDescs.emplace_back(CHalberdKnight::SPEAR, AttackDesc);
}


CHalberdKnightState_Attack3* CHalberdKnightState_Attack3::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, void* pArg)
{
	CHalberdKnightState_Attack3* pInstance = new CHalberdKnightState_Attack3(pDevice, pContext);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Created : CHalberdKnightState_Attack3"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CHalberdKnightState_Attack3::Free()
{
	__super::Free();
}
