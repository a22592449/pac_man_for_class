#include "main_header.h"

void Select_Elf_Dir(ALLEGRO_KEYBOARD_EVENT KBstate, Object *elf, int *dir)
{
    if(KBstate.keycode == ALLEGRO_KEY_UP)
    {
        *dir = UP;
    }
    if(KBstate.keycode == ALLEGRO_KEY_DOWN)
    {
        *dir = DOWN;
    }
    if(KBstate.keycode == ALLEGRO_KEY_LEFT)
    {
        *dir = LEFT;
    }
    if(KBstate.keycode == ALLEGRO_KEY_RIGHT)
    {
        *dir = RIGHT;
    }
}

void Elf_Move(Object *elf, int col, Object **Map, ALLEGRO_BITMAP **game_bitmap, int eat_time)
{
    if(elf->pixel_x <= -15)
    {
        elf->pixel_x = col * 30 - 15;
        elf->x = col - 1;
    }
    else if(elf->pixel_x >= col * 30 - 15)
    {
        elf->pixel_x = -15;
        elf->x = 0;
    }
    if(elf->dir == UP)
    {
        if(elf->state != elf_back)
        {
            elf->state = elf_back;
        }
        if(Map[elf->y-1][elf->x].state != 0)
        {
            elf->pixel_y--;
            elf->y = (elf->pixel_y-1)/30 + 1;
        }

    }
    else
    {
        if(!eat_time)
        {
            elf->state = elf_front;
        }
        else
        {
            elf->state = elf_eat;
        }

        if(elf->dir == DOWN)
        {
            if(Map[elf->y+1][elf->x].state != 0)
            {
                elf->pixel_y++;
                elf->y = elf->pixel_y/30;
            }
        }
        if(elf->dir == RIGHT)
        {
            if(Map[elf->y][elf->x+1].state != 0 || elf->x == col - 1)
            {
                elf->pixel_x++;
                elf->x = elf->pixel_x/30;
            }
        }
        if(elf->dir == LEFT)
        {
            if(Map[elf->y][elf->x-1].state != 0)
            {
                elf->pixel_x--;
                elf->x = (elf->pixel_x-1)/30 + 1;
            }
        }
    }
}

int Detect_Eaten(Object *elf, Object **Map, int n, Object **ghost, int *change_time, int *dead_time, int *elf_move_time, int *slow_time, Object **book, double *in_score, double point_score, ALLEGRO_SAMPLE_INSTANCE **music)
{
    int i, eat_flag = 0;
    Object *current[n], *previous = NULL, *now = NULL;

    if(book != NULL)
        now = *book;

    for(i = 0; i < n; i++)
    {
        current[i] = ghost[i];
        while(current[i]->next != NULL)
        {
            current[i] = current[i]->next;
        }
    }

    for(i = 0; i < n; i++)
    {
        if(current[i]->Gstate == WEAK || current[i]->Gstate == CHANGING)
        {
            if(abs(current[i]->pixel_x - elf->pixel_x) < 10 && abs(current[i]->pixel_y - elf->pixel_y) < 10)
            {
                current[i]->dir = -1;
                current[i]->Gstate = NOTHING;
                current[i]->x = current[i]->init_x;
                current[i]->y = current[i]->init_y;
                current[i]->pixel_x = 30 * current[i]->x;
                current[i]->pixel_y = 30 * current[i]->y;
                dead_time[i] = 5;
                *in_score = *in_score + 5;
                eat_flag = 1;
            }
        }
    }
    while(now != NULL)
    {
        if(abs(now->pixel_x - elf->pixel_x) < 5 && abs(now->pixel_y - elf->pixel_y) < 5)
        {
            if(now == *book)
            {
                *book = (*book)->next;
                free(now);
                now = NULL;
            }
            else
            {
                previous->next = now->next;
                free(now);
                now = NULL;
            }
            *elf_move_time = 3;
            *slow_time = 5;
            al_set_sample_instance_playing(music[desk], true);
            *in_score = *in_score + 5;
            eat_flag = 1;
        }
        else
        {
            previous = now;
            now = now->next;
        }
    }

    if(Map[elf->y][elf->x].state == point)
    {
        Map[elf->y][elf->x].state = -1;
        *in_score = *in_score + point_score;
        al_play_sample(al_get_sample(music[write]), al_get_sample_instance_gain(music[write]), al_get_sample_instance_pan(music[write]),
                       al_get_sample_instance_speed(music[write]), ALLEGRO_PLAYMODE_ONCE, NULL);
        eat_flag = 1;
    }
    if(elf->dir == UP)
    {
        if(elf->pixel_y - Map[elf->y-1][elf->x].pixel_y < 5)
        {
            if(Map[elf->y-1][elf->x].state == point)
            {
                Map[elf->y-1][elf->x].state = -1;
                if(slow_time != NULL && *slow_time != 0)
                {
                    *in_score = *in_score + point_score*2;
                }
                else
                {
                    *in_score = *in_score + point_score;
                }
                al_play_sample(al_get_sample(music[write]), al_get_sample_instance_gain(music[write]), al_get_sample_instance_pan(music[write]),
                               al_get_sample_instance_speed(music[write]), ALLEGRO_PLAYMODE_ONCE, NULL);
                eat_flag = 1;
            }
            if(Map[elf->y-1][elf->x].state == big_point)
            {
                Map[elf->y-1][elf->x].state = -1;
                for(i = 0; i < n; i++)
                {
                    if(current[i]->Gstate != NOTHING)
                        current[i]->Gstate = WEAK;
                }
                *change_time = 9;
                al_set_sample_instance_playing(music[paper], true);
                al_set_sample_instance_playing(music[invincible], true);
                eat_flag = 1;
            }
        }
    }
    if(elf->dir == DOWN)
    {
        if(Map[elf->y+1][elf->x].pixel_y - elf->pixel_y < 5)
        {
            if(Map[elf->y+1][elf->x].state == point)
            {
                Map[elf->y+1][elf->x].state = -1;
                if(slow_time != NULL && *slow_time != 0)
                {
                    *in_score = *in_score + point_score*2;
                }
                else
                {
                    *in_score = *in_score + point_score;
                }
                al_play_sample(al_get_sample(music[write]), al_get_sample_instance_gain(music[write]), al_get_sample_instance_pan(music[write]),
                               al_get_sample_instance_speed(music[write]), ALLEGRO_PLAYMODE_ONCE, NULL);
                eat_flag = 1;
            }
            if(Map[elf->y+1][elf->x].state == big_point)
            {
                Map[elf->y+1][elf->x].state = -1;
                for(i = 0; i < n; i++)
                {
                    if(current[i]->Gstate != NOTHING)
                        current[i]->Gstate = WEAK;
                }
                *change_time = 9;
                al_set_sample_instance_playing(music[paper], true);
                al_set_sample_instance_playing(music[invincible], true);
                eat_flag = 1;
            }
        }
    }
    if(elf->dir == RIGHT)
    {
        if(Map[elf->y][elf->x+1].pixel_x - elf->pixel_x < 5)
        {
            if(Map[elf->y][elf->x+1].state == point)
            {
                Map[elf->y][elf->x+1].state = -1;
                if(slow_time != NULL && *slow_time != 0)
                {
                    *in_score = *in_score + point_score*2;
                }
                else
                {
                    *in_score = *in_score + point_score;
                }
                al_play_sample(al_get_sample(music[write]), al_get_sample_instance_gain(music[write]), al_get_sample_instance_pan(music[write]),
                               al_get_sample_instance_speed(music[write]), ALLEGRO_PLAYMODE_ONCE, NULL);
                eat_flag = 1;
            }
            if(Map[elf->y][elf->x+1].state == big_point)
            {
                Map[elf->y][elf->x+1].state = -1;
                for(i = 0; i < n; i++)
                {
                    if(current[i]->Gstate != NOTHING)
                        current[i]->Gstate = WEAK;
                }
                *change_time = 9;
                al_set_sample_instance_playing(music[paper], true);
                al_set_sample_instance_playing(music[invincible], true);
                eat_flag = 1;
            }
        }
    }
    if(elf->dir == LEFT)
    {
        if(elf->pixel_x - Map[elf->y][elf->x-1].pixel_x < 5)
        {
            if(Map[elf->y][elf->x-1].state == point)
            {
                Map[elf->y][elf->x-1].state = -1;
                if(slow_time != NULL && *slow_time != 0)
                {
                    *in_score = *in_score + point_score*2;
                }
                else
                {
                    *in_score = *in_score + point_score;
                }
                al_play_sample(al_get_sample(music[write]), al_get_sample_instance_gain(music[write]), al_get_sample_instance_pan(music[write]),
                               al_get_sample_instance_speed(music[write]), ALLEGRO_PLAYMODE_ONCE, NULL);
                eat_flag = 1;
            }
            if(Map[elf->y][elf->x-1].state == big_point)
            {
                Map[elf->y][elf->x-1].state = -1;
                for(i = 0; i < n; i++)
                {
                    if(current[i]->Gstate != NOTHING)
                        current[i]->Gstate = WEAK;
                }
                *change_time = 9;
                al_set_sample_instance_playing(music[paper], true);
                al_set_sample_instance_playing(music[invincible], true);
                eat_flag = 1;
            }
        }
    }
    return eat_flag;
}
