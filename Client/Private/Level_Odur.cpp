#include "Level_Odur.h"
#include "GameInstance.h"

#include "Main_Camera.h"
#include "Player.h"

#include "UI_Manager.h"

#include "FadeScreen.h"


CLevel_Odur::CLevel_Odur(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CClientLevel(pDevice, pContext)
{
}

HRESULT CLevel_Odur::Initialize()
{
	m_iLevelID = LEVEL_ODUR;

	SET_CURLEVEL(m_iLevelID);

	CPlayer* pPlayer = static_cast<CPlayer*>(m_pGameInstance->Find_GameObject(LEVEL_STATIC, L"Player"));
	pPlayer->Set_Active(true);
	pPlayer->Get_Transform()->Set_Position(XMVectorSet(38.193f, 0.887f, -5.502f, 1.f));
	pPlayer->Reset_NaviData(LEVEL_ODUR);
	pPlayer->Enroll_AllColliders();
	pPlayer->Set_Active_DefaultEffect(true);

	UIMGR->Active_UI("UI_PlayerDefault");

	CMain_Camera* pMainCamera = static_cast<CMain_Camera*>(m_pGameInstance->Get_MainCamera());
	pMainCamera->Set_Active(true);
	pMainCamera->Set_Player(pPlayer);

	if (FAILED(Load_Map(L"../../Resources/Maps/StageOdur/")))
		return E_FAIL;

	LIGHT_DESC			LightDesc{};
	LightDesc.eType = LIGHT_DESC::TYPE_DIRECTIONAL;
	LightDesc.vAmbient = _float4(0.6f, 0.6f, 0.6f, 1.f);
	LightDesc.vDiffuse = _float4(0.5f, 0.5f, 0.5f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.f, 1.f, 1.f);
	LightDesc.vDirection = _float4(1.f, -1.f, 0.f, 0.f);
	LightDesc.fLightStrength = 1.f;

	m_pGameInstance->Add_Clone(LEVEL_ODUR, L"Light", L"Prototype_LightObject", &LightDesc);

	
	return S_OK;
}

void CLevel_Odur::Tick(_float fTimeDelta)
{
	if (KEY_DOWN(eKeyCode::L))
	{
		CFadeScreen::FADEDESC FadeDesc{};
		FadeDesc.fFadeOutSpeed = 0.5f;
		FadeDesc.fFadeInSpeed = 10.f;
		FadeDesc.fExtraTime = 0.f;
		FadeDesc.pCallback_FadeOutEnd = bind(&CClientLevel::Ready_ChangeLevel, this, LEVEL_URD);
		UIMGR->Active_UI("FadeScreen", &FadeDesc);
	}
}

HRESULT CLevel_Odur::Render()
{
	return S_OK;
}

CLevel_Odur* CLevel_Odur::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CLevel_Odur* pInstance = new CLevel_Odur(pDevice, pContext);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX(TEXT("Failed to Created : CLevel_Odur"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_Odur::Free()
{
	__super::Free();
}
