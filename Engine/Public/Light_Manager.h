#pragma once

#include "Base.h"

BEGIN(Engine)

class CLight_Manager final : public CBase
{
private:
	CLight_Manager();
	virtual ~CLight_Manager() = default;

public:
	const LIGHT_DESC* Get_LightDesc(_uint iIndex) const;

public:
	HRESULT Initialize();
	HRESULT Add_Light(class CLight* pLight);
	HRESULT Render(class CShader* pShader, class CVIBuffer* pVIBuffer);

	void Clear_Lights();

private:
	list<class CLight*>			m_Lights;

public:
	static CLight_Manager* Create();
	void Free() override;

};

END