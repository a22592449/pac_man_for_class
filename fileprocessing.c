#include "function_header.h"
#include <stdio.h>

void Save_File(char *name, double score, int time, GameMode game_mode)
{
    FILE *fplayer_name, *fplayer_score, *ftime;
    Player player[10], new_player, temp;
    int i = 0;
    char* filename[3];

    for(i = 0; i < 3; i++)
    {
        filename[i] = (char*)malloc(sizeof(char) * 45);
    }

    switch (game_mode.round)
    {
    case 0 :
        switch (game_mode.difficulty)
        {
        case 1:
            strcpy(filename[0], "./data/allround/player_name_easy.txt");
            strcpy(filename[1], "./data/allround/player_score_easy.txt");
            strcpy(filename[2], "./data/allround/time_easy.txt");
            break;
        case 2:
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
    if(Load_Player(player, filename) == -1)
    {
        return;
    }

    fplayer_name = fopen(filename[0], "w");
    fplayer_score = fopen(filename[1], "w");
    ftime = fopen(filename[2], "w");

    new_player.name = strcat(name, "\n");
    new_player.score = score;
    new_player.time = time;

    for(i = 0; i < 10; i++)
    {
        if(new_player.score > player[i].score)
        {
            temp = player[i];
            player[i] = new_player;
            new_player = temp;
        }
    }

    i = 0;

    while(player[i].name != NULL && player[i].score != -1 && player[i].time != -1 && i < 10)
    {
        fprintf(fplayer_name, "%s", player[i].name);
        fprintf(fplayer_score, "%.3lf\n", player[i].score);
        fprintf(ftime, "%d\n", player[i].time);
        i++;
    }

    for(i = 0; i<3; i++)
    {
        free(filename[i]);
    }
    free_player(player, name);
    fclose(fplayer_name);
    fclose(fplayer_score);
    fclose(ftime);
}

int File_Length(const char* file_name)
{
    int n = 0;
    int c;
    FILE *fptr;
    fptr = fopen(file_name, "r");
    if(fptr == NULL)
    {
        printf("%s loads fail ...", file_name);
        fclose(fptr);
        return -1;
    }
    c = fgetc(fptr);
    if(c !=EOF)
    {
        while(c != EOF)
        {
            c = fgetc(fptr);
            if(c == '\n' || c == EOF)
            {
                n++;
            }
        }
    }
    fclose(fptr);
    return n;
}

int Load_Player(Player *player, char** filename)
{
    FILE *fplayer_name, *fplayer_score, *ftime;
    int i;

    fplayer_name = fopen(filename[0], "r");
    fplayer_score = fopen(filename[1], "r");
    ftime = fopen(filename[2], "r");

    if(fplayer_name == NULL || fplayer_score == NULL || ftime == NULL)
    {
        printf("File loads fail ...\n");
        fclose(fplayer_name);
        fclose(fplayer_score);
        fclose(ftime);
        return -1;
    }

    for(i = 0; i < 10; i++)
    {
        player[i].name = NULL;
        player[i].score = -1;
        player[i].time = -1;
    }

    for(i = 0; i < File_Length(filename[0]); i++)
    {
        player[i].name = (char*)malloc(sizeof(char)*20);
        fgets(player[i].name, 30, fplayer_name);
    }

    for(i = 0; i < File_Length(filename[1]); i++)
    {
        fscanf(fplayer_score, "%lf", &player[i].score);
    }

    for(i = 0; i < File_Length(filename[2]); i++)
    {
        fscanf(ftime, "%d", &player[i].time);
    }

    fclose(fplayer_name);
    fclose(fplayer_score);
    fclose(ftime);
    return 0;
}


