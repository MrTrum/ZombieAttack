#ifndef __PARAMETER_H__
#define __PARAMETER_H__

#define SCALE_PARAMETER_						1.0f

//thời gian
#define TIME_CREATE_ZOMBIE_2					2.0f
#define TIME_CREATE_ZOMBIE_3					3.0f
#define TIME_CREATE_ZOMBIE_4					3.5f
#define TIME_CREATE_ZOMBIE_5					4.0f
#define TIME_CREATE_ZOMBIE_6					4.5f
#define TIME_CREATE_ZOMBIE_7					5.0f

#define TIME_ACTION_ANIMATION					7.0f
#define TIME_MOVETO_ZOMBIE						7.0f
#define TIME_REPEAT_ANIMATE						9.0f

//scale
#define ZOMBIE_SIZE_WIDTH						0.0004f
#define ZOMBIE_SIZE_HEIGHT						0.0005f

//scale zombie 6 vs 7
#define ZOMBIE_SIZE_WIDTH_Z67					0.0013f
#define ZOMBIE_SIZE_HEIGHT_Z67					0.0017f
#define BASE_SIZE_WIDTH							0.0007f
#define BASE_SIZE_HEIGHT						0.0007f

//vị trí moveto zombie
#define LOCAL_MOVETO							0.1f

//setPosition cho zombie 3
#define HEIGHT_POSITION_Z3						0.15f
#define HEIGHT_POSITION_Z4						0.3f
#define HEIGHT_POSITION_Z5						0.4f

//Bitmask
#define LINE_BITMASK							1
#define ZOMBIE_BITMASK							2
#define BULLET_CATEGORY_BITMASK					0010
#define BULLET_COLLISION_AND_CONTACT_BITMASK	0001

//bullet vec
#define BULLET_VEC								800.0f

//setTag
#define ZOMBIE_TAG								1
#define LINE_TAG								2

//Số lượng tạo Zombie
#define ZOMBIE_2								8


#endif // __PARAMETER_H__
