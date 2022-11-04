#pragma once
#include <GLLibrary.h>

//!アニメーションの種類
enum  {
	eAnimIdle = 0,
	eAnimAtkIdle,
	eAnimRun,
	eAnimAtkRun,
	eAnimJumpUp,
	eAnimAtkJumpUp,
	eAnimJumpDown,
	eAnimAtkJumpDown,
	eAnimAttack01,
	eAnimAttack01End,
	eAnimAttack02,
	eAnimAttack02End,
	eAnimAttack03,
	eAnimAttack03End,
	eAnimDamage,
	eAnimDamageEnd,
	eAnimDeath,
	eAnimDown,
	eAnimDownGround,
	eAnimWakeUp,
	eAnimGuard,
	eAnimGuardEnd,
	eAnimCrash,
	eAnimCrashEnd,
	eAnimExtAttack01,
	eAnimExtAttack01End,
	eAnimExtAttack02,
	eAnimExtAttack02End,
	eAnimStep,
};

//プレイヤーのアニメーションデータ
extern TexAnimData player_anim_data[];
//敵のアニメーションデータ
extern TexAnimData enemy_anim_data[];
extern TexAnimData enemy_witch_anim_data[];
extern TexAnimData enemy_Dragon_anim_data[];
//エフェクトのアニメーションデータ
extern TexAnimData effect_blood_anim_data[];
extern TexAnimData effect_smoke_anim_data[];
extern TexAnimData effect_slash_anim_data[];
extern TexAnimData effect_bomb_anim_data[]; 
extern TexAnimData effect_flame_anim_data[];
extern TexAnimData effect_ring_anim_data[];
extern TexAnimData effect_coin_anim_data[];