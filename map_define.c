#include "define_header.h"
#include "argument_header.h"

void wall_col(int row,int col,Object **Map, int x, int y, int j, int k)
{
    int i;
    for (i=x; i<=y; i++)
    {
        Map[i][j].state=k;
    }

}

void wall_row(int row,int col,Object **Map, int x, int y, int j, int k)
{
    int i;
    for (i=x; i<=y; i++)
    {
        Map[j][i].state=k;
    }
}

void point_map(int row, int col, Object **Map)
{
    int i, j;
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            if(Map[i][j].state == -1)
                Map[i][j].state = point;
        }
    }

}

