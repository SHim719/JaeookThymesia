#include "VillagerFState_Attack1.h"

CVillagerFState_Attack1::CVillagerFState_Attack1(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CVillagerFState_Base(pDevice, pContext)
{
}

HRESULT CVillagerFState_Attack1::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

void CVillagerFState_Attack1::OnState_Start(void* pArg)
{
	Reset_AttackIdx();
	m_pVillager_F->Set_Stanced(true);
	m_pVillager_F->Set_LookTarget(true);
	m_pVillager_F->Update_AttackDesc();

	m_pModel->Change_Animation(LV1Villager_F_Attack01);
}

void CVillagerFState_Attack1::Update(_float fTimeDelta)
{
	if (!m_pVillager_F->Is_CollPlayer())
		m_pOwnerTransform->Move_Root(m_pModel->Get_DeltaRootPos(), m_pNavigation);
}

void CVillagerFState_Attack1::Late_Update(_float fTimeDelta)
{
	if (m_pModel->Is_AnimComplete())
		Decide_State();
}

void CVillagerFState_Attack1::OnState_End()
{

}

void CVillagerFState_Attack1::Init_AttackDesc()
{
	m_AttackDescs.reserve(1);

	ATTACKDESC AttackDesc;
	AttackDesc.iDamage = 40;
	AttackDesc.eEnemyAttackType = NORMAL;
	AttackDesc.pAttacker = m_pVillager_F;

	m_AttackDescs.emplace_back(CVillager_F::HAND, AttackDesc);
}

CVillagerFState_Attack1* CVillagerFState_Attack1::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, void* pArg)
{
	CVillagerFState_Attack1* pInstance = new CVillagerFState_Attack1(pDevice, pContext);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Created : CVillagerFState_Attack1"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVillagerFState_Attack1::Free()
{
	__super::Free();
}
