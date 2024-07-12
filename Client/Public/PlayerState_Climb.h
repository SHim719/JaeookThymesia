#pragma once
#include "PlayerState_Base.h"

BEGIN(Client)
class CPlayerState_Climb final : public CPlayerState_Base
{
private:
	CPlayerState_Climb(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CPlayerState_Climb() = default;

	HRESULT Initialize(void* pArg)		override;
	void OnState_Start(void* pArg)		override;
	void Update(_float fTimeDelta)		override;
	void Late_Update(_float fTimeDelta)	override;
	void OnState_End()					override;

private:
	_int m_iDir = { 0 };

public:
	static CPlayerState_Climb* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, void* pArg);
	void Free() override;
};
END
