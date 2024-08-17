#pragma once

#include "Client_Defines.h"
#include "GameEffect.h"

BEGIN(Client)
class CToolEffect_Mesh final : public CGameEffect
{
private:
	CToolEffect_Mesh(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CToolEffect_Mesh(const CToolEffect_Mesh& rhs);
	virtual ~CToolEffect_Mesh() = default;

private:
	HRESULT Initialize_Prototype(const wstring& wstrFilePath);
	HRESULT Initialize(void* pArg)		override;
	void Tick(_float fTimeDelta)		override;
	void LateTick(_float fTimeDelta)	override;
	HRESULT Render()					override;

	HRESULT Save_EffectData(ofstream& fout)	override;
	HRESULT Load_EffectData(ifstream& fin)	override;

private:
	void Restart_Effect(EFFECTSPAWNDESC* pDesc = nullptr)	override;
	void OnEnd_Effect()	override;

	_bool Update_SpawnTime(_float fTimeDelta);
	void Update_Position();
	void Update_Rotation(_float fTimeDelta);
	void Update_Scale();
	void Update_Color();
	void Update_UV(_float fTimeDelta);
	void Update_LifeTime(_float fTimeDelta);
	void Update_FinalMatrix();

private:
	void Update_ClipRange(_float fTimeDelta);

private:
	MESHEFFECT_INFO		m_tMeshEffectInfo{};
	OLDMESHEFFECT_INFO  m_tOldMeshEffectInfo{};

	_float2				m_vMaskUVOffset = { 0.f, 0.f };
	_float2				m_vNoiseUVOffset = { 0.f, 0.f };

	_float4x4			m_FinalMatrix = {};
	_float				m_fSpawnTimeAcc = 0.f;

	_float				m_fClipRange = { 0.f };
private:
	CTransform*			m_pLocalTransform = { nullptr };
	CModel*				m_pModel = { nullptr };

private:
	HRESULT Ready_Components();
	HRESULT Bind_GlobalVariables()	override;
	HRESULT Bind_ShaderResources()	override;

public:
	static CToolEffect_Mesh* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	static CToolEffect_Mesh* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const wstring& wstrFilePath);
	CGameObject* Clone(void* pArg)	override;
	void Free() override;


	friend class CAnim_Tool;
};

END

