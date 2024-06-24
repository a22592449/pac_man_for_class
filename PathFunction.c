#include "define_header.h"
#include "argument_header.h"


int isStackEmpty(Object *ghost)
{
    if ( ghost == NULL )
        return 1;
    else
        return 0;
}

void push(int x, int y, Object **ghost)
{
    Object *new_node; 
    
    new_node = (Object*)malloc(sizeof(Object));
    new_node->state = (*ghost)->state;
    new_node->x = x;
    new_node->y = y;
    new_node->pixel_x = 30 * x;
    new_node->pixel_y = 30 * y;
    new_node->init_x = (*ghost)->init_x;
    new_node->init_y = (*ghost)->init_y;
    new_node->dir = (*ghost)->dir;
    new_node->Gstate = (*ghost)->Gstate;
    new_node->next = *ghost;
    *ghost = new_node;
}

void pop(Object **ghost)
{
    Object *ptr;
    if (!isStackEmpty(*ghost))
    {
        ptr = *ghost;
        *ghost = (*ghost)->next;
        free(ptr);
    }
}

PathNode *insert(PathNode **l, PathNode *fn, int x, int y, int f, int g)
{
    PathNode *n, *prev=NULL, *cur;

    n = (PathNode*) malloc(sizeof(PathNode));
    cur = *l;

    if(n != NULL)
    {
        n->f = f;
        n->g = g;
        n->previous = fn;
        n->x = x;
        n->y = y;

        while(cur != NULL && f > cur->f)
        {
            prev = cur;
            cur = cur->next;
        }

        if(prev != NULL)
        {
            prev->next = n;
        }
        else
        {
            *l = n;
        }
        n->next = cur;
    }
    return n;
}

int movenode(PathNode **a, PathNode **b)
{
    PathNode *t = *a;

    *a = (*a)->next;
    t->next = *b;
    *b = t;
    return 0;
}

int G(PathNode *fn)
{
    return fn->g + 1;
}

int H(int x, int y, int x2, int y2)
{
    return abs(x - x2) + abs(y - y2);
}

void Select_Weak_Track(Object **Map, Object **ghost, int dir_1, int dir_2, int dir_3, int x, int y)
{
    int k, i[3], j[3], dir[3] = {dir_1, dir_2, dir_3};

    for(k = 0; k < 3; k++)
    {
        if(dir[k] == UP)
        {
            i[k] = (*ghost)->y - 1;
            j[k] = (*ghost)->x;
        }
        if(dir[k] == DOWN)
        {
            i[k] = (*ghost)->y + 1;
            j[k] = (*ghost)->x;
        }
        if(dir[k] == RIGHT)
        {
            i[k] = (*ghost)->y;
            j[k] = (*ghost)->x + 1;
        }
        if(dir[k] == LEFT)
        {
            i[k] = (*ghost)->y;
            j[k] = (*ghost)->x - 1;
        }
    }

    if(Map[i[0]][j[0]].state != 0)
    {
        (*ghost)->dir = dir[0];
        push(j[0], i[0], ghost);
    }
    else
    {
        if(abs(x) > abs(y))
        {
            if(Map[i[1]][j[1]].state != 0)
            {
                (*ghost)->dir = dir[1];
                push(j[1], i[1], ghost);
            }
            else
            {
                if(Map[i[2]][j[2]].state != 0)
                {
                    (*ghost)->dir = dir[2];
                    push(j[2], i[2], ghost);
                }
            }
        }
        else
        {
            if(Map[i[2]][j[2]].state != 0)
            {
                (*ghost)->dir = dir[2];
                push(j[2], i[2], ghost);
            }
            else
            {
                if(Map[i[1]][j[1]].state != 0)
                {
                    (*ghost)->dir = dir[1];
                    push(j[1], i[1], ghost);
                }
            }
        }
    }
}

void Select_Track(Object **ghost, Object **Map, int dir_1, int dir_2, int dir_3, int dir_4, int *x, int *y)
{
    int k;
    int i[4], j[4];
    int dir[4] = {dir_1, dir_2, dir_3, dir_4};
    for(k = 0; k < 2; k++)
    {
        if(dir[k] == UP)
        {
            i[k] = (*ghost)->y - 1;
            j[k] = (*ghost)->x;
        }
        if(dir[k] == DOWN)
        {
            i[k] = (*ghost)->y + 1;
            j[k] = (*ghost)->x;
        }
        if(dir[k] == RIGHT)
        {
            i[k] = (*ghost)->y;
            j[k] = (*ghost)->x + 1;
        }
        if(dir[k] == LEFT)
        {
            i[k] = (*ghost)->y;
            j[k] = (*ghost)->x - 1;
        }
    }
    if(Map[i[0]][j[0]].state != 0 && Map[i[0]][j[0]].state != 4 && Map[i[0]][j[0]].state != 9)
    {
        *x = j[0];
        *y = i[0];
        (*ghost)->dir = dir[0];
    }
    else
    {
        if(Map[i[1]][j[1]].state != 0 && Map[i[1]][j[1]].state != 4 && Map[i[1]][j[1]].state != 9)
        {
            *x = j[1];
            *y = i[1];
            (*ghost)->dir = dir[1];
        }
        else
        {
            while((*ghost)->next != NULL && (*ghost)->next->dir == dir[1])
            {
                Map[(*ghost)->y][(*ghost)->x].state = 4;
                pop(ghost);
            }
            for(k = 2; k < 4; k++)
            {
                if(dir[k] == UP)
                {
                    i[k] = (*ghost)->y - 1;
                    j[k] = (*ghost)->x;
                }
                if(dir[k] == DOWN)
                {
                    i[k] = (*ghost)->y + 1;
                    j[k] = (*ghost)->x;
                }
                if(dir[k] == RIGHT)
                {
                    i[k] = (*ghost)->y;
                    j[k] = (*ghost)->x + 1;
                }
                if(dir[k] == LEFT)
                {
                    i[k] = (*ghost)->y;
                    j[k] = (*ghost)->x - 1;
                }
            }
            if(Map[i[2]][j[2]].state != 0 && Map[i[2]][j[2]].state != 4 && Map[i[2]][j[2]].state != 9)
            {
                *x = j[2];
                *y = i[2];
                (*ghost)->dir = dir[2];
            }
            else if(Map[i[3]][j[3]].state != 0 && Map[i[3]][j[3]].state != 4 && Map[i[3]][j[3]].state != 9)
            {
                *x = j[3];
                *y = i[3];
                (*ghost)->dir = dir[3];
            }
            else
            {
                Map[(*ghost)->y][(*ghost)->x].state = 4;
            }
        }
    }
}
