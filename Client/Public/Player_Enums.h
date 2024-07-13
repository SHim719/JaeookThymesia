#pragma once

enum PlayerAnimName
{
	Corvus_ArchiveGetup,
	Corvus_ArchiveLight_up,
	Corvus_ArchiveSitLoop,
	Corvus_ArchiveSitStart,
	Corvus_Healing_Big,
	Corvus_Healing_Little,
	Corvus_Healing2_InPlace,
	Corvus_Lobby_FirstWakeUp,
	Corvus_PW_Axe,
	Corvus_PW_Axe_B_V1,
	Corvus_PW_Bat_Roar_A,
	Corvus_PW_Bat_Roar_B,
	Corvus_PW_BigHand_B_End,
	Corvus_PW_BigHand_B_Loop,
	Corvus_PW_BigHand_B_Start,
	Corvus_PW_BigHand_End,
	Corvus_PW_BigHand_Start,
	Corvus_PW_Bloodwhip,
	Corvus_PW_Bloodwhip_End,
	Corvus_PW_Bloodwhip_Jump,
	Corvus_PW_Bloodwhip_Loop,
	Corvus_PW_BloodwhipPull,
	Corvus_PW_Bow_B,
	Corvus_PW_Bow_End,
	Corvus_PW_Bow_Start,
	Corvus_PW_CaneSword_Fast,
	Corvus_PW_CaneSword_SP01,
	Corvus_PW_CaneSword_SP02,
	Corvus_PW_Darts_A_B_V1,
	Corvus_PW_Darts_A_F_V1,
	Corvus_PW_Darts_A_L_V1,
	Corvus_PW_Darts_A_R_V1,
	Corvus_PW_Darts_A_V1,
	Corvus_PW_Darts_B_01,
	Corvus_PW_Darts_B_02,
	Corvus_PW_Darts_B_03,
	Corvus_PW_Darts_B_04,
	Corvus_PW_Darts_B_Start,
	Corvus_PW_DualKnife,
	Corvus_PW_DualKnife_B,
	Corvus_PW_DualKnife_B_Suc,
	Corvus_PW_GiantMaggot_A_V1,
	Corvus_PW_GreatSword,
	Corvus_PW_GreatSword_B,
	Corvus_PW_GreatSwordStep,
	Corvus_PW_Halberds,
	Corvus_PW_Halberds_B,
	Corvus_PW_Hammer_A,
	Corvus_PW_Hammer_B_Ver2,
	Corvus_PW_Knife_A_V1,
	Corvus_PW_Magician_A,
	Corvus_PW_MagicianLV2,
	Corvus_PW_Puppet_V1_A,
	Corvus_PW_Puppet_V1_A_End,
	Corvus_PW_Puppet_V1_B,
	Corvus_PW_Puppet_V1_Start,
	Corvus_PW_Researcher,
	Corvus_PW_Researcher_B,
	Corvus_PW_Scythe,
	Corvus_PW_Scythe_B,
	Corvus_PW_Shield,
	Corvus_PW_Shield_B,
	Corvus_PW_Shield_B_Suc,
	Corvus_PW_ShieldBlock,
	Corvus_PW_Slide_B,
	Corvus_PW_Slide_L,
	Corvus_PW_Slide_R,
	Corvus_PW_TwinSwords_1,
	Corvus_PW_TwinSwords_2,
	Corvus_PW_TwinSwords_3,
	Corvus_PW_TwinSwords_4,
	Corvus_PW_TwinSwords_B,
	Corvus_PW_UrdSword_B_End_Ver2,
	Corvus_PW_UrdSword_B_Loop_Ver2,
	Corvus_PW_UrdSword_B_Start_Ver2,
	Corvus_PW_UrdSword01,
	Corvus_PW_VargSword_A,
	Corvus_PW_VargSword_B,
	Corvus_PW_VargSword_Start,
	Corvus_QuicklyRecoverUP_B,
	Corvus_QuicklyRecoverUP_F,
	Corvus_QuicklyRecoverUP_L,
	Corvus_QuicklyRecoverUP_R,
	Corvus_Raven_ClawCommon_ChargeLoop,
	Corvus_Raven_ClawCommon_ChargeStep,
	Corvus_Raven_ClawCommonV2_ChargeStart,
	Corvus_Raven_ClawLong_ChargeFull,
	Corvus_Raven_ClawLong_L01,
	Corvus_Raven_ClawLong_L02,
	Corvus_Raven_ClawLong_PlunderAttack1,
	Corvus_Raven_ClawLong_PlunderAttack2TTT,
	Corvus_Raven_ClawNear,
	Corvus_Raven_ClawParry_End,
	Corvus_Raven_ClawShort_ChargeFull,
	Corvus_Raven_ClawShort_PlunderAttack1,
	Corvus_Raven_ClawShort_PlunderAttack2TT,
	Corvus_Raven_ClawShortV2_Fast01,
	Corvus_Raven_ClawShortV2_Fast02,
	Corvus_Raven_ClawShortV2_Fast03,
	Corvus_Raven_ClawShortV2_Fast031,
	Corvus_Raven_FeatherRoundAttack,
	Corvus_Raven_FeatherRoundJump,
	Corvus_Raven_FeatherRush,
	Corvus_Raven_FeatherRushAI,
	Corvus_Raven_Idle,
	Corvus_Raven_WingsParry,
	Corvus_RavenAttack_End,
	Corvus_RavenAttack_Loop,
	Corvus_RavenAttack_Near,
	Corvus_RavenAttack_Start,
	Corvus_RavenJumpBack,
	Corvus_RavenJumpBack_Start,
	Corvus_RootFix_BMedium,
	Corvus_RootFix_BSmall,
	Corvus_SD_AvoidAttack_D,
	Corvus_SD_AvoidAttack_E2,
	Corvus_SD_AvoidAttack_E3,
	Corvus_SD_AvoidF,
	Corvus_SD_AvoidLongB_NEW,
	Corvus_SD_AvoidLongF,
	Corvus_SD_AvoidLongL_NEW,
	Corvus_SD_AvoidLongR_NEW,
	Corvus_SD_AvoidShort_B_NEW,
	Corvus_SD_AvoidShort_F,
	Corvus_SD_AvoidShort_L,
	Corvus_SD_AvoidShort_R,
	Corvus_SD_AvoidShortMag_B,
	Corvus_SD_AvoidShortMag_F,
	Corvus_SD_AvoidShortMag_L,
	Corvus_SD_AvoidShortMag_R,
	Corvus_SD_Bounce,
	Corvus_SD_Dead_1,
	Corvus_SD_Defense_Hurt,
	Corvus_SD_Defense_Hurt_Large,
	Corvus_SD_Defense_Loop,
	Corvus_SD_Fall_End,
	Corvus_SD_Fall_Loop,
	Corvus_SD_Fall_Start,
	Corvus_SD_GetUp,
	Corvus_SD_Headache1_End,
	Corvus_SD_Headache1_Loop,
	Corvus_SD_Headache1_Start,
	Corvus_SD_Headache2_Loop,
	Corvus_SD_Headache2_Start,
	Corvus_SD_HurtBlown,
	Corvus_SD_HurtFallDown,
	Corvus_SD_HurtFallDown_End,
	Corvus_SD_HurtKnockDown,
	Corvus_SD_HurtLF,
	Corvus_SD_HurtMFL,
	Corvus_SD_HurtMFR,
	Corvus_SD_HurtSF_1,
	Corvus_SD_HurtSL,
	Corvus_SD_HurtSR,
	Corvus_SD_HurtXLF,
	Corvus_SD_HurtXXLF,
	Corvus_SD_Idle,
	Corvus_SD_KnockBackF,
	Corvus_SD_Ladder_Climb_L_Down,
	Corvus_SD_Ladder_Climb_L_Down_End,
	Corvus_SD_Ladder_Climb_L_UP,
	Corvus_SD_Ladder_Climb_L_UP_End,
	Corvus_SD_Ladder_Climb_R_Down,
	Corvus_SD_Ladder_Climb_R_Down_End,
	Corvus_SD_Ladder_Climb_R_UP,
	Corvus_SD_Ladder_Climb_R_UP_End,
	Corvus_SD_Ladder_Climb_Start,
	Corvus_SD_Ladder_L_Idle,
	Corvus_SD_Ladder_R_Idle,
	Corvus_SD_LAttack1,
	Corvus_SD_LAttack2,
	Corvus_SD_LAttack3_New,
	Corvus_SD_LAttack4,
	Corvus_SD_LAttack5,
	Corvus_SD_M01_SneakAttack_End,
	Corvus_SD_M01_SneakAttack_Suc,
	Corvus_SD_ParryDefance,
	Corvus_SD_ParryDeflect_L,
	Corvus_SD_ParryDeflect_LUp,
	Corvus_SD_ParryDeflect_LUP_AI,
	Corvus_SD_ParryDeflect_R,
	Corvus_SD_ParryDeflect_RUp,
	Corvus_SD_ParryDeflect_RUp_AI,
	Corvus_SD_Rebound_L,
	Corvus_SD_Rebound_R,
	Corvus_SD_RootFixJokerRunAttack1,
	Corvus_SD_RunB,
	Corvus_SD_RunBL,
	Corvus_SD_RunBR,
	Corvus_SD_RunF_24,
	Corvus_SD_RunFL,
	Corvus_SD_RunFR,
	Corvus_SD_RunL,
	Corvus_SD_RunR,
	Corvus_SD_SprintAttack_1,
	Corvus_SD_TD2Thorw2,
	Corvus_SD_TD2Thorw2_Slow,
	Corvus_SD_VSVarg_Execution,
	Corvus_SD_VSVarg_Execution_Blending,
	Corvus_SD_Walk_Poison_Pose,
	Corvus_SD_WalkB,
	Corvus_SD_WalkB_LEnd,
	Corvus_SD_WalkB_REnd,
	Corvus_SD_WalkB_Start,
	Corvus_SD_WalkBL,
	Corvus_SD_WalkBR,
	Corvus_SD_WalkF,
	Corvus_SD_WalkF_LEnd,
	Corvus_SD_WalkF_REnd,
	Corvus_SD_WalkF_Start,
	Corvus_SD_WalkFL,
	Corvus_SD_WalkFR,
	Corvus_SD_WalkIdle,
	Corvus_SD_WalkL,
	Corvus_SD_WalkL_LEnd,
	Corvus_SD_WalkL_REnd,
	Corvus_SD_WalkL_Start,
	Corvus_SD_WalkR,
	Corvus_SD_WalkR_LEnd,
	Corvus_SD_WalkR_REnd,
	Corvus_SD_WalkR_Start,
	Corvus_SD_WeakGetUp_F,
	Corvus_SD1_Fall_Attack,
	Corvus_SD1_ParryL_NEW,
	Corvus_SD1_ParryR_NEW,
	Corvus_SD1_Sprint,
	Corvus_SD1_Sprint_Start,
	Corvus_SD2Raven,
	Corvus_Seq_BossFightStart_Sit,
	Corvus_Seq_BossFightStart_Stand,
	Corvus_StunExecute_StartL_L,
	Corvus_StunExecute_StartL_R,
	Corvus_StunExecute_StartR_L,
	Corvus_StunExecute_StartR_R,
	Corvus_StunExecute_StartRDown_L,
	Corvus_StunExecute_StartRDown_R,
	Corvus_StunnedEnd,
	Corvus_StunnedLoop,
	Corvus_StunnedStart,
	Corvus_Suicide,
	Corvus_VS_Armor_Execution_01,
	Corvus_VS_Armor_Execution_02,
	Corvus_VS_Blood01_Execution,
	Corvus_VS_Blood01_RaidAttack1Hurt,
	Corvus_VS_GiantMaggotExecution_Attack03_L,
	Corvus_VS_GiantMaggotExecution_Attack03_R,
	Corvus_VS_GiantMaggotExecution_End,
	Corvus_VS_GiantMaggotExecutionL,
	Corvus_VS_GiantMaggotExecutionR,
	Corvus_VS_LArmorLV2_Execution,
	Corvus_VS_LightExecute01L,
	Corvus_VS_LightExecute01R,
	Corvus_VS_MagicianLV1_Seq_BossFightStart,
	Corvus_VS_MagicianLV2_Execution_V1,
	Corvus_VS_MagicianLV2_SPAttack1_Hurt,
	Corvus_VS_Puppet_Execution_Attack,
	Corvus_VS_Puppet_Execution_End,
	Corvus_VS_Puppet_Execution_Start,
	Corvus_VS_Researcher01_Execution,
	Corvus_VS_Researcher01_Execution_NCamera,
	Corvus_VS_Researcher01_SP01Hurt,
	Corvus_VSBossBat_Execution01,
	Corvus_VSGiantMaggot_SP1Hurt,
	Corvus_VSGrace_Execution,
	Corvus_VSHArmorLV1_Execution,
	Corvus_VSHArmorLV1_Execution_NCamera,
	Corvus_VSJoker_Execution,
	Corvus_VSLV1Villager_M_Execution,
	Corvus_VSLV2Villager01_M_Execution,
	Corvus_VSMagician_Execution,
	Corvus_VSMagician_SP1Hurt,
	Corvus_VSMagician_SP2Hurt,
	Corvus_VSSelf_ExecuteL_V1,
	Corvus_VSSelf_ExecuteS,
	Corvus_VSSelf_TakeExecuteL,
	Corvus_VSSelf_TakeExecuteS_V1,
	Corvus_VSUrd_Execution,
	Corvus_VSVarg_TakeSPAttack,
	Corvus_VSVarg_TakeSPAttackSeq1,
	Corvus_WalkN,
	O_Corvus_SD1_SprintF,
	O_Corvus_SD1_SprintF1,
	Corvus_SD_Ladder_Descend,
};

enum class PlayerState
{
	State_Idle,
	State_Jog,
	State_Sprint,
	State_Avoid,
	State_Attack,
	State_LockOn,
	State_Parry,
	State_ParrySuccess,
	State_Hit,
	State_Parried,
	State_ChargeStart,
	State_ChargeComplete,
	State_ChargeLoop,
	State_ClawAttack_Long,
	State_ClawAttack_Short,
	State_ClawAttack_ShortEnd,
	State_PlunderRush,
	State_Plunder,
	State_PlagueAttack,
	State_PW_Axe,
	State_PW_Hammer,
	State_Climb_Start,
	State_Climb_Idle,
	State_Climb,
	State_Climb_End,
	State_Execution_Default,
	State_Execution_Elite,
	State_Executed,
	State_Cutscene,
	State_End,
};