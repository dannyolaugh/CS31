// snakepit.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get Pit::display going.  That gives you
// more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cassert>
#define CHECKTYPE(f, t) { (void)(t)(f); }
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;             // max number of rows in the pit
const int MAXCOLS = 40;             // max number of columns in the pit
const int MAXSNAKES = 180;          // max number of snakes allowed

const int UP    = 0;
const int DOWN  = 1;
const int LEFT  = 2;
const int RIGHT = 3;

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
bool directionToDeltas(int dir, int& rowDelta, int& colDelta);
void clearScreen();
void doBasicTests();

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Pit;  // This is needed to let the compiler know that Pit is a
// type name, since it's mentioned in the Snake declaration.

class Snake
{
public:
    // Constructor
    Snake(Pit* pp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    
private:
    Pit* m_pit;
    int  m_row;
    int  m_col;
};

class Player
{
public:
    // Constructor
    Player(Pit *pp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;
    
    // Mutators
    void   stand();
    void   move(int dir);
    void   setDead();
    
private:
    Pit*  m_pit;
    int   m_row;
    int   m_col;
    int   m_age;
    bool  m_dead;
};

class Pit
{
public:
    // Constructor/destructor
    Pit(int nRows, int nCols);
    ~Pit();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     snakeCount() const;
    int     numberOfSnakesAt(int r, int c) const;
    void    display(string msg) const;
    
    // Mutators
    bool   addSnake(int r, int c);
    bool   addPlayer(int r, int c);
    bool   destroyOneSnake(int r, int c);
    bool   moveSnakes();
    
    
private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Snake*  m_snakes[MAXSNAKES];
    int     m_nSnakes;
};

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nSnakes);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Pit* m_pit;
};

///////////////////////////////////////////////////////////////////////////
//  Snake implementation
///////////////////////////////////////////////////////////////////////////

Snake::Snake(Pit* pp, int r, int c)
{
    if (pp == nullptr)
    {
        cout << "***** A snake must be in some Pit!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > pp->rows()  ||  c < 1  ||  c > pp->cols())
    {
        cout << "***** Snake created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    m_pit = pp;
    m_row = r;
    m_col = c;
}

int Snake::row() const
{
    return m_row;
}

int Snake::col() const
{
    // TODO: TRIVIAL:  Return the column the snake is at.
    return m_col;  // this is wrong -- replace it  //JUST DID THIS
}

void Snake::move()
{
    // Attempt to move in a random direction; if we can't move, don't move
    switch (rand() % 4)
    {
        case UP:
            // TODO:  Move the snake up one row if possible.
            if(m_row > 1)
            {
                m_row--;
            }
            break;
        case DOWN:
            if(m_row < m_pit->rows())
            {
                m_row++;
            }
            break;
        case LEFT:
            if(m_col > 1)
                m_col--;
            break;
        case RIGHT:
            // TODO:  Implement the other movements.
            if(m_col < m_pit->cols())
                m_col++;
            break;
    }
}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Pit* pp, int r, int c)
{
    if (pp == nullptr)
    {
        cout << "***** The player must be in some Pit!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > pp->rows()  ||  c < 1  ||  c > pp->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_pit = pp;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    // TODO: TRIVIAL:  Return the row the player is at.
    return m_row;  // this is wrong -- replace it //DONE
}

int Player::col() const
{
    // TODO: TRIVIAL:  Return the column the player is at.
    return m_col;  // this is wrong -- replace it  //DONE
}

int Player::age() const
{
    // TODO: TRIVIAL:  Return the player's age.
    return m_age;  // this is wrong -- replace it //DONE
}

void Player::stand()
{
    m_age++;
}

void Player::move(int dir)
{
    m_age++;
    
    // TODO:  If there's a grid position in the indicated direction that is
    //        adjacent to the player and vacant, move the player there.  If
    //        there's a grid position in the indicated direction that is
    //        adjacent to the player and contains one or more snakes, with
    //        a grid position next to and on the other side of the snake(s),
    //        jump over the snake(s), killing (destroying) it, and landing
    //        at that position (and dying if a snake is there).  In any
    //        other case, don't move.
    
    switch(dir)
    {
        case LEFT:
            if(col() > 1)    //if 1st column you cannot move left
            {
                if(m_pit->numberOfSnakesAt(row(), col() - 1) == 0)   //if no snakes to the left move one column over
                    m_col--;
                else
                {
                    if(m_col >= 3) //if there is a snake to your left move 2 over as long as you are in at least the 3rd col
                    {
                        m_col -= 2;
                        m_pit->destroyOneSnake(row(), col()+1);  //destroy snake where you jumped over it
                    }
                }
            }
            else return;
            break;
        case RIGHT:
            if(col() < m_pit->cols()) //if last column you cannot move right
            {
                if(m_pit->numberOfSnakesAt(row(), col() + 1) == 0)   //if no snakes to the right move one column over
                    m_col++;
                else
                {
                    if(m_col <= m_pit->cols()-2)//if theres a snake to the right move 2 over as long as you are in at most
                        //the 3rd to last column
                    {
                        m_col+=2;
                        m_pit->destroyOneSnake(row(), col()-1);  //destroy snake where you jumped over it
                    }
                }
                
            }
            else return;
            break;
        case UP:
            if(row() > 1)  //if 1st row player cannot move up
            {
                if(m_pit->numberOfSnakesAt(row()-1, col()) == 0) //if no snake move 1 up
                    m_row--;
                
                else
                {
                    if(m_row >= 3)  //move 2 up as long as player is in at least row 3
                    {
                        m_row -= 2;
                        m_pit->destroyOneSnake(row()+1, col()); //destroy snake where you jumped over it
                    }
                }
                
            }
            else return;
            break;
            
        case DOWN:
            if(row() < m_pit->rows()) //if last row player cannot move down
            {
                if(m_pit->numberOfSnakesAt(row()+1, col()) == 0)   //if no snake move 1 down
                    m_row++;
                else
                {
                    if(m_row <= m_pit->rows() - 2)  //move 2 down as long as player is in a row that is at least 2 away from
                        //the last row
                    {
                        m_row += 2;
                        m_pit->destroyOneSnake(row()-1, col());
                    }
                }
                
            }
            else return;
            break;
            
    }
    if(m_pit->numberOfSnakesAt(row(),col())>0)
        setDead();   //if player is on a position with a snake, player dies
    
}

bool Player::isDead() const
{
    // TODO: TRIVIAL:  Return whether the player is dead.
    return m_dead;  // this is wrong -- replace it
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Pit implementations
///////////////////////////////////////////////////////////////////////////

Pit::Pit(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Pit created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nSnakes = 0;
}

Pit::~Pit()
{
    // TODO:  Delete the player and all remaining dynamically allocated snakes.
    delete m_player;
    for(int i = 0; i < m_nSnakes; i++)
    {
        delete m_snakes[i];
    }
}

int Pit::rows() const
{
    // TODO: TRIVIAL:  Return the number of rows in the pit.
    return m_rows;  // this is wrong -- replace it //DONE
}

int Pit::cols() const
{
    // TODO: TRIVIAL:  Return the number of columns in the pit.
    return m_cols;  // this is wrong -- replace it   //DONE
}

Player* Pit::player() const
{
    return m_player;
}

int Pit::snakeCount() const
{
    return m_nSnakes;
}

int Pit::numberOfSnakesAt(int r, int c) const
{
    // TODO:  Return the number of snakes at row r, column c.
    int numSnakes = 0;
    for(int i = 0; i < m_nSnakes; i++)
    {
        if(m_snakes[i] == NULL)
            continue;
        if(m_snakes[i]->row() == r && m_snakes[i]->col() == c)
            numSnakes++;
        
    }
    return numSnakes;
    // this is wrong -- replace it
}

void Pit::display(string msg) const
{
    // Position (row,col) in the pit coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';
    
    // Indicate each snake's position
    // TODO:  If one snake is at some grid point, set the char to 'S'.
    //        If it's 2 though 8, set it to '2' through '8'.
    //        For 9 or more, set it to '9'.
    for(int r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
        {
            if(numberOfSnakesAt(r+1, c+1) == 1)
                grid[r][c] = 'S';
            else if(numberOfSnakesAt(r+1, c+1) == 2)
                grid[r][c] = '2';
            else if(numberOfSnakesAt(r+1, c+1) == 3)
                grid[r][c] = '3';
            else if(numberOfSnakesAt(r+1, c+1) == 4)
                grid[r][c] = '4';
            else if(numberOfSnakesAt(r+1, c+1) == 5)
                grid[r][c] = '5';
            else if(numberOfSnakesAt(r+1, c+1) == 6)
                grid[r][c] = '6';
            else if(numberOfSnakesAt(r+1, c+1) == 7)
                grid[r][c] = '7';
            else if(numberOfSnakesAt(r+1, c+1) == 8)
                grid[r][c] = '8';
            else if(numberOfSnakesAt(r+1, c+1) >= 9)
                grid[r][c] = '9';
            
            
        }
    
    
    
    // Indicate player's position
    if (m_player != nullptr)
    {
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (m_player->isDead())
            gridChar = '*';
        else
            gridChar = '@';
    }
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
    
    // Write message, snake, and player info
    cout << endl;
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << snakeCount() << " snakes remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
    //THIS IS A TEST
    /*cout << m_nSnakes << endl;
     for(int k = 0; k < m_nSnakes; k++)
     {
     cout << m_Snakes[k] << endl;
     }*/
}

bool Pit::addSnake(int r, int c)
{
    // If MAXSNAKES have already been added, return false.  Otherwise,
    // dynamically allocate a new snake at coordinates (r,c).  Save the
    // pointer to the newly allocated snake and return true.
    
    // TODO:  Implement this
    
    if(snakeCount()== MAXSNAKES)
        return false;
    m_snakes[m_nSnakes] = new Snake(this, r, c); //the "this" is creating a pointer back to the pit that the snake is in
    m_nSnakes++;
    
    return true;  // this is wrong -- replace it
}

bool Pit::addPlayer(int r, int c)
{
    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;
    
    // Dynamically allocate a new Player and add it to the pit
    m_player = new Player(this, r, c);
    return true;
}

bool Pit::destroyOneSnake(int r, int c)
{
    // TODO:  Destroy one snake at row r, column c.  Return true if a snake
    //was destroyed, or false if there were no snakes there.
    for(int k = 0; k < m_nSnakes; k++)
    {
        if(m_snakes[k]->row() == r && m_snakes[k]->col() == c)
        {
            delete m_snakes[k];
            m_snakes[k] = m_snakes[m_nSnakes-1];
            m_nSnakes--;
            return true;
        }
    }
    return false;
}

bool Pit::moveSnakes()
{
    for (int k = 0; k < m_nSnakes; k++)
    {
        // TODO:  Have the k-th snake in the pit make one move.
        //        If that move results in that snake being in the same
        //        position as the player, the player dies.
        m_snakes[k]->move();
        if(m_player->row() == m_snakes[k]->row() && m_player->col() == m_snakes[k]->col())
            m_player->setDead();
        
    }
    
    // return true if the player is still alive, false otherwise
    return ! m_player->isDead();
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nSnakes)
{
    if (nSnakes > MAXSNAKES)
    {
        cout << "***** Trying to create Game with " << nSnakes
        << " snakes; only " << MAXSNAKES << " are allowed!" << endl;
        exit(1);
    }
    
    // Create pit
    m_pit = new Pit(rows, cols);
    
    // Add player
    int rPlayer = 1 + rand() % rows;
    int cPlayer = 1 + rand() % cols;
    m_pit->addPlayer(rPlayer, cPlayer);
    
    // Populate with snakes
    while (nSnakes > 0)
    {
        int r = 1 + rand() % rows;
        int c = 1 + rand() % cols;
        // Don't put a snake where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_pit->addSnake(r, c);
        nSnakes--;
    }
}

Game::~Game()
{
    delete m_pit;
}

void Game::play()
{
    Player* p = m_pit->player();
    if (p == nullptr)
    {
        m_pit->display("");
        return;
    }
    string msg = "";
    do
    {
        m_pit->display(msg);
        msg = "";
        cout << endl;
        cout << "Move (u/d/l/r//q): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)
            p->stand();
        else
        {
            switch (action[0])
            {
                default:   // if bad move, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                case 'q':
                    return;
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    p->move(decodeDirection(action[0]));
                    break;
            }
        }
        m_pit->moveSnakes();
    } while ( ! m_pit->player()->isDead()  &&  m_pit->snakeCount() > 0);
    m_pit->display(msg);
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementation
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
        case 'u':  return UP;
        case 'd':  return DOWN;
        case 'l':  return LEFT;
        case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

bool directionToDeltas(int dir, int& rowDelta, int& colDelta)
{
    switch (dir)
    {
        case UP:     rowDelta = -1; colDelta =  0; break;
        case DOWN:   rowDelta =  1; colDelta =  0; break;
        case LEFT:   rowDelta =  0; colDelta = -1; break;
        case RIGHT:  rowDelta =  0; colDelta =  1; break;
        default:     return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////
void thisFunctionWillNeverBeCalled()
{
    // If the student deleted or changed the interfaces to the public
    // functions, this won't compile.  (This uses magic beyond the scope
    // of CS 31.)
    
    Snake(static_cast<Pit*>(0), 1, 1);
    CHECKTYPE(&Snake::row,  int  (Snake::*)() const);
    CHECKTYPE(&Snake::col,  int  (Snake::*)() const);
    CHECKTYPE(&Snake::move, void (Snake::*)());
    
    Player(static_cast<Pit*>(0), 1, 1);
    CHECKTYPE(&Player::row,     int  (Player::*)() const);
    CHECKTYPE(&Player::col,     int  (Player::*)() const);
    CHECKTYPE(&Player::age,     int  (Player::*)() const);
    CHECKTYPE(&Player::isDead,  bool (Player::*)() const);
    CHECKTYPE(&Player::stand,   void (Player::*)());
    CHECKTYPE(&Player::move,    void (Player::*)(int));
    CHECKTYPE(&Player::setDead, void (Player::*)());
    
    Pit(1, 1);
    CHECKTYPE(&Pit::rows,             int     (Pit::*)() const);
    CHECKTYPE(&Pit::cols,             int     (Pit::*)() const);
    CHECKTYPE(&Pit::player,           Player* (Pit::*)() const);
    CHECKTYPE(&Pit::snakeCount,       int     (Pit::*)() const);
    CHECKTYPE(&Pit::numberOfSnakesAt, int     (Pit::*)(int,int) const);
    CHECKTYPE(&Pit::display,          void    (Pit::*)(string) const);
    CHECKTYPE(&Pit::addSnake,         bool    (Pit::*)(int,int));
    CHECKTYPE(&Pit::addPlayer,        bool    (Pit::*)(int,int));
    CHECKTYPE(&Pit::destroyOneSnake,  bool    (Pit::*)(int,int));
    CHECKTYPE(&Pit::moveSnakes,       bool    (Pit::*)());
    
    Game(1,1,1);
    CHECKTYPE(&Game::play, void (Game::*)());
}

void doBasicTests()
{
    {
        Pit brad(10, 20);
        assert(brad.addPlayer(2, 6));
        Player* pp = brad.player();
        assert(pp->row() == 2  &&  pp->col() == 6  && ! pp->isDead());
        pp->move(UP);
        assert(pp->row() == 1  &&  pp->col() == 6  && ! pp->isDead());
        pp->move(UP);
        assert(pp->row() == 1  &&  pp->col() == 6  && ! pp->isDead());
        pp->setDead();
        assert(pp->row() == 1  &&  pp->col() == 6  && pp->isDead());
    }
    {
        Pit brad(2, 2);
        assert(brad.addPlayer(1, 1));
        assert(brad.addSnake(2, 2));
        Player* pp = brad.player();
        assert(brad.moveSnakes());
        assert( ! pp->isDead());
        for (int k = 0; k < 1000  &&  brad.moveSnakes(); k++)
            ;
        assert(pp->isDead());
    }
    {
        Pit brad(1, 5);
        assert(brad.addPlayer(1, 1));
        assert(brad.addSnake(1, 2));
        assert(brad.addSnake(1, 4));
        assert(brad.addSnake(1, 4));
        assert(brad.snakeCount() == 3  &&  brad.numberOfSnakesAt(1, 4) == 2);
        Player* pp = brad.player();
        pp->move(RIGHT);
        pp->move(RIGHT);
        assert(brad.snakeCount() == 1  &&  brad.numberOfSnakesAt(1, 4) == 1);
        pp->move(LEFT);
        assert(brad.snakeCount() == 0);
        assert(brad.addSnake(1, 5));
        assert(brad.snakeCount() == 1);
    }
    cout << "Passed all basic tests" << endl;
}


///////////////////////////////////////////////////////////////////////////
int main()
{
    // Initialize the random number generator.  (You don't need to
    // understand how this works.)
    srand(static_cast<unsigned int>(time(0)));
    
    // Create a game
    //Use this instead to create a mini-game:
    //Game g(3, 3, 2);
    Game g(9, 10, 40);
    doBasicTests();
    // Play the game
    g.play();
    
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementations
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++ UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>
return <#expression#>
void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <cstring>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif

