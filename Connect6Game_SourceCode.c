/* 
 * File:   TheConnect6Game.c
 * Author: aamirmuh
 *
 * Created on November 9, 2014, 1:24 AM
 */
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

void printBoard(char board[22][22], int n);
int playerMove(char board[22][22], char colour[6], char bOrW, int n, int r, int c);
void complexComputerMove(char board[22][22], int n, char wOrB);
void simpleComputerMove(char board[22][22], int n, char wOrB);
int drawChecker(char board[22][22], int n);
int checkWinner(char board[22][22], int n);
int findLongest(char board[22][22], int n, int row, int col);
int horizontalLength(char board[22][22], int n, int row, int col, char wOrB);
int verticalLength(char board[22][22], int n, int row, int col, char wOrB);
int downDiagonalLength(char board[22][22], int n, int row, int col, char wOrB);
int upDiagonalLength(char board[22][22], int n, int row, int col, char wOrB);

int main()
{
	system("Color 0A");
	printf("WELCOME TO CONNECT6\n\n");
    int dimensions;
    printf("Enter board dimensions (n), n>=6 and n<=21: ");
    fflush(stdout);
    scanf("%d", &dimensions);
    
    //Declaration and initialization of  the array
    char board[22][22];
    int row, col;
    for(row = 0; row < dimensions; row++)
    {
        for(col = 0; col < dimensions; col++)
        {
            board[row][col] = '-';
        }
    }
    
    //User input must be between 6 and 21
    if(dimensions >= 6 && dimensions <= 21)
    {
        printBoard(board, dimensions);
    }
    
    char complexComputer;
    printf("Computer playing B or W?: ");
    fflush(stdout);
    scanf(" %c", &complexComputer);
    
    //Blocked square
    int r = 0, c = 0;
    while(r != -1 && c != -1)
    {
       printf("Enter position (ROW COL) of blocked square; (-1 -1) to finish: ");
       fflush(stdout);
       scanf("%2d %2d", &r, &c);
       
       if(r >= dimensions || c >= dimensions) printf("Out of range row or column\n");
       else if(board[r][c] == 'R') printf("Position already occupied, try again\n");
       else if(r != -1 && c != -1) 
       {
           board[r][c] = 'R';
           printBoard(board, dimensions);
       }    
    }
    
    char b = 'B', w = 'W';
    char black[6] = {'B', 'l', 'a', 'c', 'k'};
    char white[6] = {'W', 'h', 'i', 't', 'e'};
    //25 is a randomly selected large number to make program enter while loop
    int inputR = 25, inputC = 25;
    if(complexComputer == 'W')
    {
        while(1)
        {    
            if(!playerMove(board, black, b, dimensions, inputR, inputC)) break; 
            //simpleComputerMove(board, dimensions, b); // for making computers play against each other
            if(checkWinner(board, dimensions)) break;
            complexComputerMove(board, dimensions, w);
            if(checkWinner(board, dimensions)) break;
            
        }
    }
    else if(complexComputer == 'B')
    {
        while(1)
        {    
            complexComputerMove(board, dimensions, b);
            if(checkWinner(board, dimensions)) break;
            if(!playerMove(board, white, w, dimensions, inputR, inputC)) break;
            //simpleComputerMove(board, dimensions, w); //for making computers play against each other
            if(checkWinner(board, dimensions)) break;
        }
    }
	
	int exitKey; 
	printf("\n\n");
    fflush(stdout);
    scanf(" %d", &exitKey); //so program waits for user input before closing terminal window
   
    return 0;
}


void printBoard(char board[22][22], int n)
{
	system("Color 0A");
	system("cls");
    int row, col;
    for(row = 0; row < n; row++)
    {
        for(col = 0; col < n; col++)
        {
            printf("%c", board[row][col]);
        }
        printf("\n");
    }
}


int playerMove(char board[22][22], char colour[6], char bOrW, int n, int r, int c)
{
    while(r != -1 && ((board[r][c] != '-') || (r >= n || c >= n)))
    {
        printf("Enter %s Move (ROW COL): ", colour);
        fflush(stdout);
        scanf("%2d %2d", &r, &c);
        
        if(r >= n || c >= n)
        {
            printf("Out of range row or column\n");
        }
        else if(board[r][c] != '-' && r != -1)
        {
            printf("That square is already occupied or blocked\n");
        }
    } 
    if(r != -1 && c != -1)
    {
        board[r][c] = bOrW;
        printBoard(board, n);
        return 1;
    }
    return 0;
}

int findLongest(char board[22][22], int n, int row, int col)
{
    int longest = 0;
    char b = 'B', w = 'W';
    int h = 0, v = 0, d1 = 0, d2 = 0;
    if(board[row][col] == 'B' || board[row][col] == 'W')
    {
        if(board[row][col] == 'B')
        {
            h = horizontalLength(board, n, row, col, b);
            v = verticalLength(board, n, row, col, b);
            d1 = upDiagonalLength(board, n, row, col, b);
            d2 = downDiagonalLength(board, n, row, col, b);          
        }
        else if(board[row][col] == 'W')
        {
            h = horizontalLength(board, n, row, col, w);
            v = verticalLength(board, n, row, col, w);
            d1 = upDiagonalLength(board, n, row, col, w);
            d2 = downDiagonalLength(board, n, row, col, w);
        }
        
        if(h >= v && h >= d1 && h >= d2)  longest = h;
        else if(v >= h && v >= d1 && v >= d2)  longest = v;
        else if(d1 >= h && d1 >= v && d1 >= d2)  longest = d1;
        else if(d2 >= h && d2 >= v && d2 >= d1)  longest = d2;
    }
    
    return longest;
}

int horizontalLength(char board[22][22], int n, int row, int col, char wOrB)
{
    int c;
    int length1 = 0, length2 = 0, length = 0;
    for(c = col; c < n; c++)
    {
        if(board[row][c] == wOrB)
        {
            length1++;
        }
        else if(board[row][c] != wOrB) break;
    }
        
    for(c = (col - 1); c >= 0; c--)
    {
        if(board[row][c] == wOrB)
        {
            length2++;
        }
        else if(board[row][c] != wOrB) break;
    }
    length = length1 + length2;
    
    return length;
}

int verticalLength(char board[22][22], int n, int row, int col, char wOrB)
{
    int r;
    int length1 = 0, length2 = 0, length = 0;
    for(r = row; r < n; r++)
    {
        if(board[r][col] == wOrB)
        {
            length1++;
        }
        else if(board[r][col] != wOrB) break;
    }
    for(r = (row - 1); r >= 0; r--)
    {
        if(board[r][col] == wOrB)
        {
            length2++;
        }
        else if(board[r][col] != wOrB) break;
    }
    length = length1 + length2;
    
    return length;
}

int downDiagonalLength(char board[22][22], int n, int row, int col, char wOrB)
{
    int r, c;
    int length = 0, length1 = 0, length2 = 0;
    for(r = row, c = col; r < n, c < n; r++, c++)
    {
        if(board[r][c] == wOrB)
        {
            length1++;
        }
        else if(board[r][c] != wOrB) break;
    }
    
    if(row != 0 && col != 0)
    {
        for(r = (row - 1), c = (col - 1); r >= 0, c >= 0; r--, c--)
        {
            if(board[r][c] == wOrB)
            {
                length2++;
            }
            else if(board[r][c] != wOrB) break;
        }
    }
    
    length = length1 + length2;
    
    return length;
}

int upDiagonalLength(char board[22][22], int n, int row, int col, char wOrB)
{
    int r, c;
    int length = 0, length1 = 0, length2 = 0;
    if(row != 0)
    {
        for(r = row, c = col; r >= 0, c < n; r--, c++)
        {
            if(board[r][c] == wOrB)
            {
                length1++;
            }
            else if(board[r][c] != wOrB) break;
        }
    }
    
    
    if(col != 0)
    {
        for(r = (row + 1), c = (col - 1); r < n, c >= 0; r++, c--)
        {
            if(board[r][c] == wOrB)
            {
                length2++;
            }
            else if(board[r][c] != wOrB) break;
        }
    }
    length = length1 + length2;
    
    return length;    
}

int checkWinner(char board[22][22], int n)
{
    int result, x, y;
    for(x = 0; x < n; x++)
    {
        for(y = 0; y < n; y++)
        {
            result = findLongest(board, n, x, y);
            if(result >= 6)
            {
                if(board[x][y] == 'B') 
				{
					printf("\nBlack player wins. \nPress ENTER after typing in '0' key to exit.");
				}
                else if(board[x][y] == 'W') 
				{
					printf("\nWhite player wins. \nPress ENTER after typing in '0' key to exit.");
				}
                return 1;
                break;
            }
            else if(!drawChecker(board, n))
            {
                printf("\nDraw!\nPress any key to exit.");
            }
        }
        if(result >= 6) break; 
        else if(!drawChecker(board, n)) break;
    }
    return 0;
}

int drawChecker(char board[22][22], int n)
{
    int r, c;
    for(r = 0; r < n; r++)
    {
        for(c = 0; c < n; c++)
        {
            if(board[r][c] == '-')
            {
                return 1;
                break;
            }
        }
        if(board[r][c] == '-') break;
    }
    return 0;
}

void complexComputerMove(char board[22][22], int n, char wOrB)
{
    int scorekeeper[n][n];
    int s, t;
    //Assigning default values to positions
    int w = n / 6;
    
    if(n <= 12)
    {
        for(s = 0; s < n; s++)
        {
            for(t = 0; t < n; t++)
            {
                if(s == (n / 2))
                {
                    scorekeeper[s][t] = 2;
                }
                else
                {
                    scorekeeper[s][t] = 1;
                }
            }
        }
    }
    else
    {
       for(s = 0; s < n; s++)
        {
            for(t = 0; t < n; t++)
            {
                if( (t >= 0 && t < w) || (t < n && t >= (n - w)) || (s >= 0 && s < w)
                    || (s < n && s >= (n - w)) )
                {
                    scorekeeper[s][t] = 0;
                }
                else if( (t >= w && t < (2 * w)) || (t < n && t >= (n - (2 * w))) || 
                    (s >= w && s < (2 * w)) || (s < n && s >= (n - (2 * w))) )
                {
                    scorekeeper[s][t] = 1;
                }
                else scorekeeper[s][t] = 2;
            }
        } 
    }
    
    //Counting Blocks
    int blockCount = 0;
    int p, q;
    for(p = 0; p < n; p++)
    {
        for(q = 0; q < n; q++)
        {
            if(board[p][q] == 'R')
            {
                blockCount++;
            }
        }
    }
    int checker = 0;
    if(blockCount >= n)
    {
        checker = 1;
    }
    
    int score = 0, longestBlack = 0, longestWhite = 0;
    int x, y;
    for(x = 0; x < n; x++)
    {
        for(y = 0; y < n; y++)
        {
            if(board[x][y] == '-')
            {
                //Building upon basic algorithm
                board[x][y] = 'B';
                longestBlack = findLongest(board, n, x, y);
                board[x][y] = 'W';
                longestWhite = findLongest(board, n, x, y);
                score = scorekeeper[x][y] + (longestBlack) + (longestWhite);
                scorekeeper[x][y] = score;
                board[x][y] = '-';
                
                if(score >= 7 && score < 9)
                {
                    if((longestBlack == 6 && longestWhite >= 1) || (longestBlack >= 1 && longestWhite == 6))
                    scorekeeper[x][y] = 30;
                }
                
                //Vital moves to ensure winning and not losing
                if(wOrB == 'B')
                {
                    if(longestBlack == 6)
                    {
                        scorekeeper[x][y] = 100;
                    }
                    if(longestWhite == 6)
                    {
                        scorekeeper[x][y] = 100;
                    }
                    if(longestWhite == 5)
                    {
                        scorekeeper[x][y] = 50;
                    }
                    if(longestBlack == 5)
                    {
                        scorekeeper[x][y] = 20;
                    }
                }
                else if(wOrB == 'W')
                {
                    if(longestWhite == 6)
                    {
                        scorekeeper[x][y] = 100;
                    }
                    if(longestBlack == 6)
                    {
                        scorekeeper[x][y] = 100;
                    }
                    if(longestBlack == 5)
                    {
                        scorekeeper[x][y] = 50;
                    }
                    if(longestWhite == 5)
                    {
                        scorekeeper[x][y] = 20;
                    }
                }
                
                //Ensuring efficient blocking
                board[x][y] = 'B';
                int blackVertical = verticalLength(board, n, x, y, 'B');
                int blackHorizontal = horizontalLength(board, n, x, y, 'B');
                board[x][y] = 'W';
                int whiteVertical = verticalLength(board, n, x, y, 'W');
                int whiteHorizontal = horizontalLength(board, n, x, y, 'W');
                board[x][y] = '-';
                //When computer is black
                if(wOrB == 'B' && checker == 0)
                {
                    if(longestWhite >= 3 && longestWhite < 5 )//SET BLOCKING VALUE
                    {
                        if( ((y < (n - 3)) && (y > 3)) && ((x < (n - 2)) && x > 2))
                        {
                            scorekeeper[x][y] = 12;
                        }
                        else if((y < (n - 3)) && (y > 3))
                        {
                            if(whiteHorizontal > 1)
                            {
                                scorekeeper[x][y] = 12;
                            } 
                        }
                        
                        else if((x < (n - 2)) && x > 2)
                        {
                            if(whiteVertical > 1)
                            {
                                scorekeeper[x][y] = 12;
                            }
                        }
                    }
                }
                //When computer is white
                else if(wOrB == 'W' && checker == 0)
                {
                    if((longestBlack >= 3 && longestBlack < 5))
                    {
                        if( ((y < (n - 3)) && (y > 3)) && ((x < (n - 2)) && x > 2))
                        {
                            scorekeeper[x][y] = 12;
                        }
                        else if((y < (n - 3)) && (y > 3))
                        {
                            if(blackHorizontal > 1)
                            {
                                scorekeeper[x][y] = 12;
                            } 
                        }
                        
                        else if((x < (n - 2)) && x > 2)
                        {
                            if(blackVertical > 1)
                            {
                                scorekeeper[x][y] = 12;
                            }
                        }
                        
                    }
                }
            }
            else if(board[x][y] != '-')
            {
                scorekeeper[x][y] = 0;
            }
            
            //Offensive move 
            //Horizontal Winner
            int move = horizontalLength(board, n, x, y, wOrB);
            
            if(board[x][y] == wOrB && checker == 0)   
            {
                if(move == 2 && board[x][y + 1] == '-' && 
                board[x][y + 2] == '-' && board[x][y + 3] == '-' && board[x][y + 4] == '-' && 
                board[x][y + 5] == '-' && board[x][y + 6] == '-' && board[x][y + 7] == '-' && 
                board[x][y + 8] != wOrB)
                {
                    scorekeeper[x][y + 3] = 9;
                }
                
                if(move == 1 && board[x][y - 1] == '-' && board[x][y - 2] == '-' && board[x][y - 3] == wOrB && 
                   board[x][y - 4] == wOrB && board[x][y - 5] != wOrB && board[x][y + 1] == '-' 
                   && board[x][y + 2] == '-' && board[x][y + 3] == '-' && board[x][y + 4] == '-'
                   && board[x][y + 5] != wOrB)
                {
                    scorekeeper[x][y + 3] = 9;
                }
                
                if(move == 1 && board[x][y - 1] == '-' && board[x][y - 2] == '-' && board[x][y - 3] == wOrB
                    && board[x][y - 4] == '-' && board[x][y - 5] == '-' && board[x][y - 6] == wOrB
                    && board[x][y - 7] == wOrB && board[x][y + 1] == '-' && board[x][y + 2] != wOrB)
                {
                    scorekeeper[x][y + 1] = 9;
                }
                
               if(move == 1 && board[x][y + 1] == '-' && board[x][y + 2] == '-' && board[x][y + 3] == wOrB
                        && board[x][y + 4] == wOrB && board[x][y + 5] != wOrB && board[x][y - 1] == '-'
                        && board[x][y - 2] == '-' && board[x][y - 3] == wOrB && board[x][y - 4] == wOrB
                        && board[x - 1][y + 1] == '-' && board[x - 2][y + 1] == '-' 
                       && board[x - 3][y + 1] == '-')
                {
                    scorekeeper[x - 1][y + 1] = 9;
                }
                
                if(move == 1 && board[x][y + 1] == '-' && board[x][y + 2] == '-' && board[x][y + 3] == wOrB
                        && board[x][y + 4] == wOrB && board[x][y + 5] != wOrB && board[x][y - 1] == '-'
                        && board[x][y - 2] == '-' && board[x][y - 3] == wOrB && board[x][y - 4] == wOrB
                        && board[x - 1][y + 1] == wOrB && board[x - 2][y + 1] == '-' 
                       && board[x - 3][y + 1] == '-')
                {
                    scorekeeper[x - 2][y + 1] = 9;
                }
                
                if(move == 1 && board[x][y + 1] == '-' && board[x][y + 2] == '-' && board[x][y + 3] == wOrB
                        && board[x][y + 4] == wOrB && board[x][y + 5] != wOrB && board[x][y - 1] == '-'
                        && board[x][y - 2] == '-' && board[x][y - 3] == wOrB && board[x][y - 4] == wOrB
                        && board[x - 1][y + 1] == wOrB && board[x - 2][y + 1] == wOrB 
                       && board[x - 3][y + 1] == '-')
                {
                    scorekeeper[x - 3][y + 1] = 9;
                }
                
                if(move == 1 && board[x][y - 1] == '-' && board[x][y - 2] == '-' && board[x][y - 3] == wOrB
                        && board[x][y - 4] == wOrB && board[x][y + 1] == '-' && board[x][y + 2] == '-' 
                        && board[x][y + 3] == wOrB && board[x][y + 4] == wOrB && board[x][y + 5] != wOrB
                        && board[x - 1][y + 1] == wOrB && board[x - 2][y + 1] == wOrB 
                        && board[x - 3][y + 1] == wOrB)
                {
                    scorekeeper[x][y + 1] = 9;
                }
       
                if(move == 2 && board[x][y - 1] == '-' && board[x][y - 2] == '-' && board[x][y - 3] == wOrB
                        && board[x][y - 4] == wOrB && board[x][y + 1] == wOrB
                        && board[x][y + 2] == '-' && board[x][y + 3] == wOrB && board[x][y + 4] == wOrB 
                        && board[x][y + 5] != wOrB && board[x - 1][y + 1] == wOrB 
                        && board[x - 2][y + 1] == wOrB && board[x - 3][y + 1] == wOrB)
                {
                    scorekeeper[x][y - 1] = 25; //WIN
                }
            }
        }
    }
    
    
    //The following finds largest score in 'scorekeeper' array
    int a, b;
    int largestScore = scorekeeper[0][0];
    for(a = 0; a < n; a++)
    {
        for(b = 0; b < n; b++)
        {
            if(scorekeeper[a][b] > largestScore)
            {
                largestScore = scorekeeper[a][b];
            }
        }
    }
    
    //Only for testing purposes
    /*int i ,j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
           printf("%d", scorekeeper[i][j]); 
        }
        printf("\n");
    }*/
    
    //Computer makes move based on the largest score
    bool found = false;
    int r, c;
    for(r = 0; r < n; r++)
    {
        for(c = 0; c < n; c++)
        {
            if(scorekeeper[r][c] == largestScore  && board[r][c] == '-' && !found)
            {
                board[r][c] = wOrB;
				printBoard(board, n);
                printf("Computer moves %c at %d %d\n", wOrB, r, c);
                found = true;
            }
        }
    }
}

void simpleComputerMove(char board[22][22], int n, char wOrB)
{
    int scorekeeper[n][n];
    int score = 0, longestBlack = 0, longestWhite = 0;
    int x, y;
    for(x = 0; x < n; x++)
    {
        for(y = 0; y < n; y++)
        {
            if(board[x][y] == '-')
            {
                board[x][y] = 'B';
                longestBlack = findLongest(board, n, x, y);
                board[x][y] = 'W';
                longestWhite = findLongest(board, n, x, y);
                score = longestBlack + longestWhite;
                scorekeeper[x][y] = score;
                board[x][y] = '-';
                
            }
            else if(board[x][y] != '-')
            {
                scorekeeper[x][y] = 0;
            }
        }
    }
    
    //The following finds largest score in 'scorekeeper' array
    int a, b;
    int largestScore = scorekeeper[0][0];
    for(a = 0; a < n; a++)
    {
        for(b = 0; b < n; b++)
        {
            if(scorekeeper[a][b] > largestScore)
            {
                largestScore = scorekeeper[a][b];
            }
        }
    }
    
    //Only for testing purposes
    int i ,j;
    /*for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
           printf("%d", scorekeeper[i][j]); 
        }
        printf("\n");
    }*/
    
    //Computer makes move based on largest score
    bool found = false;
    int r, c;
    for(r = 0; r < n; r++)
    {
        for(c = 0; c < n; c++)
        {
            if(scorekeeper[r][c] == largestScore  && board[r][c] == '-' && !found)
            {
                board[r][c] = wOrB;
				printBoard(board, n);
                printf("Computer moves %c at %d %d\n", wOrB, r, c);
                found = true;
            }
        }
    }
}

