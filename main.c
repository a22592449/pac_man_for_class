#include "main_header.h"

int main()
{
    PLAY_State play_state = INIT;
    double score;
    int time = 0;
    AudioMode audio_state;
    Object **Map, *elf, **ghost;
    GameMode game_mode;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_BITMAP *game_bitmap[MAX_Object];
    ALLEGRO_SAMPLE *sample[MAX_Sample];
    ALLEGRO_SAMPLE_INSTANCE *music[MAX_Sample];
    ALLEGRO_MIXER *mixer = NULL;
    ALLEGRO_VOICE *voice = NULL;

    while(play_state != FINISH)
    {
        switch(play_state)
        {
        case INIT:
            allegro_init();
            display = al_create_display(0, 0);
            mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
            voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
            elf = (Object *) malloc(sizeof(Object));
            Init_GameBitmap(game_bitmap);
            Init_Audiosample(sample);
            Music_Init(music, mixer, voice, sample);
            Audio_state_Init(&audio_state);
            Set_Music_Gain(music, audio_state);
            al_set_display_icon(display, game_bitmap[elf_front]);
            play_state = MENU;
            break;
        case MENU:
            score = 0;
            time = 0;
            Game_mode_Init(&game_mode);
            al_set_window_position(display, 300, 100);
            al_resize_display(display, MENU_W, MENU_H);
            play_state = menu(music, &audio_state);
            break;
        case RULE:
            play_state = Rule();
            break;

        case SELECT:
            play_state = Select_Mode (&game_mode);
            break;

        case GAME_1:
            cutscene(game_bitmap, music, play_state);
            Map = create_matrix2(ROW_1, COL_1);
            ghost = Create_Ghost(N_1);
            Game_Init(ROW_1, COL_1, Map, elf, N_1, ghost, GAME_WIDTH_1, GAME_HEIGHT_1, 550, 150, Map1);
            printf_array_2D(ROW_1, COL_1, Map);
            play_state = Game_1(ROW_1, COL_1, Map, N_1, ghost, elf, game_bitmap, game_mode, &audio_state, &score, music, &time);
            printf("score = %lf\n", score);
            free_matrix(ROW_1, Map);
            free_ghost(ghost, N_1);
            break;

        case GAME_2:
            cutscene(game_bitmap, music, play_state);
            Map = create_matrix2(ROW_2, COL_2);
            ghost = Create_Ghost(N_2);
            Game_Init(ROW_2, COL_2, Map, elf, N_2, ghost, GAME_WIDTH_2, GAME_HEIGHT_2, 700, 15, Map2);
            printf_array_2D(ROW_2, COL_2, Map);
            play_state = Game_2(ROW_2, COL_2, Map, N_2, ghost, elf, game_bitmap, game_mode, &audio_state, &score, music, &time);
            printf("score = %lf\n", score);
            free_matrix(ROW_2, Map);
            free_ghost(ghost, N_2);
            break;

        case GAME_3:
            cutscene(game_bitmap, music, play_state);
            Map = create_matrix2(ROW_3, COL_3);
            ghost = Create_Ghost(N_3);
            Game_Init(ROW_3, COL_3, Map, elf, N_3, ghost, GAME_WIDTH_3, GAME_HEIGHT_3, 300, 50, Map3);
            printf_array_2D(ROW_3, COL_3, Map);
            play_state = Game_3(ROW_3, COL_3, Map, N_3, ghost, elf, game_bitmap, game_mode, &audio_state, &score, music, &time);
            printf("score = %lf\n", score);
            free_matrix(ROW_3, Map);
            free_ghost(ghost, N_3);
            break;

        case LEADERBOARD:
            al_set_window_position(display, 300, 100);   //�]�wdisplay�q�ù������ӹ����}�l
            al_resize_display(display, MENU_W, MENU_H); //�Ndisplay�j�p�վ㦨menu�j�p
            play_state = leaderboard(game_mode);
            break;

        case WIN: case LOSE:
            cutscene(game_bitmap, music, play_state);
            al_set_window_position(display, 300, 100);
            al_resize_display(display, MENU_W, MENU_H);
            play_state = User_Name(score, time, play_state, game_mode);
            break;

        case FINISH:
            free_sample(sample);
            Free_GameBitmap(game_bitmap);
            al_destroy_display(display);
            break;
        }
    }

    return 0;
}
