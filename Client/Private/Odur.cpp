#include "Odur.h"
#include "Odur_States.h"

COdur::COdur(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CEnemy(pDevice, pContext)
{
}

COdur::COdur(const COdur& rhs)
	: CEnemy(rhs)
{
}

HRESULT COdur::Initialize_Prototype()
{
	return S_OK;
}

HRESULT COdur::Initialize(void* pArg)
{
	//Ready_States()
	//Ready_Weapons()

	if (FAILED(Ready_Components()))
		return E_FAIL;

	m_pModel->Change_Animation(Magician_Idle, 0.f);

	return S_OK;
}

void COdur::Tick(_float fTimeDelta)
{

	m_pModel->Play_Animation(fTimeDelta);
}

void COdur::LateTick(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderObject(CRenderer::RENDER_NONBLEND, this);
}

HRESULT COdur::Render()
{
	if (nullptr == m_pModel ||
		nullptr == m_pShader)
		return E_FAIL;

	if (FAILED(m_pShader->Set_RawValue("g_WorldMatrix", &m_pTransform->Get_WorldFloat4x4_TP(), sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_RawValue("g_ViewMatrix", &m_pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_RawValue("g_ProjMatrix", &m_pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	m_pModel->SetUp_BoneMatrices(m_pShader);

	_uint		iNumMeshes = m_pModel->Get_NumMeshes();

	for (_uint i = 0; i < iNumMeshes; ++i)
	{
		if (FAILED(m_pModel->SetUp_OnShader(m_pShader, i, TextureType_DIFFUSE, "g_DiffuseTexture")))
			return E_FAIL;
		/*if (FAILED(m_pModelCom->SetUp_OnShader(m_pShaderCom, m_pModel->Get_MaterialIndex(i), aiTextureType_NORMALS, "g_NormalTexture")))
			return E_FAIL;*/


		if (FAILED(m_pModel->Render(m_pShader, i)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT COdur::Ready_Components()
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 5.f;
	TransformDesc.fRotationPerSec = To_Radian(90.0f);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Transform"), TEXT("Transform"), (CComponent**)&m_pTransform, &TransformDesc)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Shader_VtxAnim"), TEXT("Shader"), (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(GET_CURLEVEL, TEXT("Prototype_Model_Odur"), TEXT("Model"), (CComponent**)&m_pModel)))
		return E_FAIL;

	return S_OK;
}

HRESULT COdur::Ready_States()
{
	return S_OK;
}

HRESULT COdur::Ready_Weapons()
{
	return S_OK;
}

COdur* COdur::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	COdur* pInstance = new COdur(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed To Created : COdur"));
		Safe_Release(pInstance);
	}

	return pInstance;

	
}

CGameObject* COdur::Clone(void* pArg)
{
	COdur* pInstance = new COdur(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : COdur"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void COdur::Free()
{
	__super::Free();

	Safe_Release(m_pModel);
	Safe_Release(m_pShader);

}