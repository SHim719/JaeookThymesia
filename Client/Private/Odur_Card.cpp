#include "Odur_Card.h"

COdur_Card::COdur_Card(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CWeapon(pDevice, pContext)
{
}

COdur_Card::COdur_Card(const COdur_Card& rhs)
	: CWeapon(rhs)
{
}

HRESULT COdur_Card::Initialize_Prototype()
{
	m_iTag = TAG_ENEMY_WEAPON;

	return S_OK;
}

HRESULT COdur_Card::Initialize(void* pArg)
{
	if (FAILED(Ready_Component()))
		return E_FAIL;

	return S_OK;
}

HRESULT COdur_Card::OnEnter_Layer(void* pArg)
{
	if (FAILED(__super::OnEnter_Layer(pArg)))
		return E_FAIL;

	_matrix ParamMatrix = XMLoadFloat4x4((_float4x4*)pArg);

	m_pTransform->LookTo(ParamMatrix.r[2]);
	m_pTransform->Add_RollInput(To_Radian(-90.f));

	m_pTransform->Set_MoveLook(ParamMatrix.r[2]);

	m_pTransform->Set_Position(ParamMatrix.r[3]);
	return S_OK;
}

void COdur_Card::Tick(_float fTimeDelta)
{
	m_fTimeAcc += fTimeDelta;
	if (m_fTimeAcc >= m_fLifeSpan)
	{
		m_fTimeAcc = 0.f;
		m_bReturnToPool = true;
	}

	m_pTransform->Go_Dir(m_pTransform->Get_MoveLook(), fTimeDelta);
}

void COdur_Card::LateTick(_float fTimeDelta)
{
	m_pCollider->Update(m_pTransform->Get_WorldMatrix());

	m_pGameInstance->Add_RenderObject(CRenderer::RENDER_NONBLEND, this);
}

HRESULT COdur_Card::Render()
{
	if (nullptr == m_pModel ||
		nullptr == m_pShader)
	{
		return E_FAIL;
	}

	if (FAILED(m_pShader->Set_RawValue("g_WorldMatrix", &m_pTransform->Get_WorldFloat4x4_TP(), sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_RawValue("g_ViewMatrix", &m_pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_RawValue("g_ProjMatrix", &m_pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	_uint		iNumMeshes = m_pModel->Get_NumMeshes();

	for (_uint i = 0; i < iNumMeshes; ++i)
	{
		if (FAILED(m_pModel->SetUp_OnShader(m_pShader, i, TextureType_DIFFUSE, "g_DiffuseTexture")))
			return E_FAIL;
		/*if (FAILED(m_pModelCom->SetUp_OnShader(m_pShaderCom, m_pModel->Get_MaterialIndex(i), aiTextureType_NORMALS, "g_NormalTexture")))
			return E_FAIL;*/

		if (FAILED(m_pModel->Render(m_pShader, i, 0)))
			return E_FAIL;
	}

	if (m_pCollider)
		m_pCollider->Render();

	return S_OK;
}

void COdur_Card::OnCollisionEnter(CGameObject* pOther)
{
	m_bReturnToPool = true;
	// ��ƼŬ
}

HRESULT COdur_Card::Ready_Component()
{
	CTransform::TRANSFORMDESC TransformDesc;
	TransformDesc.fSpeedPerSec = 50.f;

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Transform"), TEXT("Transform"), (CComponent**)&m_pTransform, &TransformDesc)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Shader_VtxModel"), TEXT("Shader"), (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(GET_CURLEVEL, TEXT("Prototype_Model_Odur_Card"), TEXT("Model"), (CComponent**)&m_pModel)))
		return E_FAIL;

	CCollider::COLLIDERDESC ColliderDesc;
	ColliderDesc.eType = CCollider::SPHERE;
	ColliderDesc.pOwner = this;
	ColliderDesc.vCenter = { 0.f, 0.f, 0.f };
	ColliderDesc.vSize = { 0.3f, 0.f, 0.f };
	ColliderDesc.vRotation = { 0.f, 0.f, 0.f };
	ColliderDesc.strCollisionLayer = "Enemy_Weapon";
	ColliderDesc.bActive = true;

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Sphere"), TEXT("Collider"), (CComponent**)&m_pCollider, &ColliderDesc)))
		return E_FAIL;
	

	return S_OK;
}

COdur_Card* COdur_Card::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	COdur_Card* pInstance = new COdur_Card(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : COdur_Card"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* COdur_Card::Clone(void* pArg)
{
	COdur_Card* pInstance = new COdur_Card(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : COdur_Card"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void COdur_Card::Free()
{
	__super::Free();

	Safe_Release(m_pShader);
	Safe_Release(m_pModel);
	Safe_Release(m_pCollider);
}