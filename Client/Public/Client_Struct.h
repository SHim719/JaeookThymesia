#pragma once

#include "Engine_Defines.h"

namespace Engine
{
	class CBone;
	class CTransform;
}


namespace Client
{
	enum ENEMYATTACKTYPE
	{
		WEAK,
		NORMAL,
		SEMIKNOCKBACK,
		KNOCKBACK,
		KNOCKDOWN,
		BIG_HIT,
		VERY_BIG_HIT,
		ENEMYATTACKTYPE_END,
	};

	enum PLAYERATTACKTYPE
	{
		STEAL_TALENT,
		PLAYERATTACKTYPE_END,
	};

	typedef struct tagAttackDesc
	{
		class CCharacter*	pAttacker = nullptr;
		ENEMYATTACKTYPE		eEnemyAttackType;
		PLAYERATTACKTYPE	ePlayerAttackType;
		_int				iDamage = 0;
		_int				iPlagueDamage = 0;
	}ATTACKDESC;


	typedef struct tagEnemyDesc
	{
		wstring wstrEnemyName = L"";
		int		iMaxHp = 0;
	}ENEMYDESC;

	typedef struct tagAttachDesc
	{
		Engine::CBone* pAttachBone = nullptr;
		Engine::CTransform* pParentTransform = nullptr;
	}ATTACHDESC;


	typedef struct tagExecutedDesc
	{
		tagAttachDesc			AttachDesc;
		unsigned int			iExecutedAnimIndex = 0;
	}EXECUTEDDESC;

	typedef struct tagLoadObjectDesc
	{
		OBJTYPE		eObjType;
		_float4x4	WorldMatrix;
		_int		iNaviIdx;
		_int		iTriggerIdx;
		_float3		vColliderSize;
		_tchar		szModelTag[MAX_PATH];
	}LOADOBJDESC;

}
