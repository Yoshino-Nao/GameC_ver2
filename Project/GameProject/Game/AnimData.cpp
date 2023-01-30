#include "AnimData.h"
static TexAnim playerIdle[] = {
	{ 0,20 },
	{ 1,20 },
	{ 2,20 },
};
static TexAnim playerAtkIdle[] = {
	{ 28,20 },
	{ 29,20 },
	{ 30,20 },
};
static TexAnim playerRun[] = {
	{ 7,4 },
	{ 8,4 },
	{ 9,4 },
	{ 10,4 },
	{ 14,4 },
	{ 15,4 },
	{ 16,4 },
	{ 17,4 },
};
static TexAnim playerAtkRun[] = {
	{ 35,4 },
	{ 36,4 },
	{ 37,4 },
	{ 38,4 },
	{ 42,4 },
	{ 43,4 },
	{ 44,4 },
	{ 45,4 },
};
static TexAnim playerJumpUp[] = {
	{ 21,4 },
	{ 22,4 },
	{ 23,4 },
};
static TexAnim playerAtkJumpUp[] = {
	{ 49,4 },
	{ 50,4 },
	{ 51,4 },
};
static TexAnim playerJumpDown[] = {
	{ 24,4 },
	{ 25,4 },
	{ 26,4 },
	{ 27,4 },
	{ 26,4 },
	{ 27,4 },
	{ 26,4 },
	{ 27,4 },
	{ 26,4 },
	{ 27,4 },
};
static TexAnim playerAtkJumpDown[] = {
	{ 52,4 },
	{ 53,4 },
	{ 54,4 },
	{ 55,4 },
	{ 54,4 },
	{ 55,4 },
	{ 54,4 },
	{ 55,4 },
	{ 54,4 },
	{ 55,4 },
};
static TexAnim playerAttack01[] = {
	{ 40,3 },
	{ 41,3 },
	{ 42,3 },
	{ 43,2 },
	{ 44,2 },
	{ 45,3 },
	{ 46,4 },
};
static TexAnim playerAttack01End[] = {
	{ 48,4 },
	{ 49,4 },
	{ 50,4 },
	{ 51,4 },
	{ 52,4 },
};
static TexAnim playerAttack02[] = {
	{ 56,6 },
	{ 57,6 },
	{ 58,4 },
	{ 59,2 },
	{ 60,2 },
	{ 61,2 },
	{ 62,4 },
};
static TexAnim playerAttack02End[] = {
	{ 64,4 },
	{ 65,4 },
	{ 66,4 },
	{ 67,4 },
	{ 68,4 },
};
static TexAnim playerAttack03[] = {
	{ 72,6 },
	{ 73,6 },
	{ 74,4 },
	{ 75,4 },
	{ 76,3 },
	{ 77,2 },
	{ 78,2 },
	{ 79,4 },
};
static TexAnim playerAttack03End[] = {
	{ 80,4 },
	{ 81,4 },
	{ 82,4 },
	{ 83,4 },
};
static TexAnim playerDamage[] = {
	{ 3,6 },
	{ 4,6 },
};
static TexAnim playerDamageEnd[] = {
	{ 3,6 },
	{ 4,6 },
};
static TexAnim playerDeath[] = {
	{ 96,4 },
	{ 97,4 },
	{ 98,8 },
	{ 99,4 },
	{ 100,4 },
	{ 101,4 },
	{ 102,4 },
	{ 103,4 },
};
static TexAnim playerDown[] = {
	{ 104,4 },
	{ 105,4 },
	{ 106,4 },
	{ 107,4 },
	{ 108,4 },
};
static TexAnim playerDownGround[] = {
	{ 109,4 },
	{ 110,4 },
	{ 111,4 },
};
static TexAnim playerWakeup[] = {
	{ 112,4 },
	{ 113,4 },
	{ 114,4 },
	{ 115,4 },
	{ 116,4 },
	{ 117,4 },
	{ 118,4 },
};
static TexAnim playerGuard[] = {
	//	{ 120,4 },
	//	{ 121,4 },
	{ 122,4 },
};
static TexAnim playerGuardEnd[] = {
	{ 122,4 },
	{ 121,4 },
	{ 120,4 },
};
static TexAnim playerCrash[] = {
	{ 128,4 },
	{ 129,4 },
	{ 130,4 },
	{ 131,90 },
};
static TexAnim playerCrash01End[] = {
	{ 131,4 },
	{ 130,4 },
	{ 129,4 },
	{ 128,4 },
};
static TexAnim playerExtAttack01[] = {
	{ 144,4 },
	{ 145,4 },
	{ 146,12 },
	{ 147,2 },
	{ 148,2 },
	{ 149,2 },
	{ 150,16 },
};
static TexAnim playerExtAttack01End[] = {
	{ 151,4 },
	{ 152,4 },
};
static TexAnim playerExtAttack02[] = {
	{ 160,2 },
	{ 161,2 },
	{ 162,2 },
	{ 163,2 },
	{ 164,2 },
	{ 165,2 },
	{ 166,2 },
	{ 167,2 },
	{ 168,2 },
};
static TexAnim playerExtAttack02End[] = {
	{ 169,16 },
	{ 170,4 },
	{ 171,4 },
};
static TexAnim playerStep[] = {
	{ 120,4 },
	{ 121,4 },
	{ 122,4 },
};
TexAnimData player_anim_data[] = {
	ANIMDATA(playerIdle),
	ANIMDATA(playerAtkIdle),
	ANIMDATA(playerRun),
	ANIMDATA(playerAtkRun),
	ANIMDATA(playerJumpUp),
	ANIMDATA(playerAtkJumpUp),
	ANIMDATA(playerJumpDown),
	ANIMDATA(playerAtkJumpDown),
	ANIMDATA(playerAttack01),
	ANIMDATA(playerAttack01End),
	ANIMDATA(playerAttack02),
	ANIMDATA(playerAttack02End),
	ANIMDATA(playerAttack03),
	ANIMDATA(playerAttack03End),
	ANIMDATA(playerDamage),
	ANIMDATA(playerDamageEnd),
	ANIMDATA(playerDeath),
	ANIMDATA(playerDown),
	ANIMDATA(playerDownGround),
	ANIMDATA(playerWakeup),
	ANIMDATA(playerGuard),
	ANIMDATA(playerGuardEnd),
	ANIMDATA(playerCrash),
	ANIMDATA(playerCrash01End),
	ANIMDATA(playerExtAttack01),
	ANIMDATA(playerExtAttack01End),
	ANIMDATA(playerExtAttack02),
	ANIMDATA(playerExtAttack02End),
	ANIMDATA(playerStep),
};
static TexAnim uniIdle[] = {
	{ 49,20 },
	{ 50,20 },
	{ 51,20 },
	{ 52,20 },
};
static TexAnim uniWalk[] = {
	{ 0,8 },
	{ 1,8 },
	{ 2,8 },
	{ 3,8 },
	{ 4,8 },
	{ 5,8 },
	{ 6,4 },
	{ 7,4 },
	{ 8,4 },
	{ 9,4 },
	{ 10,8 },
	{ 11,8 },
	{ 12,8 },
	{ 13,8 },
};
static TexAnim uniRun[] = {
	{ 20,4 },
	{ 21,4 },
	{ 22,4 },
	{ 23,4 },
	{ 24,4 },
	{ 25,4 },
	{ 26,4 },
	{ 27,4 },
	{ 28,4 },
	{ 29,4 },
	{ 30,4 },
	{ 31,4 },
	{ 32,4 },
	{ 33,4 },
	{ 34,2 },
	{ 35,2 },
	{ 36,2 },
	{ 37,2 },
};
static TexAnim uniBrake[] = {
	{140,4 },
	{141,4 },
	{142,4 },
	{143,4 },
	{144,4 },
	{145,4 },
	{146,4 },
	{147,4 },
	{148,4 },
	{149,4 },
	{150,4 },
	{151,4 },
	{152,4 },
	{153,4 },
	{154,4 },
	{155,4 },
	{156,4 },
};
static TexAnim uniCrouch[] = {
	{ 15,4 },
	{ 16,4 },
	{ 17,4 },
	{ 18,4 },
	{ 19,4 },
};
static TexAnim uniJumpUp[] = {
	{ 40,4 },
	{ 41,4 },
	
};
static TexAnim uniJumpFall[] = {
	{ 42,4 },
	{ 43,4 },
	{ 44,4 },
	{ 45,4 },
	{ 46,4 },
	{ 45,4 },
	{ 46,4 },
	{ 45,4 },
	{ 46,4 },
};
static TexAnim uniLanding[] = {
	{ 47,2 },
	{ 47,2 },
};
static TexAnim uniDamage1[] = {
	{ 60,4 },
	{ 61,4 },
	{ 62,4 },
	{ 77,4 },
	{ 78,4 },
};
static TexAnim uniDamage2[] = {
	{ 60,4 },
	{ 61,4 },
	{ 62,4 },
	{ 63,4 },
	{ 64,4 },
	{ 65,4 },
	{ 77,4 },
	{ 78,4 },
};
static TexAnim uniDamage3[] = {
	{ 60,4 },
	{ 61,4 },
	{ 62,4 },
	{ 63,4 },
	{ 64,4 },
	{ 65,4 },
	{ 66,4 },
	{ 75,4 },
	{ 76,4 },
	{ 77,4 },
	{ 78,4 },
};
static TexAnim uniDead[] = {
	{ 60,4 },
	{ 61,4 },
	{ 62,4 },
	{ 63,4 },
	{ 64,4 },
	{ 65,4 },
	{ 66,4 },
	{ 67,4 },
	{ 68,4 },
	{ 69,4 },
	{ 70,4 },
};
static TexAnim uniSoard_Combo1[] = {
	{200,4 },
	{201,4 },
	{202,4 },
	{203,4 },
	{204,4 },
	{205,4 },
	{206,4 },
};
static TexAnim uniSoard_Combo2[] = {
	{207,4 },
	{208,4 },
	{209,4 },
	{210,4 },
	{211,4 },
	{212,4 },
	{213,4 },
	{214,4 },
};
static TexAnim uniSoard_Combo3[] = {
	{215,4 },
	{216,4 },
	{217,4 },
	{218,4 },
	{219,4 },
	{220,4 },
	{221,4 },
	{222,4 },
	{223,4 },
	{224,4 },
};
static TexAnim uniHundgunDraw[] = {
	{160,4 },
	{161,4 },
	{162,4 },
	{163,4 },
};
static TexAnim uniHundgunLow[] = {
	{165,4 },
	{166,4 },
	{167,4 },
	{168,4 },
	{169,4 },
};
static TexAnim uniHundgunMid[] = {
	{171,4 },
	{172,4 },
	{173,4 },
	{174,4 },
	{175,4 },
};
static TexAnim uniHundgunHigh[] = {
	{180,4 },
	{181,4 },
	{182,4 },
	{183,4 },
	{184,4 },
};
static TexAnim uniHundgunUp[] = {
	{186,4 },
	{187,4 },
	{188,4 },
	{189,4 },
	{190,4 },
};
static TexAnim uniHundgunSP[] = {
	{192,4},
	{193,4},
	{194,4},
	{195,4},
	{196,4},
	{197,4},
	{198,4},
	{199,4},
};
static TexAnim uniPoint_at[] = {
	{ 80,4 },
	{ 81,4 },
	{ 82,4 },
	{ 83,4 },
	{ 84,4 },
	{ 85,4 },
	{ 86,4 },
	{ 87,4 },
};
static TexAnim uniPositive[] = {
	{ 89,4 },
	{ 90,4 },
	{ 91,4 },
	{ 92,4 },
	{ 93,4 },
	{ 94,4 },
};
static TexAnim uniNegative[] = {
	{ 95,4 },
	{ 96,4 },
	{ 97,4 },
	{ 98,4 },
	{ 99,4 },
};
static TexAnim uniLook_around[] = {
	{100,4 },
	{101,4 },
	{102,4 },
	{103,4 },
	{104,4 },
	{105,4 },
	{106,4 },
	{107,4 },
	{108,4 },
	{109,4 },
};
static TexAnim uniWave_hand[] = {
	{111,4 },
	{112,4 },
	{113,4 },
	{114,4 },
	{115,4 },
};
static TexAnim uniWarming_up[] = {
	{120,4 },
	{121,4 },
	{122,4 },
	{123,4 },
	{124,4 },
	{125,4 },
	{126,4 },
	{127,4 },
	{128,4 },
	{129,4 },
	{130,4 },
	{131,4 },
	{132,4 },
	{133,4 },
	{134,4 },
	{135,4 },
};
TexAnimData uni_anim_data[] = {
	ANIMDATA(uniIdle),		  //0
	ANIMDATA(uniWalk),        //1
	ANIMDATA(uniRun),         //2
	ANIMDATA(uniBrake),       //3
	ANIMDATA(uniCrouch),      //4
	ANIMDATA(uniJumpUp),      //5
	ANIMDATA(uniJumpFall),    //6
	ANIMDATA(uniLanding),     //7
	ANIMDATA(uniDamage1),     //8
	ANIMDATA(uniDamage2),     //9
	ANIMDATA(uniDamage3),     //10
	ANIMDATA(uniDead),		  //11
	ANIMDATA(uniSoard_Combo1),//12
	ANIMDATA(uniSoard_Combo2),//13
	ANIMDATA(uniSoard_Combo3),//14
	ANIMDATA(uniHundgunDraw), //15
	ANIMDATA(uniHundgunLow),  //16
	ANIMDATA(uniHundgunMid),  //17
	ANIMDATA(uniHundgunHigh), //18
	ANIMDATA(uniHundgunUp),   //19
	ANIMDATA(uniHundgunSP),	  //20
	ANIMDATA(uniPoint_at),    //21
	ANIMDATA(uniPositive),    //22
	ANIMDATA(uniNegative),    //23
	ANIMDATA(uniLook_around), //24
	ANIMDATA(uniWave_hand),   //25
	ANIMDATA(uniWarming_up),  //26
};

static TexAnim enemy_Slime_move[] = {
	{ 0,8 },
	{ 1,8 },
	{ 2,8 },
	{ 3,8 },
};
static TexAnim enemy_Slime_attack[] = {
	{ 0,8 },
	{ 1,8 },
	{ 2,8 },
	{ 3,8 },
};
static TexAnim enemy_Slime_stand[] = {
	{ 0,8 },
	{ 1,8 },
	{ 2,8 },
	{ 3,8 },
};
static TexAnim enemy_Slime_damage[] = {
	{ 5,8 },
};
static TexAnim enemy_Slime_dead[] = {
	{ 4,8 },
};
TexAnimData enemy_anim_data[] = {
	ANIMDATA(enemy_Slime_move),
	ANIMDATA(enemy_Slime_attack),
	ANIMDATA(enemy_Slime_stand),
	ANIMDATA(enemy_Slime_damage),
	ANIMDATA(enemy_Slime_dead),
};
static TexAnim enemy_witch_move[] = {
	{ 0,8 },
	{ 1,8 },
	{ 2,8 },
	{ 3,8 },
	{ 4,8 },
	{ 5,8 },
};
static TexAnim enemy_witch_attack[] = {
	{ 6,8 },
	{ 7,8 },
	{ 8,8 },
	{ 9,8 },
};
static TexAnim enemy_witch_stand[] = {
	{ 12,8 },
	{ 13,8 },
	{ 14,8 },
	{ 15,8 },
};
TexAnimData enemy_witch_anim_data[] = {
	ANIMDATA(enemy_witch_move),
	ANIMDATA(enemy_witch_stand),
	ANIMDATA(enemy_witch_attack),
};
static TexAnim enemy_Dragon_move[] = {
	{ 10,8 },
	{ 11,8 },
	{ 12,8 },
	{ 13,8 },
	{ 14,8 },
	{ 15,8 },
};
static TexAnim enemy_Dragon_attack[] = {
	{ 0,8 },
	{ 1,8 },
	{ 2,8 },
	{ 3,8 },
	{ 4,8 },
};
static TexAnim enemy_Dragon_stand[] = {
	{ 5,8 },
	{ 6,8 },
	{ 7,8 },
	{ 8,8 },
};
TexAnimData enemy_Dragon_anim_data[] = {
	ANIMDATA(enemy_Dragon_move),
	ANIMDATA(enemy_Dragon_stand),
	ANIMDATA(enemy_Dragon_attack),
};

static TexAnim enemy_slo_move[] = {
	{ 0,8 } ,
	{ 1,8 },
	{ 2,8 },
	{ 3,8 },
	{ 4,8 },
	{ 5,8 },
};
static TexAnim enemy_slo_stand[] = {
	{ 10,8 },
	{ 11,8 },
	{ 12,8 },
	{ 13,8 },
	{ 14,8 },
	{ 15,8 },
	{ 16,8 },
	{ 17,8 },
	{ 18,8 },
	{ 19,8 },
	{ 20,8 },
	{ 21,8 },
	{ 22,8 },
};
static TexAnim enemy_slo_damage[] = {
	{ 30,4 },
	{ 31,4 },
	{ 32,4 },
	{ 33,4 },
};
static TexAnim enemy_slo_dead[] = {
	{ 30,4 },
	{ 31,4 },
	{ 32,4 },
	{ 33,4 },
	{ 34,4 },
	{ 35,4 },
	{ 36,4 },
	{ 37,4 },
	{ 38,4 },
	{ 39,4 },
	{ 40,4 },
	{ 41,4 },
	{ 42,4 },
	{ 43,4 },
	{ 44,4 },
	{ 45,4 },
};
TexAnimData enemy_slo_anim_data[] = {

	ANIMDATA(enemy_slo_stand),
	ANIMDATA(enemy_slo_move),
	ANIMDATA(enemy_slo_move),
	ANIMDATA(enemy_slo_damage),
	ANIMDATA(enemy_slo_dead),
};

static TexAnim _effect_blood[] = {
	{ 0,1 },
	{ 1,1 },
	{ 2,1 },
	{ 3,1 },
};
TexAnimData effect_blood_anim_data[] = {
	ANIMDATA(_effect_blood),
};
static TexAnim _effect_smoke[] = {
	{ 0,2 },
	{ 1,2 },
	{ 2,2 },
	{ 3,2 },
	{ 4,2 },
};
TexAnimData effect_smoke_anim_data[] = {
	ANIMDATA(_effect_smoke),
};

static TexAnim _effect_bomb[] = {
	{ 0,2 },
	{ 1,2 },
	{ 2,2 },
	{ 3,2 },
	{ 4,2 },
}; 
TexAnimData effect_bomb_anim_data[] = {
	ANIMDATA(_effect_smoke),
};
static TexAnim _effect_slash[] = {
	{ 0,2 },
	{ 1,2 },
	{ 2,2 },
	{ 3,2 },
	{ 4,2 },
};
TexAnimData effect_slash_anim_data[] = {
	ANIMDATA(_effect_slash),
};
static TexAnim _effect_flame[] = {
	{ 0,4 },
	{ 1,4 },
	{ 2,4 },
	{ 3,4 },
	{ 4,4 },
	{ 5,4 },
	{ 6,4 },
	{ 7,4 },
	{ 8,4 },
	{ 9,4 },
};
TexAnimData effect_flame_anim_data[] = {
	ANIMDATA(_effect_flame),
};
static TexAnim _effect_ring[] = {
	{ 0,1 },
	{ 1,1 },
	{ 2,1 },
	{ 3,1 },
	{ 4,1 },
	{ 5,1 },
	{ 6,1 },
	{ 7,1 },
	{ 8,1 },
	{ 9,1 },
	{ 10,1 },
	{ 11,1 },
	{ 12,1 },
	{ 13,1 },
	{ 14,1 },
	{ 15,1 },
	{ 16,1 },
	{ 17,1 },
	{ 18,1 },
	{ 19,1 },
	{ 20,1 },
	{ 21,1 },
	{ 22,1 },
	{ 23,1 },
	{ 24,1 },
	{ 25,1 },
	{ 26,1 },
	{ 27,1 },
	{ 28,1 },
	{ 29,1 },
};
TexAnimData effect_ring_anim_data[] = {
	ANIMDATA(_effect_ring),
};
static TexAnim _effect_coin[] = {
	{ 0,4 },
	{ 1,4 },
	{ 2,4 },
	{ 3,4 },
	{ 4,4 },
	{ 5,4 },
	{ 6,4 },
	{ 7,4 },
	{ 8,4 },
	{ 9,4 },
	{ 10,4 },
	{ 11,4 },
	{ 12,4 },
	{ 13,4 },
	{ 14,4 },
	{ 15,4 },
	{ 16,4 },
	{ 17,4 },
	{ 18,4 },
	{ 19,4 },
	{ 20,4 },
	
};
TexAnimData effect_coin_anim_data[] = {
	ANIMDATA(_effect_coin),
};