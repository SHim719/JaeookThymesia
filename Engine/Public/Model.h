#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CModel final : public CComponent
{
public:
	enum TYPE { TYPE_NONANIM, TYPE_SKELETALMESH, TYPE_ANIM, TYPE_END };
	typedef vector<class CBone*>	BONES;
	typedef vector<class CMeshContainer*>	MESHES;

private:
	CModel(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CModel(const CModel& rhs);
	virtual ~CModel() = default;

public:
	class CBone* Get_Bone(const char* pNodeName);

	_uint Find_BoneIndex(const char* pBoneName);

	_uint Get_NumMeshes() const {
		return m_iNumMeshes;
	}

	_uint Get_MaterialIndex(_uint iMeshIndex);

	_matrix Get_PivotMatrix() {
		return XMLoadFloat4x4(&m_PivotMatrix);
	}


public:
	HRESULT Initialize_Prototype(const string& strModelFilePath, const string& strModelFileName);
	HRESULT Initialize(void* pArg, CModel* pModel);

public:
	HRESULT SetUp_BoneMatrices(class CShader* pShader);
	HRESULT SetUp_OnShader(class CShader* pShader, _uint iMaterialIndex, TextureType eTextureType, const char* pConstantName);
	HRESULT Render(class CShader* pShader, _uint iMeshIndex, _uint iPassIndex = 0);

	void Set_PivotMatrix(_fmatrix PivotMatrix);
private:
	_float4x4					m_PivotMatrix;
	TYPE						m_eModelType = TYPE_END;

private:
	_uint									m_iNumMeshes = 0;
	vector<class CMeshContainer*>			m_Meshes;

private:
	static map<const string, class CTexture*>	g_ModelTextures;
	_uint										m_iNumMaterials = 0;
	vector<MATERIALDESC>						m_Materials;

private:
	vector<class CBone*>					m_Bones;
	vector<_uint>							m_BoneIndices;
	_uint									m_iNumBones;
	_uint									m_iRootBoneIdx;
	_float4									m_vPrevRootPos = {};
	_float4									m_vDeltaRootPos = {};
public:
	const BONES& Get_Bones() { return m_Bones; }

	_vector Get_DeltaRootPos() const {
		return XMLoadFloat4(&m_vDeltaRootPos);
	}

	_vector Organize_RootPos(_vector OriginRootPos) {
		return XMVectorSet(OriginRootPos.m128_f32[0] * 0.001f, OriginRootPos.m128_f32[1] * 0.001f, -OriginRootPos.m128_f32[2] * 0.001f, 1.f);
	}

	void Reset_RootPos() {
		XMStoreFloat4(&m_vPrevRootPos, XMVectorZero());
	}

private:
	void Calc_DeltaRootPos();
private:
	_uint									m_iCurrentAnimIndex = 0;
	_uint									m_iNumAnimations = 0;
	vector<class CAnimation*>				m_Animations;

	_bool									m_bIsPlaying = false;
	_bool									m_bBlending = false;
public:
	const vector<CAnimation*>& Get_Animations() const { return m_Animations; }

	_uint	Get_NumAnimations() const { return m_iNumAnimations; }
	_uint	Get_CurrentAnimIndex() const { return m_iCurrentAnimIndex; }

	HRESULT		Play_Animation(_float fTimeDelta);
	void		Change_Animation(_uint iAnimIdx, _float fBlendingTime = 0.1f);
	_bool		Is_Playing() const { return m_bIsPlaying; }
	void		Set_AnimPlay() { m_bIsPlaying = true; }
	void		Set_AnimPause() { m_bIsPlaying = false; }

private:
	HRESULT Import_Model(const string& strFilePath, const string& strFileName);
	HRESULT Import_Meshes(ifstream& fin);
	HRESULT Import_MaterialInfo(ifstream& fin, const string& strFilePath);
	HRESULT Import_Bones(ifstream& fin);
	HRESULT Import_Animations(ifstream& fin);

public:
	static CModel* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const string& strModelFilePath, const string& strModelFileName);
	static void Release_Textures();
	virtual CComponent* Clone(void* pArg = nullptr);
	virtual void Free() override;
};

END



//private:
//	class CVTF* m_pVTF = nullptr;
//	void	Update_VTF(_uint iMeshIndex);
//HRESULT Bind_VTF(CShader* pShader, const char* pConstantName, _uint iMeshIndex);