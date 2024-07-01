#include "OdurState_ThrowCard.h"

#include "Odur_Card.h"

#include "Bone.h"


COdurState_ThrowCard::COdurState_ThrowCard(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: COdurState_Base(pDevice, pContext)
{
}

HRESULT COdurState_ThrowCard::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_AnimPlaylists[0] = { Magician_ShootCombo1_1, Magician_ShootCombo1_2 };
	m_AnimPlaylists[1] = { Magician_Shoot_2_V1, Magician_Shoot3, Magician_Shoot2, Magician_Shoot1 };

	m_Cards.resize(20);
	for (size_t i = 0; i < m_Cards.size(); ++i)
		m_Cards[i] = static_cast<COdur_Card*>(m_pGameInstance->Clone_GameObject(L"Prototype_Odur_Card"));

	m_pLeftHandBone = m_pModel->Get_Bone("hand_l");
	Safe_AddRef(m_pLeftHandBone);

	m_pModel->Bind_Func("Throw_Card", bind(&COdurState_ThrowCard::Throw_SingleCard, this));
	m_pModel->Bind_Func("Throw_MultipleCard", bind(&COdurState_ThrowCard::Throw_MultipleCards, this));
	m_pModel->Bind_Func("Odur_ChangeToNextCardAnim", bind(&COdurState_ThrowCard::Change_To_NextAnim, this));
		
	return S_OK;
}

void COdurState_ThrowCard::OnState_Start(void* pArg)
{
	m_pOdur->Set_LookTarget(true);
	m_pOdur->Set_Stanced(true);

	m_iCurAnimIdx = 0;

	m_iThrowState = m_iThrowCount == (m_iMaxThrowCount - 1) ? 1 : 0;
	m_iThrowCount = (m_iThrowCount + 1) % m_iMaxThrowCount;

	m_fTimeAcc = m_fThrowingGap;

	m_pModel->Change_Animation(m_AnimPlaylists[m_iThrowState][m_iCurAnimIdx++]);
}

void COdurState_ThrowCard::Update(_float fTimeDelta)
{
	if (m_pModel->Is_AnimComplete())
	{
		Change_To_NextAnim();
		return;
	}


	if (m_bThrowMultipleCard)
	{
		m_fTimeAcc += fTimeDelta;
		if (m_fTimeAcc >= m_fThrowingGap)
		{
			m_fTimeAcc = 0.f;

			Throw_Card(JoMath::Calc_GroundLook(m_pTargetTransform->Get_Position(), m_pOwnerTransform->Get_Position()));

			++m_iNumCurrentThrowingCard;
			if (m_iNumCurrentThrowingCard >= m_iNumThrowCard)
			{
				m_iNumCurrentThrowingCard = 0;
				m_bThrowMultipleCard = false;
			}
		}	
	}

}

void COdurState_ThrowCard::OnState_End()
{
}

void COdurState_ThrowCard::Init_AttackDesc()
{
	m_CardAttackDescs[0].reserve(1);
	m_CardAttackDescs[1].reserve(2);

	ATTACKDESC AttDesc;
	AttDesc.eEnemyAttackType = WEAK;
	m_CardAttackDescs[0].emplace_back(AttDesc);

	m_CardAttackDescs[1].emplace_back(AttDesc);
	
	AttDesc.eEnemyAttackType = VERY_BIG_HIT;

	m_CardAttackDescs[1].emplace_back(AttDesc);

}


_vector COdurState_ThrowCard::Calc_LeftHandPos()
{
	_matrix BoneMatrix = m_pLeftHandBone->Get_CombinedTransformation() * m_pOwnerTransform->Get_WorldMatrix();

	return BoneMatrix.r[3];
}

void COdurState_ThrowCard::Throw_Card(_vector vLook)
{
	_vector vLeftHandPos = Calc_LeftHandPos();

	_matrix ParamMatrix;
	ParamMatrix.r[2] = vLook;
	ParamMatrix.r[3] = vLeftHandPos;

	_float4x4 ParamMatrix4x4;
	XMStoreFloat4x4(&ParamMatrix4x4, ParamMatrix);

	m_Cards[m_iCurCardIdx]->OnEnter_Layer(&ParamMatrix4x4);

	ADD_EVENT(bind(&CGameInstance::Insert_GameObject, m_pGameInstance, GET_CURLEVEL, L"Enemy_Weapon", m_Cards[m_iCurCardIdx]));

	m_iCurCardIdx = (m_iCurCardIdx + 1) % m_Cards.size();
}

void COdurState_ThrowCard::Throw_SingleCard()
{
	Throw_Card(JoMath::Calc_GroundLook(m_pTargetTransform->Get_Position(), m_pOwnerTransform->Get_Position()));
}

void COdurState_ThrowCard::Throw_MultipleCards()
{
	m_bThrowMultipleCard = true;
}

void COdurState_ThrowCard::Change_To_NextAnim()
{
	if (m_AnimPlaylists[m_iThrowState].size() == m_iCurAnimIdx)
	{
		if (0 == m_iThrowState)
			Decide_State();
		else
			m_pOdur->Change_State((_uint)OdurState::State_ExecutionDisappear);
	}
	else
	{
		m_pModel->Change_Animation(m_AnimPlaylists[m_iThrowState][m_iCurAnimIdx++]);
	}
}

COdurState_ThrowCard* COdurState_ThrowCard::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, void* pArg)
{
	COdurState_ThrowCard* pInstance = new COdurState_ThrowCard(pDevice, pContext);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Created : COdurState_ThrowCard"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void COdurState_ThrowCard::Free()
{
	__super::Free();

	Safe_Release(m_pLeftHandBone);

	for (auto& pCard : m_Cards)
		Safe_Release(pCard);
	
	m_Cards.clear();
}