#ifndef CONFIG_H
#define CONFIG_H

/* ROBOT */
#define ROBOT_1 true
#define ROBOT_2 (!ROBOT_1)

/* DEBUG */
#define DEBUG_MOTORS false
#define DEBUG_IMU false
#define DEBUG_CAMERA false
#define DEBUG_GOAL_CORRECT false
#define DEBUG (DEBUG_MOTORS || DEBUG_IMU || DEBUG_CAMERA || DEBUG_GOAL_CORRECT)

/* ATTACK DIRECTION */
#define BLUE_GOAL_ATTACK true
// True: Attacking Blue Goal (Defending Yellow Goal)
// False: Attacking Yellow Goal (Defending Blue Goal)

#endif