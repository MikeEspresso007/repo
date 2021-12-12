#include <queue>
#include <string>
#include <utility>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

enum class Player{ PLAYER_O, PLAYER_X};
/* Class Prototype */
class GameBoard
{
	private:
	   static int direct[6][2];
	   static char shape1;
	   static char shape2;
	   static char empty;
	   int size;
	   string line;
	   vector<vector<char>> board;
	   
	public:
	   GameBoard(){}
	   GameBoard(int size):size(size),board(size,vector<char>(size,'.'))
	   {
		  line = "\\";                   // easier to follow paths
		  for(int i = 1; i < size; i++)
			 line += " / \\";
	   } 
	   
	   bool placeMove(int x, int y, Player p);
	   bool retractMove(int x, int y);
	   vector< pair<int,int> > getEmpty();
	   bool checkWinCondition(int x, int y);

	   void printGameBoard();
	   bool inGameBoard(int x, int y);
	   void borders(int x, int y, vector<bool>& condition, char side);
	   void bfsSearch(vector<pair<int,int>>& start, vector<bool>& condition);
	   
	   bool getWinner(char colour);
	   
	   int boardSize(){return size;};
};

class MonteCarloAI // based on montecarlo simulation, more below
{
	public:
	   static vector<int> generatePermutation(int size);
	   static double calculateBestMove(GameBoard& board, Player p);
	   virtual pair <int, int> nextMove(GameBoard& board, Player p);
};

class Game
{
	private:
	   Player computer;
	   Player player;
	   MonteCarloAI robotAI;
	   GameBoard board;
	   
	public:
	   Game(){}  
	   void play();
	   void setup();
	   void chooseSide();
	   bool computerTurn();
	   bool playerTurn();

};

/* Static Definition */
// the 6 edges direction
int GameBoard::direct[6][2] = 
{ 
   {-1, 0}, {1, 0}, 
   {0, -1}, {0, 1}, 
   {1, -1}, {-1,1}    
};

char GameBoard::shape1 = 'O';
char GameBoard::shape2 = 'X';
char GameBoard::empty = '.';

/* Main program */
int main()
{
  
   Game hexGame;
   srand(time(0));
   hexGame.play();
   
   return 0; 
}

/* Class Definition */
bool GameBoard::inGameBoard(int x, int y)
{
   return (x < size && y < size && x >= 0 && y >= 0);
}

void GameBoard::borders(int x, int y, vector<bool>& condition, char side)
{
   if(side == shape2)
   {
      if(y == 0)
         condition[0] = true;
      if(y == size - 1)
         condition[1] = true;
      
   }
   else
   {
      if(x == 0)
         condition[0] = true;
      if(x == size - 1)
         condition[1] = true;
   }
}

bool GameBoard::placeMove(int x, int y, Player p)
{
   if(inGameBoard(x,y) && board[x][y] == empty)
   {
      if(p == Player::PLAYER_X)
         board[x][y] = shape2;
      else
         board[x][y] = shape1;
      return true;
   }
   return false;
}


bool GameBoard::retractMove(int x, int y)
{
   if(inGameBoard(x,y))
   {
      board[x][y] = empty;
      return true;
   }
   return false;
}


vector<pair<int,int>> GameBoard::getEmpty()
{
   vector<pair<int,int>> blankSpots;
   for(int i=0; i<size; i++)
   {
      for(int j=0; j<size; j++)
         if(board[i][j] == empty)
            blankSpots.push_back(make_pair(i,j));
   }
   return blankSpots;
}

void GameBoard::bfsSearch(vector<pair<int,int>>& start, vector<bool>& condition)
{
   if(start.size() != 0)
   {
      int x = start[0].first;
      int y = start[0].second;
      char side = board[x][y];
      
      vector<vector<bool>> visited(size, vector<bool>(size));
      queue<pair<int,int>> trace;
      
	 auto itr = start.cbegin(); 
	 trace.push(*itr);
	 visited[itr->first][itr->second] = true;

	  
      while(!(trace.empty()))
      {
         auto top = trace.front();
         borders(top.first, top.second, condition, side);
         trace.pop();
         
         for(int i = 0; i < 6; i++)
         {
            int xCursor = top.first + direct[i][0];
            int yCursor = top.second + direct[i][1];
            if(inGameBoard(xCursor, yCursor) && board[xCursor][yCursor] == side 
               && visited[xCursor][yCursor] == false)
            {
               visited[xCursor][yCursor] = true;
               trace.push(make_pair(xCursor,yCursor));
            }
         }
      }
   }  
}


bool GameBoard::checkWinCondition(int x, int y)
{
   if(inGameBoard(x,y) && board[x][y] != empty)
   {
     
      vector<bool> condition(2, false); // two opposite ends
      vector<pair<int,int>> start(1, make_pair(x,y));
      
      bfsSearch(start, condition);
      return condition[0] && condition[1];
   }
   return false;
}


void GameBoard::printGameBoard()
{
	if (size <= 0)
		return;

	// start top left
	cout << "  0";
	for (int i=1; i<size; i++)
		cout << " o " << i; // readability
	cout << endl;

	// print the first line
	cout << "0 " << board[0][0];
	for (int i=1; i<size; i++)
		cout << " - " << board[0][i];
	cout << endl;

	string indent = "";
	for (int i=1; i<size; i++)
	{
		indent += ' ';
		cout << indent << "x " << line << endl;
		if (i < 10)
		{
			indent += ' ';
			cout << indent << i << ' ' << board[i][0];
		}
		else
		{
			cout << indent << i << ' ' << board[i][0];
			indent += ' ';
		}

		for (int j=1; j<size; j++)
			cout << " - " << board[i][j];
		cout << endl;
	}
   cout << "_________________________________________________________" << endl;
}


void Game::play()
{
   cout<< "Let's play Hex Game!" 
       << endl << endl;
   
	setup();
	chooseSide();
	char userIn;
	bool counter = false;

	int turn = (computer == Player::PLAYER_X ? 0:1);
	while(!counter)
	{
		turn = !turn;
		if(turn)
			counter = computerTurn();
		else
			counter = playerTurn();
	}

	if(turn == 1)
	{
		cout << "AI won!" << endl; 
	}  
	else
	{
		cout << "You won!" << endl;
  	}

	cout << "Exiting game..." << endl;
}


void Game::setup()
{
   int dimensions;
   cout << "Board size? (7 - 11): ";
   cin >> dimensions;
    
	while(true)
	{
		if((dimensions>=7)&&(dimensions<=11))
		{
			break;
		}   
		else
		{
		    cout << "Please key again for board size... (7 - 11)? .\n"; 
			cin >> dimensions;		  
		}	
	}
   
   board = GameBoard(dimensions);
   cout << "The board is set!\n";
   board.printGameBoard();
}


void Game::chooseSide()
{
   char side = 'o';
  
   cout << "Please chooseSide a side (o/x)? : ";
   cin >> side;

	while(true)
	{
	   if(side == 'x' || side == 'X')
	   {
		  player = Player::PLAYER_X;
		  computer = Player::PLAYER_O;
		  break;
	   }
	   else if(side == 'o' || side == 'O')
	   {
		  player = Player::PLAYER_O;
		  computer = Player::PLAYER_X;
		  break;
	   }
	   else
	   {
		  cout << "That's not a valid side\n";
		  cout << "Please chooseSide again (o/x)?";
		  cin >> side;
	   }
	}
	
   cin.clear();
}


bool Game::computerTurn()
{
   cout << "My turn! I move: ";
   auto move = robotAI.nextMove(board, computer); // calculate optimal move
   board.placeMove(move.first, move.second, computer);
   cout << move.first << " " << move.second << endl;
   board.printGameBoard();
   return board.checkWinCondition(move.first, move.second);
}


bool Game::playerTurn()
{
   int x, y;
   cout << "Your turn!" << endl;
   while(true)
   {
      cout << "Where are you putting your piece? (x y = ) ";
      cin >> x >> y;
      if(board.placeMove(x,y,player))
         break;
      cout << "You can't do that!" << endl;
   }
   board.printGameBoard();
   return board.checkWinCondition(x,y);
}


double MonteCarloAI::calculateBestMove(GameBoard &board, Player player)
{
	auto blank = board.getEmpty();
	int checkWinConditionCount = 0; 
	vector<int> perm(blank.size());
	for (int i=0; i<perm.size(); i++)
		perm[i] = i;	
	
	int trialNumber  = 3000 - 10*blank.size();
	
	for (int n=0; n<trialNumber; n++)
	{
   		for (int i=perm.size(); i>1; i--)
    	{
    		int swap = rand() % i;
    		int temp = perm[i-1];
    		perm[i-1] = perm[swap];
			perm[swap] = temp; // prand the permutation		
    	}
		
		// turn = 1 is O, turn = 0 is X
		int turn = (player == Player::PLAYER_X ? 0 : 1);	
		
		for (int i=0; i<perm.size(); i++)
		{
			turn = !turn; //easy bool turn tracking
			int x = blank[perm[i]].first;
			int y = blank[perm[i]].second;
			if (turn) // 1
			{
				board.placeMove(x, y, Player::PLAYER_O);		
			}
			else      
			{
				board.placeMove(x, y, Player::PLAYER_X);
			}
		}
	
	
		char colour;
		if(player == Player::PLAYER_X)
		{
			colour = 'X';
		}
		else
		{
			colour = 'O';
		}
			
		if( board.getWinner(colour))
		{
			checkWinConditionCount++;
		}

		
		for (auto itr = blank.begin(); itr != blank.end(); ++itr)
			board.retractMove(itr->first, itr->second); // take back rand moves
	}
	return static_cast<double>(checkWinConditionCount) / trialNumber;
}


pair<int, int> MonteCarloAI::nextMove(GameBoard &board, Player p)
{
	auto blank = board.getEmpty();
	double bestMove = 0;
	pair<int, int> move = blank[0];
	
	for (int i=0; i<blank.size(); i++)
	{
		int x = blank[i].first;
		int y = blank[i].second;
		board.placeMove(x, y, p);

		double moveValue = calculateBestMove(board, p);
		
		if (moveValue > bestMove)
		{
			move = blank[i];
			bestMove = moveValue;
		}

		board.retractMove(x, y);
	}
	return move;
}


bool GameBoard::getWinner(char colour)
{
   vector<bool> condition(2, false); // tracks side to side win
   vector<pair<int,int>> start;
   for(int i =0; i<size; i++)
      if(board[i][0] == colour)
         start.push_back(make_pair(i,0));
      
   bfsSearch(start, condition);
   
   return (condition[0] && condition[1]);
}