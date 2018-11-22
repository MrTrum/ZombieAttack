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
//#define TIME_REPEAT_ANIMATE						15.0f

//scale
#define ZOMBIE_SIZE_WIDTH						0.0004f
#define ZOMBIE_SIZE_HEIGHT						0.0005f

//scale zombie 6 vs 7
#define ZOMBIE_SIZE_WIDTH_Z67					0.0013f
#define ZOMBIE_SIZE_HEIGHT_Z67					0.0017f
#define BASE_SIZE_WIDTH							0.0007f
#define BASE_SIZE_HEIGHT						0.0007f

//vị trí moveto zombie
#define LOCAL_MOVETO							0.25f

//setPosition cho zombie 3
#define HEIGHT_POSITION_Z3						0.15f
#define HEIGHT_POSITION_Z4						0.3f
#define HEIGHT_POSITION_Z5						0.4f
#define LINE_BITMASK							1
#define ZOMBIE_BITMASK							2

//bullet vec
#define BULLET_VEC								1000.0f

//setTag
#define TAG_ZOMBIE1								2
#define TAG_ZOMBIE2								3
#define TAG_ZOMBIE3								4
#define TAG_ZOMBIE4								5

#define TAG_LINE								6
#define TAG_LINE2								7
#define TAG_HERO								8
#define TAG_BULLET								9
#define	TAG_DYNAMITE							10
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

//DAMAGE Zombie
//#define DAMAGE_ZOMBIE2							50.0f
#define DAMAGE_OF_ZOMBIE2						0.5f
//DAMAGE M4A1
#define DAMAGE_M4A1                             30
//NUMBER BULLET M4A1
#define NUMBER_BULLET_M4A1                      30
//PRICE M4A1
#define PRICE_M4A1                              200

//STAT HP
#define STAT_HP									50
//NUMBER HP
#define NUMBER_HP								3
//PRICE HP
#define PRICE_HP							    300
#endif // __PARAMETER_H__
