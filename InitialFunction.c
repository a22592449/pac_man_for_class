#include "main_header.h"

void allegro_init()
{
    al_init();
    al_init_image_addon();
    al_install_mouse();
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_init_primitives_addon();
    al_init_native_dialog_addon();
    al_reserve_samples(MAX_Sample);
}

Object **create_matrix2(int rows, int cols)
{

    Object **mat = (Object **) malloc(sizeof(Object *)*rows);
    int i=0;
    for(i=0; i<rows; i++)
        mat[i] = (Object *) malloc(sizeof(Object)*cols);

    return mat;
}

Object **Create_Ghost(int n)
{
    Object **ghost;
    int i;
    ghost = (Object**) malloc(sizeof(Object*)*n);
    for(i = 0; i < n; i++)
    {
        ghost[i] = (Object *) malloc(sizeof(Object));
    }
    return ghost;
}

void Init_GameBitmap(ALLEGRO_BITMAP **game_bitmap)
{
    game_bitmap[WALL_30] = al_load_bitmap("./img/WALL-30.png");
    game_bitmap[point] = al_load_bitmap("./img/pencil.png");
    game_bitmap[big_point] = al_load_bitmap("./img/paper.png");
    game_bitmap[elf_front] = al_load_bitmap("./img/elf_front.png");
    game_bitmap[elf_back] = al_load_bitmap("./img/elf_back.png");
    game_bitmap[elf_eat] = al_load_bitmap("./img/elf_front_eat.png");
    game_bitmap[ghost1_front] = al_load_bitmap("./img/ghost1_front.png");
    game_bitmap[ghost1_back] = al_load_bitmap("./img/ghost1_back.png");
    game_bitmap[ghost2_front] = al_load_bitmap("./img/ghost2_front.png");
    game_bitmap[ghost2_back] = al_load_bitmap("./img/ghost2_back.png");
    game_bitmap[ghost3_front] = al_load_bitmap("./img/ghost3_front.png");
    game_bitmap[ghost3_back] = al_load_bitmap("./img/ghost3_back.png");
    game_bitmap[ghost4_front] = al_load_bitmap("./img/ghost4_front.png");
    game_bitmap[ghost4_back] = al_load_bitmap("./img/ghost4_back.png");
    game_bitmap[book_state] = al_load_bitmap("./img/book.png");
}

void Init_Audiosample(ALLEGRO_SAMPLE **audiotype_sample)
{
    audiotype_sample[game_music] = al_load_sample("./music/background.wav");
    audiotype_sample[background_1] = al_load_sample("./music/background-1.wav");
    audiotype_sample[menu_music] = al_load_sample("./music/background-2.wav");
    audiotype_sample[death] = al_load_sample("./music/death.wav");
    audiotype_sample[resurrection] = al_load_sample("./music/resurrection.wav");
    audiotype_sample[desk] = al_load_sample("./music/desk.wav");
    audiotype_sample[paper] = al_load_sample("./music/paper.wav");
    audiotype_sample[write] = al_load_sample("./music/write.wav");
    audiotype_sample[invincible] = al_load_sample("./music/invincible.wav");
    audiotype_sample[win] = al_load_sample("./music/win.wav");
    audiotype_sample[lose] = al_load_sample("./music/lose.wav");
}

void Init_Map(int row, int col, Object **Map)
{
    int i, j;
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            Map[i][j].state = -1;
            Map[i][j].x = j;
            Map[i][j].y = i;
            Map[i][j].pixel_x = j * 30;
            Map[i][j].pixel_y = i * 30;
            Map[i][j].Gstate = NOTHING;
        }
    }
}

void Elf_Init(Object *elf)
{
    elf->state = elf_front;
    elf->dir = -1;
    elf->x = 1;
    elf->y = 1;
    elf->pixel_x = 30*elf->x;
    elf->pixel_y = 30*elf->y;
    elf->Gstate = NOTHING;
}

void Game_mode_Init(GameMode *game_mode)
{
    game_mode->play_all = 0;
    game_mode->difficulty = 0;
    game_mode->round = -1;
}

void Music_Init(ALLEGRO_SAMPLE_INSTANCE **instance, ALLEGRO_MIXER *mixer, ALLEGRO_VOICE *voice, ALLEGRO_SAMPLE **sample)
{
    int i;
    for(i = 0; i < MAX_Sample; i++)
    {
        instance[i] = al_create_sample_instance(sample[i]);
        al_attach_sample_instance_to_mixer(instance[i], mixer);
        al_attach_mixer_to_voice(mixer, voice);
        if(i < MAX_BGM || i == invincible)
        {
            al_set_sample_instance_playmode(instance[i], ALLEGRO_PLAYMODE_LOOP);
        }
        else
        {
            al_set_sample_instance_playmode(instance[i], ALLEGRO_PLAYMODE_ONCE);
        }
    }
}
//*
void Game_Init(int row, int col, Object **Map, Object *elf, int n, Object **ghost, int DISPLAY_W, int DISPLAY_H, int DISPLAY_X, int DISPLAY_Y, Map_f MAP)
{
    int i;
    al_set_window_position(al_get_current_display(), DISPLAY_X, DISPLAY_Y);   //設定display從螢幕的哪個像素開始
    al_resize_display(al_get_current_display(), DISPLAY_W, DISPLAY_H); //將display大小調整成menu大小
    Init_Map(row, col, Map);
    Elf_Init(elf);
    MAP(row, col, Map, ghost);
    for(i = 0; i < n; i++)
    {
        Ghost_Init(ghost[i]);
    }
}

void Ghost_Init(Object *ghost)
{
    ghost->dir = -1;
    ghost->pixel_x = 30 * ghost->x;
    ghost->pixel_y = 30 * ghost->y;
    ghost->Gstate = NORMAL;
    ghost->next = NULL;
}

void Audio_state_Init(AudioMode *audio_state)
{
    audio_state -> all_gain = 1;
    audio_state -> bgm_gain = 1;
    audio_state -> se_gain = 1;
    audio_state -> all_play = 1;
    audio_state -> bgm_play = 1;
    audio_state -> se_play = 1;
}

void Set_Music_Gain(ALLEGRO_SAMPLE_INSTANCE **instance, AudioMode audio_state)
{
    int i;
    for(i = 0; i < MAX_Sample; i++)
    {
        if(i < MAX_BGM)
        {
            al_set_sample_instance_gain(instance[i], audio_state.all_gain * audio_state.bgm_gain);
        }
        else
        {
            al_set_sample_instance_gain(instance[i], audio_state.all_gain * audio_state.se_gain);
        }
    }
}

void Stop_Music(ALLEGRO_SAMPLE_INSTANCE **instance)
{
    int i;
    for(i = 0; i < MAX_Sample; i++)
    {
        al_set_sample_instance_playing(instance[i], false);
    }
}

void Free_GameBitmap(ALLEGRO_BITMAP **game_bitmap)
{
    int i;
    for(i = 0; i < MAX_Object; i++)
    {
        if(game_bitmap[i] != NULL)
        {
            al_destroy_bitmap(game_bitmap[i]);
        }
    }
}

void free_sample(ALLEGRO_SAMPLE **audiotype_sample)
{
    int i;
    for(i = 0; i < MAX_Sample; i++)
    {
        al_destroy_sample(audiotype_sample[i]);
    }
}

void free_matrix(int rows, Object **mat)
{
    int i=0;
    for(i=0; i<rows; i++)
        free(mat[i]);
    free(mat);
}

void free_ghost(Object **ghost, int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        while(!isStackEmpty(ghost[i]))
        {
            pop(&ghost[i]);
        }
    }
    free(ghost);
}

void free_book(Object **book)
{
    Object *ptr;
    while(*book != NULL)
    {
        ptr = *book;
        *book = (*book)->next;
        free(ptr);
    }
}

void free_player(Player *player, char *name)
{
    int i = 0;
    while (player[i].name != NULL && player[i].name != name && i < 10)
    {
        free(player[i].name);
        i++;
    }
}

void free_thread(ALLEGRO_THREAD **thread, ALLEGRO_COND *cond, void **data)
{
    al_set_thread_should_stop(*thread);
    al_broadcast_cond(cond);
    al_join_thread(*thread, NULL);
    free(*data);
    al_destroy_thread(*thread);
}
