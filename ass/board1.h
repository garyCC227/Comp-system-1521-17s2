// Game of Life on a 10x10 grid

#define NN 50

int N = NN;

char board[NN][NN] = {
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0,1,1,1,0},


};
char newboard[NN][NN];

