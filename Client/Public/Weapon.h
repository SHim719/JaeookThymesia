#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CModel;
class CShader;
class CCollider;
class CBone;
END

BEGIN(Client)

class CWeapon : public CGameObject
{
public:
	typedef struct tagWeaponDesc
	{
		_uint						iTag = 0;
		_uint						iLevelID = 0;
		CBone*						pSocketBone = nullptr;
		CTransform*					pParentTransform = nullptr;
		wstring						wstrModelTag = L"";
		_bool						bAlphaBlend = false;
		CGameObject*				pOwner = nullptr;
		CCollider::COLLIDERDESC*	pColliderDesc = nullptr;
	} WEAPONDESC;

protected:
	CWeapon(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CWeapon(const CWeapon& rhs);
	virtual ~CWeapon() = default;

public:
	HRESULT Initialize_Prototype()		override;
	HRESULT Initialize(void* pArg)		override;
	void Tick(_float fTimeDelta)		override;
	void LateTick(_float fTimeDelta)	override;
	HRESULT Render()					override;

protected:
	CGameObject*	m_pOwner = { nullptr };
	CBone*			m_pSocketBone = { nullptr };
	CTransform*		m_pParentTransform = { nullptr };

public:
	void Swap_SocketBone(CBone*& pBone) {
		swap(m_pSocketBone, pBone);
	}

	CGameObject* Get_Owner() const {
		return m_pOwner;
	}

protected:
	ATTACKDESC		m_AttackDesc;

public:
	void Set_AttackDesc(const ATTACKDESC& Desc) {
		m_AttackDesc = Desc;
	}

	const ATTACKDESC& Get_AttackDesc() const {
		return m_AttackDesc;
	}

protected:
	_bool			m_bAlphaBlend = { false };
	_float			m_fAlpha = { 1.f };

	
public:
	void Set_Alpha(_float fAlpha) { m_fAlpha = fAlpha; }


protected:
	CShader*	m_pShader = nullptr;
	CModel*		m_pModel = nullptr;
	CCollider*	m_pCollider = nullptr;


public:
	void Set_Active_Collider(_bool bActive) {
		if (m_pCollider)
			m_pCollider->Set_Active(bActive);
	}
	void Enroll_Collider() {
		if (m_pCollider)
			m_pCollider->Enroll_Collider();
	}

protected:
	HRESULT Ready_Components(WEAPONDESC* pDesc);

public:
	static CWeapon* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END