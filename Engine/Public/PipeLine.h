#pragma once

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CPipeLine final : public CBase
{
public:
	enum TRANSFORMSTATE { D3DTS_VIEW, D3DTS_PROJ, D3DTS_END };

private:
	CPipeLine();
	virtual ~CPipeLine() = default;

public:
	void Set_Transform(TRANSFORMSTATE eTransformState, _fmatrix TransformMatrix);

	_matrix Get_TransformMatrix(TRANSFORMSTATE eTransformState) const {
		return XMLoadFloat4x4(&m_TransformMatrix[eTransformState]);
	}

	_float4x4 Get_TransformFloat4x4(TRANSFORMSTATE eTransformState) const {
		return m_TransformMatrix[eTransformState];
	}

	_float4x4 Get_TransformFloat4x4_TP(TRANSFORMSTATE eTransformState) const {
		_float4x4	Transform;
		XMStoreFloat4x4(&Transform, XMMatrixTranspose(Get_TransformMatrix(eTransformState)));
		return Transform;
	}

	_matrix Get_TransformMatrixInverse(TRANSFORMSTATE eTransformState) const {
		return XMLoadFloat4x4(&m_TransformInverseMatrix[eTransformState]);
	}

	_float4x4 Get_TransformFloat4x4_Inverse_TP(TRANSFORMSTATE eTransformState) const {
		_float4x4	Transform;
		XMStoreFloat4x4(&Transform, XMMatrixTranspose(Get_TransformMatrixInverse(eTransformState)));
		return Transform;
	}

	const _float4& Get_CamPosition() const {
		return m_vCamPosition;
	}

public:
	void Update();

private:
	_float4x4				m_TransformMatrix[D3DTS_END];
	_float4x4				m_TransformInverseMatrix[D3DTS_END];
	_float4					m_vCamPosition;

public:
	static CPipeLine* Create();
	virtual void Free() override;
};

END