#ifndef FUNCTION_HEADER_H_INCLUDED
#define FUNCTION_HEADER_H_INCLUDED

#include "define_header.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//InitialFunction
void allegro_init();
Object **create_matrix2(int rows, int cols);
Object **Create_Ghost(int n);
void Init_GameBitmap(ALLEGRO_BITMAP **game_bitmap);
void Init_Audiosample(ALLEGRO_SAMPLE **audiotype_sample);
void Init_Map(int row, int col, Object **Map);
void Elf_Init(Object *elf);
void Game_mode_Init(GameMode *game_mode);
void Music_Init(ALLEGRO_SAMPLE_INSTANCE **instance, ALLEGRO_MIXER *mixer, ALLEGRO_VOICE *voice, ALLEGRO_SAMPLE **sample);
void Game_Init(int row, int col, Object **Map, Object *elf, int n, Object **ghost, int DISPLAY_W, int DISPLAY_H, int DISPLAY_X, int DISPLAY_Y, Map_f MAP);
void Ghost_Init(Object *ghost);
void Audio_state_Init(AudioMode *audio_state);
void Set_Music_Gain(ALLEGRO_SAMPLE_INSTANCE **instance, AudioMode audio_state);
void Stop_Music(ALLEGRO_SAMPLE_INSTANCE **instance);
void printf_array_2D(int row, int col, Object **Map);
void Free_GameBitmap(ALLEGRO_BITMAP **game_bitmap);
void free_sample(ALLEGRO_SAMPLE **audiotype_sample);
void free_matrix(int rows, Object **mat);
void free_ghost(Object **ghost, int n);
void free_book(Object **book);
void free_player(Player *player, char *name);
void free_thread(ALLEGRO_THREAD **thread, ALLEGRO_COND *cond, void **data);

//LayoutFunction
PLAY_State menu(ALLEGRO_SAMPLE_INSTANCE **music, AudioMode *audio_state);
void Draw_Map(int row, int col, Object **Map, ALLEGRO_BITMAP **game_bitmap);
void voice_control(AudioMode *audio_state, ALLEGRO_SAMPLE_INSTANCE **instance, PLAY_State *play_state);
PLAY_State leaderboard(GameMode game_mode);
PLAY_State User_Name(double score, int time, PLAY_State play_state, GameMode game_mode);
PLAY_State Select_Mode (GameMode *game_mode);
void Draw_Frame(int game, ALLEGRO_BITMAP *frame, int select, ALLEGRO_BITMAP *frame2, ALLEGRO_MOUSE_EVENT mouse);
void Draw_player(int page, ALLEGRO_FONT *FONT, ALLEGRO_COLOR white, GameMode game_mode);
void Leaderboard_Select(GameMode game_mode);
void cutscene(ALLEGRO_BITMAP **game_bitmap, ALLEGRO_SAMPLE_INSTANCE **music, PLAY_State play_state);
PLAY_State Rule();
void draw_special(ALLEGRO_MOUSE_EVENT mouse, ALLEGRO_BITMAP **sp);
void draw_bitmap(ALLEGRO_BITMAP *bitmap, ALLEGRO_BITMAP *bitmap2, ALLEGRO_MOUSE_EVENT mouse, int max_x, int min_x, int max_y, int min_y, int x, int y, int flags);
void draw_text(ALLEGRO_FONT *font, ALLEGRO_COLOR color, ALLEGRO_COLOR color2, ALLEGRO_MOUSE_EVENT mouse, int max_x, int min_x, int max_y, int min_y, int x, int y, int flags, const char* text);


//map_define
void wall_col(int row,int col,Object **Map, int x, int y, int j, int k);
void wall_row(int row,int col,Object **Map, int x, int y, int j, int k);
void point_map(int row, int col, Object **Map);

//map_species
void Map1(int row,int col,Object **Map, Object **ghost);
void Map2(int row,int col,Object **Map, Object **ghost);
void Map3(int row,int col,Object **Map, Object **ghost);

//ElfFunction
void Select_Elf_Dir(ALLEGRO_KEYBOARD_EVENT KBstate, Object *elf, int *dir);
void Elf_Move(Object *elf, int col, Object **Map, ALLEGRO_BITMAP **game_bitmap, int eat_time);
int Detect_Eaten(Object *elf, Object **Map, int n, Object **ghost, int *change_time, int *dead_time, int *elf_move_time, int *slow_time, Object **book, double *in_score, double point_score, ALLEGRO_SAMPLE_INSTANCE **music);

//GameFunction
PLAY_State Game_1(int row, int col, Object **Map, int n, Object **ghost, Object *elf, ALLEGRO_BITMAP **game_bitmap, GameMode game_mode, AudioMode *audio_state, double *score, ALLEGRO_SAMPLE_INSTANCE **music, int *time);
PLAY_State Game_2(int row, int col, Object **Map, int n, Object **ghost, Object *elf, ALLEGRO_BITMAP **game_bitmap, GameMode game_mode, AudioMode *audio_state, double *score, ALLEGRO_SAMPLE_INSTANCE **music, int *time);
PLAY_State Game_3(int row, int col, Object **Map, int n, Object **ghost, Object *elf, ALLEGRO_BITMAP **game_bitmap, GameMode game_mode, AudioMode *audio_state, double *score, ALLEGRO_SAMPLE_INSTANCE **music, int *time);
int Count_Point(int row, int col, Object **Map);
void *Count_Time(ALLEGRO_THREAD *timer, void *data);

//GhostFunction
void Ghost_track_0(int row, int col, Object **Map, int fin_x, int fin_y, int fin_dir, Object **ghost);
void Ghost_track_1(int row, int col, Object **Map, int fin_x, int fin_y, int fin_dir, Object **ghost);
void Ghost_track_2(int row, int col, Object **Map, int fin_x, int fin_y, int fin_dir, Object **ghost);
void Ghost_track_3(int row, int col, Object **Map, int fin_x, int fin_y, int fin_dir, Object **ghost);
Object *Ghost_Move(int row, int col, Object **Map, Object **ghost, ALLEGRO_BITMAP **game_bitmap);
int Select_Dir(int fin_x, int fin_y, Object *ghost);
void Select_Ghost_Bitmap(Object **ghost, ALLEGRO_BITMAP **game_bitmap);
void Select_Track(Object **ghost, Object **Map, int dir_1, int dir_2, int dir_3, int dir_4, int *x, int *y);
void Show_Ghost(Object *ghost, int change_time, int timer, int dead_time, ALLEGRO_BITMAP **game_bitmap, ALLEGRO_SAMPLE_INSTANCE **music);
Object* Create_Book(Object *ghost, Object *book);
void Show_Book(Object *book, ALLEGRO_BITMAP **game_bitmap);
int Ghost_Runaway_Dir(int fin_x, int fin_y, Object *ghost);
void Track_If_Ghost_Weak(Object **ghost, int fin_x, int fin_y, Object **Map, int col);
void Select_Weak_Track(Object **Map, Object **ghost, int dir_1, int dir_2, int dir_3, int x, int y);
void *load_track(ALLEGRO_THREAD *track, void *data);

//PathFunction
int isStackEmpty(Object *ghost);
void push(int x, int y, Object **ghost);
void pop(Object **ghost);
PathNode *insert(PathNode **l, PathNode *fn, int x, int y, int f, int g);
int movenode(PathNode **a, PathNode **b);
int G(PathNode *fn);
int H(int x,int y,int x2, int y2);

//fileprocessing
int File_Length(const char* file_name);
int Load_Player(Player *player,  char* *filename);
void Save_File(char *name, double score, int time, GameMode game_mode);

#endif
