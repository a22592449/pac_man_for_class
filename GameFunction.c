#include "main_header.h"

PLAY_State Game_1(int row, int col, Object **Map, int n, Object **ghost, Object *elf, ALLEGRO_BITMAP **game_bitmap, GameMode game_mode, AudioMode *audio_state, double *score, ALLEGRO_SAMPLE_INSTANCE **music, int *time)
{
    int dir = -1, i, change_time = 0, change_time_temp, dead_time[n], eat_time = 0, count;
    double point_score, in_score = 0;
    PLAY_State play_state = GAME_1;
    ThreadsArg *arg[n];
    TimeThreads *game_time;
    Track_f Ghost_Track[n];
    Object *current[n];
    ALLEGRO_BITMAP *setting = NULL;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *event_q;
    ALLEGRO_EVENT ev;
    ALLEGRO_THREAD *Track_Thread[n], *Time_Thread;
    ALLEGRO_FONT *FONT2;

    timer = al_create_timer(1.0/240);
    event_q = al_create_event_queue();

    setting = al_load_bitmap("./audio_img/setting_button.png");
    FONT2 = al_load_font("./Font/Pixeboy-z8XGD.ttf", 35, 0);

    al_register_event_source(event_q, al_get_display_event_source(al_get_current_display()));
    al_register_event_source(event_q, al_get_keyboard_event_source());
    al_register_event_source(event_q, al_get_timer_event_source(timer));
    al_register_event_source(event_q, al_get_mouse_event_source());

    if(game_mode.difficulty == 1)
    {
        Ghost_Track[0] = Ghost_track_0;
        Ghost_Track[1] = Ghost_track_1;
    }
    else if(game_mode.difficulty == 2)
    {
        Ghost_Track[0] = Ghost_track_3;
        Ghost_Track[1] = Ghost_track_1;
    }
    else
    {
        Ghost_Track[0] = Ghost_track_3;
        Ghost_Track[1] = Ghost_track_0;
    }


    for(i = 0; i < n; i++)
    {
        current[i] = ghost[i];
        dead_time[i] = 0;
        arg[i] = (ThreadsArg *)malloc(sizeof(ThreadsArg));
        arg[i]->row = row;
        arg[i]->col = col;
        arg[i]->elf = elf;
        arg[i]->Map = Map;
        arg[i]->ghost = &ghost[i];
        arg[i]->Ghost_Track = Ghost_Track[i];
        arg[i]->is_pause = 1;
        arg[i]->cond = al_create_cond();
        arg[i]->mutex = al_create_mutex();
        Track_Thread[i] = al_create_thread(load_track, arg[i]);
        al_start_thread(Track_Thread[i]);
    }

    game_time = (TimeThreads*) malloc(sizeof(TimeThreads));
    game_time->is_pause = 1;
    game_time->time = time;
    game_time->cond = al_create_cond();
    game_time->mutex = al_create_mutex();
    Time_Thread = al_create_thread(Count_Time, game_time);
    al_start_thread(Time_Thread);

    point_score = 60.0 / Count_Point(row, col, Map);

    printf("point_score = %lf\n", point_score);

    al_start_timer(timer);


    al_set_sample_instance_playing(music[menu_music], false);
    al_set_sample_instance_playing(music[game_music], true);

    while(play_state == GAME_1)
    {
        while(al_get_next_event(event_q, &ev))
        {
            switch(ev.type)
            {
            case ALLEGRO_EVENT_KEY_CHAR:
                if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    if(change_time != 0)
                    {
                        change_time_temp = al_get_sample_instance_position(music[invincible]);
                        al_set_sample_instance_playing(music[invincible], false);
                    }
                    game_time->is_pause = 1;
                    al_broadcast_cond(game_time->cond);
                    al_pause_event_queue(event_q, true);
                    al_stop_timer(timer);
                    voice_control(audio_state, music, &play_state);
                    al_resume_timer(timer);
                    al_pause_event_queue(event_q, false);
                    if(change_time != 0)
                    {
                        al_set_sample_instance_position(music[invincible], change_time_temp);
                        al_set_sample_instance_playing(music[invincible], true);
                    }
                }
                Select_Elf_Dir(ev.keyboard, elf, &dir);
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if(ev.mouse.button & 1)
                {
                    if(ev.mouse.x >= GAME_WIDTH_1 - 32 && ev.mouse.x <= GAME_WIDTH_1 - 2 && ev.mouse.y >= 5 && ev.mouse.y <= 35)
                    {
                        if(change_time != 0)
                        {
                            change_time_temp = al_get_sample_instance_position(music[invincible]);
                            al_set_sample_instance_playing(music[invincible], false);
                        }
                        game_time->is_pause = 1;
                        al_broadcast_cond(game_time->cond);
                        al_pause_event_queue(event_q, true);
                        al_stop_timer(timer);
                        voice_control(audio_state, music, &play_state);
                        al_resume_timer(timer);
                        al_pause_event_queue(event_q, false);
                        if(change_time != 0)
                        {
                            al_set_sample_instance_position(music[invincible], change_time_temp);
                            al_set_sample_instance_playing(music[invincible], true);
                        }
                    }
                }
                break;
            case  ALLEGRO_EVENT_DISPLAY_CLOSE:
                play_state = FINISH;
                break;
            case ALLEGRO_EVENT_TIMER:
                al_clear_to_color(al_map_rgb(0, 0, 0));
                Draw_Map(row,col,Map, game_bitmap);
                al_draw_bitmap(setting, GAME_WIDTH_1 - 32, 5, 0);
                game_time->is_pause = 0;
                al_broadcast_cond(game_time->cond);
                al_draw_textf(FONT2, al_map_rgb(210, 122, 0), GAME_WIDTH_1-145, GAME_HEIGHT_1-25, ALLEGRO_ALIGN_LEFT, "time: %d", *time / CLOCKS_PER_SEC);
                count = 0;
                for(i = 0; i < n; i++)
                {
                    if(current[i]->pixel_x % 30 == 0 && current[i]->pixel_y % 30 == 0)
                    {
                        if(current[i]->Gstate != NOTHING)
                        {
                            if(current[i]->Gstate == NORMAL)
                            {
                                arg[i]->is_pause = 0;
                                al_broadcast_cond(arg[i]->cond);
                            }
                            else
                            {
                                Track_If_Ghost_Weak(&ghost[i], elf->x, elf->y, Map, col);
                            }
                        }
                    }
                    if(current[i]->Gstate != CHANGING && current[i]->Gstate != WEAK)
                        count++;
                }
                if(count == n)
                {
                    al_set_sample_instance_playing(music[invincible], false);
                }
                for(i = 0; i < n; i++)
                {
                    while(!arg[i]->is_pause);
                }
                if(elf->pixel_x % 30 == 0 && elf->pixel_y % 30 == 0)
                {
                    elf->dir = dir;
                }
                if(ev.timer.count % 240 == 0)
                {
                    if(change_time != 0)
                        change_time--;
                    for(i = 0; i < n; i++)
                    {
                        if(dead_time[i] != 0)
                        {
                            dead_time[i]--;
                        }
                    }
                }
                if(ev.timer.count % 120 == 0)
                {
                    if(eat_time != 0)
                        eat_time--;
                }

                if(ev.timer.count % 2 == 0)
                {
                    if(Detect_Eaten(elf, Map, n, ghost, &change_time, dead_time, NULL, NULL, NULL, &in_score, point_score, music))
                    {
                        eat_time = 1;
                    }
                    Elf_Move(elf, col, Map, game_bitmap, eat_time);
                }

                for(i = 0; i < n; i++)
                {
                    if(current[i]->Gstate != CHANGING && current[i]->Gstate != WEAK && ev.timer.count % 2 == 0)
                    {
                        if(current[i]->Gstate != NOTHING)
                            current[i] = Ghost_Move(row, col, Map, &ghost[i], game_bitmap);
                        else
                        {
                            while(ghost[i]->next != NULL)
                            {
                                pop(&ghost[i]);
                            }
                            current[i] = ghost[i];
                        }
                    }
                    if(current[i]->Gstate != NORMAL && ev.timer.count % 3 == 0)
                    {
                        if(current[i]->Gstate != NOTHING)
                            current[i] = Ghost_Move(row, col, Map, &ghost[i], game_bitmap);
                        else
                        {
                            while(ghost[i]->next != NULL)
                            {
                                pop(&ghost[i]);
                            }
                            current[i] = ghost[i];
                        }
                    }
                }
                if(elf->dir == RIGHT)
                {
                    al_draw_bitmap(game_bitmap[elf->state], elf->pixel_x, elf->pixel_y, 1);
                }
                else
                {
                    al_draw_bitmap(game_bitmap[elf->state], elf->pixel_x, elf->pixel_y, 0);
                }
                for(i = 0; i < n; i++)
                {
                    Show_Ghost(current[i], change_time, ev.timer.count, dead_time[i], game_bitmap,music);
                }
                for(i = 0; i < n; i++)
                {
                    if(current[i]->Gstate == NORMAL)
                    {
                        if(abs(current[i]->pixel_x - elf->pixel_x) < 10 && abs(current[i]->pixel_y - elf->pixel_y) < 10)
                        {
                            if(in_score >= 60)
                            {
                                if(game_mode.play_all)
                                    play_state = GAME_2;
                                else
                                    play_state = WIN;
                            }
                            else
                                play_state = LOSE;
                        }
                    }
                }
                if(in_score >= 100 || !Count_Point(row, col, Map))
                {
                    if(game_mode.play_all)
                        play_state = GAME_2;
                    else
                        play_state = WIN;
                }
                al_flip_display();
                break;
            }
        }
    }

    if(in_score >= 100)
    {
        in_score = 100;
    }
    *score = in_score + *score;

    Stop_Music(music);

    for(i = 0; i < n; i++)
    {
        free_thread(&Track_Thread[i], arg[i]->cond, (void**)(&arg[i]));
    }
    free_thread(&Time_Thread, game_time->cond, ((void**)(&game_time)));
    al_destroy_font(FONT2);
    al_destroy_bitmap(setting);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_q);
    return play_state;
}

PLAY_State Game_2(int row, int col, Object **Map, int n, Object **ghost, Object *elf, ALLEGRO_BITMAP **game_bitmap, GameMode game_mode, AudioMode *audio_state, double *score, ALLEGRO_SAMPLE_INSTANCE **music, int *time)
{
    int dir = -1, i, change_time = 0, dead_time[n], eat_time = 0, count, change_time_temp;
    double point_score, in_score = 0;
    PLAY_State play_state = GAME_2;
    ThreadsArg *arg[n];
    TimeThreads *game_time;
    Track_f Ghost_Track[n];
    Object *current[n];
    ALLEGRO_TIMER *timer;
    ALLEGRO_BITMAP *setting = NULL;
    ALLEGRO_EVENT_QUEUE *event_q;
    ALLEGRO_EVENT ev;
    ALLEGRO_THREAD *Track_Thread[n], *Time_Thread;
    ALLEGRO_FONT *FONT2;

    timer = al_create_timer(1.0/240);
    event_q = al_create_event_queue();

    setting = al_load_bitmap("./audio_img/setting_button.png");
    FONT2 = al_load_font("./Font/Pixeboy-z8XGD.ttf", 35, 0);

    al_register_event_source(event_q, al_get_display_event_source(al_get_current_display()));
    al_register_event_source(event_q, al_get_keyboard_event_source());
    al_register_event_source(event_q, al_get_timer_event_source(timer));
    al_register_event_source(event_q, al_get_mouse_event_source());

    if(game_mode.difficulty == 1)
    {
        Ghost_Track[0] = Ghost_track_0;
        Ghost_Track[1] = Ghost_track_1;
        Ghost_Track[2] = Ghost_track_1;
    }
    else if(game_mode.difficulty == 2)
    {
        Ghost_Track[0] = Ghost_track_0;
        Ghost_Track[1] = Ghost_track_1;
        Ghost_Track[2] = Ghost_track_2;
    }
    else
    {
        Ghost_Track[0] = Ghost_track_3;
        Ghost_Track[1] = Ghost_track_0;
        Ghost_Track[2] = Ghost_track_2;
    }

    for(i = 0; i < n; i++)
    {
        current[i] = ghost[i];
        dead_time[i] = 0;
        arg[i] = (ThreadsArg *)malloc(sizeof(ThreadsArg));
        arg[i]->row = row;
        arg[i]->col = col;
        arg[i]->elf = elf;
        arg[i]->Map = Map;
        arg[i]->ghost = &ghost[i];
        arg[i]->Ghost_Track = Ghost_Track[i];
        arg[i]->is_pause = 1;
        arg[i]->cond = al_create_cond();
        arg[i]->mutex = al_create_mutex();
        Track_Thread[i] = al_create_thread(load_track, arg[i]);
        al_start_thread(Track_Thread[i]);
    }

    game_time = (TimeThreads*) malloc(sizeof(TimeThreads));
    game_time->is_pause = 1;
    game_time->time = time;
    game_time->cond = al_create_cond();
    game_time->mutex = al_create_mutex();
    Time_Thread = al_create_thread(Count_Time, game_time);
    al_start_thread(Time_Thread);

    point_score = 60.0 / Count_Point(row, col, Map);

    al_start_timer(timer);

    al_set_sample_instance_playing(music[menu_music], false);
    al_set_sample_instance_playing(music[game_music], true);

    while(play_state == GAME_2)
    {
        while(al_get_next_event(event_q, &ev))
        {
            switch(ev.type)
            {
            case ALLEGRO_EVENT_KEY_CHAR:
                if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    if(change_time != 0)
                    {
                        change_time_temp = al_get_sample_instance_position(music[invincible]);
                        al_set_sample_instance_playing(music[invincible], false);
                    }
                    game_time->is_pause = 1;
                    al_broadcast_cond(game_time->cond);
                    al_pause_event_queue(event_q, true);
                    al_stop_timer(timer);
                    voice_control(audio_state, music, &play_state);
                    al_resume_timer(timer);
                    al_pause_event_queue(event_q, false);
                    if(change_time != 0)
                    {
                        al_set_sample_instance_position(music[invincible], change_time_temp);
                        al_set_sample_instance_playing(music[invincible], true);
                    }
                }
                Select_Elf_Dir(ev.keyboard, elf, &dir);
                break;
                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if(ev.mouse.button & 1)
                {
                    if(ev.mouse.x >= GAME_WIDTH_2 - 32 && ev.mouse.x <= GAME_WIDTH_2 - 2 && ev.mouse.y >= 5 && ev.mouse.y <= 35)
                    {
                        if(change_time != 0)
                        {
                            change_time_temp = al_get_sample_instance_position(music[invincible]);
                            al_set_sample_instance_playing(music[invincible], false);
                        }
                        game_time->is_pause = 1;
                        al_broadcast_cond(game_time->cond);
                        al_pause_event_queue(event_q, true);
                        al_stop_timer(timer);
                        voice_control(audio_state, music, &play_state);
                        al_resume_timer(timer);
                        al_pause_event_queue(event_q, false);
                        if(change_time != 0)
                        {
                            al_set_sample_instance_position(music[invincible], change_time_temp);
                            al_set_sample_instance_playing(music[invincible], true);
                        }
                    }
                }
                break;
            case  ALLEGRO_EVENT_DISPLAY_CLOSE:
                play_state = FINISH;
                break;
            case ALLEGRO_EVENT_TIMER:
                al_clear_to_color(al_map_rgb(0, 0, 0));
                Draw_Map(row,col,Map, game_bitmap);
                al_draw_bitmap(setting, GAME_WIDTH_2 - 32, 5, 0);
                game_time->is_pause = 0;
                al_broadcast_cond(game_time->cond);
                al_draw_textf(FONT2, al_map_rgb(210, 122, 0), GAME_WIDTH_2 - 145, GAME_HEIGHT_2 - 25, ALLEGRO_ALIGN_LEFT, "time: %d", *time / CLOCKS_PER_SEC);
                count = 0;
                for(i = 0; i < n; i++)
                {
                    if(current[i]->pixel_x % 30 == 0 && current[i]->pixel_y % 30 == 0)
                    {
                        if(current[i]->Gstate != NOTHING)
                        {
                            if(current[i]->Gstate == NORMAL)
                            {
                                arg[i]->is_pause = 0;
                                al_broadcast_cond(arg[i]->cond);
                            }
                            else
                            {
                                Track_If_Ghost_Weak(&ghost[i], elf->x, elf->y, Map, col);
                            }
                        }
                    }
                    if(current[i]->Gstate != CHANGING && current[i]->Gstate != WEAK)
                        count++;
                }
                if(count == n)
                {
                    al_set_sample_instance_playing(music[invincible], false);
                }
                for(i = 0; i < n; i++)
                {
                    while(!arg[i]->is_pause);
                }
                if(elf->pixel_x % 30 == 0 && elf->pixel_y % 30 == 0)
                {
                    elf->dir = dir;
                }
                if(ev.timer.count % 240 == 0)
                {
                    if(change_time != 0)
                        change_time--;
                    for(i = 0; i < n; i++)
                    {
                        if(dead_time[i] != 0)
                        {
                            dead_time[i]--;
                        }
                    }
                }
                if(ev.timer.count % 120 == 0)
                {
                    if(eat_time != 0)
                        eat_time--;
                }
                if(ev.timer.count % 2 == 0)
                {
                    if(Detect_Eaten(elf, Map, n, ghost, &change_time, dead_time, NULL, NULL, NULL, &in_score, point_score, music))
                    {
                        eat_time = 1;
                    }
                    Elf_Move(elf, col, Map, game_bitmap, eat_time);
                }
                for(i = 0; i < n; i++)
                {
                    if(current[i]->Gstate != CHANGING && current[i]->Gstate != WEAK && ev.timer.count % 2 == 0)
                    {
                        if(current[i]->Gstate != NOTHING)
                            current[i] = Ghost_Move(row, col, Map, &ghost[i], game_bitmap);
                        else
                        {
                            while(ghost[i]->next != NULL)
                            {
                                pop(&ghost[i]);
                            }
                            current[i] = ghost[i];
                        }
                    }
                    if(current[i]->Gstate != NORMAL && ev.timer.count % 3 == 0)
                    {
                        if(current[i]->Gstate != NOTHING)
                            current[i] = Ghost_Move(row, col, Map, &ghost[i], game_bitmap);
                        else
                        {
                            while(ghost[i]->next != NULL)
                            {
                                pop(&ghost[i]);
                            }
                            current[i] = ghost[i];
                        }
                    }
                }
                if(elf->dir == RIGHT)
                {
                    al_draw_bitmap(game_bitmap[elf->state], elf->pixel_x, elf->pixel_y, 1);
                }
                else
                {
                    al_draw_bitmap(game_bitmap[elf->state], elf->pixel_x, elf->pixel_y, 0);
                }
                for(i = 0; i < n; i++)
                {
                    Show_Ghost(current[i], change_time, ev.timer.count, dead_time[i], game_bitmap,music);
                }
                for(i = 0; i < n; i++)
                {
                    if(current[i]->Gstate == NORMAL)
                    {
                        if(abs(current[i]->pixel_x - elf->pixel_x) < 10 && abs(current[i]->pixel_y - elf->pixel_y) < 10)
                        {
                            if(in_score >= 60)
                            {
                                if(game_mode.play_all)
                                    play_state = GAME_3;
                                else
                                    play_state = WIN;
                            }
                            else
                                play_state = LOSE;
                        }
                    }
                }
                if(in_score >= 100 || !Count_Point(row, col, Map))
                {
                    if(game_mode.play_all)
                        play_state = GAME_3;
                    else
                        play_state = WIN;
                }
                al_flip_display();
                break;
            }
        }
    }
    if(in_score >= 100)
    {
        in_score = 100;
    }
    *score = in_score + *score;

    Stop_Music(music);

    for(i = 0; i < n; i++)
    {
        free_thread(&Track_Thread[i], arg[i]->cond, (void**)(&arg[i]));
    }
    free_thread(&Time_Thread, game_time->cond, ((void**)(&game_time)));
    al_destroy_font(FONT2);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_q);
    return play_state;
}

PLAY_State Game_3(int row, int col, Object **Map, int n, Object **ghost, Object *elf, ALLEGRO_BITMAP **game_bitmap, GameMode game_mode, AudioMode *audio_state, double *score, ALLEGRO_SAMPLE_INSTANCE **music, int *time)
{
    int dir = -1, i, change_time = 0, dead_time[n], extra_class = 0, elf_move_time = 2, slow_time = 0, eat_time = 0, count, change_time_temp;
    double point_score, in_score = 0;
    PLAY_State play_state = GAME_3;
    ThreadsArg *arg[n];
    TimeThreads *game_time;
    Track_f Ghost_Track[] = {Ghost_track_3, Ghost_track_1, Ghost_track_2, Ghost_track_1};
    Object *current[n], *book = NULL;
    ALLEGRO_TIMER *timer;
    ALLEGRO_BITMAP *setting = NULL;
    ALLEGRO_EVENT_QUEUE *event_q;
    ALLEGRO_EVENT ev;
    ALLEGRO_THREAD *Track_Thread[n], *Time_Thread;
    ALLEGRO_FONT *FONT2;

    timer = al_create_timer(1.0/240);
    event_q = al_create_event_queue();

    setting = al_load_bitmap("./audio_img/setting_button.png");
    FONT2 = al_load_font("./Font/Pixeboy-z8XGD.ttf", 35, 0);

    al_register_event_source(event_q, al_get_display_event_source(al_get_current_display()));
    al_register_event_source(event_q, al_get_keyboard_event_source());
    al_register_event_source(event_q, al_get_timer_event_source(timer));
    al_register_event_source(event_q, al_get_mouse_event_source());

    if(game_mode.difficulty == 1)
    {
        Ghost_Track[0] = Ghost_track_0;
        Ghost_Track[1] = Ghost_track_1;
        Ghost_Track[2] = Ghost_track_2;
        Ghost_Track[3] = Ghost_track_1;

    }
    else if(game_mode.difficulty == 2)
    {
        Ghost_Track[0] = Ghost_track_3;
        Ghost_Track[1] = Ghost_track_1;
        Ghost_Track[2] = Ghost_track_2;
        Ghost_Track[3] = Ghost_track_1;
    }
    else
    {
        Ghost_Track[0] = Ghost_track_3;
        Ghost_Track[1] = Ghost_track_0;
        Ghost_Track[2] = Ghost_track_2;
        Ghost_Track[3] = Ghost_track_2;
    }


    for(i = 0; i < n; i++)
    {
        current[i] = ghost[i];
        dead_time[i] = 0;
        arg[i] = (ThreadsArg *)malloc(sizeof(ThreadsArg));
        arg[i]->row = row;
        arg[i]->col = col;
        arg[i]->elf = elf;
        arg[i]->Map = Map;
        arg[i]->ghost = &ghost[i];
        arg[i]->Ghost_Track = Ghost_Track[i];
        arg[i]->is_pause = 1;
        arg[i]->cond = al_create_cond();
        arg[i]->mutex = al_create_mutex();
        Track_Thread[i] = al_create_thread(load_track, arg[i]);
        al_start_thread(Track_Thread[i]);
    }

    game_time = (TimeThreads*) malloc(sizeof(TimeThreads));
    game_time->is_pause = 1;
    game_time->time = time;
    game_time->cond = al_create_cond();
    game_time->mutex = al_create_mutex();
    Time_Thread = al_create_thread(Count_Time, game_time);
    al_start_thread(Time_Thread);

    point_score = 60.0 / Count_Point(row, col, Map);

    al_start_timer(timer);

    al_set_sample_instance_playing(music[menu_music], false);
    al_set_sample_instance_playing(music[game_music], true);

    while(play_state == GAME_3)
    {
        if(extra_class == 0)
        {
            extra_class = 6;
        }
        while(al_get_next_event(event_q, &ev))
        {
            switch(ev.type)
            {
            case ALLEGRO_EVENT_KEY_CHAR:
                if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    if(change_time != 0)
                    {
                        change_time_temp = al_get_sample_instance_position(music[invincible]);
                        al_set_sample_instance_playing(music[invincible], false);
                    }
                    game_time->is_pause = 1;
                    al_broadcast_cond(game_time->cond);
                    al_pause_event_queue(event_q, true);
                    al_stop_timer(timer);
                    voice_control(audio_state, music, &play_state);
                    al_resume_timer(timer);
                    al_pause_event_queue(event_q, false);
                    if(change_time != 0)
                    {
                        al_set_sample_instance_position(music[invincible], change_time_temp);
                        al_set_sample_instance_playing(music[invincible], true);
                    }
                }
                Select_Elf_Dir(ev.keyboard, elf, &dir);
                break;
                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if(ev.mouse.button & 1)
                {
                    if(ev.mouse.x >= GAME_WIDTH_3 - 32 && ev.mouse.x <= GAME_WIDTH_3 - 2 && ev.mouse.y >= 5 && ev.mouse.y <= 35)
                    {
                        if(change_time != 0)
                        {
                            change_time_temp = al_get_sample_instance_position(music[invincible]);
                            al_set_sample_instance_playing(music[invincible], false);
                        }
                        game_time->is_pause = 1;
                        al_broadcast_cond(game_time->cond);
                        al_pause_event_queue(event_q, true);
                        al_stop_timer(timer);
                        voice_control(audio_state, music, &play_state);
                        al_resume_timer(timer);
                        al_pause_event_queue(event_q, false);
                        if(change_time != 0)
                        {
                            al_set_sample_instance_position(music[invincible], change_time_temp);
                            al_set_sample_instance_playing(music[invincible], true);
                        }
                    }
                }
                break;
            case  ALLEGRO_EVENT_DISPLAY_CLOSE:
                play_state = FINISH;
                break;
            case ALLEGRO_EVENT_TIMER:
                al_clear_to_color(al_map_rgb(0, 0, 0));
                Draw_Map(row,col,Map, game_bitmap);
                al_draw_bitmap(setting, GAME_WIDTH_3 - 32, 5, 0);
                game_time->is_pause = 0;
                al_broadcast_cond(game_time->cond);
                al_draw_textf(FONT2, al_map_rgb(210, 122, 0), GAME_WIDTH_3 - 145, GAME_HEIGHT_3 - 25, ALLEGRO_ALIGN_LEFT, "time: %d", *time / CLOCKS_PER_SEC);
                count = 0;
                for(i = 0; i < n; i++)
                {
                    if(current[i]->pixel_x % 30 == 0 && current[i]->pixel_y % 30 == 0)
                    {
                        if(current[i]->Gstate != NOTHING)
                        {
                            if(current[i]->Gstate == NORMAL)
                            {
                                arg[i]->is_pause = 0;
                                al_broadcast_cond(arg[i]->cond);
                            }
                            else
                            {
                                Track_If_Ghost_Weak(&ghost[i], elf->x, elf->y, Map, col);
                            }
                        }
                    }
                    if(current[i]->Gstate != CHANGING && current[i]->Gstate != WEAK)
                        count++;
                }
                if(count == n)
                {
                    al_set_sample_instance_playing(music[invincible], false);
                }
                for(i = 0; i < n; i++)
                {
                    while(!arg[i]->is_pause);
                }
                if(elf->pixel_x % 30 == 0 && elf->pixel_y % 30 == 0)
                {
                    elf->dir = dir;
                }
                if(ev.timer.count % 240 == 0)
                {
                    if(change_time != 0)
                        change_time--;
                    for(i = 0; i < n; i++)
                    {
                        if(dead_time[i] != 0)
                            dead_time[i]--;
                    }
                    if(extra_class != 0)
                        extra_class--;
                    if(slow_time != 0)
                        slow_time--;
                }
                if(ev.timer.count % 120 == 0)
                {
                    if(eat_time != 0)
                        eat_time--;
                }
                if(ev.timer.count % elf_move_time == 0)
                {
                    if(Detect_Eaten(elf, Map, n, ghost, &change_time, dead_time, &elf_move_time,&slow_time, &book, &in_score, point_score, music))
                    {
                        eat_time = 1;
                    }
                    Elf_Move(elf, col, Map, game_bitmap, eat_time);
                }
                for(i = 0; i < n; i++)
                {
                    if(current[i]->Gstate != CHANGING && current[i]->Gstate != WEAK && ev.timer.count % 2 == 0)
                    {
                        if(current[i]->Gstate != NOTHING)
                            current[i] = Ghost_Move(row, col, Map, &ghost[i], game_bitmap);
                        else
                        {
                            while(ghost[i]->next != NULL)
                            {
                                pop(&ghost[i]);
                            }
                            current[i] = ghost[i];
                        }
                    }
                    if(current[i]->Gstate != NORMAL && ev.timer.count % 3 == 0)
                    {
                        if(current[i]->Gstate != NOTHING)
                            current[i] = Ghost_Move(row, col, Map, &ghost[i], game_bitmap);
                        else
                        {
                            while(ghost[i]->next != NULL)
                            {
                                pop(&ghost[i]);
                            }
                            current[i] = ghost[i];
                        }
                    }
                }
                if(extra_class == 0)
                {
                    book = Create_Book(current[3], book);
                }
                Show_Book(book, game_bitmap);
                if(slow_time == 0)
                {
                    elf_move_time = 2;
                }
                if(elf->dir == RIGHT)
                {
                    al_draw_bitmap(game_bitmap[elf->state], elf->pixel_x, elf->pixel_y, 1);
                }
                else
                {
                    al_draw_bitmap(game_bitmap[elf->state], elf->pixel_x, elf->pixel_y, 0);
                }
                for(i = 0; i < n; i++)
                {
                    Show_Ghost(current[i], change_time, ev.timer.count, dead_time[i], game_bitmap,music);
                }
                for(i = 0; i < n; i++)
                {
                    if(current[i]->Gstate == NORMAL)
                    {
                        if(abs(current[i]->pixel_x - elf->pixel_x) < 10 && abs(current[i]->pixel_y - elf->pixel_y) < 10)
                        {
                            if(in_score >= 60)
                                play_state = WIN;
                            else
                                play_state = LOSE;
                        }
                    }
                }
                if(in_score >= 100 || !Count_Point(row, col, Map))
                        play_state = WIN;
                al_flip_display();
                break;
            }
        }

    }

    if(in_score >= 100)
    {
        in_score = 100;
    }
    *score = in_score + *score;

    Stop_Music(music);

    for(i = 0; i < n; i++)
    {
        free_thread(&Track_Thread[i], arg[i]->cond, (void**)(&arg[i]));
    }
    free_thread(&Time_Thread, game_time->cond, ((void**)(&game_time)));
    al_destroy_font(FONT2);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_q);
    free_book(&book);
    return play_state;
}

int Count_Point(int row, int col, Object **Map)
{
    int i, j, count = 0;
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            if(Map[i][j].state == point)
                count++;
        }
    }
    return count;
}

void *Count_Time(ALLEGRO_THREAD *timer, void *data)
{
    TimeThreads *time = (TimeThreads*) data;
    int clock1;
    clock1 = clock();

    while(!al_get_thread_should_stop(timer))
    {
        al_lock_mutex(time->mutex);
        switch(time->is_pause)
        {
        case 0:
            if(clock()-clock1 != 0)
            {
                *(time->time) = *(time->time) + clock()-clock1;
                clock1 = clock();
            }
            break;
        case 1:
            al_wait_cond(time->cond, time->mutex);
            printf("time pause\n");
            clock1 = clock();
            break;
        }
        al_unlock_mutex(time->mutex);
    }

    return (void*)time;
}
