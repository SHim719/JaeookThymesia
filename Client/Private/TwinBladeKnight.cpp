#include "TwinBladeKnight.h"
#include "TwinBladeKnight_States.h"
#include "Weapon.h"
#include "Bone.h"
#include "PerceptionBounding.h"

#include "UI_Manager.h"
#include "UI_EnemyBar.h"

CTwinBladeKnight::CTwinBladeKnight(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CEnemy(pDevice, pContext)
{
}

CTwinBladeKnight::CTwinBladeKnight(const CTwinBladeKnight& rhs)
	: CEnemy(rhs)
{
}

HRESULT CTwinBladeKnight::Initialize_Prototype()
{
	m_iTag = (_uint)TAG_ENEMY;
	m_eExecutionTag = TWINBLADEKNIGHT;
	m_eSkillType = SKILLTYPE::TWINBLADE;
	return S_OK;
}

HRESULT CTwinBladeKnight::Initialize(void* pArg)
{
	if (nullptr == pArg)
		return E_FAIL;

	if (FAILED(Ready_Components(pArg)))
		return E_FAIL;

	if (FAILED(Ready_States()))
		return E_FAIL;

	if (FAILED(Ready_Weapon()))
		return E_FAIL;

	if (FAILED(Ready_Stats()))
		return E_FAIL;

	if (FAILED(Ready_UI()))
		return E_FAIL;

	Bind_KeyFrames();

	m_pGameInstance->Add_Clone(GET_CURLEVEL, L"PerceptionBounding", L"Prototype_PerceptionBounding", this);

	m_bLookTarget = false;
	m_bStanced = true;

	Change_State((_uint)TwinBladeKnight_State::State_Idle);
	m_pModel->Set_AnimPlay();

	return S_OK;
}

void CTwinBladeKnight::Tick(_float fTimeDelta)
{
	if (KEY_DOWN(eKeyCode::K))
	{
		Change_State((_uint)TwinBladeKnight_State::State_Stunned_Start);
	}

	if (m_bLookTarget)
	{
		m_pTransform->Rotation_Quaternion(
			JoMath::Slerp_TargetLook(m_pTransform->Get_GroundLook()
				, JoMath::Calc_GroundLook(s_pTarget->Get_Transform()->Get_Position(), m_pTransform->Get_Position())
				, m_fRotRate * fTimeDelta));
	}

	m_States[m_iState]->Update(fTimeDelta);

	if (m_bAdjustNaviY)
		Compute_YPos();

	__super::Update_Colliders();

	__super::Tick_Weapons(fTimeDelta);

	m_pModel->Play_Animation(fTimeDelta);
}

void CTwinBladeKnight::LateTick(_float fTimeDelta)
{
	m_States[m_iState]->Late_Update(fTimeDelta);

	__super::LateTick_Weapons(fTimeDelta);

	if (m_bNoRender)
		return;

#ifdef _DEBUG
	m_pGameInstance->Add_RenderComponent(m_pCollider);
	m_pGameInstance->Add_RenderComponent(m_pHitBoxCollider);
#endif

	m_pGameInstance->Add_RenderObject(CRenderer::RENDER_NONBLEND, this);
}

HRESULT CTwinBladeKnight::Render()
{
	if (FAILED(m_pShader->Set_RawValue("g_WorldMatrix", &m_pTransform->Get_WorldFloat4x4_TP(), sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pModel->SetUp_BoneMatrices(m_pShader)))
		return E_FAIL;


	_uint		iNumMeshes = m_pModel->Get_NumMeshes();

	for (_uint i = 0; i < iNumMeshes; ++i)
	{
		if (FAILED(m_pModel->SetUp_OnShader(m_pShader, i, TextureType_DIFFUSE, "g_DiffuseTexture")))
			return E_FAIL;
		/*if (FAILED(m_pModelCom->SetUp_OnShader(m_pShaderCom, m_pModel->Get_MaterialIndex(i), aiTextureType_NORMALS, "g_NormalTexture")))
			return E_FAIL;*/

		if (FAILED(m_pModel->Bind_Buffers(i)))
			return E_FAIL;

		if (FAILED(m_pModel->Render(m_pShader, i, 0)))
			return E_FAIL;
	}

	return S_OK;
}


void CTwinBladeKnight::Bind_KeyFrames()
{
	m_pModel->Bind_Func("Active_WeaponCollider_L", bind(&CWeapon::Set_Active_Collider, m_Weapons[BLADE_L], true));
	m_pModel->Bind_Func("Inactive_WeaponCollider_L", bind(&CWeapon::Set_Active_Collider, m_Weapons[BLADE_L], false));
	m_pModel->Bind_Func("Active_WeaponCollider_R", bind(&CWeapon::Set_Active_Collider, m_Weapons[BLADE_R], true));
	m_pModel->Bind_Func("Inactive_WeaponCollider_R", bind(&CWeapon::Set_Active_Collider, m_Weapons[BLADE_R], false));
	m_pModel->Bind_Func("Active_Weapons", bind(&CTwinBladeKnight::Active_Weapons, this));
	m_pModel->Bind_Func("Enable_LookTarget", bind(&CEnemy::Set_LookTarget, this, true));
	m_pModel->Bind_Func("Disable_LookTarget", bind(&CEnemy::Set_LookTarget, this, false));
	m_pModel->Bind_Func("Enable_Stanced", bind(&CCharacter::Set_Stanced, this, true));
	m_pModel->Bind_Func("Disable_Stanced", bind(&CCharacter::Set_Stanced, this, false));
	m_pModel->Bind_Func("Update_AttackDesc", bind(&CCharacter::Update_AttackDesc, this));
	m_pModel->Bind_Func("ChangeToNextAttackAnim", bind(&CTwinBladeKnight::Change_To_NextComboAnim, this));
}


void CTwinBladeKnight::SetState_Executed(void* pArg)
{
	Change_State((_uint)TwinBladeKnight_State::State_Executed_Start, pArg);
}

void CTwinBladeKnight::SetState_Death()
{
	Change_State((_uint)TwinBladeKnight_State::State_Death);
}

void CTwinBladeKnight::Percept_Target()
{
	m_pModel->Change_Animation(LArmor_TwinSwords_IdleN2Fight);
	m_bLookTarget = true;
	
}

void CTwinBladeKnight::Change_To_NextComboAnim()
{
	static_cast<CTwinBladeKnightState_Base*>(m_States[m_iState])->Change_To_NextComboAnim();
}

void CTwinBladeKnight::Active_Weapons()
{
	m_Weapons[BLADE_L]->Set_Active(true);
	m_Weapons[BLADE_R]->Set_Active(true);
}

HRESULT CTwinBladeKnight::Ready_Components(void* pArg)
{
	LOADOBJDESC* pLoadDesc = (LOADOBJDESC*)pArg;

	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 2.f;
	TransformDesc.fRotationPerSec = To_Radian(90.0f);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Transform"), TEXT("Transform"), (CComponent**)&m_pTransform, &TransformDesc)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Shader_VtxAnim"), TEXT("Shader"), (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(GET_CURLEVEL, TEXT("Prototype_Model_TwinBladeKnight"), TEXT("Model"), (CComponent**)&m_pModel)))
		return E_FAIL;

	CCollider::COLLIDERDESC Desc;
	Desc.eType = CCollider::SPHERE;
	Desc.pOwner = this;
	Desc.vCenter = { 0.f, 1.3f, 0.f };
	Desc.vSize = { 1.f, 0.f, 0.f };
	Desc.vRotation = { 0.f, 0.f, 0.f };
	Desc.strCollisionLayer = "Enemy";
	Desc.bActive = true;

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Sphere"), TEXT("Collider"), (CComponent**)&m_pCollider, &Desc)))
		return E_FAIL;

	Desc.eType = CCollider::SPHERE;
	Desc.pOwner = this;
	Desc.vCenter = { 0.f, 1.3f, 0.f };
	Desc.vSize = { 1.5f, 0.f, 0.0f };
	Desc.vRotation = { 0.f, 0.f, 0.f };
	Desc.strCollisionLayer = "Enemy_HitBox";
	Desc.bActive = true;

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Sphere"), TEXT("HitBox"), (CComponent**)&m_pHitBoxCollider, &Desc)))
		return E_FAIL;

	CNavigation::NAVIGATION_DESC NaviDesc;
	NaviDesc.iCurrentCellIndex = pLoadDesc->iNaviIdx;

	if (FAILED(__super::Add_Component(GET_CURLEVEL, TEXT("Prototype_Navigation"), TEXT("Navigation"), (CComponent**)&m_pNavigation, &NaviDesc)))
		return E_FAIL;

	m_pTransform->Set_WorldMatrix(XMLoadFloat4x4(&pLoadDesc->WorldMatrix));

	return S_OK;
}

HRESULT CTwinBladeKnight::Ready_States()
{
	m_States.resize((_uint)TwinBladeKnight_State::State_End);

	m_States[(_uint)TwinBladeKnight_State::State_Idle] = CTwinBladeKnightState_Idle::Create(m_pDevice, m_pContext, this);
	m_States[(_uint)TwinBladeKnight_State::State_Walk] = CTwinBladeKnightState_Walk::Create(m_pDevice, m_pContext, this);
	m_States[(_uint)TwinBladeKnight_State::State_Hit] = CTwinBladeKnightState_Hit::Create(m_pDevice, m_pContext, this);
	m_States[(_uint)TwinBladeKnight_State::State_ComboA] = CTwinBladeKnightState_ComboA::Create(m_pDevice, m_pContext, this);
	m_States[(_uint)TwinBladeKnight_State::State_ComboB] = CTwinBladeKnightState_ComboB::Create(m_pDevice, m_pContext, this);
	m_States[(_uint)TwinBladeKnight_State::State_ComboC] = CTwinBladeKnightState_ComboC::Create(m_pDevice, m_pContext, this);
	m_States[(_uint)TwinBladeKnight_State::State_ParryAttack] = CTwinBladeKnightState_ParryAttack::Create(m_pDevice, m_pContext, this);
	m_States[(_uint)TwinBladeKnight_State::State_Dodge] = CTwinBladeKnightState_Dodge::Create(m_pDevice, m_pContext, this);
	m_States[(_uint)TwinBladeKnight_State::State_Stunned_Start] = CTwinBladeKnightState_Stunned_Start::Create(m_pDevice, m_pContext, this);
	m_States[(_uint)TwinBladeKnight_State::State_Stunned_Loop] = CTwinBladeKnightState_Stunned_Loop::Create(m_pDevice, m_pContext, this);
	m_States[(_uint)TwinBladeKnight_State::State_Executed_Start] = CTwinBladeKnightState_Executed_Start::Create(m_pDevice, m_pContext, this);
	m_States[(_uint)TwinBladeKnight_State::State_Death] = CTwinBladeKnightState_Executed_End::Create(m_pDevice, m_pContext, this);

	return S_OK;
}

HRESULT CTwinBladeKnight::Ready_Weapon()
{
	m_Weapons.resize(WEAPON_END);

	CCollider::COLLIDERDESC ColliderDesc = {};
	ColliderDesc.eType = CCollider::SPHERE;
	ColliderDesc.pOwner = this;
	ColliderDesc.vCenter = { 0.7f, 0.f, 0.f };
	ColliderDesc.vSize = { 1.f, 0.f, 0.f };
	ColliderDesc.vRotation = { 0.f, 0.f, 0.f };
	ColliderDesc.bActive = false;
	ColliderDesc.strCollisionLayer = "Enemy_Weapon";

	CWeapon::WEAPONDESC WeaponDesc;
	WeaponDesc.iTag = (_uint)TAG_ENEMY_WEAPON;
	WeaponDesc.iLevelID = GET_CURLEVEL;
	WeaponDesc.pParentTransform = m_pTransform;
	WeaponDesc.pSocketBone = m_pModel->Get_Bone("weapon_l");
	WeaponDesc.wstrModelTag = L"Prototype_Model_Sword";
	WeaponDesc.pOwner = this;
	WeaponDesc.pColliderDesc = &ColliderDesc;

	m_Weapons[BLADE_L] = static_cast<CWeapon*>(m_pGameInstance->Clone_GameObject(L"Prototype_Weapon", &WeaponDesc));
	if (nullptr == m_Weapons[BLADE_L])
		return E_FAIL;
	
	WeaponDesc.pSocketBone = m_pModel->Get_Bone("weapon_r");

	m_Weapons[BLADE_R] = static_cast<CWeapon*>(m_pGameInstance->Clone_GameObject(L"Prototype_Weapon", &WeaponDesc));
	if (nullptr == m_Weapons[BLADE_R])
		return E_FAIL;

	m_Weapons[BLADE_L]->Set_Active(false);
	m_Weapons[BLADE_R]->Set_Active(false);

	return S_OK;
}

HRESULT CTwinBladeKnight::Ready_Stats()
{
	ENEMYDESC EnemyDesc;
	EnemyDesc.wstrEnemyName = L"��Į��";
	EnemyDesc.iMaxHp = 500;

	m_pStats = CEnemyStats::Create(EnemyDesc);

	return S_OK;
}

HRESULT CTwinBladeKnight::Ready_UI()
{
	CUI_EnemyBar::UIENEMYBARDESC EnemyBarDesc;
	EnemyBarDesc.pStats = m_pStats;
	EnemyBarDesc.vOffset.y = 2.5f;
	EnemyBarDesc.pOwnerTransform = m_pTransform;

	UIMGR->Active_UI("UI_EnemyBar", &EnemyBarDesc);

	return S_OK;
}


CTwinBladeKnight* CTwinBladeKnight::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CTwinBladeKnight* pInstance = new CTwinBladeKnight(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : CTwinBladeKnight"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CTwinBladeKnight::Clone(void* pArg)
{
	CTwinBladeKnight* pInstance = new CTwinBladeKnight(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CTwinBladeKnight"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTwinBladeKnight::Free()
{
	__super::Free();
}