#include "main_header.h"

PLAY_State menu(ALLEGRO_SAMPLE_INSTANCE **music, AudioMode *audio_state)
{
    int play = 0;
    PLAY_State play_state = MENU;
    ALLEGRO_BITMAP *menu = NULL, *button = NULL, *button2 = NULL, *setting_button = NULL, *setting_button2 = NULL, *sp = NULL;
    ALLEGRO_FONT *font;
    ALLEGRO_COLOR WHITE, GRAY;
    ALLEGRO_EVENT_QUEUE *event_q;
    ALLEGRO_EVENT ev;
    ALLEGRO_SAMPLE *pick;

    event_q = al_create_event_queue();

    pick = al_load_sample("./music/point.wav");
    font = al_load_font("./Font/ARCHRISTY.ttf", 50, 0);

    menu = al_load_bitmap("./menu/menu.png");
    button = al_load_bitmap("./menu/button.png");
    button2 = al_load_bitmap("./menu/button2.png");
    setting_button = al_load_bitmap("./menu/setting_button.png");
    setting_button2 = al_load_bitmap("./menu/setting_button2.png");

    WHITE = al_map_rgb(225, 215, 205);
    GRAY = al_map_rgb(128, 128, 105);

    al_register_event_source(event_q, al_get_display_event_source(al_get_current_display()));
    al_register_event_source(event_q, al_get_mouse_event_source());

    al_set_sample_instance_playing(music[menu_music], true);

    while(play_state == MENU)
    {
        al_draw_bitmap(menu, 0, 0, 0);
        draw_special(ev.mouse, &sp);

        draw_bitmap(setting_button2, setting_button, ev.mouse, 1050, 1000, 300, 250, 1000, 250, 0);
        draw_bitmap(button2, button, ev.mouse, 1200, 1000, 405, 345, 1000, 345, 0);
        draw_bitmap(button2, button, ev.mouse, 1200, 1000, 505, 445, 1000, 445, 0);
        draw_bitmap(button2, button, ev.mouse, 1200, 1000, 605, 545, 1000, 545, 0);
        draw_bitmap(button2, button, ev.mouse, 1200, 1000, 705, 645, 1000, 645, 0);
        draw_text(font, GRAY, WHITE, ev.mouse, 1200, 1000, 405, 345, 1100, 345, ALLEGRO_ALIGN_CENTRE, "Play");
        draw_text(font, GRAY, WHITE, ev.mouse, 1200, 1000, 505, 445, 1100, 445, ALLEGRO_ALIGN_CENTRE, "RULE");
        draw_text(font, GRAY, WHITE, ev.mouse, 1200, 1000, 605, 545, 1100, 545, ALLEGRO_ALIGN_CENTRE, "RECORD");
        draw_text(font, GRAY, WHITE, ev.mouse, 1200, 1000, 705, 645, 1100, 645, ALLEGRO_ALIGN_CENTRE, "Exit");

        if(ev.mouse.x >= 1000 && ev.mouse.x <= 1200 && ((ev.mouse.y >= 445 && ev.mouse.y <= 505) || (ev.mouse.y >= 545 && ev.mouse.y <= 605) ||
                (ev.mouse.y >= 345 && ev.mouse.y <= 405) || (ev.mouse.y >= 645 && ev.mouse.y <= 705)))
        {
            if(play == 0)
            {
                al_play_sample(pick, audio_state->all_gain * audio_state->se_gain, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                play = 1;
            }
        }
        else
        {
            play = 0;
        }

        al_flip_display();
        al_wait_for_event(event_q, &ev);
        switch(ev.type)
        {
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            if(ev.mouse.button & 1)
            {
                printf("mouse position: (X:%d, Y:%d)\n", ev.mouse.x, ev.mouse.y);

                if(ev.mouse.x >= 1000 && ev.mouse.x <= 1050 && ev.mouse.y >= 250 && ev.mouse.y <= 300)
                {
                    al_pause_event_queue(event_q, true);
                    voice_control(audio_state, music, &play_state);
                    al_pause_event_queue(event_q, false);
                }
                if(ev.mouse.x >= 1000 && ev.mouse.x <= 1200 && ev.mouse.y >= 345 && ev.mouse.y <= 405)
                {
                    play_state = SELECT;
                }
                if(ev.mouse.x >= 1000 && ev.mouse.x <= 1200 && ev.mouse.y >= 445 && ev.mouse.y <= 505)
                {
                    play_state = RULE;
                }
                if(ev.mouse.x >= 1000 && ev.mouse.x <= 1200 && ev.mouse.y >= 545 && ev.mouse.y <= 605)
                {
                    play_state = LEADERBOARD;
                }
                if(ev.mouse.x >= 1000 && ev.mouse.x <= 1200 && ev.mouse.y >= 645 && ev.mouse.y <= 705)
                {
                    play_state = FINISH;
                }
            }
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            play_state = FINISH;
            break;
        }
    }
    al_destroy_bitmap(button);
    al_destroy_bitmap(button2);
    al_destroy_bitmap(setting_button);
    al_destroy_bitmap(setting_button2);
    al_destroy_bitmap(menu);
    al_destroy_event_queue(event_q);
    al_destroy_sample(pick);
    return play_state;
}

void Draw_Map(int row, int col, Object **Map, ALLEGRO_BITMAP **game_bitmap)   //顯示圖片//
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            if(Map[i][j].state != -1)
                al_draw_bitmap(game_bitmap[Map[i][j].state], 30*j, 30*i, 0);
        }
    }
}

void voice_control(AudioMode *audio_state, ALLEGRO_SAMPLE_INSTANCE **instance, PLAY_State *play_state)
{
    int finish = 0, display_w, display_h;
    ALLEGRO_MOUSE_STATE mouse;
    ALLEGRO_BITMAP *frame = NULL, *point2 = NULL, *line = NULL, *backbuffer = NULL, *setting = NULL, *speaker = NULL, *nospeaker = NULL;
    ALLEGRO_FONT *font, *font2;
    ALLEGRO_COLOR BLACK, SNOW_WHITE, ORANGE;
    ALLEGRO_EVENT_QUEUE *event_q;
    ALLEGRO_EVENT ev;

    display_h = (al_get_display_height(al_get_current_display())-270)/2;
    display_w = (al_get_display_width(al_get_current_display())-550)/2;

    event_q = al_create_event_queue();

    font = al_load_font("./Font/BAUHS93.TTF", 30, 0);
    font2 = al_load_font("./Font/LBRITE.TTF", 20, 0);
    frame = al_load_bitmap("./audio_img/frame.png");
    line = al_load_bitmap("./audio_img/line.png");
    point2 = al_load_bitmap("./audio_img/point2.png");
    speaker = al_load_bitmap("./audio_img/speaker.png");
    nospeaker = al_load_bitmap("./audio_img/nospeaker.png");
    setting = al_load_bitmap("./audio_img/setting.png");

    backbuffer = al_get_backbuffer(al_get_current_display());

    BLACK = al_map_rgb(0, 0, 0);
    SNOW_WHITE = al_map_rgb(255, 250, 250);
    ORANGE = al_map_rgb(255, 128, 0);

    al_draw_tinted_bitmap(backbuffer, al_map_rgb(100, 100, 100), 0, 0, 0);
    al_draw_bitmap(setting, display_w, display_h, 0);
    al_draw_text(font, SNOW_WHITE, display_w + 40, display_h + 2, ALLEGRO_ALIGN_LEFT, "Setting");
    al_draw_bitmap(frame, display_w + 35, display_h + 50, 0);
    al_draw_text(font, BLACK, display_w + 48, display_h + 60, ALLEGRO_ALIGN_LEFT, "ALL Volume:");
    al_draw_bitmap(line, display_w + 235, display_h + 55, 0);
    al_draw_bitmap(point2, (audio_state->all_gain)*100 + display_w + 228, display_h + 73, 0);

    al_draw_bitmap(frame, display_w + 35, display_h + 120, 0);
    al_draw_text(font, BLACK, display_w + 48, display_h + 130, ALLEGRO_ALIGN_LEFT, "BGM Volume:");
    al_draw_bitmap(line, display_w + 235, display_h + 125, 0);
    al_draw_bitmap(point2, (audio_state->bgm_gain)*100 + display_w + 228, display_h + 143, 0);

    al_draw_bitmap(frame, display_w + 35, display_h + 190, 0);
    al_draw_text(font, BLACK, display_w + 68, display_h + 200, ALLEGRO_ALIGN_LEFT, "SE Volume:");
    al_draw_bitmap(line, display_w + 235, display_h + 195, 0);
    al_draw_bitmap(point2, (audio_state->se_gain)*100 + display_w + 228, display_h + 213, 0);

    al_register_event_source(event_q, al_get_display_event_source(al_get_current_display()));
    al_register_event_source(event_q, al_get_mouse_event_source());
    al_register_event_source(event_q, al_get_keyboard_event_source());

    while(!finish)
    {
        al_get_mouse_state(&mouse);
        al_draw_bitmap_region(frame,306, 5, 60, 30, display_w + 348, display_h + 60, 0);
        al_draw_textf(font, BLACK, display_w + 348, display_h + 60, ALLEGRO_ALIGN_LEFT, "%d", (int) (100 * (audio_state->all_gain)));
        al_draw_bitmap_region(frame,306, 5, 60, 30, display_w + 348, display_h + 130, 0);
        al_draw_textf(font, BLACK, display_w + 348, display_h + 130, ALLEGRO_ALIGN_LEFT, "%d", (int) (100 * (audio_state->bgm_gain)));
        al_draw_bitmap_region(frame,306, 5, 60, 30, display_w + 348, display_h + 200, 0);
        al_draw_textf(font, BLACK, display_w + 348, display_h + 200, ALLEGRO_ALIGN_LEFT, "%d", (int) (100 * (audio_state->se_gain)));

        if(*play_state != MENU)
        {
            al_draw_bitmap_region(setting, 460, 108, 80, 20, display_w + 460, display_h + 108, 0);
            al_draw_bitmap_region(setting, 460, 180, 80, 20, display_w + 460, display_h + 180, 0);
            if(mouse.x >= display_w + 460 && mouse.x <= display_w + 540 && mouse.y >= display_h + 108 && mouse.y <= display_h + 128)
            {
                al_draw_text(font2, ORANGE, display_w + 500, display_h + 105, ALLEGRO_ALIGN_CENTER,"Resume");
            }
            else
            {
                al_draw_text(font2, SNOW_WHITE, display_w + 500, display_h + 105, ALLEGRO_ALIGN_CENTER,"Resume");
            }
            if(mouse.x >= display_w + 460 && mouse.x <= display_w + 540 && mouse.y >= display_h + 180 && mouse.y <= display_h + 200)
            {
                al_draw_text(font2, ORANGE, display_w + 500, display_h + 180, ALLEGRO_ALIGN_CENTER,"Menu");
            }
            else
            {
                al_draw_text(font2, SNOW_WHITE, display_w + 500, display_h + 180, ALLEGRO_ALIGN_CENTER,"Menu");
            }
        }


        if(audio_state->all_play == 1)
        {
            al_draw_bitmap_region(setting, 415, 55, 50, 50, display_w + 415, display_h + 55, 0);
            al_draw_bitmap(speaker, display_w + 415, display_h + 55, 0);
        }
        else
        {
            al_draw_bitmap(nospeaker, display_w + 415, display_h + 55, 0);
        }
        if(audio_state->bgm_play == 1 && audio_state->all_play != 0)
        {
            al_draw_bitmap_region(setting, 415, 55, 50, 50, display_w + 415, display_h + 125, 0);
            al_draw_bitmap(speaker, display_w + 415, display_h + 125, 0);
        }
        else
        {
            al_draw_bitmap(nospeaker, display_w + 415, display_h + 125, 0);
        }
        if(audio_state->se_play == 1 && audio_state->all_play != 0)
        {
            al_draw_bitmap_region(setting, 415, 55, 50, 50, display_w + 415, display_h + 195, 0);
            al_draw_bitmap(speaker, display_w + 415, display_h + 195, 0);
        }
        else
        {
            al_draw_bitmap(nospeaker, display_w + 415, display_h + 195, 0);
        }
        al_flip_display();
        al_wait_for_event(event_q, &ev);
        switch(ev.type)
        {
        case ALLEGRO_EVENT_KEY_CHAR:
            if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                finish = 1;
            }
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            finish = 1;
            *play_state = FINISH;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            if(ev.mouse.button & 1)
            {
                if(ev.mouse.x >= display_w + 515 && ev.mouse.x <= display_w + 543 && ev.mouse.y >= display_h + 7 && ev.mouse.y <= display_h + 34)
                {
                    finish = 1;
                }
                if(*play_state != MENU)
                {
                    if(mouse.x >= display_w + 460 && mouse.x <= display_w + 540 && mouse.y >= display_h + 108 && mouse.y <= display_h + 128)
                    {
                        finish = 1;
                    }
                    if(mouse.x >= display_w + 460 && mouse.x <= display_w + 540 && mouse.y >= display_h + 180 && mouse.y <= display_h + 200)
                    {
                        *play_state = MENU;
                        finish = 1;
                    }
                }
                if(ev.mouse.x >= display_w + 415 && ev.mouse.x <= display_w + 465 && ev.mouse.y >= display_h + 55 && ev.mouse.y <= display_h + 105)
                {
                    if(audio_state->all_play)
                    {
                        audio_state->all_play = 0;

                        audio_state->saved_all = audio_state->all_gain;
                        audio_state->all_gain = 0;

                        if(audio_state->bgm_play)
                        {
                            audio_state->saved_bgm = audio_state->bgm_gain;
                            audio_state->bgm_gain = 0;
                        }

                        if(audio_state->se_play)
                        {
                            audio_state->saved_se = audio_state->se_gain;
                            audio_state->se_gain = 0;
                        }
                        al_draw_bitmap_region(frame,193, 5, 117, 50, display_w + 228, display_h + 55, 0);
                        al_draw_bitmap(line, display_w + 235, display_h + 55, 0);
                        al_draw_bitmap(point2, display_w + 228, display_h + 73, 0);

                        al_draw_bitmap_region(frame,193, 5, 117, 50, display_w + 228, display_h + 125, 0);
                        al_draw_bitmap(line, display_w + 235, display_h + 125, 0);
                        al_draw_bitmap(point2, display_w + 228, display_h + 143, 0);

                        al_draw_bitmap_region(frame,193, 5, 117, 50, display_w + 228, display_h + 195, 0);
                        al_draw_bitmap(line, display_w + 235, display_h + 195, 0);
                        al_draw_bitmap(point2, display_w + 228, display_h + 213, 0);
                    }
                    else
                    {
                        audio_state->all_play = 1;
                        audio_state->all_gain = audio_state->saved_all;
                        if(audio_state->bgm_play)
                        {
                            audio_state->bgm_gain = audio_state->saved_bgm;
                        }
                        if(audio_state->se_play)
                        {
                            audio_state->se_gain = audio_state->saved_se;
                        }
                        al_draw_bitmap_region(frame,193, 5, 117, 50, display_w + 228, display_h + 55, 0);
                        al_draw_bitmap(line, display_w + 235, display_h + 55, 0);
                        al_draw_bitmap(point2, (audio_state->all_gain)*100 + display_w + 228, display_h + 73, 0);

                        al_draw_bitmap_region(frame,193, 5, 117, 50, display_w + 228, display_h + 125, 0);
                        al_draw_bitmap(line, display_w + 235, display_h + 125, 0);
                        al_draw_bitmap(point2, (audio_state->bgm_gain)*100 + display_w + 228, display_h + 143, 0);

                        al_draw_bitmap_region(frame,193, 5, 117, 50, display_w + 228, display_h + 195, 0);
                        al_draw_bitmap(line, display_w + 235, display_h + 195, 0);
                        al_draw_bitmap(point2, (audio_state->se_gain)*100 + display_w + 228, display_h + 213, 0);
                    }
                }
                else if(ev.mouse.x >= display_w + 415 && ev.mouse.x <= display_w + 465 && ev.mouse.y >= display_h + 125 && ev.mouse.y <= display_h + 175)
                {
                    if(audio_state->all_play)
                    {
                        if(audio_state->bgm_play)
                        {
                            audio_state->bgm_play = 0;
                            audio_state->saved_bgm = audio_state->bgm_gain;
                            audio_state->bgm_gain = 0;
                            al_draw_bitmap_region(frame,193, 5, 117, 50, display_w + 228, display_h + 125, 0);
                            al_draw_bitmap(line, display_w + 235, display_h + 125, 0);
                            al_draw_bitmap(point2, display_w + 228, display_h + 143, 0);
                        }
                        else
                        {
                            audio_state->bgm_play = 1;
                            audio_state->bgm_gain = audio_state->saved_bgm;
                            al_draw_bitmap_region(frame,193, 5, 117, 50, display_w + 228, display_h + 125, 0);
                            al_draw_bitmap(line, display_w + 235, display_h + 125, 0);
                            al_draw_bitmap(point2, (audio_state->bgm_gain)*100 + display_w + 228, display_h + 143, 0);
                        }
                    }

                }
                else if(ev.mouse.x >= display_w + 415 && ev.mouse.x <= display_w + 465 && ev.mouse.y >= display_h + 195 && ev.mouse.y <= display_h + 245)
                {
                    if(audio_state->all_play)
                    {
                        if(audio_state->se_play)
                        {
                            audio_state->se_play = 0;
                            audio_state->saved_se = audio_state->se_gain;
                            audio_state->se_gain = 0;
                            al_draw_bitmap_region(frame,193, 5, 117, 50, display_w + 228, display_h + 195, 0);
                            al_draw_bitmap(line, display_w + 235, display_h + 195, 0);
                            al_draw_bitmap(point2, display_w + 228, display_h + 213, 0);
                        }
                        else
                        {
                            audio_state->se_play = 1;
                            audio_state->se_gain = audio_state->saved_se;
                            al_draw_bitmap_region(frame,193, 5, 117, 50, display_w + 228, display_h + 195, 0);
                            al_draw_bitmap(line, display_w + 235, display_h + 195, 0);
                            al_draw_bitmap(point2, (audio_state->se_gain)*100 + display_w + 228, display_h + 213, 0);
                        }
                    }
                }
                printf("mouse position: (X:%d, Y:%d)\n", ev.mouse.x, ev.mouse.y);
            }
            break;

        }
        if(mouse.buttons & 1)
        {
            if(mouse.x >= display_w + 235 && mouse.x <= display_w + 335 && mouse.y >= display_h + 50  && mouse.y <= display_h + 110 && audio_state->all_play != 0)
            {
                al_draw_bitmap_region(frame,193, 5, 117, 50, display_w + 228, display_h + 55, 0);
                al_draw_bitmap(line, display_w + 235, display_h + 55, 0);
                al_draw_bitmap(point2, mouse.x - 7, display_h + 73, 0);
                audio_state->all_gain = 1.0*(mouse.x-(display_w + 235))/100;
                printf("gain = %f\n", audio_state->all_gain);
            }
            else if(mouse.x >= display_w + 235 && mouse.x <= display_w + 335 && mouse.y >= display_h + 125 && mouse.y <= display_h + 185 && audio_state->bgm_play && audio_state->all_play)
            {
                al_draw_bitmap_region(frame,193, 5, 117, 50, display_w + 228, display_h + 125, 0);
                al_draw_bitmap(line, display_w + 235, display_h + 125, 0);
                al_draw_bitmap(point2, mouse.x - 7, display_h + 143, 0);
                audio_state->bgm_gain = 1.0*(mouse.x-(display_w + 235))/100;
                printf("bgm_gain = %f\n", audio_state->bgm_gain);
            }
            else if(mouse.x >= display_w + 235 && mouse.x <= display_w + 335 && mouse.y >= display_h + 195 && mouse.y <= display_h + 260 && audio_state->se_play && audio_state->all_play)
            {
                al_draw_bitmap_region(frame,193, 5, 117, 50, display_w + 228, display_h + 195, 0);
                al_draw_bitmap(line, display_w + 235, display_h + 195, 0);
                al_draw_bitmap(point2, mouse.x - 7, display_h + 213, 0);
                audio_state->se_gain = 1.0*(mouse.x-(display_w + 235))/100;
                printf("se_gain = %f\n", audio_state->se_gain);
            }
        }
        Set_Music_Gain(instance, *audio_state);
    }

    al_destroy_bitmap(frame);
    al_destroy_bitmap(line);
    al_destroy_bitmap(point2);
    al_destroy_bitmap(speaker);
    al_destroy_bitmap(nospeaker);
    al_destroy_bitmap(setting);
    al_destroy_font(font);
    al_destroy_font(font2);
}

PLAY_State leaderboard(GameMode game_mode)
{
    int i = 0, page = 0;
    PLAY_State play_state = LEADERBOARD;
    ALLEGRO_BITMAP *LB, *POINTER, *menu;
    ALLEGRO_FONT *FONT;
    ALLEGRO_EVENT_QUEUE *event_q;
    ALLEGRO_EVENT ev;
    ALLEGRO_COLOR white;

    FONT = al_load_ttf_font("./Font/Pixeboy-z8XGD.ttf", 40, 0);
    menu = al_load_bitmap("./menu/menu.png");
    LB = al_load_bitmap("./leaderboard/Leaderboard.png");
    POINTER = al_load_bitmap("./leaderboard/pointer.png");
    white = al_map_rgb(255, 255, 255);
    event_q = al_create_event_queue();

    al_register_event_source(event_q, al_get_mouse_event_source());
    al_register_event_source(event_q, al_get_display_event_source(al_get_current_display()));

    while(play_state == LEADERBOARD)
    {
        al_draw_tinted_bitmap(menu, al_map_rgb(50, 50, 50), 0, 0, 0);
        al_draw_bitmap(LB, 240, 75, 0);
        al_draw_text(FONT, white, 450, 190, 0, "Name");
        al_draw_text(FONT, white, 710, 190, 0, "Score");
        al_draw_text(FONT, white, 880, 190, 0, "Time");

        while(al_get_next_event(event_q, &ev))
        {
            switch(ev.type)
            {
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if(ev.mouse.button & 1)
                {
                    if(ev.mouse.x >= 930 && ev.mouse.x <= 1010 && ev.mouse.y >= 650 && ev.mouse.y <= 700 && page == 0)
                    {
                        page = 1;
                    }
                    if(ev.mouse.x >= 300 && ev.mouse.x <= 380 && ev.mouse.y >= 650 && ev.mouse.y <= 700 && page == 1)
                    {
                        page = 0;
                    }
                    if(ev.mouse.x >= 980 && ev.mouse.x <= 1013 && ev.mouse.y >= 93 && ev.mouse.y <= 129)
                    {
                        play_state = MENU;
                    }
                    if(ev.mouse.x >= 520 && ev.mouse.x <= 568 && ev.mouse.y >= 650 && ev.mouse.y <= 670)
                    {
                        game_mode.round = 0;
                    }
                    if(ev.mouse.x >= 590 && ev.mouse.x <= 638 && ev.mouse.y >= 650 && ev.mouse.y <= 670)
                    {
                        game_mode.round = 1;
                    }
                    if(ev.mouse.x >= 660 && ev.mouse.x <= 708 && ev.mouse.y >= 650 && ev.mouse.y <= 670)
                    {
                        game_mode.round = 2;
                    }
                    if(ev.mouse.x >= 730 && ev.mouse.x <= 778 && ev.mouse.y >= 650 && ev.mouse.y <= 670)
                    {
                        game_mode.round = 3;
                    }
                    if(ev.mouse.x >= 522 && ev.mouse.x <= 586 && ev.mouse.y >= 690 && ev.mouse.y <= 710)
                    {
                        game_mode.difficulty = 1;
                    }
                    if(ev.mouse.x >= 602 && ev.mouse.x <= 698 && ev.mouse.y >= 690 && ev.mouse.y <= 710)
                    {
                        game_mode.difficulty = 2;
                    }
                    if(ev.mouse.x >= 712 && ev.mouse.x <= 760 && ev.mouse.y >= 690 && ev.mouse.y <= 710)
                    {
                        game_mode.difficulty = 3;
                    }

                    printf("mouse position: (X:%d, Y:%d)\n", ev.mouse.x, ev.mouse.y);
                }
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                play_state = FINISH;
                break;
            }
        }
        if(page == 0)
        {
            if(ev.mouse.x >= 930 && ev.mouse.x <= 1010 && ev.mouse.y >= 650 && ev.mouse.y <= 700 && page == 0)
            {
                al_draw_tinted_bitmap(POINTER, al_map_rgb(150, 0, 0), 930, 650, 0);
            }
            else
            {
                al_draw_bitmap(POINTER, 930, 650, 0);
            }
            for(i = 0; i < 5; i++)
            {
                al_draw_line(290, (i+1)*80 + 150, 1010, (i+1)*80 + 150, al_map_rgb(255, 255, 255), 1);
                al_draw_line(680, 190, 680, 625, al_map_rgb(255, 255, 255), 1);
                al_draw_line(830, 190, 830, 625, al_map_rgb(255, 255, 255), 1);
                al_draw_textf(FONT, white, 290, (i+1)*80 + 180, 0, "%d.", i+1);
            }
        }
        if(page == 1)
        {
            if(ev.mouse.x >= 300 && ev.mouse.x <= 380 && ev.mouse.y >= 650 && ev.mouse.y <= 700 && page == 1)
            {
                al_draw_tinted_bitmap(POINTER, al_map_rgb(150, 0, 0), 300, 650, 1);
            }
            else
            {
                al_draw_bitmap(POINTER, 300, 650, 1);
            }
            for(i = 5; i < 10; i++)
            {
                al_draw_line(290, (i-4)*80 + 150, 1010, (i-4)*80 + 150, al_map_rgb(255, 255, 255), 1);
                al_draw_line(680, 190, 680, 625, al_map_rgb(255, 255, 255), 1);
                al_draw_line(830, 190, 830, 625, al_map_rgb(255, 255, 255), 1);
                al_draw_textf(FONT, white, 290, (i-4)*80 + 180, 0, "%d.", i+1);
            }
        }
        Leaderboard_Select(game_mode);
        Draw_player(page, FONT, white, game_mode);
        al_flip_display();
    }



    al_destroy_bitmap(LB);
    al_destroy_bitmap(menu);
    al_destroy_bitmap(POINTER);
    al_destroy_font(FONT);
    al_destroy_event_queue(event_q);
    return play_state;
}

PLAY_State User_Name(double score, int time, PLAY_State play_state, GameMode game_mode)
{
    int pos;
    ALLEGRO_EVENT_QUEUE *event_q;
    ALLEGRO_EVENT ev;
    ALLEGRO_USTR *name, *nothing;
    ALLEGRO_BITMAP *menu, *ranking;
    ALLEGRO_FONT *FONT, *FONT2, *FONT3;

    nothing = al_ustr_new("Please enter your name.");
    name = al_ustr_new("");
    pos = (int)al_ustr_size(name);
    menu = al_load_bitmap("./menu/menu.png");
    if(play_state == WIN)
    {
        ranking = al_load_bitmap("./leaderboard/win.png");
    }
    if(play_state == LOSE)
    {
        ranking = al_load_bitmap("./leaderboard/lose.png");
    }
    FONT = al_load_font("./Font/Pixeboy-z8XGD.ttf", 30, 0);
    FONT2 = al_load_font("./Font/Pixeboy-z8XGD.ttf", 35, 0);
    FONT3 = al_load_font("./Font/Pixeboy-z8XGD.ttf", 40, 0);
    event_q = al_create_event_queue();

    al_register_event_source(event_q, al_get_keyboard_event_source());
    al_register_event_source(event_q, al_get_mouse_event_source());
    al_register_event_source(event_q, al_get_display_event_source(al_get_current_display()));

    time = time / CLOCKS_PER_SEC;

    while(play_state == WIN || play_state == LOSE)
    {
        al_draw_bitmap(menu, 0, 0, 0);
        al_draw_bitmap(ranking, 700, 199, 0);
        al_draw_textf(FONT2, al_map_rgb(255, 255, 255), 800, 220, ALLEGRO_ALIGN_LEFT, "Your total score is: %.3lf", score);
        al_draw_textf(FONT2, al_map_rgb(255, 255, 255), 815, 290, ALLEGRO_ALIGN_LEFT, "The time you spent is: %d", time);
        if(play_state == WIN)
        {
            al_draw_text(FONT3, al_map_rgb(255, 0, 0), 710, 245, ALLEGRO_ALIGN_LEFT, "WINNER!!");
            al_draw_text(FONT3, al_map_rgb(0, 219, 0), 850, 350, ALLEGRO_ALIGN_LEFT, "Congratulations!");
            al_draw_text(FONT3, al_map_rgb(255, 255, 255), 880, 400, ALLEGRO_ALIGN_LEFT, "You can graduate");
            al_draw_text(FONT3, al_map_rgb(255, 255, 255), 1020, 450, ALLEGRO_ALIGN_LEFT, "from here!!");
        }
        else
        {
            al_draw_text(FONT3, al_map_rgb(0, 0, 255), 775, 445, ALLEGRO_ALIGN_LEFT, "WASTED!!");
            al_draw_text(FONT3, al_map_rgb(170, 170, 170), 850, 350, ALLEGRO_ALIGN_LEFT, "Sorry!");
            al_draw_text(FONT3, al_map_rgb(255, 255, 255), 980, 350, ALLEGRO_ALIGN_LEFT, "You can't");
            al_draw_text(FONT3, al_map_rgb(255, 255, 255), 920, 400, ALLEGRO_ALIGN_LEFT, "graduate from");
            al_draw_text(FONT3, al_map_rgb(255, 255, 255), 1100, 450, ALLEGRO_ALIGN_LEFT, "here!!");
        }
        if(strcmp((char*)name->data, "") == 0)
            al_draw_ustr(FONT, al_map_rgb(0, 0, 0), 740, 495, ALLEGRO_ALIGN_LEFT, nothing);
        else
            al_draw_ustr(FONT, al_map_rgb(0, 0, 0), 740, 495, ALLEGRO_ALIGN_LEFT, name);
        al_flip_display();
        al_wait_for_event(event_q, &ev);
        switch(ev.type)
        {
        case ALLEGRO_EVENT_KEY_CHAR:
            if(ev.keyboard.unichar >= 32 && pos < 20)
            {
                pos += al_ustr_append_chr(name, ev.keyboard.unichar);
            }
            else if(ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
            {
                if(al_ustr_prev(name, &pos))
                    al_ustr_truncate(name, pos);
            }
            else if((ev.keyboard.keycode == ALLEGRO_KEY_ENTER || ev.keyboard.keycode == ALLEGRO_KEY_PAD_ENTER) && strcmp((char*)name->data, ""))
            {
                Save_File((char*)name->data, score, time, game_mode);
                play_state = MENU ;
            }
            else if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                play_state = MENU;
            }
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            if(ev.mouse.x >= 1091 && ev.mouse.x <= 1124 && ev.mouse.y >= 487 && ev.mouse.y <= 521 && strcmp((char*)name->data, ""))
            {
                Save_File((char*)name->data, score, time, game_mode);
                play_state = MENU;
            }
            if(ev.mouse.x >= 1144 && ev.mouse.x <= 1177 && ev.mouse.y >= 487 && ev.mouse.y <= 521)
            {
                play_state = MENU;
            }
            printf("mouse position: (X:%d, Y:%d)\n", ev.mouse.x, ev.mouse.y);
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            play_state = FINISH;
        }
    }

    if(play_state != FINISH)
    {
        play_state = leaderboard(game_mode);
    }

    al_ustr_free(name);
    al_ustr_free(nothing);
    al_destroy_font(FONT);
    al_destroy_font(FONT2);
    al_destroy_event_queue(event_q);
    al_destroy_bitmap(menu);
    al_destroy_bitmap(ranking);
    return play_state;
}

PLAY_State Select_Mode (GameMode *game_mode)
{
    PLAY_State play_state = SELECT;
    ALLEGRO_BITMAP *menu = NULL, *game = NULL, *game1 = NULL, *game2 = NULL, *game3 = NULL, *frame = NULL, *frame2 = NULL,
                    *EAZY = NULL, *HARD = NULL, *NORMAL = NULL, *button = NULL;
    ALLEGRO_FONT *font;
    ALLEGRO_COLOR white;
    ALLEGRO_EVENT_QUEUE *event_q;
    ALLEGRO_EVENT ev;

    event_q = al_create_event_queue();

    font = al_load_font("./Font/cambriab.ttf", 50, 0);
    menu = al_load_bitmap("./menu/menu2.png");
    game = al_load_bitmap("./select_game/game.png");
    game1 = al_load_bitmap("./select_game/game1.png");
    game2 = al_load_bitmap("./select_game/game2.png");
    game3 = al_load_bitmap("./select_game/game3.png");
    frame = al_load_bitmap("./select_game/frame.png");
    frame2 = al_load_bitmap("./select_game/frame2.png");
    EAZY  = al_load_bitmap("./select_game/EAZY.png");
    NORMAL  = al_load_bitmap("./select_game/NORMAL.png");
    HARD  = al_load_bitmap("./select_game/HARD.png");
    button = al_load_bitmap("./select_game/button.png");
    white = al_map_rgb(255, 255, 255);

    al_register_event_source(event_q, al_get_display_event_source(al_get_current_display()));
    al_register_event_source(event_q, al_get_mouse_event_source());

    while(play_state == SELECT)
    {
        al_draw_bitmap(menu, 0, 0, 0);
        al_draw_text(font, white, 70, 80, 0, "all round");
        al_draw_bitmap(game, 32, 150, 0);
        al_draw_text(font, white, 375, 80, 0, "1st round");
        al_draw_bitmap(game1, 344, 150, 0);
        al_draw_text(font, white, 680, 80, 0, "2nd round");
        al_draw_bitmap(game2, 656, 150, 0);
        al_draw_text(font, white, 980, 80, 0, "3rd round");
        al_draw_bitmap(game3, 968, 150, 0);
        al_draw_bitmap(EAZY, 220, 500, 0);
        al_draw_bitmap(NORMAL, 550, 500, 0);
        al_draw_bitmap(HARD, 870, 500, 0);

        if(ev.mouse.x >= 1020 && ev.mouse.x <= 1220 && ev.mouse.y >= 575 && ev.mouse.y <= 635)
        {
            al_draw_tinted_bitmap(button, al_map_rgb(240, 50, 50), 1020, 575, 0);
        }
        else
        {
            al_draw_bitmap(button, 1020, 575, 0);
        }

        if(ev.mouse.x >= 1020 && ev.mouse.x <= 1220 && ev.mouse.y >= 655 && ev.mouse.y <= 715)
        {
            al_draw_tinted_bitmap(button, al_map_rgb(240, 50, 50), 1020, 655, 0);
        }
        else
        {
            al_draw_bitmap(button, 1020, 655, 0);
        }

        al_draw_text(font, al_map_rgb(0, 0, 0), 1025, 575, 0, "Confirm");
        al_draw_text(font, al_map_rgb(0, 0, 0), 1045, 655, 0, "Cancel");

        Draw_Frame(game_mode->round, frame, game_mode->difficulty, frame2, ev.mouse);
        al_flip_display();
        al_wait_for_event(event_q, &ev);
        switch(ev.type)
        {
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            if(ev.mouse.button & 1)
            {
                if(ev.mouse.x >= 32 && ev.mouse.x <= 312 && ev.mouse.y >= 150 && ev.mouse.y <= 430)
                {
                    if(game_mode->round != 0)
                        game_mode->round = 0;
                    else
                        game_mode->round = -1;
                }
                if(ev.mouse.x >= 344 && ev.mouse.x <= 624 && ev.mouse.y >= 150 && ev.mouse.y <= 430)
                {
                    if(game_mode->round != 1)
                        game_mode->round = 1;
                    else
                        game_mode->round = -1;
                }
                if(ev.mouse.x >= 656 && ev.mouse.x <= 936 && ev.mouse.y >= 150 && ev.mouse.y <= 430)
                {
                    if(game_mode->round != 2)
                        game_mode->round = 2;
                    else
                        game_mode->round = -1;
                }
                if(ev.mouse.x >= 968 && ev.mouse.x <= 1208 && ev.mouse.y >= 150 && ev.mouse.y <= 430)
                {
                    if(game_mode->round != 3)
                        game_mode->round = 3;
                    else
                        game_mode->round = -1;
                }
                if(ev.mouse.x >= 223 && ev.mouse.x <= 418 && ev.mouse.y >= 502 && ev.mouse.y <= 559)
                {
                    if(game_mode->difficulty != 1)
                        game_mode->difficulty = 1;
                    else
                        game_mode->difficulty = 0;
                }
                if(ev.mouse.x >= 553 && ev.mouse.x <= 748 && ev.mouse.y >= 502 && ev.mouse.y <= 559)
                {
                    if(game_mode->difficulty != 2)
                        game_mode->difficulty = 2;
                    else
                        game_mode->difficulty = 0;
                }
                if(ev.mouse.x >= 873 && ev.mouse.x <= 1068 && ev.mouse.y >= 502 && ev.mouse.y <= 559)
                {
                    if(game_mode->difficulty != 3)
                        game_mode->difficulty = 3;
                    else
                        game_mode->difficulty = 0;
                }
                if(ev.mouse.x >= 1020 && ev.mouse.x <= 1220 && ev.mouse.y >= 575 && ev.mouse.y <= 635)
                {
                    if(game_mode->round != -1 && game_mode->difficulty != 0)
                    {
                        if(game_mode->round == 0 || game_mode->round == 1)
                        {
                            if(game_mode->round == 0)
                            {
                                game_mode->play_all = 1;
                            }
                            play_state = GAME_1;
                        }
                        if(game_mode->round == 2)
                        {
                            play_state = GAME_2;
                        }
                        if(game_mode->round == 3)
                        {
                            play_state = GAME_3;
                        }
                    }
                    else
                    {
                        if(game_mode->round == -1 && game_mode->difficulty != 0)
                        {
                            al_show_native_message_box(al_get_current_display(), "Select round error", "Wrong", "please select your round", NULL, ALLEGRO_MESSAGEBOX_WARN);
                        }
                        if(game_mode->round != -1 && game_mode->difficulty == 0)
                        {
                            al_show_native_message_box(al_get_current_display(), "Select difficulty error", "Wrong", "please select your difficulty", NULL, ALLEGRO_MESSAGEBOX_WARN);
                        }
                        if(game_mode->round == -1 && game_mode->difficulty == 0)
                        {
                            al_show_native_message_box(al_get_current_display(), "Select error", "Wrong", "please select your difficulty and round", NULL, ALLEGRO_MESSAGEBOX_WARN);
                        }
                    }
                }
                if(ev.mouse.x >= 1020 && ev.mouse.x <= 1220 && ev.mouse.y >= 655 && ev.mouse.y <= 715)
                {
                    play_state = MENU;
                }

                printf("mouse position: (X:%d, Y:%d)\n", ev.mouse.x, ev.mouse.y);
                if(game_mode->round != -1 && game_mode->difficulty != 0)
                    printf("game = %d, difficulty = %d\n", game_mode->round, game_mode->difficulty);
            }
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            play_state = FINISH;
            break;
        }
    }
    al_destroy_event_queue(event_q);
    al_destroy_font(font);
    al_destroy_bitmap(menu);
    al_destroy_bitmap(game);
    al_destroy_bitmap(frame);
    al_destroy_bitmap(frame2);
    al_destroy_bitmap(game1);
    al_destroy_bitmap(game2);
    al_destroy_bitmap(game3);
    al_destroy_bitmap(EAZY);
    al_destroy_bitmap(NORMAL);
    al_destroy_bitmap(HARD);
    return play_state;
}

void Draw_Frame(int game, ALLEGRO_BITMAP *frame, int select, ALLEGRO_BITMAP *frame2, ALLEGRO_MOUSE_EVENT mouse)
{
    if(mouse.x >= 32 && mouse.x <= 312 && mouse.y >= 150 && mouse.y <= 430)
    {
        al_draw_bitmap(frame, 32, 150, 0);
    }
    if(mouse.x >= 344 && mouse.x <= 624 && mouse.y >= 150 && mouse.y <= 430)
    {
        al_draw_bitmap(frame, 344, 150, 0);
    }

    if(mouse.x >= 656 && mouse.x <= 936 && mouse.y >= 150 && mouse.y <= 430)
    {
        al_draw_bitmap(frame, 656, 150, 0);
    }

    if(mouse.x >= 968 && mouse.x <= 1208 && mouse.y >= 150 && mouse.y <= 430)
    {
        al_draw_bitmap(frame, 968, 150, 0);
    }
    if(mouse.x >= 223 && mouse.x <= 418 && mouse.y >= 502 && mouse.y <= 559)
    {
        al_draw_bitmap(frame2, 220, 500, 0);
    }
    if(mouse.x >= 553 && mouse.x <= 748 && mouse.y >= 502 && mouse.y <= 559)
    {
        al_draw_bitmap(frame2, 550, 500, 0);
    }
    if(mouse.x >= 873 && mouse.x <= 1068 && mouse.y >= 502 && mouse.y <= 559)
    {
        al_draw_bitmap(frame2, 870, 500, 0);
    }
    switch(game)
    {
    case 0:
        al_draw_bitmap(frame, 32, 150, 0);
        break;
    case 1:
        al_draw_bitmap(frame, 344, 150, 0);
        break;
    case 2:
        al_draw_bitmap(frame, 656, 150, 0);
        break;
    case 3:
        al_draw_bitmap(frame, 968, 150, 0);
        break;
    }
    switch(select)
    {
    case 1:
        al_draw_bitmap(frame2, 220, 500, 0);
        break;
    case 2:
        al_draw_bitmap(frame2, 550, 500, 0);
        break;
    case 3:
        al_draw_bitmap(frame2, 870, 500, 0);
        break;
    }
}

void Draw_player(int page, ALLEGRO_FONT *FONT, ALLEGRO_COLOR white, GameMode game_mode)
{
    int i = 0;
    Player player[10];
    char* filename[3];
    for(i = 0; i < 3; i++)
    {
        filename[i] = (char*)malloc(sizeof(char) * 45);
    }
    switch (game_mode.round)
    {
    case 0 :
    case -1:
        switch (game_mode.difficulty)
        {
        case 1:
            strcpy(filename[0], "./data/allround/player_name_easy.txt");
            strcpy(filename[1], "./data/allround/player_score_easy.txt");
            strcpy(filename[2], "./data/allround/time_easy.txt");
            break;
        case 2:
        case 0:
            strcpy(filename[0], "./data/allround/player_name_normal.txt");
            strcpy(filename[1], "./data/allround/player_score_normal.txt");
            strcpy(filename[2], "./data/allround/time_normal.txt");
            break;
        case 3:
            strcpy(filename[0], "./data/allround/player_name_hard.txt");
            strcpy(filename[1], "./data/allround/player_score_hard.txt");
            strcpy(filename[2], "./data/allround/time_hard.txt");
            break;
        }
        break;

    case 1:
        switch (game_mode.difficulty)
        {
        case 1:
            strcpy(filename[0], "./data/firstround/player_name_easy.txt");
            strcpy(filename[1], "./data/firstround/player_score_easy.txt");
            strcpy(filename[2], "./data/firstround/time_easy.txt");

            break;
        case 2:
        case 0:
            strcpy(filename[0], "./data/firstround/player_name_normal.txt");
            strcpy(filename[1], "./data/firstround/player_score_normal.txt");
            strcpy(filename[2], "./data/firstround/time_normal.txt");
            break;
        case 3:
            strcpy(filename[0], "./data/firstround/player_name_hard.txt");
            strcpy(filename[1], "./data/firstround/player_score_hard.txt");
            strcpy(filename[2], "./data/firstround/time_hard.txt");
            break;
        }
        break;

    case 2:
        switch (game_mode.difficulty)
        {
        case 1:
            strcpy(filename[0], "./data/secondround/player_name_easy.txt");
            strcpy(filename[1], "./data/secondround/player_score_easy.txt");
            strcpy(filename[2], "./data/secondround/time_easy.txt");
            break;
        case 2:
        case 0:
            strcpy(filename[0], "./data/secondround/player_name_normal.txt");
            strcpy(filename[1], "./data/secondround/player_score_normal.txt");
            strcpy(filename[2], "./data/secondround/time_normal.txt");
            break;
        case 3:
            strcpy(filename[0], "./data/secondround/player_name_hard.txt");
            strcpy(filename[1], "./data/secondround/player_score_hard.txt");
            strcpy(filename[2], "./data/secondround/time_hard.txt");
            break;
        }
        break;

    case 3:
        switch (game_mode.difficulty)
        {
        case 1:
            strcpy(filename[0], "./data/thirdround/player_name_easy.txt");
            strcpy(filename[1], "./data/thirdround/player_score_easy.txt");
            strcpy(filename[2], "./data/thirdround/time_easy.txt");
            break;
        case 2:
        case 0:
            strcpy(filename[0], "./data/thirdround/player_name_normal.txt");
            strcpy(filename[1], "./data/thirdround/player_score_normal.txt");
            strcpy(filename[2], "./data/thirdround/time_normal.txt");
            break;
        case 3:
            strcpy(filename[0], "./data/thirdround/player_name_hard.txt");
            strcpy(filename[1], "./data/thirdround/player_score_hard.txt");
            strcpy(filename[2], "./data/thirdround/time_hard.txt");
            break;
        }
        break;
    }

    Load_Player(player, filename);

    if(page == 0)
    {
        i = 0;
        while(player[i].name != NULL && player[i].score != -1 && player[i].time != -1 && i < 5)
        {
            al_draw_textf(FONT, white, 495, (i+1)*80 + 180, ALLEGRO_ALIGN_CENTRE, "%s", strtok(player[i].name, "\n"));
            al_draw_textf(FONT, white, 750, (i+1)*80 + 180, ALLEGRO_ALIGN_CENTRE, "%.3lf", player[i].score);
            al_draw_textf(FONT, white, 920, (i+1)*80 + 180, ALLEGRO_ALIGN_CENTRE, "%d", player[i].time);
            i++;
        }
    }
    if(page == 1)
    {

        i = 5;
        while(player[i].name != NULL && player[i].score != -1 && player[i].time != -1 && i < 10)
        {
            al_draw_textf(FONT, white, 495, (i-4)*80 + 180, ALLEGRO_ALIGN_CENTRE, "%s", strtok(player[i].name, "\n"));
            al_draw_textf(FONT, white, 750, (i-4)*80 + 180, ALLEGRO_ALIGN_CENTRE, "%.3lf", player[i].score);
            al_draw_textf(FONT, white, 920, (i-4)*80 + 180, ALLEGRO_ALIGN_CENTRE, "%d", player[i].time);
            i++;
        }
    }
    for(i = 0; i<3; i++)
    {
        free(filename[i]);
    }

    free_player(player, NULL);
}

void Leaderboard_Select(GameMode game_mode)
{
    ALLEGRO_COLOR WHITE, SKY_BLUE;
    ALLEGRO_FONT *FONT;

    FONT = al_load_ttf_font("./Font/Pixeboy-z8XGD.ttf", 35, 0);
    WHITE = al_map_rgb(255, 255, 255);
    SKY_BLUE = al_map_rgb(64, 224, 208);

    al_draw_text(FONT, WHITE, 520, 650, 0, "ALL");
    al_draw_text(FONT, WHITE, 590, 650, 0, "1st");
    al_draw_text(FONT, WHITE, 660, 650, 0, "2nd");
    al_draw_text(FONT, WHITE, 730, 650, 0, "3rd");

    al_draw_text(FONT, WHITE, 522, 690, 0, "EASY");
    al_draw_text(FONT, WHITE, 602, 690, 0, "NORMAL");
    al_draw_text(FONT, WHITE, 712, 690, 0, "HARD");

    switch(game_mode.round)
    {
    case 0:
    case -1:
        al_draw_text(FONT, SKY_BLUE, 520, 650, 0, "ALL");
        break;
    case 1:
        al_draw_text(FONT, SKY_BLUE, 590, 650, 0, "1st");
        break;
    case 2:
        al_draw_text(FONT, SKY_BLUE, 660, 650, 0, "2nd");
        break;
    case 3:
        al_draw_text(FONT, SKY_BLUE, 730, 650, 0, "3rd");
        break;
    }
    switch(game_mode.difficulty)
    {
    case 1:
        al_draw_text(FONT, SKY_BLUE, 522, 690, 0, "EASY");
        break;
    case 2:
    case 0:
        al_draw_text(FONT, SKY_BLUE, 602, 690, 0, "NORMAL");
        break;
    case 3:
        al_draw_text(FONT, SKY_BLUE, 712, 690, 0, "HARD");
        break;
    }

    al_destroy_font(FONT);
}

PLAY_State Rule()
{
    PLAY_State play_state = RULE;
    ALLEGRO_BITMAP *rule = NULL, *cross = NULL;
    ALLEGRO_EVENT ev;
    ALLEGRO_EVENT_QUEUE *event_q;

    event_q = al_create_event_queue();

    al_register_event_source(event_q, al_get_display_event_source(al_get_current_display()));
    al_register_event_source(event_q, al_get_mouse_event_source());

    cross = al_load_bitmap("./menu/cross.png");
    rule = al_load_bitmap("./menu/rule.png");


    while(play_state == RULE)
    {
        al_draw_bitmap(rule, 0, 0, 0);
        al_draw_bitmap(cross, 1000, 50, 0);
        al_flip_display();
        al_wait_for_event(event_q, &ev);

        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(ev.mouse.button & 1)
            {
                printf("mouse position: (X:%d, Y:%d)\n", ev.mouse.x, ev.mouse.y);

                if(ev.mouse.x >= 1000 && ev.mouse.x <= 1050 && ev.mouse.y >= 50 && ev.mouse.y <= 100)
                {
                    play_state = MENU;
                }
            }
        }
        if(ev.type ==ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            play_state = FINISH;
        }
    }
    al_destroy_bitmap(rule);
    al_destroy_bitmap(cross);
    al_destroy_event_queue(event_q);

    return(play_state);
}

void cutscene(ALLEGRO_BITMAP **game_bitmap, ALLEGRO_SAMPLE_INSTANCE **music, PLAY_State play_state)
{
    int x = 500, y = 300, x1 = 500;
    int finish = 0;
    ALLEGRO_BITMAP *menu = NULL;
    ALLEGRO_FONT *font;
    ALLEGRO_COLOR YELLOW;

    YELLOW = al_map_rgb(255, 215, 0);

    menu = al_load_bitmap("./menu/menu2.png");
    font = al_load_font("./Font/ARCHRISTY.ttf", 75, 0);

    al_resize_display(al_get_current_display(), MENU_W, MENU_H);

    switch(play_state)
    {
    case INIT:
        break;
    case MENU:
        break;
    case SELECT:
        break;
    case RULE:
        break;
    case GAME_1:
        while(!finish)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_tinted_bitmap(menu, al_map_rgb(50, 50, 50), 0, 0, 0);
            al_draw_text(font, YELLOW, 1000, 645, ALLEGRO_ALIGN_CENTRE, "LOADING......");

            al_draw_scaled_bitmap(game_bitmap[ghost1_front],0, 0, 30, 30, x1-100, y-30, 60, 60, 0);
            al_draw_scaled_bitmap(game_bitmap[ghost2_front],0, 0, 30, 30, x1-100, y+30, 60, 60, 0);
            al_draw_scaled_bitmap(game_bitmap[elf_front],0, 0, 30, 30, x, y, 60, 60, 0);
            x = x+1;

            x1 = x1+1;

            if(x == 835)
            {
                finish = 1;
            }
            al_flip_display();

            al_rest(0.003);
        }
        break;
    case GAME_2:

        while(!finish)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_tinted_bitmap(menu, al_map_rgb(50, 50, 50), 0, 0, 0);
            al_draw_text(font, YELLOW, 1000, 645, ALLEGRO_ALIGN_CENTRE, "LOADING......");

            al_draw_scaled_bitmap(game_bitmap[ghost1_front],0, 0, 30, 30, x1-100, y-30, 60, 60, 0);
            al_draw_scaled_bitmap(game_bitmap[ghost2_front],0, 0, 30, 30, x1-100, y+30, 60, 60, 0);
            al_draw_scaled_bitmap(game_bitmap[ghost3_front],0, 0, 30, 30, x1-160, y, 60, 60, 0);
            al_draw_scaled_bitmap(game_bitmap[elf_front],0, 0, 30, 30, x, y, 60, 60, 0);

            x = x+1;
            x1 = x1+1;

            al_rest(0.003);

            al_flip_display();

            if(x == 835)
            {
                finish = 1;
            }
        }
        break;
    case GAME_3:

        while(!finish)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_tinted_bitmap(menu, al_map_rgb(50, 50, 50), 0, 0, 0);
            al_draw_text(font, YELLOW, 1000, 645, ALLEGRO_ALIGN_CENTRE, "LOADING......");

            al_draw_scaled_bitmap(game_bitmap[ghost1_front],0, 0, 30, 30, x1-100, y-30, 60, 60, 0);
            al_draw_scaled_bitmap(game_bitmap[ghost2_front],0, 0, 30, 30, x1-100, y+30, 60, 60, 0);
            al_draw_scaled_bitmap(game_bitmap[ghost3_front],0, 0, 30, 30, x1-160, y-30, 60, 60, 0);
            al_draw_scaled_bitmap(game_bitmap[ghost4_front],0, 0, 30, 30, x1-160, y+30, 60, 60, 0);

            al_draw_scaled_bitmap(game_bitmap[elf_front],0, 0, 30, 30, x, y, 60, 60, 0);

            x = x+1;
            x1 = x1+1;

            if(x == 835)
            {
                finish = 1;
            }

            al_flip_display();

            al_rest(0.003);
        }
        break;
    case LEADERBOARD:
        break;
    case WIN:
        al_set_sample_instance_playing(music[win], true);
        while(!finish)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_tinted_bitmap(menu, al_map_rgb(50, 50, 50), 0, 0, 0);
            al_draw_text(font, YELLOW, 1000, 645, ALLEGRO_ALIGN_CENTRE, "LOADING......");

            al_draw_scaled_bitmap(game_bitmap[ghost1_front],0, 0, 30, 30, x1+200, y-30, 60, 60, 0);
            al_draw_scaled_bitmap(game_bitmap[ghost2_front],0, 0, 30, 30, x1+200, y+30, 60, 60, 0);
            al_draw_scaled_bitmap(game_bitmap[ghost3_front],0, 0, 30, 30, x1+260, y-30, 60, 60, 0);
            al_draw_scaled_bitmap(game_bitmap[ghost4_front],0, 0, 30, 30, x1+260, y+30, 60, 60, 0);

            al_draw_scaled_bitmap(game_bitmap[elf_front],0, 0, 30, 30, x, y, 60, 60, 0);

            x = x+2;
            x1 = x1+1;

            if(x-2>=x1+200)
            {
                finish = 1;
            }

            al_flip_display();

            al_rest(0.003);
        }
        break;
    case LOSE:
        al_set_sample_instance_playing(music[lose], true);
        while(!finish)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_tinted_bitmap(menu, al_map_rgb(50, 50, 50), 0, 0, 0);
            al_draw_text(font, YELLOW, 1000, 645, ALLEGRO_ALIGN_CENTRE, "LOADING......");

            al_draw_scaled_bitmap(game_bitmap[elf_front],0, 0, 30, 30, x1 + 200, y, 60, 60, 0);

            al_draw_scaled_bitmap(game_bitmap[ghost1_front],0, 0, 30, 30, x, y-30, 60, 60, 0);
            al_draw_scaled_bitmap(game_bitmap[ghost2_front],0, 0, 30, 30, x, y+30, 60, 60, 0);
            al_draw_scaled_bitmap(game_bitmap[ghost3_front],0, 0, 30, 30, x+60, y-30, 60, 60, 0);
            al_draw_scaled_bitmap(game_bitmap[ghost4_front],0, 0, 30, 30, x+60, y+30, 60, 60, 0);

            x = x+2;

            x1 = x1+1;

            if(x+60 >= x1+200)
            {
                finish = 1;
            }


            al_flip_display();
            al_rest(0.003);
        }
        break;
    case FINISH:
        break;
    }

    al_destroy_bitmap(menu);
    al_destroy_font(font);

}

void printf_array_2D(int row, int col, Object **Map)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            printf("%d ", Map[i][j].state);
        }
        printf("\n");
    }
}

void draw_special(ALLEGRO_MOUSE_EVENT mouse, ALLEGRO_BITMAP **sp)
{
    if(mouse.x >= 134 && mouse.x <= 136 && mouse.y >= 340 && mouse.y <= 342)
    {
        if(*sp == NULL)
            *sp = al_load_bitmap("./obj/sp/sp1.jpg");
        al_draw_bitmap(*sp, 85, 290, 0);
    }
    else if(mouse.x >= 283 && mouse.x <= 285 && mouse.y >= 373 && mouse.y <= 375)
    {
        if(*sp == NULL)
            *sp = al_load_bitmap("./obj/sp/sp2.jpg");
        al_draw_bitmap(*sp, 240, 365, 0);
    }
    else if(mouse.x >= 431 && mouse.x <= 433 && mouse.y >= 323 && mouse.y <= 325)
    {
        if(*sp == NULL)
            *sp = al_load_bitmap("./obj/sp/sp3.jpg");
        al_draw_bitmap(*sp, 385, 255, 0);
    }
    else if(mouse.x >= 577 && mouse.x <= 579 && mouse.y >= 364 && mouse.y <= 366)
    {
        if(*sp == NULL)
            *sp = al_load_bitmap("./obj/sp/sp4.jpg");
        al_draw_bitmap(*sp, 510, 300, 0);
    }
    else if(mouse.x >= 805 && mouse.x <= 807 && mouse.y >= 336 && mouse.y <= 338)
    {
        if(*sp == NULL)
            *sp = al_load_bitmap("./obj/sp/sp5.jpg");
        al_draw_bitmap(*sp, 780, 250, 0);
    }
    else
    {
        if(*sp != NULL)
        {
            al_destroy_bitmap(*sp);
            *sp = NULL;
        }
    }
}

void draw_bitmap(ALLEGRO_BITMAP *bitmap, ALLEGRO_BITMAP *bitmap2, ALLEGRO_MOUSE_EVENT mouse, int max_x, int min_x, int max_y, int min_y, int x, int y, int flags)
{
    if (mouse.x >= min_x && mouse.x <= max_x && mouse.y >= min_y  && mouse.y <= max_y)
    {
        al_draw_bitmap(bitmap, x, y, flags);
    }
    else
    {
        if(bitmap2 != NULL)
        {
            al_draw_bitmap(bitmap2, x, y, flags);
        }
    }
}

void draw_text(ALLEGRO_FONT *font, ALLEGRO_COLOR color, ALLEGRO_COLOR color2, ALLEGRO_MOUSE_EVENT mouse, int max_x, int min_x, int max_y, int min_y, int x, int y, int flags, const char* text)
{
    if (mouse.x >= min_x && mouse.x <= max_x && mouse.y >= min_y  && mouse.y <= max_y)
    {
        al_draw_text(font, color, x, y, flags, text);
    }
    else
    {
        if(font != NULL)
        {
            al_draw_text(font, color2, x, y, flags, text);
        }
    }
}
