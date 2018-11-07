#ifndef __PARAMETER_H__
#define __PARAMETER_H__

//thời gian
#define TIME_CREATE_ZOMBIE_2					4.0f
#define TIME_CREATE_ZOMBIE_3					3.0f
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
#define BULLET_VEC								2000.0f

//setTag
#define ZOMBIE_TAG								3
#define LINE_TAG								4
#define BULLET_TAG								5
#define LINE_TAG2								6
#define HERO_TAG								7

//Số lượng tạo Zombie
#define ZOMBIE_2								20


//Health Zombie
#define HEALTH_ZOMBIE2							100.0f

//DAMAGE Zombie
#define DAMAGE_ZOMBIE2							50.0f
#define DAMAGE_OF_ZOMBIE2						0.5f


#endif // __PARAMETER_H__
