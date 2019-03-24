/*
 =====
 Seokho Han
 700657609
 CS3500
 
 Minesweeper game by C language
 - If user chooses a cell which has a mine, the user will lose.
 - If user discovers all cells which do not have a mine, the user will win the game
 - Use flood_fill algorithm to make a chain effect that discovers all non-mine-cells that are neighboring by a chosen cell.
 =====
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//cell is for a output
//mine is for a number of mines neighboring to the cell
//discover is for the cell is whether discovered(1) or not(0)
typedef struct Mine{
    char cell;
    int mine;
    int discover;
} mine_t;

//counting how many cells are discovered
static int c = 0;

void flood_fill(mine_t **grid, int x, int y, int num){
    int i, j;
    i = x;
    j = y;
    
    //For chain effect
    if(i >=1 && i<=10 && j>=1 && j<=10){
        if(grid[i][j].discover == 0){
            if(grid[i][j].cell != '*'){//Not mine
                grid[i][j].discover = 1;//the cell is discovered
                c += 1;//increment c by one
                if((c + num) == 100){
                    printf("-----You Win-----\n");
                    for(i=1; i<11; i++){
                        for(j=1; j<11; j++){
                            if(grid[i][j].cell == '*'){
                                printf("%c ", grid[i][j].cell);
                            }else{
                                printf("%d ", grid[i][j].mine);
                            }
                        }
                        printf("\n");
                    }
                    printf("\n");
                    exit(0);
                }
                if(grid[i][j].mine ==0){//call itself
                    flood_fill(grid, i+1, j+1, num);
                    flood_fill(grid, i+1, j, num);
                    flood_fill(grid, i+1, j-1, num);
                    flood_fill(grid, i, j+1, num);
                    flood_fill(grid, i, j-1, num);
                    flood_fill(grid, i-1, j+1, num);
                    flood_fill(grid, i-1, j, num);
                    flood_fill(grid, i-1, j-1, num);
                }
            }else{//If user chooses the cell containing a mine
                for(i=1; i<11; i++){
                    for(j=1; j<11; j++){
                        if(grid[i][j].cell == '*'){
                            printf("%c ", grid[i][j].cell);
                        }else{
                            printf("%d ", grid[i][j].mine);
                        }
                    }
                    printf("\n");
                }
                printf("\n-----You lost-----\n-----Game Over-----\n");
                //Game over
                exit(0);
            }
        }
    }
}

int main(int argc, char **argv){
    
    int i, j, h, w, x, y;
    //set a random integer to numOfMines
    //count is for mining the random number of mines
    int numOfMines, count;
    //mine_t structure for making a 2D array
    mine_t **grid;
    
    //random number of mines and prinf how many mines are in game
    srand(time(NULL));
    numOfMines = rand()%10 + 1;
    printf("Welcome to minsweeper game v.1.0\t<created by Seokho Han>\n%d mines are set\n\n", numOfMines);
    
    //make 2D array
    grid = (mine_t **)malloc(sizeof(mine_t *) * 12);
    for(i=0; i<12; i++){
        grid[i] = (mine_t *)malloc(sizeof(mine_t) * 12);
    }
    
    //set values
    for(i=0; i<12; i++){
        for(j=0; j<12; j++){
            grid[i][j].cell = '.';//cell without the mine
            grid[i][j].discover = 0;//Not discovered
        }
    }
    
    //set mines till numOfMines will be equal to count
    while(count != numOfMines){
        h = rand()%10+1;
        w = rand()%10+1;
        if(grid[h][w].cell != '*'){//if the cell does not have the mine
            grid[h][w].cell = '*';
            count++;
        }
    }
    
    //set a number of mines in its neighboring squares.
    int d;
    for(i=1; i<11; i++){
        for(j=1; j<11; j++){
            d = 0;
            if(grid[i-1][j-1].cell == '*')//left top diagonal
                d+=1;
            if(grid[i-1][j].cell == '*')//upper
                d+=1;
            if(grid[i-1][j+1].cell == '*')//right top diagonal
                d+=1;
            if(grid[i][j-1].cell == '*')//left
                d+=1;
            if(grid[i][j+1].cell == '*')//right
                d+=1;
            if(grid[i+1][j-1].cell == '*')//left bottom diagonal
                d+=1;
            if(grid[i+1][j].cell == '*')//bottom
                d+=1;
            if(grid[i+1][j+1].cell == '*')//right bottom diagonal
                d+=1;
            
            if(grid[i][j].cell != '*'){
                grid[i][j].mine = d;//set a number that indicates how many neighboring mines exist
            }
        }
    }
    
    //print the grid
    for(i=0; i<12; i++){
        for(j=0; j<12; j++){
            if(i ==0 && j==0){
                printf("  ");
            }
            if(i == 0 && j >=1 && j <=10){
                if(j==10){
                    printf(" %d", j);
                }else
                    printf("%2d", j);//print index of row
                
            }else if(j == 0 && i >=1 && i <= 10){
                printf("%2d ", i);//print index of col
            }
            //print out the grid
            else if(i >= 1 && i <=10 && j >= 1 && j <= 10){
                if(grid[i][j].discover == 1){
                    if(grid[i][j].cell == '*')
                        printf("%c ", grid[i][j].cell);
                    else
                        printf("%d ", grid[i][j].mine);
                }else{
                    printf("o ");
                }
            }
        }
        printf("\n");
    }
    //end of printing the grid
    
    
    //play the game till it ends
    while(1){
        printf("%d mines remaining\n", numOfMines);
        printf("\nEnter x y: (1~10)");
        scanf("%d %d", &x, &y);
        printf("\n");
        flood_fill(grid, x, y, numOfMines);
        //print out the grid
        for(i=0; i<12; i++){
            for(j=0; j<12; j++){
                if(i ==0 && j==0){
                    printf("  ");
                }
                if(i == 0 && j >=1 && j <=10){
                    if(j==10){
                        printf(" %d", j);
                    }else
                        printf("%2d", j);//print index of row
                    
                }else if(j == 0 && i >=1 && i <= 10){
                    printf("%2d ", i);//print index of col
                }
                //print out the grid
                else if(i >= 1 && i <=10 && j >= 1 && j <= 10){
                    if(grid[i][j].discover == 1){
                        if(grid[i][j].cell == '*')
                            printf("%c ", grid[i][j].cell);
                        else
                            printf("%d ", grid[i][j].mine);
                    }else{
                        printf("o ");
                    }
                }
            }
            printf("\n");
        }
    }
    
    return 0;
}
