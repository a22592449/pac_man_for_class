#ifndef DEFINE_HEADER_H_INCLUDED
#define DEFINE_HEADER_H_INCLUDED

#include <allegro5/allegro.h>

typedef enum {NOTHING, NORMAL, CHANGING, WEAK} Ghost_State;

typedef enum {INIT, MENU, LEADERBOARD, RULE, SELECT, GAME_1, GAME_2, GAME_3, FINISH, WIN, LOSE } PLAY_State;

typedef struct Object
{
    int state;
    int x;
    int y;
    int pixel_x;
    int pixel_y;
    int dir;

    int init_x;
    int init_y;

    Ghost_State Gstate;
    struct Object *next;
}Object;

typedef struct pathnode
{
    int x;
	int y;
	struct pathnode *previous;
	struct pathnode *next;
	int f;
	int g;
}PathNode;

typedef struct
{
    double score;
    char *name;
    int time;
}Player;

typedef struct
{
    float all_gain;
    float bgm_gain;
    float se_gain;
    float saved_all;
    float saved_bgm;
    float saved_se;
    int all_play;
    int bgm_play;
    int se_play;
}AudioMode;

typedef struct
{
    int play_all;
    int difficulty;
    int round;
}GameMode;

typedef struct
{
    int is_pause;
    int row;
    int col;
    Object *elf;
    Object **Map;
    Object **ghost;
    void (*Ghost_Track)(int, int, Object**, int, int, int, Object**);

    ALLEGRO_COND *cond;
    ALLEGRO_MUTEX *mutex;
}ThreadsArg;

typedef struct
{
    int is_pause;
    int *time;

    ALLEGRO_COND *cond;
    ALLEGRO_MUTEX *mutex;
}TimeThreads;

typedef void (*Map_f)(int, int, Object**, Object**);
typedef void (*Track_f)(int, int, Object**, int, int, int, Object**);

#endif
