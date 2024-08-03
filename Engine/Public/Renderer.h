#pragma once

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CRenderer final : public CBase
{
public:
	enum RENDERGROUP { RENDER_PRIORITY, RENDER_NONBLEND, RENDER_NONLIGHT, RENDER_BLEND
		, RENDER_EFFECT_NONBLEND, RENDER_EFFECT_BLEND, RENDER_GLOW, RENDER_UI, RENDER_END };
private:
	CRenderer(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CRenderer() = default;

private:
	ID3D11Device*			m_pDevice = { nullptr };
	ID3D11DeviceContext*	m_pContext = { nullptr };

	class CGameInstance*	m_pGameInstance = { nullptr };

	class CVIBuffer_Rect*	m_pVIBuffer_Rect = { nullptr };
	class CVIBuffer_Screen*	m_pVIBuffer = { nullptr };

	/* 렌더타겟 디버깅용 패스 (0), 빛연산을 위한 패스 (1) */
	class CShader*			m_pDeferredShader = { nullptr };
	class CShader*			m_pGlowShader = { nullptr };
	class CShader*			m_pBloomShader = { nullptr };
	class CShader*			m_pPostProcessShader = { nullptr };

private:
	/* m_WorldMatrix : 화면을 꽉 채우는 직교투영이 빈번히 활용되기때문에 저장해둘꺼야 .*/
	_float4x4					m_WorldMatrix{};

public:
	HRESULT Initialize();
	HRESULT Add_RenderObject(RENDERGROUP eRenderGroup, class CGameObject* pRenderObject);	
	HRESULT Add_RenderComponent(class CComponent* pRenderComponent);
	void	Add_UsingShader(class CShader* pShader);
	void	Tick(_float fTimeDelta);
	HRESULT Draw();
	void	Clear();

private:
	void Draw_Objects(_uint iGroup);
	void Bind_ViewProj();

	HRESULT Copy_RenderTarget(const wstring& wstrTargetTag);

	HRESULT Render_NonBlend();
	HRESULT Render_NonLight();
	HRESULT Render_LightAcc();
	HRESULT Render_Deferred();

	HRESULT Render_Effect();

	HRESULT Render_Glow();

	HRESULT Render_SampleForBloom();
	HRESULT Render_BrightPass();
	HRESULT Render_DownSample();
	HRESULT Render_UpSample();
	
	HRESULT Render_PostProcess();
	HRESULT PostProcess_Bloom();
	HRESULT Render_RadialBlur();

	HRESULT Render_Final();

	HRESULT Render_Blend();
	HRESULT Render_UI();
	HRESULT Render_Components();

private:
	HRESULT Ready_DefaultTargets(_uint iWidth, _uint iHeight);
	HRESULT Ready_LightTargets(_uint iWidth, _uint iHeight);
	HRESULT Ready_DeferredTarget(_uint iWidth, _uint iHeight);
	HRESULT Ready_EffectTargets(_uint iWidth, _uint iHeight);
	HRESULT Ready_GlowTargets(_uint iWidth, _uint iHeight);
	HRESULT Ready_BloomTargets(_uint iWidth, _uint iHeight);

#ifdef _DEBUG
private:
	HRESULT Ready_Debug();
	HRESULT Render_Debug();
	_bool m_bRenderRTV = { true };
#endif

private:
	list<class CGameObject*>			m_RenderObjects[RENDER_END];
	list<class CComponent*>				m_RenderComponents;
	list<class CShader*>				m_UsingShaders;

	class CVIBuffer*					m_pVIBuffer_UI = { nullptr };

	D3D11_VIEWPORT						m_OriginViewPort = {};

private:
	_uint				m_iBloomLevel = { 3 };
	
private:
	_bool				m_bRadialBlur = { false };
	RADIALBLUR_DESCS	m_tRadialBlurDescs = {};

	_float				m_fRadialBlurLerpTime = { 0.f };
	_float				m_fRadialBlurLerpTimeAcc = { 0.f };
	_float				m_fNowBlurStrength = { 0.f };
	_float3				m_vBlurCenterWorld = {};

private:
	void Update_RadialBlur(_float fTimeDelta);
	_float2 Calc_BlurCenterUV();

public:
	void Active_RadialBlur(const RADIALBLUR_DESCS& Descs) {
		m_bRadialBlur = true;
		m_tRadialBlurDescs = Descs;
		m_fNowBlurStrength = Descs.fBlurStrength;
		m_fRadialBlurLerpTimeAcc = 0.f;
	}

	void Inactive_RadialBlur(_float fLerpTime) {
		if (m_fRadialBlurLerpTimeAcc > 0.f)
			return;
		m_fRadialBlurLerpTime = m_fRadialBlurLerpTimeAcc = fLerpTime;
	}

	void Update_BlurCenterWorld(_vector vBlurCenterWorld) {
		XMStoreFloat3(&m_vBlurCenterWorld, vBlurCenterWorld);
	}

	_bool Is_Active_RadialBlur() const {
		return m_bRadialBlur;
	}

private:
	HRESULT Ready_Buffers();
	HRESULT Ready_Shaders();
	HRESULT Bind_Matrices();

public:
	static CRenderer* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual void Free() override;
};

END