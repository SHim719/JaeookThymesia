#include "Effect_Manager.h"
#include "Effect_Group.h"
//#include "Effect_Mesh.h"
#include "Effect_Particle.h"

IMPLEMENT_SINGLETON(CEffect_Manager)

CEffect_Manager::CEffect_Manager()
	: m_pGameInstance(CGameInstance::Get_Instance())
{
}

CEffect_Manager::~CEffect_Manager()
{
	Release();
}

HRESULT CEffect_Manager::Initialize()
{
	if (FAILED(Init_Effects()))
		return E_FAIL;

	return S_OK;
}

void CEffect_Manager::Active_Effect(const string& strTag, void* pArg)
{
	auto it = m_EffectGroups.find(strTag);
	if (m_EffectGroups.end() == it)
		return;

	vector<CEffect_Group*>& EffectGroups = it->second;

	for (auto& pEffect_Group : EffectGroups)
	{
		if (false == pEffect_Group->Is_Using())
		{
			pEffect_Group->OnEnter_Layer(pArg);
			Safe_AddRef(pEffect_Group);

			m_pGameInstance->Insert_GameObject(GET_CURLEVEL, L"Effect", pEffect_Group);
			//ADD_EVENT(bind(&CGameInstance::Insert_GameObject, m_pGameInstance, GET_CURLEVEL, L"Effect", pEffect_Group));
			return;
		}
	}
}

HRESULT CEffect_Manager::Init_Effects()
{
	if (FAILED(Add_EffectGroups("Effect_Corvus_Parry_Success", 3, L"Prototype_Effect_Parry_Particle")))
		assert(false);

	if (FAILED(Add_EffectGroups("Effect_Corvus_Healing", 1, L"Prototype_Effect_HealingCurve")))
		assert(false);

	if (FAILED(Add_EffectGroups("Effect_Corvus_LAttack1", 1, L"Prototype_Effect_Corvus_LAttack1")))
		assert(false);

	if (FAILED(Add_EffectGroups("Effect_Corvus_LAttack2", 1, L"Prototype_Effect_Corvus_LAttack2")))
		assert(false);

	if (FAILED(Add_EffectGroups("Effect_Corvus_LAttack3", 1, L"Prototype_Effect_Corvus_LAttack3")))
		assert(false);

	if (FAILED(Add_EffectGroups("Effect_Corvus_LAttack4", 1, L"Prototype_Effect_Corvus_LAttack4")))
		assert(false);

	if (FAILED(Add_EffectGroups("Effect_Corvus_Claw_Long1", 1, L"Prototype_Effect_Claw_Long1")))
		assert(false);

	if (FAILED(Add_EffectGroups("Effect_Corvus_PW_Axe_Impact", 1, L"Prototype_Effect_Corvus_PW_Axe_Impact")))
		assert(false);

	if (FAILED(Add_EffectGroups("Effect_Corvus_PW_Axe_Slash", 1, L"Prototype_Effect_Corvus_PW_Axe_Slash")))
		assert(false);

	if (FAILED(Add_EffectGroups("Effect_Corvus_PW_Axe_StartParticle", 1, L"Prototype_Effect_Corvus_PW_Axe_StartParticle")))
		assert(false);

	if (FAILED(Add_EffectGroups("Effect_Corvus_PW_Spear_Start", 1, L"Prototype_Effect_Corvus_PW_Spear_Start")))
		assert(false);

	if (FAILED(Add_EffectGroups("Effect_Corvus_PW_Spear_Slash", 1, L"Prototype_Effect_Corvus_PW_Spear_Slash")))
		assert(false);

	if (FAILED(Add_EffectGroups("Effect_Corvus_PW_Spear_Particle", 1, L"Prototype_Effect_Corvus_PW_Spear_Particle")))
		assert(false);

	if (FAILED(Add_EffectGroups("Effect_Corvus_PW_Spear_Particle", 1, L"Prototype_Effect_Corvus_PW_Spear_Particle")))
		assert(false); 

	if (FAILED(Add_EffectGroups("Effect_Corvus_PW_TwinBlade_Start", 1, L"Prototype_Effect_Corvus_PW_TwinBlade_Start")))
		assert(false);

	if (FAILED(Add_EffectGroups("Effect_Corvus_PW_TwinBlade_Slash0", 1, L"Prototype_Effect_Corvus_PW_TwinBlade_Slash0")))
		assert(false);

	if (FAILED(Add_EffectGroups("Effect_Corvus_PW_TwinBlade_Slash1", 1, L"Prototype_Effect_Corvus_PW_TwinBlade_Slash1")))
		assert(false);

	if (FAILED(Add_EffectGroups("Effect_Corvus_PW_TwinBlade_Slash2", 1, L"Prototype_Effect_Corvus_PW_TwinBlade_Slash2")))
		assert(false);

	if (FAILED(Add_EffectGroups("Effect_Corvus_PW_TwinBlade_Slash3", 1, L"Prototype_Effect_Corvus_PW_TwinBlade_Slash3")))
		assert(false);

	if (FAILED(Add_EffectGroups("Effect_Corvus_PW_TwinBlade_Slash4", 1, L"Prototype_Effect_Corvus_PW_TwinBlade_Slash4")))
		assert(false);

	if (FAILED(Add_EffectGroups("Effect_Corvus_PW_TwinBlade_Slash_End", 1, L"Prototype_Effect_Corvus_PW_TwinBlade_Slash_End")))
		assert(false);
	return S_OK;
};

HRESULT CEffect_Manager::Add_EffectGroups(const string& strEffectGroupTags, _uint iNumGroups, const wstring& wstrPrototypeTag)
{
	vector<CEffect_Group*> vecGroups;
	vecGroups.reserve(iNumGroups);

	for (_uint i = 0; i < iNumGroups; ++i)
		vecGroups.emplace_back(static_cast<CEffect_Group*>(m_pGameInstance->Clone_GameObject(wstrPrototypeTag)));

	m_EffectGroups.emplace(strEffectGroupTags, vecGroups);

	return S_OK;
}

void CEffect_Manager::Release()
{
	for (auto& Pair : m_EffectGroups)
		for (auto& pEffect_Group : Pair.second)
			Safe_Release(pEffect_Group);
		

}