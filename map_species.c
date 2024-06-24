#include "main_header.h"

void Map1(int row,int col,Object **Map, Object **ghost)
{
    point_map(row, col,Map);
    wall_row(row,col,Map, 0,29,10,-1);  //通道//
    wall_row(row,col,Map, 17,19,4,-1);
    wall_row(row,col,Map, 18,18,3,-1);

    wall_row(row,col,Map, 0,29, 0,WALL_30); //第一列的圖//
    wall_col(row,col,Map, 0, 9, 0,WALL_30);//第一行的圖//
    wall_col(row,col,Map, 11, 19, 0,WALL_30);
    wall_row(row,col,Map, 0, 29, 19,WALL_30);
    wall_col(row,col,Map, 0, 9, 29,WALL_30);
    wall_col(row,col,Map, 11, 19, 29,WALL_30);
    wall_row(row,col,Map, 0, 1, 9, WALL_30);
    wall_row(row,col,Map, 0, 1, 11,WALL_30);
    wall_row(row,col,Map, 28, 29, 9,WALL_30);
    wall_row(row,col,Map, 28, 29, 11,WALL_30);

    wall_col(row,col,Map, 13,17,2,WALL_30);//N//
    wall_col(row,col,Map, 14,14,3,WALL_30);//N//
    wall_col(row,col,Map, 15,15,4,WALL_30);//N//
    wall_col(row,col,Map, 16,16,5,WALL_30);//N//
    wall_col(row,col,Map, 13,17,6,WALL_30);//N//
    wall_col(row,col,Map, 13,17,8,WALL_30);//U//
    wall_col(row,col,Map, 13,17,12,WALL_30);//U//
    wall_row(row,col,Map, 9,11,17,WALL_30);//U//

    wall_col(row,col,Map, 13,17,14,WALL_30);//K//
    wall_col(row,col,Map, 15,15,15,WALL_30);//K//
    wall_col(row,col,Map, 14,14,16,WALL_30);//K//
    wall_col(row,col,Map, 16,16,16,WALL_30);//K//
    wall_col(row,col,Map, 13,13,17,WALL_30);//K//
    wall_col(row,col,Map, 17,17,17,WALL_30);//K//
    wall_col(row,col,Map, 13,17,19,WALL_30);//LEFT E//
    wall_row(row,col,Map, 20,22,13,WALL_30);
    wall_row(row,col,Map, 20,22,15,WALL_30);
    wall_row(row,col,Map, 20,22,17,WALL_30);

    wall_col(row,col,Map, 13,17,24,WALL_30);//RIGHT E//
    wall_row(row,col,Map, 25,27,13,WALL_30);
    wall_row(row,col,Map, 25,27,15,WALL_30);
    wall_row(row,col,Map, 25,27,17,WALL_30);

    wall_row(row,col,Map, 2,6,2,WALL_30);//I//
    wall_row(row,col,Map, 2,6,7,WALL_30);
    wall_col(row,col,Map, 3,6,4,WALL_30);

    wall_row(row,col,Map, 9,13,2,WALL_30);//C//
    wall_row(row,col,Map, 9,13,7,WALL_30);
    wall_col(row,col,Map, 3,6,9,WALL_30);

    wall_col(row,col,Map, 4,7,16,WALL_30); //A//
    wall_col(row,col,Map, 3,3,17,WALL_30);
    wall_col(row,col,Map, 2,2,18,WALL_30);
    wall_col(row,col,Map, 3,3,19,WALL_30);
    wall_col(row,col,Map, 4,7,20,WALL_30);
    wall_row(row,col,Map, 17,19,5,WALL_30);

    wall_col(row,col,Map, 2,7,23,WALL_30);//L//
    wall_row(row,col,Map, 24,27,7,WALL_30);

    wall_row(row,col,Map, 3,3,3,big_point);
    wall_row(row,col,Map, 3,3,13,big_point);
    wall_row(row,col,Map, 25,25,14,big_point);
    wall_row(row,col,Map, 15,15,14,big_point);
    wall_row(row,col,Map, 25,25,5,big_point);

    wall_row(row,col,Map, 4,7,9,WALL_30);
    wall_row(row,col,Map, 10,13,9,WALL_30);
    wall_row(row,col,Map, 16,19,9,WALL_30);
    wall_row(row,col,Map, 22,25,9,WALL_30);

    wall_row(row,col,Map, 4,7,11,WALL_30);
    wall_row(row,col,Map, 10,13,11,WALL_30);
    wall_row(row,col,Map, 16,19,11,WALL_30);
    wall_row(row,col,Map, 22,25,11,WALL_30);

    ghost[0]->x = 28;
    ghost[0]->y = 8;
    ghost[0]->init_x = 28;
    ghost[0]->init_y = 8;
    ghost[0]->state = ghost1_front;
    ghost[1]->x = 18;
    ghost[1]->y = 8;
    ghost[1]->init_x = 18;
    ghost[1]->init_y = 8;
    ghost[1]->state = ghost2_front;
}

void Map2(int row,int col,Object **Map, Object **ghost)
{
    point_map(row, col,Map);
    wall_row(row,col,Map, 0,18,13,-1);

    wall_row(row,col,Map, 0,2, 11,-1);
    wall_row(row,col,Map, 0,2, 15,-1);
    wall_row(row,col,Map, 16,18, 11,-1);
    wall_row(row,col,Map, 16,18, 15,-1);

    wall_col(row,col,Map, 0,9, 0,WALL_30);
    wall_col(row,col,Map, 17,31, 0,WALL_30);
    wall_row(row,col,Map, 0, 18, 0,WALL_30);
    wall_row(row,col,Map, 0, 18, 31,WALL_30);
    wall_col(row,col,Map, 0,9, 18,WALL_30);
    wall_col(row,col,Map, 17,31, 18,WALL_30);

    wall_row(row,col,Map, 0, 3, 12,WALL_30);
    wall_row(row,col,Map, 0, 3, 14,WALL_30);
    wall_row(row,col,Map, 0, 3, 16,WALL_30);
    wall_row(row,col,Map, 3, 3, 15,WALL_30);
    wall_row(row,col,Map, 3, 3, 11,WALL_30);
    wall_row(row,col,Map, 0, 3, 10,WALL_30);

    wall_row(row,col,Map, 15,18,12,WALL_30);
    wall_row(row,col,Map, 15, 18, 14,WALL_30);
    wall_row(row,col,Map, 15, 18, 16,WALL_30);
    wall_row(row,col,Map, 15, 18, 10,WALL_30);
    wall_row(row,col,Map, 15, 15, 11,WALL_30);

    wall_row(row,col,Map, 15, 15, 15,WALL_30);

    wall_row(row,col,Map, 2, 3, 2,WALL_30);
    wall_row(row,col,Map, 2, 3, 3,WALL_30);
    wall_row(row,col,Map, 2, 4, 5,WALL_30);
    wall_row(row,col,Map, 2, 4, 8,WALL_30);
    wall_row(row,col,Map, 6, 8, 5,WALL_30);
    wall_row(row,col,Map, 6, 8, 8,WALL_30);
    wall_row(row,col,Map, 10, 12, 5,WALL_30);
    wall_row(row,col,Map, 10, 12, 8,WALL_30);
    wall_row(row,col,Map, 14, 16, 5,WALL_30);
    wall_row(row,col,Map, 14, 16, 8,WALL_30);

    wall_row(row,col,Map, 2, 2, 6,WALL_30);
    wall_row(row,col,Map, 4, 4, 7,WALL_30);
    wall_row(row,col,Map, 8, 8, 6,WALL_30);
    wall_row(row,col,Map, 6, 6, 7,WALL_30);
    wall_row(row,col,Map, 10, 10, 6,WALL_30);
    wall_row(row,col,Map, 16, 16, 6,WALL_30);
    wall_row(row,col,Map, 12, 12, 7,WALL_30);
    wall_row(row,col,Map, 14, 14, 7,WALL_30);

    wall_row(row,col,Map, 5, 7, 2,WALL_30);
    wall_row(row,col,Map, 5, 7, 3,WALL_30);

    wall_col(row,col,Map, 1,3, 9,WALL_30);

    wall_row(row,col,Map, 11,13, 2,WALL_30);
    wall_row(row,col,Map, 11,13, 3,WALL_30);
    wall_row(row,col,Map, 15,16, 3,WALL_30);
    wall_row(row,col,Map, 15,16, 2,WALL_30);

    wall_row(row,col,Map, 5,8, 10,WALL_30);
    wall_row(row,col,Map, 10,13, 10,WALL_30);
    wall_row(row,col,Map, 5,8, 16,WALL_30);
    wall_row(row,col,Map, 10,13, 16,WALL_30);
    wall_col(row,col,Map, 10,12, 5,WALL_30);
    wall_col(row,col,Map, 10,12, 13,WALL_30);
    wall_col(row,col,Map, 14,16, 5,WALL_30);
    wall_col(row,col,Map, 14,16, 13,WALL_30);

    wall_row(row,col,Map, 7,8, 12,WALL_30);
    wall_row(row,col,Map, 10,11, 12,WALL_30);
    wall_row(row,col,Map, 7,8, 14,WALL_30);
    wall_row(row,col,Map, 10,11, 14,WALL_30);

    wall_row(row,col,Map, 2,8, 18,WALL_30);
    wall_col(row,col,Map, 19,24, 2,WALL_30);
    wall_row(row,col,Map, 4,8, 20,WALL_30);
    wall_col(row,col,Map, 21,24, 4,WALL_30);
    wall_row(row,col,Map, 6,8, 22,WALL_30);
    wall_col(row,col,Map, 22,24, 6,WALL_30);
    wall_row(row,col,Map, 8,8, 24,WALL_30);

    wall_row(row,col,Map, 10,16, 18,WALL_30);
    wall_col(row,col,Map, 19,24, 16,WALL_30);
    wall_row(row,col,Map, 10,14, 20,WALL_30);
    wall_col(row,col,Map, 21,24, 14,WALL_30);
    wall_row(row,col,Map, 10,12, 22,WALL_30);
    wall_col(row,col,Map, 22,24, 12,WALL_30);
    wall_row(row,col,Map, 10,10, 24,WALL_30);

    wall_row(row,col,Map, 4,14, 26,WALL_30);
    wall_col(row,col,Map, 27,29, 9,WALL_30);

    wall_col(row,col,Map, 26,29, 2,WALL_30);
    wall_row(row,col,Map, 3,4, 28,WALL_30);
    wall_row(row,col,Map, 4,4, 29,WALL_30);
    wall_row(row,col,Map, 6,7, 28,WALL_30);
    wall_row(row,col,Map, 6,7, 29,WALL_30);
    wall_row(row,col,Map, 11,12, 28,WALL_30);
    wall_row(row,col,Map, 11,12, 29,WALL_30);

    wall_col(row,col,Map, 26,29, 16,WALL_30);
    wall_row(row,col,Map, 14,15, 28,WALL_30);
    wall_row(row,col,Map, 14,14, 29,WALL_30);

    wall_row(row,col,Map, 1,1, 6,big_point);
    wall_row(row,col,Map, 15,15, 29,big_point);
    wall_row(row,col,Map, 3,3, 19,big_point);
    wall_row(row,col,Map, 13,13, 1,big_point);


    ghost[0]->x = 8;
    ghost[0]->y = 13;
    ghost[0]->init_x = 8;
    ghost[0]->init_y = 13;
    ghost[0]->state = ghost1_front;
    ghost[1]->x = 10;
    ghost[1]->y = 13;
    ghost[1]->init_x = 10;
    ghost[1]->init_y = 13;
    ghost[1]->state = ghost2_front;
    ghost[2]->x = 9;
    ghost[2]->y = 13;
    ghost[2]->init_x = 9;
    ghost[2]->init_y = 13;
    ghost[2]->state = ghost3_front;
}


void Map3(int row,int col,Object **Map, Object **ghost)
{
    point_map(row, col, Map);

    wall_row(row,col,Map, 0,44, 0,WALL_30);
    wall_row(row,col,Map, 0,44, 29,WALL_30);
    wall_col(row,col,Map, 0,29, 0,WALL_30);
    wall_col(row,col,Map, 0,29,44,WALL_30);
    wall_col(row,col,Map, 2,7, 2,WALL_30);
    wall_col(row,col,Map, 11,11,1,WALL_30);
    wall_col(row,col,Map, 2,2,1,WALL_30);
    wall_row(row,col,Map, 3,4,6,WALL_30);
    wall_col(row,col,Map, 2,6,4,WALL_30);
    wall_row(row,col,Map, 2,4,9,WALL_30);
    wall_row(row,col,Map, 4,4,8,WALL_30);
    wall_col(row,col,Map, 10,11,3,WALL_30);
    wall_row(row,col,Map, 3,5,13,WALL_30);
    wall_col(row,col,Map, 11,13,5,WALL_30);
    wall_col(row,col,Map, 13,13,1,WALL_30);
    wall_row(row,col,Map, 2,4,15,WALL_30);
    wall_col(row,col,Map, 14,14,4,WALL_30);
    wall_col(row,col,Map, 15,18,2,WALL_30);
    wall_col(row,col,Map, 18,18,3,WALL_30);
    wall_col(row,col,Map, 20,20,3,WALL_30);
    wall_row(row,col,Map, 1,3,20,WALL_30);
    wall_row(row,col,Map, 4,6,17,WALL_30);
    wall_col(row,col,Map, 17,20,5,WALL_30);
    wall_row(row,col,Map, 3,4,22,WALL_30);
    wall_row(row,col,Map, 1,1,22,WALL_30);
    wall_row(row,col,Map, 1,4,24,WALL_30);
    wall_row(row,col,Map, 4,4,23,WALL_30);
    wall_col(row,col,Map, 22,23,6,WALL_30);
    wall_col(row,col,Map, 23,25,7,WALL_30);
    wall_row(row,col,Map, 6,6,25,WALL_30);
    wall_row(row,col,Map, 1,2,26,WALL_30);
    wall_row(row,col,Map, 2,2,27,WALL_30);
    wall_row(row,col,Map, 3,6,27,WALL_30);
    wall_row(row,col,Map, 4,4,26,WALL_30);
    wall_col(row,col,Map, 23,25,9,WALL_30);
    wall_col(row,col,Map, 25,27,10,WALL_30);
    wall_row(row,col,Map, 8,10,27,WALL_30);
    wall_row(row,col,Map, 8,8,28,WALL_30);
    wall_col(row,col,Map, 19,20,7,WALL_30);
    wall_col(row,col,Map, 20,21,8,WALL_30);
    wall_row(row,col,Map, 6,8,15,WALL_30);
    wall_col(row,col,Map, 15,17,8,WALL_30);
    wall_col(row,col,Map, 25,25,8,WALL_30);
    wall_col(row,col,Map, 17,18,9,WALL_30);
    wall_row(row,col,Map, 10,11,18,WALL_30);
    wall_col(row,col,Map, 18,20,11,WALL_30);
    wall_col(row,col,Map, 20,21,10,WALL_30);
    wall_col(row,col,Map, 1,4,6,WALL_30);
    wall_row(row,col,Map, 7,8,3,WALL_30);
    wall_col(row,col,Map, 4,6,8,WALL_30);
    wall_col(row,col,Map, 6,7,6,WALL_30);
    wall_row(row,col,Map, 7,8,7,WALL_30);
    wall_row(row,col,Map, 6,9,9,WALL_30);
    wall_col(row,col,Map, 10,12,7,WALL_30);
    wall_row(row,col,Map, 7,7,14,WALL_30);
    wall_row(row,col,Map, 8,10,1,WALL_30);
    wall_row(row,col,Map, 9,10,11,WALL_30);
    wall_col(row,col,Map, 12,13,10,WALL_30);
    wall_row(row,col,Map, 9,9,13,WALL_30);
    wall_row(row,col,Map, 10,12,15,WALL_30);
    wall_col(row,col,Map, 16,16,11,WALL_30);
    wall_row(row,col,Map, 10,12,3,WALL_30);
    wall_col(row,col,Map, 1,3,12,WALL_30);
    wall_col(row,col,Map, 5,5,9,WALL_30);
    wall_col(row,col,Map, 4,8,11,WALL_30);
    wall_col(row,col,Map, 7,7,10,WALL_30);
    wall_row(row,col,Map, 11,13,10,WALL_30);
    wall_col(row,col,Map, 7,10,13,WALL_30);
    wall_row(row,col,Map, 13,15,7,WALL_30);
    wall_row(row,col,Map, 13,15,5,WALL_30);
    wall_col(row,col,Map, 3,4,15,WALL_30);
    wall_col(row,col,Map, 1,1,14,WALL_30);
    wall_col(row,col,Map, 1,1,15,WALL_30);
    wall_col(row,col,Map, 3,3,13,WALL_30);
    wall_col(row,col,Map, 13,13,11,WALL_30);
    wall_row(row,col,Map, 12,12,11,WALL_30);
    wall_row(row,col,Map, 11,14,23,WALL_30);
    wall_col(row,col,Map, 22,24,12,WALL_30);
    wall_col(row,col,Map, 21,22,14,WALL_30);
    wall_row(row,col,Map, 12,13,26,WALL_30);
    wall_col(row,col,Map, 28,28,12,WALL_30);
    wall_col(row,col,Map, 25,26,14,WALL_30);
    wall_row(row,col,Map, 15,16,25,WALL_30);
    wall_col(row,col,Map, 27,27,14,WALL_30);
    wall_row(row,col,Map, 16,18,27,WALL_30);
    wall_col(row,col,Map, 26,29,18,WALL_30);
    wall_row(row,col,Map, 13,16,19,WALL_30);
    wall_col(row,col,Map, 18,20,16,WALL_30);
    wall_row(row,col,Map, 13,14,17,WALL_30);
    wall_col(row,col,Map, 16,16,14,WALL_30);
    wall_row(row,col,Map, 16,17,22,WALL_30);
    wall_col(row,col,Map, 22,23,16,WALL_30);
    wall_row(row,col,Map, 13,15,13,WALL_30);
    wall_col(row,col,Map, 12,14,14,WALL_30);
    wall_row(row,col,Map, 15,17,10,WALL_30);
    wall_col(row,col,Map, 9,10,15,WALL_30);
    wall_col(row,col,Map, 11,11,16,WALL_30);
    wall_col(row,col,Map, 13,15,17,WALL_30);
    wall_col(row,col,Map, 15,16,16,WALL_30);
    wall_col(row,col,Map, 2,4,17,WALL_30);
    wall_col(row,col,Map, 4,6,18,WALL_30);
    wall_col(row,col,Map, 6,8,17,WALL_30);
    wall_col(row,col,Map, 3,3,16,WALL_30);
    wall_row(row,col,Map, 18,20,12,WALL_30);
    wall_col(row,col,Map, 8,10,19,WALL_30);
    wall_row(row,col,Map, 19,20,6,WALL_30);
    wall_row(row,col,Map, 20,22,4,WALL_30);
    wall_col(row,col,Map, 1,5,22,WALL_30);
    wall_row(row,col,Map, 19,20,2,WALL_30);
    wall_row(row,col,Map, 21,22,8,WALL_30);
    wall_col(row,col,Map, 7,9,22,WALL_30);
    wall_col(row,col,Map, 10,10,20,WALL_30);
    wall_col(row,col,Map, 14,17,19,WALL_30);
    wall_col(row,col,Map, 17,17,18,WALL_30);
    wall_col(row,col,Map, 19,20,18,WALL_30);
    wall_row(row,col,Map, 19,20,20,WALL_30);
    wall_col(row,col,Map, 21,21,19,WALL_30);
    wall_row(row,col,Map, 19,21,23,WALL_30);
    wall_col(row,col,Map, 22,22,21,WALL_30);
    wall_col(row,col,Map, 24,25,20,WALL_30);
    wall_row(row,col,Map, 20,21,27,WALL_30);
    wall_col(row,col,Map, 28,28,21,WALL_30);

    wall_row(row,col,Map, 22,24,25,WALL_30);
    wall_col(row,col,Map, 26,27,23,WALL_30);
    wall_col(row,col,Map, 11,11,20,WALL_30);
    wall_row(row,col,Map, 20,22,15,WALL_30);
    wall_row(row,col,Map, 24,26,3,WALL_30);
    wall_col(row,col,Map, 2,2,26,WALL_30);
    wall_col(row,col,Map, 4,5,25,WALL_30);
    wall_col(row,col,Map, 5,5,23,WALL_30);
    wall_col(row,col,Map, 2,2,24,WALL_30);
    wall_col(row,col,Map, 14,14,20,WALL_30);
    wall_col(row,col,Map, 11,13,22,WALL_30);
    wall_row(row,col,Map, 23,24,12,WALL_30);
    wall_row(row,col,Map, 22,24,21,WALL_30);
    wall_col(row,col,Map, 23,24,23,WALL_30);
    wall_row(row,col,Map, 24,27,7,WALL_30);
    wall_col(row,col,Map, 5,6,27,WALL_30);
    wall_col(row,col,Map, 8,10,24,WALL_30);
    wall_col(row,col,Map, 9,13,26,WALL_30);
    wall_row(row,col,Map, 24,28,14,WALL_30);
    wall_col(row,col,Map, 17,17,21,WALL_30);
    wall_col(row,col,Map, 17,18,20,WALL_30);
    wall_row(row,col,Map, 22,24,19,WALL_30);
    wall_col(row,col,Map, 18,18,23,WALL_30);
    wall_row(row,col,Map, 25,26,17,WALL_30);
    wall_col(row,col,Map, 16,16,26,WALL_30);
    wall_col(row,col,Map, 17,17,23,WALL_30);
    wall_col(row,col,Map, 15,15,24,WALL_30);
    wall_col(row,col,Map, 2,3,28,WALL_30);
    wall_col(row,col,Map, 3,6,29,WALL_30);
    wall_col(row,col,Map, 8,9,29,WALL_30);
    wall_col(row,col,Map, 9,9,28,WALL_30);
    wall_col(row,col,Map, 13,13,28,WALL_30);
    wall_row(row,col,Map, 28,30,11,WALL_30);
    wall_col(row,col,Map, 12,15,30,WALL_30);
    wall_col(row,col,Map, 25,25,18,WALL_30);
    wall_row(row,col,Map, 26,28,19,WALL_30);
    wall_col(row,col,Map, 16,18,28,WALL_30);
    wall_col(row,col,Map, 1,1,30,WALL_30);
    wall_col(row,col,Map, 27,28,25,WALL_30);
    wall_col(row,col,Map, 25,27,26,WALL_30);
    wall_row(row,col,Map, 25,28,23,WALL_30);
    wall_col(row,col,Map, 21,22,26,WALL_30);
    wall_row(row,col,Map, 28,30,27,WALL_30);
    wall_col(row,col,Map, 21,21,28,WALL_30);
    wall_col(row,col,Map, 24,25,28,WALL_30);
    wall_row(row,col,Map, 29,31,17,WALL_30);
    wall_row(row,col,Map, 30,32,25,WALL_30);
    wall_col(row,col,Map, 26,28,32,WALL_30);
    wall_row(row,col,Map, 30,32,19,WALL_30);
    wall_col(row,col,Map, 16,21,33,WALL_30);
    wall_row(row,col,Map, 29,31,21,WALL_30);
    wall_col(row,col,Map, 22,23,30,WALL_30);
    wall_row(row,col,Map, 31,32,3,WALL_30);
    wall_row(row,col,Map, 32,33,2,WALL_30);
    wall_col(row,col,Map, 5,6,31,WALL_30);
    wall_row(row,col,Map, 32,34,5,WALL_30);
    wall_col(row,col,Map, 4,4,34,WALL_30);
    wall_col(row,col,Map, 1,4,35,WALL_30);
    wall_row(row,col,Map, 33,35,7,WALL_30);
    wall_col(row,col,Map, 8,9,35,WALL_30);
    wall_col(row,col,Map, 8,9,31,WALL_30);
    wall_row(row,col,Map, 32,33,9,WALL_30);
    wall_row(row,col,Map, 31,32,11,WALL_30);
    wall_col(row,col,Map, 11,13,34,WALL_30);
    wall_row(row,col,Map, 32,34,13,WALL_30);
    wall_row(row,col,Map, 32,35,15,WALL_30);
    wall_row(row,col,Map, 32,34,23,WALL_30);
    wall_col(row,col,Map, 24,25,34,WALL_30);
    wall_col(row,col,Map, 27,27,33,WALL_30);
    wall_col(row,col,Map, 26,27,35,WALL_30);
    wall_row(row,col,Map, 36,38,6,WALL_30);
    wall_col(row,col,Map, 19,21,35,WALL_30);
    wall_row(row,col,Map, 36,37,21,WALL_30);
    wall_row(row,col,Map, 35,37,17,WALL_30);
    wall_col(row,col,Map, 14,19,37,WALL_30);
    wall_col(row,col,Map, 11,13,36,WALL_30);
    wall_col(row,col,Map, 22,24,36,WALL_30);
    wall_row(row,col,Map, 37,39,23,WALL_30);
    wall_col(row,col,Map, 26,28,37,WALL_30);
    wall_col(row,col,Map, 25,26,38,WALL_30);
    wall_col(row,col,Map, 2,4,37,WALL_30);
    wall_row(row,col,Map, 37,40,8,WALL_30);
    wall_row(row,col,Map, 38,39,2,WALL_30);
    wall_col(row,col,Map, 4,4,39,WALL_30);
    wall_col(row,col,Map, 4,7,40,WALL_30);
    wall_col(row,col,Map, 28,28,39,WALL_30);
    wall_row(row,col,Map, 41,43,2,WALL_30);
    wall_col(row,col,Map, 3,4,42,WALL_30);
    wall_row(row,col,Map, 40,41,26,WALL_30);
    wall_col(row,col,Map, 27,27,41,WALL_30);
    wall_col(row,col,Map, 27,27,43,WALL_30);
    wall_col(row,col,Map, 25,25,42,WALL_30);
    wall_col(row,col,Map, 25,25,40,WALL_30);
    wall_col(row,col,Map, 6,7,42,WALL_30);
    wall_col(row,col,Map, 9,10,42,WALL_30);
    wall_col(row,col,Map, 7,7,43,WALL_30);
    wall_col(row,col,Map, 9,9,37,WALL_30);
    wall_col(row,col,Map, 11,12,38,WALL_30);
    wall_col(row,col,Map, 10,11,39,WALL_30);
    wall_col(row,col,Map, 19,19,43,WALL_30);
    wall_col(row,col,Map, 21,21,43,WALL_30);
    wall_row(row,col,Map, 39,41,21,WALL_30);
    wall_col(row,col,Map, 22,23,41,WALL_30);
    wall_col(row,col,Map, 23,23,42,WALL_30);
    wall_row(row,col,Map, 39,41,19,WALL_30);
    wall_col(row,col,Map, 17,18,39,WALL_30);
    wall_col(row,col,Map, 14,15,39,WALL_30);
    wall_row(row,col,Map, 40,42,15,WALL_30);
    wall_col(row,col,Map, 16,17,41,WALL_30);
    wall_col(row,col,Map, 15,15,43,WALL_30);
    wall_col(row,col,Map, 17,17,42,WALL_30);
    wall_col(row,col,Map, 10,10,40,WALL_30);
    wall_row(row,col,Map, 40,41,13,WALL_30);
    wall_col(row,col,Map, 12,12,41,WALL_30);
    wall_col(row,col,Map, 14,14,43,WALL_30);
    wall_col(row,col,Map, 12,12,42,WALL_30);

    wall_row(row,col,Map, 23,23,28,big_point);
    wall_row(row,col,Map, 3,3,26,big_point);
    wall_row(row,col,Map, 28,28,20,big_point);
    wall_row(row,col,Map, 39,39,6,big_point);
    wall_row(row,col,Map, 17,17,5,big_point);
    wall_row(row,col,Map, 7,7,6,big_point);
    wall_row(row,col,Map, 43,43,4,big_point);
    wall_row(row,col,Map, 25,25,2,big_point);
    wall_row(row,col,Map, 15,15,27,big_point);
    wall_row(row,col,Map, 20,20,16,big_point);
    wall_row(row,col,Map, 43,43,16,big_point);
    wall_row(row,col,Map, 41,41,25,big_point);
    wall_row(row,col,Map, 10,10,19,big_point);
    wall_row(row,col,Map, 1,1,23,big_point);
    wall_row(row,col,Map, 33,33,28,big_point);

    ghost[0]->x = 23;
    ghost[0]->y = 13;
    ghost[0]->init_x = 23;
    ghost[0]->init_y = 13;
    ghost[0]->state = ghost1_front;
    ghost[1]->x = 23;
    ghost[1]->y = 14;
    ghost[1]->init_x = 23;
    ghost[1]->init_y = 14;
    ghost[1]->state = ghost2_front;
    ghost[2]->x = 23;
    ghost[2]->y = 15;
    ghost[2]->init_x = 23;
    ghost[2]->init_y = 15;
    ghost[2]->state = ghost3_front;
    ghost[3]->x = 23;
    ghost[3]->y = 16;
    ghost[3]->init_x = 23;
    ghost[3]->init_y = 16;
    ghost[3]->state = ghost4_front;
}
