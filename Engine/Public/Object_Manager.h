#pragma once

#include "Base.h"

/* 1. ������ü���� �����Ѵ�. */
/* 2. ������ü�� ã�Ƽ� �����Ͽ� �纻��ü�� �����Ѵ�. */
/* 3. ������ ������ �纻��ü�� �����Ѵ�. */
/* 4. �����ϰ��ִ� ���̾���� Tick���� ȣ���Ѵ�. */
/* 5. �����ϰ��ִ� ���̾���� Render (x : �׸��� ������ �����ؾ� �� �ʿ䰡 �־. ) */

BEGIN(Engine)

class CObject_Manager final : public CBase
{
private:
	CObject_Manager();
	virtual ~CObject_Manager() = default;

public:
	HRESULT Initialize(_uint iNumLevels);
	void Clear(_uint iLevelIndex);
public:
	HRESULT Add_Prototype(const wstring& strPrototypeTag, class CGameObject* pPrototype);
	CGameObject* Add_Clone(_uint iLevelIndex, const wstring& strLayerTag, const wstring& strPrototypeTag, void* pArg);

	void Destroy_Objects();
	void PriorityTick(_float fTimeDelta);
	void Tick(_float fTimeDelta);
	void LateTick(_float fTimeDelta);

public:
	class CComponent* Find_Component(_uint iLevelIndex, const wstring& strLayerTag, const wstring& strComponentTag, _uint iIndex);
	class CGameObject* Find_GameObject(_uint iLevelIndex, const wstring& strLayerTag, _uint iIndex);
	class CLayer* Find_Layer(_uint iLevelIndex, const wstring& strLayerTag);

private:
	map<const wstring, class CGameObject*>			m_Prototypes;

private:
	_uint											m_iNumLevels = { 0 };
	map<const wstring, class CLayer*>*				m_pLayers = { nullptr };
	typedef map<const wstring, class CLayer*>		LAYERS;

private:
	class CGameObject* Find_Prototype(const wstring& strPrototypeTag);

public:
	static CObject_Manager* Create(_uint iNumLevels);
	virtual void Free() override;
};

END