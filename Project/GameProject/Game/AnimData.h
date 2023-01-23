#pragma once
#include <GLLibrary.h>

//!アニメーションの種類
enum player_anim_data {
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
/*
enum uni_anim_data{
	uniIdle,	  //0
	uniWalk,        //1
	uniRun,         //2
	uniBrake,       //3
	uniCrouch,      //4
	uniJumpUp,      //5
	uniJumpFall,    //6
	uniLanding,     //7
	uniDamage1,     //8
	uniDamage2,     //9
	uniDamage3,     //10
	uniDead,		//11
	uniSoard_Combo1,//12
	uniSoard_Combo2,//13
	uniSoard_Combo3,//14
	uniHundgunDraw, //15
	uniHundgunLow,  //16
	uniHundgunMid,  //17
	uniHundgunHigh, //18
	uniHundgunUp,   //19
	uniHundgunSP,	//20
	uniPoint_at,    //21
	uniPositive,    //22
	uniNegative,    //23
	uniLook_around, //24
	uniWave_hand,   //25
	uniWarming_up,  //26
};
*/
extern TexAnimData uni_anim_data[];
//敵のアニメーションデータ
extern TexAnimData enemy_anim_data[];
extern TexAnimData enemy_witch_anim_data[];
extern TexAnimData enemy_Dragon_anim_data[];
extern TexAnimData enemy_slo_anim_data[];
//エフェクトのアニメーションデータ
extern TexAnimData effect_blood_anim_data[];
extern TexAnimData effect_smoke_anim_data[];
extern TexAnimData effect_slash_anim_data[];
extern TexAnimData effect_bomb_anim_data[]; 
extern TexAnimData effect_flame_anim_data[];
extern TexAnimData effect_ring_anim_data[];
extern TexAnimData effect_coin_anim_data[];