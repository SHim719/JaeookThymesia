#include "UI_SkillSlot.h"
#include "UI_SkillIcon.h"


CUI_SkillSlot::CUI_SkillSlot(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CUI(pDevice, pContext)
{
}

CUI_SkillSlot::CUI_SkillSlot(const CUI_SkillSlot& rhs)
	: CUI(rhs)
{
}
HRESULT CUI_SkillSlot::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Transform"), TEXT("Transform"), (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Texture_SkillSlot"), TEXT("Texture"), (CComponent**)&m_pUITexture)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Texture_Slot_Inactive"), TEXT("CoolDown_Texture"), (CComponent**)&m_pCoolDown_Texture)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_VIBuffer_Point"), TEXT("VIBuffer"), (CComponent**)&m_pVIBuffer)))
		return E_FAIL;

	m_pSkillIcon = static_cast<CUI_SkillIcon*>(m_pGameInstance->Clone_GameObject(L"Prototype_SkillIcon"));
	if (nullptr == m_pSkillIcon)
		return E_FAIL;

	m_pSkillIcon->Get_Transform()->Set_Position(Convert_ScreenToRenderPos(XMVectorSet(1120.f, 633.f, 1.f, 1.f)));

	m_pTransform->Set_Scale({ 72.f, 72.f, 1.f });
	m_pTransform->Set_Position(Convert_ScreenToRenderPos(XMVectorSet(1120.f, 633.f, 1.f, 1.f)));

	return S_OK;
}


void CUI_SkillSlot::Tick(_float fTimeDelta)
{

}

void CUI_SkillSlot::LateTick(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderObject(CRenderer::RENDER_UI, this);

}

HRESULT CUI_SkillSlot::Render()
{
	if (FAILED(m_pShader->Set_RawValue("g_WorldMatrix", &m_pTransform->Get_WorldFloat4x4_TP(), sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pUITexture->Set_SRV(m_pShader, "g_DiffuseTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pShader->Begin(0)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;

	if (FAILED(m_pSkillIcon->Render()))
		return E_FAIL;

	if (m_fCoolDownRatio < 1.f)
	{
		if (FAILED(Render_CoolDown()))
			return E_FAIL;
	}
	
	return S_OK;
}

HRESULT CUI_SkillSlot::Render_CoolDown()
{
	if (FAILED(m_pShader->Set_RawValue("g_WorldMatrix", &m_pTransform->Get_WorldFloat4x4_TP(), sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_RawValue("g_fCoolDownRatio", &m_fCoolDownRatio, sizeof(_float))))
		return E_FAIL;

	if (FAILED(m_pCoolDown_Texture->Set_SRV(m_pShader, "g_DiffuseTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pShader->Begin(5)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CUI_SkillSlot::OnEnter_Layer(void* pArg)
{
	if (FAILED(__super::OnEnter_Layer(pArg)))
		return E_FAIL;

	return S_OK;
}

void CUI_SkillSlot::Update_SkillIcon(const SKILLTYPE eSkillType)
{
	m_pSkillIcon->Change_Texture(eSkillType);
}

CUI_SkillSlot* CUI_SkillSlot::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CUI_SkillSlot* pInstance = new CUI_SkillSlot(pDevice, pContext);

	if (FAILED(pInstance->Initialize(nullptr)))
	{
		MSG_BOX(TEXT("Failed To Created : CUI_SkillSlot"));
		Safe_Release(pInstance);
	}

	return pInstance;
}


CGameObject* CUI_SkillSlot::Clone(void* pArg)
{
	CUI_SkillSlot* pInstance = new CUI_SkillSlot(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed To Cloned : CUI_SkillSlot"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_SkillSlot::Free()
{
	__super::Free();

	Safe_Release(m_pSkillIcon);
	Safe_Release(m_pCoolDown_Texture);
}
