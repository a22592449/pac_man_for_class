#include "main_header.h"

void Ghost_track_0(int row, int col, Object **Map, int fin_x, int fin_y, int fin_dir, Object **ghost)//fin == final
{
    int flag = 0, time = 0, block;
    int i, j, x, y;
    Object *current;
    Object **maze2;

    maze2 = create_matrix2(row, col);

    for(i = 0; i < row; i++)
        for(j = 0; j < col; j++)
            maze2[i][j] = Map[i][j];

    current = *ghost;
    while(current->next != NULL) //let route copy to maze2
    {
        maze2[current->y][current->x].state = 9;
        current = current->next;
    }

    maze2[current->y][current->x].state = 9;

    if((*ghost)->y == fin_y)
    {
        if((*ghost)->x < fin_x)
        {
            while((*ghost)->x < fin_x && (*ghost)->next != NULL)
            {
                maze2[(*ghost)->y][(*ghost)->x].state = Map[(*ghost)->y][(*ghost)->x].state;
                pop(ghost);
            }
        }
        else if((*ghost)->x > fin_x)
        {
            while((*ghost)->x > fin_x && (*ghost)->next != NULL)
            {
                maze2[(*ghost)->y][(*ghost)->x].state = Map[(*ghost)->y][(*ghost)->x].state;
                pop(ghost);
            }
        }
    }
    else if((*ghost)->x == fin_x)
    {
        if((*ghost)->y < fin_y)
        {
            while((*ghost)->y < fin_y && (*ghost)->next != NULL)
            {
                maze2[(*ghost)->y][(*ghost)->x].state = Map[(*ghost)->y][(*ghost)->x].state; //return map state to maze2
                pop(ghost);
            }

        }
        else if((*ghost)->y > fin_y)
        {
            while((*ghost)->y > fin_y && (*ghost)->next != NULL)
            {
                maze2[(*ghost)->y][(*ghost)->x].state = Map[(*ghost)->y][(*ghost)->x].state;
                pop(ghost);
            }
        }
    }
    else
    {
        while((*ghost)->next != NULL)
        {
            maze2[(*ghost)->y][(*ghost)->x].state = Map[(*ghost)->y][(*ghost)->x].state;
            pop(ghost);
        }
    }

    if(fin_dir == UP && Map[fin_y-1][fin_x].state != 0 && (*ghost)->dir != DOWN)
    {
        fin_y = fin_y - 1;
    }
    else if(fin_dir == DOWN && Map[fin_y+1][fin_x].state != 0 && (*ghost)->dir != UP)
    {
        fin_y = fin_y + 1;
    }
    else if(fin_dir == LEFT && Map[fin_y][fin_x-1].state != 0 && (*ghost)->dir != RIGHT)
    {
        fin_x = fin_x - 1;
    }
    else if(fin_dir == RIGHT && Map[fin_y][fin_x+1].state != 0 && (*ghost)->dir != LEFT)
    {
        fin_x = fin_x + 1;
    }

    while(flag != 1 && time <= 50)//time <= 50 because warry colculate
    {
        block = 0;
        if((*ghost)->x == fin_x && (*ghost)->y == fin_y)
        {
            flag = 1;
        }
        else if(maze2[(*ghost)->y][(*ghost)->x].state != 0)
        {
            switch(Select_Dir(fin_x, fin_y, *ghost))
            {
            case UP:
                i = (*ghost)->y;
                while(!block && i > fin_y)
                {
                    if(maze2[i - 1][(*ghost)->x].state == 0 || maze2[i - 1][(*ghost)->x].state == 9 || maze2[i - 1][(*ghost)->x].state == 4)
                    {
                        block = 1;
                    }
                    else
                    {
                        i--;
                    }
                }
                if(block)
                {
                    if((*ghost)->x < fin_x)
                    {
                        Select_Track(ghost, maze2, RIGHT, UP, DOWN, LEFT, &x, &y);
                    }
                    else
                    {
                        Select_Track(ghost, maze2, LEFT, UP, DOWN, RIGHT, &x, &y);
                    }
                }
                else
                {
                    x = (*ghost)->x;
                    y = (*ghost)->y - 1;
                    (*ghost)->dir = UP;
                }
                break;
            case DOWN:
                i = (*ghost)->y;
                while(!block && i < fin_y)
                {
                    if(maze2[i + 1][(*ghost)->x].state == 0 || maze2[i + 1][(*ghost)->x].state == 9 || maze2[i + 1][(*ghost)->x].state == 4)
                    {
                        block = 1;
                    }
                    else
                    {
                        i++;
                    }
                }
                if(block)
                {
                    if((*ghost)->x < fin_x)
                    {
                        Select_Track(ghost, maze2, RIGHT, DOWN, UP, LEFT, &x, &y);
                    }
                    else
                    {
                        Select_Track(ghost, maze2, LEFT, DOWN, UP, RIGHT, &x, &y);
                    }
                }
                else
                {
                    x = (*ghost)->x;
                    y = (*ghost)->y + 1;
                    (*ghost)->dir = DOWN;
                }
                break;
            case LEFT:
                i = (*ghost)->x;
                while(!block && i > fin_x)
                {
                    if(maze2[(*ghost)->y][i - 1].state == 0 || maze2[(*ghost)->y][i - 1].state == 9 || maze2[(*ghost)->y][i - 1].state == 4)
                    {

                        block = 1;
                    }
                    else
                    {
                        i--;
                    }
                }
                if(block)
                {
                    if((*ghost)->y > fin_y)
                    {
                        Select_Track(ghost, maze2, UP, LEFT, RIGHT, DOWN, &x, &y);
                    }
                    else
                    {
                        Select_Track(ghost, maze2, DOWN, LEFT, RIGHT, UP, &x, &y);
                    }
                }
                else
                {
                    x = (*ghost)->x - 1;
                    y = (*ghost)->y;
                    (*ghost)->dir = LEFT;
                }
                break;
            case RIGHT:
                i = (*ghost)->x;
                while(!block && i < fin_x)
                {
                    if(maze2[(*ghost)->y][i + 1].state == 0 || maze2[(*ghost)->y][i + 1].state == 9 || maze2[(*ghost)->y][i + 1].state == 4)
                    {
                        block = 1;
                    }
                    else
                    {
                        i++;
                    }
                }
                if(block)
                {
                    if((*ghost)->y > fin_y)
                    {
                        Select_Track(ghost, maze2, UP, RIGHT, LEFT, DOWN, &x, &y);
                    }
                    else
                    {
                        Select_Track(ghost, maze2, DOWN, RIGHT, LEFT, UP, &x, &y);
                    }
                }
                else
                {
                    x = (*ghost)->x + 1;
                    y = (*ghost)->y;
                    (*ghost)->dir = RIGHT;
                }
                break;
            }
            if(maze2[(*ghost)->y][(*ghost)->x].state == 4)
            {
                if((*ghost)->next != NULL)
                {
                    pop(ghost);
                }
            }
            else
            {
                if(x == col && Map[y][x - 1].state == -1)
                {
                    x = 0;
                }
                if(x == -1 && Map[y][x + 1].state == -1)
                {
                    x = col - 1;
                }
                push(x, y, ghost);
                maze2[(*ghost)->y][(*ghost)->x].state = 9;
            }
        }
        time++;
    }
    free_matrix(row, maze2);
}

void Ghost_track_1(int row, int col, Object **Map, int fin_x, int fin_y, int fin_dir, Object **ghost)
{
    int x, y, turn;

    if(fin_dir == UP && Map[fin_y-1][fin_x].state != 0 && (*ghost)->dir != DOWN)
    {
        fin_y = fin_y - 1;
    }
    else if(fin_dir == DOWN && Map[fin_y+1][fin_x].state != 0 && (*ghost)->dir != UP)
    {
        fin_y = fin_y + 1;
    }
    else if(fin_dir == LEFT && Map[fin_y][fin_x-1].state != 0 && (*ghost)->dir != RIGHT)
    {
        fin_x = fin_x - 1;
    }
    else if(fin_dir == RIGHT && Map[fin_y][fin_x+1].state != 0 && (*ghost)->dir != LEFT)
    {
        fin_x = fin_x + 1;
    }

    if((*ghost)->dir == -1)
        (*ghost)->dir = Select_Dir(fin_x, fin_y, *ghost);

    do
    {
        turn = clock()%5;

        switch((*ghost)->dir)
        {
        case UP: //向上
            x = (*ghost)->x;
            y = (*ghost)->y - 1;
            break;
        case DOWN://向下
            x = (*ghost)->x;
            y = (*ghost)->y + 1;
            break;
        case LEFT://向左
            x = (*ghost)->x - 1;
            y = (*ghost)->y;
            break;
        case RIGHT://向右
            x = (*ghost)->x + 1;
            y = (*ghost)->y;
            break;
        }
        if(x == col && Map[y][x - 1].state == -1)
        {
            x = 0;
        }
        if(x == -1 && Map[y][x + 1].state == -1)
        {
            x = col - 1;
        }
        if(Map[y][x].state == 0 || turn == 0)
        {
            (*ghost)->dir = rand()%4;
        }
    }
    while(Map[y][x].state == 0 || turn == 0);
    push(x, y, ghost);
}

void Ghost_track_2(int row, int col, Object **Map, int fin_x, int fin_y, int fin_dir, Object **ghost)
{
    Object *current = NULL;

    current = *ghost;
    while(current->next != NULL)
    {
        current = current->next;
    }

    if(abs(current->x - fin_x) <= col/3 && abs(current->y - fin_y) <= row/3)
    {
        Ghost_track_3(row, col, Map, fin_x, fin_y, fin_dir, ghost);
    }
    else
    {
        while((*ghost)->next != NULL)
        {
            pop(ghost);
        }
        Ghost_track_1(row, col, Map, fin_x, fin_y, fin_dir, ghost);
    }
}

void Ghost_track_3(int row, int col, Object **Map, int fin_x, int fin_y, int fin_dir, Object **ghost)
{
    PathNode *path, *temp_path, *ptr;
    PathNode *openlist = NULL, *closedlist = NULL;
    PathNode *temp_map[row][col];
    Object **target_map, **maze2;
    int i, j, tx, ty, finish = 0;
    int x[4] = {1, -1, 0, 0};
    int y[4] = {0, 0, 1, -1};

    target_map = create_matrix2(row, col);
    maze2 = create_matrix2(row, col);

    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            target_map[i][j] = Map[i][j];
            temp_map[i][j] = NULL;
            maze2[i][j] = Map[i][j];
        }
    }

    while((*ghost)->next != NULL)
    {
        pop(ghost);
    }

    if(fin_dir == UP && Map[fin_y-1][fin_x].state != 0 && (*ghost)->dir != DOWN)
    {
        fin_y = fin_y - 1;
    }
    else if(fin_dir == DOWN && Map[fin_y+1][fin_x].state != 0 && (*ghost)->dir != UP)
    {
        fin_y = fin_y + 1;
    }
    else if(fin_dir == LEFT && Map[fin_y][fin_x-1].state != 0 && (*ghost)->dir != RIGHT)
    {
        fin_x = fin_x - 1;
    }
    else if(fin_dir == RIGHT && Map[fin_y][fin_x+1].state != 0 && (*ghost)->dir != LEFT)
    {
        fin_x = fin_x + 1;
    }

    insert(&openlist, NULL, (*ghost)->x, (*ghost)->y, H((*ghost)->x, (*ghost)->y, fin_x, fin_y), 0);
    while(openlist != NULL && !finish)
    {
        path = openlist;
        if(path->x == fin_x && path->y == fin_y) finish = 1;
        movenode(&openlist, &closedlist);
        target_map[path->y][path->x].state = 9;

        for(i=0; i<4; i++)
        {
            tx = path->x + x[i];
            ty = path->y + y[i];

            if(tx == col && Map[ty][tx-1].state == -1)
            {
                tx = 0;
            }
            if(tx == -1 && Map[ty][tx + 1].state == -1)
            {
                tx = col - 1;
            }

            if(target_map[ty][tx].state != 0 && target_map[ty][tx].state != 9)
            {
                if(target_map[ty][tx].state != 4)
                {
                    temp_map[ty][tx] = insert(&openlist, path, tx, ty, G(path) + H(tx, ty, fin_x, fin_y), G(path));
                    target_map[ty][tx].state = 4;
                }
                else
                {
                    temp_path = temp_map[ty][tx];
                    if(G(path) < temp_path->g)
                    {
                        temp_path->previous = path;
                    }
                }
            }
        }
    }
    if(openlist != NULL)
    {
        path->next = NULL;
        while(path->previous->previous != NULL)
        {
            //maze2[path->y][path->x].state = 9;
            ptr = path;
            path = path->previous;
            path->next = ptr;
        }
        //printf_array_2D(row, col, maze2);

        while(path != NULL)
        {
            if(path->x > path->previous->x && path->y == path->previous->y)
            {
                (*ghost)->dir = RIGHT;
            }
            else if(path->x < path->previous->x && path->y == path->previous->y)
            {
                (*ghost)->dir = LEFT;
            }
            else if(path->y < path->previous->y && path->x == path->previous->x)
            {
                (*ghost)->dir = UP;
            }
            else if(path->y > path->previous->y && path->x == path->previous->x)
            {
                (*ghost)->dir = DOWN;
            }
            push(path->x, path->y, ghost);
            path = path->next;
        }
    }


    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            if(temp_map[i][j] != NULL)
                free(temp_map[i][j]);
        }
    }
    free_matrix(row, target_map);
}

Object *Ghost_Move(int row, int col, Object **Map, Object **ghost, ALLEGRO_BITMAP **game_bitmap)
{
    Object *current, *previous = NULL;
    current = *ghost;

    while(current->next!=NULL)//找原點
    {
        previous = current;
        current = current->next;
    }

    if(previous != NULL)  //是否有下一步
    {
        if(current->state % 2 == 0 && current->dir == UP)
        {
            current->state++;
        }
        else
        {
            if(current->state % 2 == 1 && current->dir != UP)
            {
                current->state--;
            }
        }
        if(current->dir == RIGHT)
        {
            current->pixel_x++;
        }
        else if(current->dir == LEFT)
        {
            current->pixel_x--;
        }
        else if(current->dir == UP)
        {
            current->pixel_y--;
        }
        else if(current->dir == DOWN)
        {
            current->pixel_y++;
        }
        if((previous->pixel_x == current->pixel_x && previous->pixel_y == current->pixel_y) || (current->pixel_x <= -15 || current->pixel_x >= col * 30 - 15))
        {
            previous->state = current->state;
            previous->Gstate = current->Gstate;
            previous->next = NULL;
            free(current);
            return previous;
        }
    }
    return current;
}

int Select_Dir(int fin_x, int fin_y, Object *ghost)
{
    int x, y;
    x = ghost->x - fin_x;
    y = ghost->y - fin_y;
    if(abs(x) > abs(y))
    {
        if(x < 0)
            return RIGHT;
        else if(x > 0)
            return LEFT;
        else
        {
            if(y < 0)
                return DOWN;
            else
                return UP;
        }
    }
    else
    {
        if(y > 0)
            return UP;
        else if(y < 0)
            return DOWN;
        else
        {
            if(x < 0)
                return RIGHT;
            else
                return LEFT;
        }
    }
}

void Show_Ghost(Object *ghost, int change_time, int timer, int dead_time, ALLEGRO_BITMAP **game_bitmap, ALLEGRO_SAMPLE_INSTANCE **music)
{
    switch(ghost->Gstate)
    {
    case NOTHING:
        if(dead_time == 0)
        {
            ghost->Gstate = NORMAL;

        }
        break;
    case NORMAL:
        if(ghost->dir == RIGHT)
            al_draw_bitmap(game_bitmap[ghost->state], ghost->pixel_x, ghost->pixel_y, 1);
        else
            al_draw_bitmap(game_bitmap[ghost->state], ghost->pixel_x, ghost->pixel_y, 0);
        break;
    case CHANGING:
        if(ghost->dir == RIGHT)
        {
            if(timer % 240 > 120)
            {
                al_draw_bitmap(game_bitmap[ghost->state], ghost->pixel_x, ghost->pixel_y, 1);
            }
            else if(timer % 240 < 120)
            {
                al_draw_tinted_bitmap(game_bitmap[ghost->state], al_map_rgb(40, 148, 255), ghost->pixel_x, ghost->pixel_y, 1);
            }
        }
        else
        {
            if(timer % 240 > 120)
            {
                al_draw_bitmap(game_bitmap[ghost->state], ghost->pixel_x, ghost->pixel_y, 0);
            }
            else if(timer % 240 < 120)
            {
                al_draw_tinted_bitmap(game_bitmap[ghost->state], al_map_rgb(40, 148, 255), ghost->pixel_x, ghost->pixel_y, 0);
            }
        }
        if(change_time == 0)
        {
            ghost->Gstate = NORMAL;
            al_set_sample_instance_playing(music[invincible], false);
        }
        break;
    case WEAK:
        if(ghost->dir == RIGHT)
            al_draw_tinted_bitmap(game_bitmap[ghost->state], al_map_rgb(40, 148, 255), ghost->pixel_x, ghost->pixel_y, 1);
        else
            al_draw_tinted_bitmap(game_bitmap[ghost->state], al_map_rgb(40, 148, 255), ghost->pixel_x, ghost->pixel_y, 0);
        if(change_time == 3)
        {
            ghost->Gstate = CHANGING;
        }
        break;
    }
}

Object* Create_Book(Object *ghost, Object *book)
{
    Object* new_book;
    new_book = (Object*)malloc(sizeof(Object));
    new_book->pixel_x = ghost->pixel_x;
    new_book->pixel_y = ghost->pixel_y;
    new_book->state = book_state;
    new_book->next = book;

    return new_book;
}

void Show_Book(Object *book, ALLEGRO_BITMAP **game_bitmap)
{
    while(book != NULL)
    {
        al_draw_bitmap(game_bitmap[book->state], book->pixel_x, book->pixel_y, 0);
        book = book->next;
    }
}

int Ghost_Runaway_Dir(int fin_x, int fin_y, Object *ghost)
{
    int x, y;
    x = ghost->x - fin_x;
    y = ghost->y - fin_y;
    if(abs(x) < abs(y))
    {
        if(x < 0)
            return LEFT;
        else if(x > 0)
            return RIGHT;
        else
        {
            if(y < 0)
                return UP;
            else
                return DOWN;
        }
    }
    else
    {
        if(y > 0)
            return DOWN;
        else if(y < 0)
            return UP;
        else
        {
            if(x < 0)
                return LEFT;
            else
                return RIGHT;
        }
    }
}

void Track_If_Ghost_Weak(Object **ghost, int fin_x, int fin_y, Object **Map, int col)
{
    int x, y;

    while((*ghost)->next != NULL)
    {
        pop(ghost);
    }

    x = (*ghost)->x - fin_x;
    y = (*ghost)->x - fin_y;

    switch(Ghost_Runaway_Dir(fin_x, fin_y, *ghost))
    {
    case UP:
        if(Map[(*ghost)->y-1][(*ghost)->x].state != 0)
        {
            (*ghost)->dir = UP;
            push((*ghost)->x, (*ghost)->y-1, ghost);
        }
        else
        {
            if(x < 0)
            {
                Select_Weak_Track(Map, ghost, LEFT, RIGHT, DOWN, x, y);
            }
            else//x > 0
            {
                Select_Weak_Track(Map, ghost, RIGHT, LEFT, DOWN, x, y);
            }
        }
        break;
    case DOWN:
        if(Map[(*ghost)->y+1][(*ghost)->x].state != 0)
        {
            (*ghost)->dir = DOWN;
            push((*ghost)->x, (*ghost)->y+1, ghost);
        }
        else
        {
            if(x < 0)
            {
                Select_Weak_Track(Map, ghost, LEFT, RIGHT, UP, x, y);
            }
            else//x > 0
            {
                Select_Weak_Track(Map, ghost, RIGHT, LEFT, UP, x, y);
            }
        }
        break;
    case RIGHT:
        if(Map[(*ghost)->y][(*ghost)->x+1].state != 0)
        {
            (*ghost)->dir = RIGHT;
            push((*ghost)->x+1, (*ghost)->y, ghost);
        }
        else
        {
            if(y < 0)
            {
                Select_Weak_Track(Map, ghost, UP, LEFT, DOWN, x, y);
            }
            else//y > 0
            {
                Select_Weak_Track(Map, ghost, DOWN, LEFT, UP, x, y);
            }
        }
        break;
    case LEFT:
        if(Map[(*ghost)->y][(*ghost)->x-1].state != 0)
        {
            (*ghost)->dir = LEFT;
            push((*ghost)->x-1, (*ghost)->y, ghost);
        }
        else
        {
            if(y < 0)
            {
                Select_Weak_Track(Map, ghost, UP, RIGHT, DOWN, x, y);
            }
            else//y > 0
            {
                Select_Weak_Track(Map, ghost, DOWN, RIGHT, UP, x, y);
            }
        }
        break;
    }

    if((*ghost)->x == col && Map[(*ghost)->y][(*ghost)->x - 1].state == -1)
    {
        (*ghost)->x = 0;
    }
    if((*ghost)->x == -1 && Map[(*ghost)->y][(*ghost)->x + 1].state == -1)
    {
        (*ghost)->x = col - 1;
    }
}

void *load_track(ALLEGRO_THREAD *track, void *data)
{
    ThreadsArg *arg = (ThreadsArg*)data;

    while(!al_get_thread_should_stop(track))
    {
        al_lock_mutex(arg->mutex);
        switch(arg->is_pause)
        {
        case 0:
            arg->Ghost_Track(arg->row, arg->col, arg->Map, arg->elf->x, arg->elf->y, arg->elf->dir, arg->ghost);
            arg->is_pause = 1;
            break;
        case 1:
            al_wait_cond(arg->cond, arg->mutex);
            printf("thread pause\n");
            break;
        }
        al_unlock_mutex(arg->mutex);
    }

    return NULL;
}
