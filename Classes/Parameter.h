#ifndef __PARAMETER_H__
#define __PARAMETER_H__

//thời gian
#define TIME_CREATE_ZOMBIE_2					8.0f
#define TIME_CREATE_ZOMBIE_3					6.0f
#define TIME_CREATE_ZOMBIE_4					3.5f
#define TIME_CREATE_ZOMBIE_5					4.0f
#define TIME_CREATE_ZOMBIE_6					4.5f
#define TIME_CREATE_ZOMBIE_7					5.0f

#define TIME_ACTION_ANIMATION					6.0f
#define TIME_MOVETO_ZOMBIE						15.0f
#define TIME_MOVETO_ZOMBIE_SKILL				20.0f

//scale
#define ZOMBIE_SIZE_WIDTH						0.0004f
#define ZOMBIE_SIZE_HEIGHT						0.0005f

//scale zombie 6 vs 7
#define ZOMBIE_SIZE_WIDTH_Z67					0.0013f
#define ZOMBIE_SIZE_HEIGHT_Z67					0.0017f
#define BASE_SIZE_WIDTH							0.0007f
#define BASE_SIZE_HEIGHT						0.0007f


//setPosition cho zombie 3
#define HEIGHT_POSITION_Z3						0.15f
#define HEIGHT_POSITION_Z4						0.3f
#define HEIGHT_POSITION_Z5						0.4f

//setTag
#define TAG_ZOMBIE2								2
#define TAG_ZOMBIE3								3
#define TAG_ZOMBIE4								4
#define TAG_ZOMBIE5								5
#define TAG_ZOMBIE6								6
#define TAG_ZOMBIE7								7
#define TAG_ZOMBIE8								8
#define TAG_ZOMBIE9								9
#define TAG_ZOMBIE10							10
#define TAG_ZOMBIE11							11

#define TAG_SKILL2								12
#define TAG_SKILL3								13
#define TAG_SKILL4								14
#define TAG_SKILL5								15
#define TAG_SKILL6								16
#define TAG_SKILL7								17
#define TAG_SKILL8								18
#define TAG_SKILL9								19
#define TAG_SKILL10								20
#define TAG_SKILL11								21


#define TAG_LINE								23
#define TAG_LINE2								24
#define TAG_HERO								25
#define TAG_BULLET								27
#define	TAG_DYNAMITE							27
#define	TAG_ACTION_MOVETO_ZOMBIE				28
#define	TAG_ACTION_ATTACK_ZOMBIE				29
#define	TAG_BORDER								30

//Số lượng tạo Zombie
#define ZOMBIE_SIZE								20


//Health Zombie
#define HEALTH_ZOMBIE							100.0f
#define HEALTH_ZOMBIE2							150.0f
#define HEALTH_ZOMBIE3							300.0f
#define HEALTH_ZOMBIE4							200.0f
#define HEALTH_ZOMBIE5							250.0f
#define HEALTH_ZOMBIE6							200.0f
#define HEALTH_ZOMBIE7							200.0f

#define START_POS								Vec2(winSize * 0.26f)
#define BULLET_VEC								1000.0f

#define DAMAGE_OF_ZOMBIE2						0.5f
//DAMAGE M4A1
#define DAMAGE_M4A1                             30
//NUMBER BULLET M4A1
#define NUMBER_BULLET_M4A1                      120
//PRICE M4A1
#define PRICE_M4A1                              200

//STAT HP
#define STAT_HP									50
//NUMBER HP
#define NUMBER_HP								3
//PRICE HP
#define PRICE_HP							    500
#endif // __PARAMETER_H__
