#pragma once

#include "Client_Defines.h"
#include "MyCamera.h"


BEGIN(Client)

class CMain_Camera final : public CCamera
{
public:
	enum CameraState
	{
		DEFAULT,
		LOCKON,
		CUTSCENE,
		UI,
		TARGET_END
	};

protected:
	CMain_Camera(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMain_Camera(const CMain_Camera& rhs, CTransform::TRANSFORMDESC* pArg);
	virtual ~CMain_Camera() = default;

public:
	HRESULT Initialize(void* pArg)			override;
	void OnActive()							override;
	void OnInActive()						override;
	void PriorityTick(_float fTimeDelta)	override;
	void Tick(_float fTimeDelta)			override;
	void LateTick(_float fTimeDelta)		override;

private:
	CameraState m_eState = DEFAULT;

	class CGameObject*	m_pTarget = nullptr;
	class CBone*		m_pCameraBone = nullptr;
	
	_float4				m_vOffset = { 0.f, 1.f, 2.5f, 0.f };
	_float4				m_vPlayerNeckOffset = { 0.f, 2.f, 0.f, 0.f };
	_float4				m_vPrevTargetPos = {};
	_float4				m_vCameraArmDist = {};

	_int				m_iSensitivity = 2;
	_float				m_fFollowingSpeed = 3.f;
public:
	void Init_TargetPos();
	void Set_Target(CGameObject* pTarget);


private:
	void Default_State(_float fTimeDelta);

	_vector Get_PlayerNeckPos() const { 
		return m_pTarget->Get_Transform()->Get_Position() + XMLoadFloat4(&m_vPlayerNeckOffset); }
	void Follow_Player(_float fTimeDelta);
	void Rotate_By_Mouse(_float fTimeDelta);
	void Rotate_CameraArm(_fvector vAxis, _float fDeltaTheta);

public:
	static CMain_Camera* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CGameObject* Clone(void* pArg) override;
	void Free()	override;
};

END

