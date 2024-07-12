#pragma once

#include "HalberdKnightState_Base.h"

BEGIN(Client)
class CHalberdKnightState_Idle : public CHalberdKnightState_Base
{
protected:
	CHalberdKnightState_Idle(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CHalberdKnightState_Idle() = default;

public:
	HRESULT Initialize(void* pArg)		override;
	void OnState_Start(void* pArg)		override;
	void Update(_float fTimeDelta)		override;
	void OnState_End()					override;

public:
	static CHalberdKnightState_Idle* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, void* pArg);
	void Free() override;
};

END

