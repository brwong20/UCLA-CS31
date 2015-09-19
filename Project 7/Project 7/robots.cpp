//
//  main.cpp
//  Project 7
//
//  Created by Brian Wong on 5/29/15.
//  Copyright (c) 2015 Brian Wong. All rights reserved.
//

// robots.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get Arena::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cassert>
using namespace std;



///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;             // max number of rows in the arena
const int MAXCOLS = 40;             // max number of columns in the arena
const int MAXROBOTS = 130;          // max number of robots allowed

const int UP    = 0;
const int DOWN  = 1;
const int LEFT  = 2;
const int RIGHT = 3;

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena;  // This is needed to let the compiler know that Arena is a
// type name, since it's mentioned in the Robot declaration.

class Robot
{
public:
    // Constructor
    Robot(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool takeDamageAndLive();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_hits = 0;
};

class Player
{
public:
    // Constructor
    Player(Arena *ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;
    
    // Mutators
    string takeComputerChosenTurn();
    void   stand();
    void   move(int dir);
    bool   shoot(int dir);
    void   setDead();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_age;
    bool   m_dead;
};

class Arena
{
public:
    // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     robotCount() const;
    int     nRobotsAt(int r, int c) const;
    void    display(string msg) const;
    
    // Mutators
    bool   addRobot(int r, int c);
    bool   addPlayer(int r, int c);
    void   damageRobotAt(int r, int c);
    bool   moveRobots();
    
private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Robot*  m_robots[MAXROBOTS];
    int     m_nRobots;
};

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRobots);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
};

///////////////////////////////////////////////////////////////////////////
//  Robot implementation
///////////////////////////////////////////////////////////////////////////

Robot::Robot(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A robot must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Robot created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
}

int Robot::row() const
{
    return m_row;
}

int Robot::col() const
{
    return m_col;
}

void Robot::move()
{
    // Attempt to move in a random direction; if we can't move, don't move
    switch (rand() % 4)
    {
        case UP:
            if (m_row > 1) //checks that moving up will not take the robot off the grid
            {
                m_row--;
                break;
            }
            else
                break;
        case DOWN:
            if (m_row < m_arena->rows())
            {
                m_row++;
                break;
            }
            else
                break;
        case LEFT:
            if (m_col > 1)
            {
                m_col--;
                break;
            }
            else
                break;
        case RIGHT:
            if (m_col < m_arena->cols())
            {
                m_col++;
                break;
            }
            else
                break; //do nothing
    }
}

bool Robot::takeDamageAndLive()
{
    if(m_hits<=1){
        m_hits++;
        return true;
    }else{
        return false;
    }

}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

int Player::age() const
{
    return m_age;
}

string Player::takeComputerChosenTurn()
{
    // Your replacement implementation should do something intelligent
    // and return a string that describes what happened.  When you've
    // decided what action to take, take it by calling move, shoot, or stand.
    // This function must return one of the following four strings:
    //     "Moved."
    //     "Shot and hit!"
    //     "Shot and missed!"
    //     "Stood."
    
    int r = row();
    int c = col();
    int nRobotsLeft = 0;
    if (c > 1) //checking the number of robots 1 space to the left of the player. if the player is on the leftmost space, sets this to 0.
        nRobotsLeft = m_arena->nRobotsAt(r,c-1);
    
    int nRobotsRight = 0;
    if (c < m_arena->cols()) //checking the number of robots 1 space to the right of the player. if the player is on the rightmost space, sets this to 0.
        nRobotsRight = m_arena->nRobotsAt(r,c+1);
    
    int nRobotsDown = 0;
    if (r < m_arena->rows()) //checking the number of robots 1 space under the player. if the player is on the bottommost space, sets this to 0.
        nRobotsDown = m_arena->nRobotsAt(r+1,c);
    
    int nRobotsUp = 0;
    if (r > 1) //checking the number of robots 1 space above the player. if the player is on the top space, sets this to 0.
        nRobotsUp = m_arena->nRobotsAt(r-1,c);
    
    int nRobotsLeftRow = 0;
    for (int k = (c-2); k >= 1; k--) //looking for robots on the same row, to the left, but not adjacent to the player
        nRobotsLeftRow += m_arena->nRobotsAt(r,k); //increments the number of robots if any are found
    
    
    int nRobotsRightRow = 0;
    for (int k = (c+2); k <= (m_arena->cols()); k++) //looking for robots on the same row, to the right, but not adjacent to the player
        nRobotsRightRow += m_arena->nRobotsAt(r,k); //increments the number of robots if any are found
    
    int nRobotsAboveCol = 0;
    for (int k = (r-2); k >= 1; k--) //looks for robots in the same column, above but not adjacent to the player
        nRobotsAboveCol += m_arena->nRobotsAt(k,c);
    
    int nRobotsBelowCol = 0;
    for (int k = (r+2); k <= (m_arena->rows()); k++) //looks for robots in the same column, below but not adjacent to the player
        nRobotsBelowCol += m_arena->nRobotsAt(k,c);
    
    int nRobotsAdjacent = nRobotsRight + nRobotsLeft + nRobotsUp + nRobotsDown; //# robots directly next to player
    int nRobotsInRange = nRobotsRightRow + nRobotsLeftRow + nRobotsAboveCol + nRobotsBelowCol; //# robots not directly next to player but in shooting range
    
    if (nRobotsAdjacent == 0) //if there are no robots adjacent to the player,
        if (nRobotsInRange > 0) //and there are robots in shooting range, the player should shoot towards a robot.
        {
            if (nRobotsRightRow > 0) //shoots right
            {
                bool hit = shoot(RIGHT);
                if (hit)
                    return "Shot and hit!";
                else
                    return "Shot and missed!";
            }
            else if (nRobotsLeftRow > 0) //shoots left
            {
                bool hit = shoot(LEFT);
                if (hit)
                    return "Shot and hit!";
                else
                    return "Shot and missed!";
            }
            else if (nRobotsAboveCol > 0) //shoots up
            {
                bool hit = shoot(UP);
                if (hit)
                    return "Shot and hit!";
                else
                    return "Shot and missed!";
            }
            else if (nRobotsBelowCol > 0) //shoots down
            {
                bool hit = shoot(DOWN);
                if (hit)
                    return "Shot and hit!";
                else
                    return "Shot and missed!";
            }
            else //If all else fails
            {
                stand();
                return "Stood.";
            }
        }
        else {
            stand();
            return "Stood.";//If player is safe from robots
        }
    if (nRobotsAdjacent > 0)
    {
        //should calculate which of the 4 spots is "safest" and choose which one to move to based on relative safety
        int safetyRatingR = (m_arena->nRobotsAt(r+1,c+1)) + (m_arena->nRobotsAt(r-1,c+1)) + (m_arena->nRobotsAt(r,c+2));
        //creates an integer value of the amount of robots directly adjacent to the space 1 spot to the right of the player
        int safetyRatingL = (m_arena->nRobotsAt(r+1,c-1)) + (m_arena->nRobotsAt(r-1,c-1)) + (m_arena->nRobotsAt(r,c-2)); //safety value for the left space
        int safetyRatingU = (m_arena->nRobotsAt(r-1,c-1)) + (m_arena->nRobotsAt(r-1,c+1)) + (m_arena->nRobotsAt(r-2,c)); //safety value for the above space
        int safetyRatingD = (m_arena->nRobotsAt(r+1,c+1)) + (m_arena->nRobotsAt(r+1,c-1)) + (m_arena->nRobotsAt(r+2,c)); //s v for the below space
        
        if ((safetyRatingR <= safetyRatingL) && (safetyRatingR <= safetyRatingU) && (safetyRatingR <= safetyRatingD) && (c != m_arena->cols()))
            //if R has the lowest safety rating, and moving right would not take you off the grid
        {
            move(RIGHT);
            return "Moved.";
        }
        else if ((safetyRatingL <= safetyRatingU) && (safetyRatingL <= safetyRatingD) && (c != 1))
            //if L has the lowest safety rating of the remaining possible directions to move, and moving left would not go off the grid
        {
            move(LEFT);
            return "Moved."; 
        }
        else if ((safetyRatingU <= safetyRatingD) && (r != 1))
            //if U has the lowest safety rating of the 2 remaining possible directions, and moving up would not go off the grid
        {
            move(UP);
            return "Moved."; 
        }
        else if (r != m_arena->rows())
            //final option is to move down, only triggers if this would not take you off the grid
        { 
            move(DOWN);
            return "Moved."; 
        }
        else
        {
            stand();
            return "Stood."; 
        }
    }
    return "Stood.";
}

void Player::stand()
{
    m_age++;
}

void Player::move(int dir)
{
    m_age++;
    
    switch (dir)
    {
        case UP:
            if (m_row > 1)
                m_row--;
            break;
        case DOWN:
            if (m_row < m_arena->rows())
                m_row++;
            break;
        case LEFT:
            if (m_col > 1)
                m_col--;
            break;
        case RIGHT:
            if (m_col < m_arena->cols())
                m_col++;
            break;
    }
}

bool Player::shoot(int dir)
{
    m_age++;
    
    if (rand() % 3 == 0)  // miss with 1/3 probability
        return false;
    
    switch(dir)
    {
        case UP:
            for (int r = m_row; r >= 1; r--) //starts at the player's row position and steps down, stopping at the end of the arena
            {
                if (m_arena->nRobotsAt(r, m_col) >= 1) //if there is a robot at the current step, destroy it and return
                {
                    m_arena->damageRobotAt(r, m_col);
                    return true;
                }
            }
            break;
        case DOWN:
            for (int r = m_row; r <= m_arena->rows(); r++) //starts at player's row and goes down
            {
                if (m_arena->nRobotsAt(r, m_col) >= 1)
                {
                    m_arena->damageRobotAt(r, m_col);
                    return true;
                }
            }
            break;
        case LEFT:
            for (int c = m_col; c >= 1; c--) //starts at player's column position and steps to the left one space at a time
            {
                if (m_arena->nRobotsAt(m_row, c) >= 1)
                {
                    m_arena->damageRobotAt(m_row, c);
                    return true;
                }
            }
            break;
        case RIGHT:
            for (int c = m_col; c <= m_arena->cols(); c++) //starts at player's column and goes right
            {
                if (m_arena->nRobotsAt(m_row, c) >= 1)
                {
                    m_arena->damageRobotAt(m_row, c);
                    return true;
                }
            }
            break;
    }
    return false; //didn't hit anything
}

bool Player::isDead() const
{
    if(!m_dead){
        return false;
    }
    return true;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementations
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nRobots = 0;
}

Arena::~Arena()
{
    delete m_player;
    for(int i = 0; i<m_nRobots; i++){
        delete m_robots[i];
    }
    
}

int Arena::rows() const
{
    return m_rows;
}

int Arena::cols() const
{
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::robotCount() const
{
    return m_nRobots;
}

int Arena::nRobotsAt(int r, int c) const//ASK
{
    int counter = 0;
    for (int n = 0; n < m_nRobots; n++){ // goes through each robot
        if ((m_robots[n]->col() == c) && (m_robots[n]->row() == r)){
            counter++;
        }
    }
    return counter;
}

void Arena::display(string msg) const
{
    // Position (row,col) in the arena coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';
    
    // Indicate each robot's position

    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            if (nRobotsAt(r+1, c+1) == 1) //1 robot = value of the grid is R
                grid[r][c] = 'R';
            else if (nRobotsAt(r+1,c+1) > 1 && nRobotsAt(r+1,c+1) < 9)
                grid[r][c] = '0' + nRobotsAt(r+1,c+1); //sets the value of the grid to the number of robots (the '0' + ... converts the int to the correct char)
            else if (nRobotsAt(r+1,c+1) >= 9)
                grid[r][c] = '9'; //for any value higher than 9, this sets the grid value to 9.
            else
                grid[r][c] = '.'; //leave it as a .
    
    // Indicate player's position
    if (m_player != nullptr)
    {
        // Set the char to '@', unless there's also a robot there,
        // in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
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
    
    // Write message, robot, and player info
    cout << endl;
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << robotCount() << " robots remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Arena::addRobot(int r, int c)
{
    // If MAXROBOTS have already been added, return false.  Otherwise,
    // dynamically allocate a new robot at coordinates (r,c).  Save the
    // pointer to the newly allocated robot and return true.
    
    if(m_nRobots >=MAXROBOTS){
        return false;
    }
    else{
        m_robots[m_nRobots] = new Robot(this, r, c);
        m_nRobots++;
    }
    return true;  // This implementation compiles, but is incorrect.
}

bool Arena::addPlayer(int r, int c)
{
    // Don't add a player if one already exists
    if (m_player != nullptr){
        return false;
    }
    // Dynamically allocate a new Player and add it to the arena
    else{
        m_player = new Player(this, r, c);
    }
    return true;
}

void Arena::damageRobotAt(int r, int c)
{
    if (nRobotsAt(r,c) > 0)//If the robot is within bounds
    {
        for (int k = 0; k < m_nRobots; k++)
        {
            if ((m_robots[k]->col() == c) && (m_robots[k]->row() == r)) //looks through the robot array to find an element that has coordinates matching the robot being destroyed
            {
                if(m_robots[k]->takeDamageAndLive()){
                    return;
                }else{
                    delete m_robots[k]; //removes this element from the array
                    while (k < m_nRobots)
                    {
                        m_robots[k] = m_robots[k+1]; //copy all the elements of the array over one element
                        k++; //continues stepping through the array
                    }
                    m_nRobots--; //decrements the number of total robots
                    return; //a robot was deleted
                }
            }
        }
    }
        return;
}

bool Arena::moveRobots()
{
    for (int k = 0; k < m_nRobots; k++)
    {
        m_robots[k]->move();
        if ((m_robots[k]->row() == m_player->row()) && (m_robots[k]->col() == m_player->col()))
            m_player->setDead();
    }
    // return true if the player is still alive, false otherwise
    return ! m_player->isDead();
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nRobots)
{
    if (nRobots > MAXROBOTS)
    {
        cout << "***** Trying to create Game with " << nRobots
        << " robots; only " << MAXROBOTS << " are allowed!" << endl;
        exit(1);
    }
    
    // Create arena
    m_arena = new Arena(rows, cols);
    
    // Add player
    int rPlayer = 1 + rand() % rows;
    int cPlayer = 1 + rand() % cols;
    m_arena->addPlayer(rPlayer, cPlayer);
    
    // Populate with robots
    while (nRobots > 0)
    {
        int r = 1 + rand() % rows;
        int c = 1 + rand() % cols;
        // Don't put a robot where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_arena->addRobot(r, c);
        nRobots--;
    }
}

Game::~Game()
{
    delete m_arena;
}

void Game::play()
{
    Player* p = m_arena->player();
    if (p == nullptr)
    {
        m_arena->display("");
        return;
    }
    string msg = "";
    do
    {
        m_arena->display(msg);
        msg = "";
        cout << endl;
        cout << "Move (u/d/l/r/su/sd/sl/sr/c//q): ";
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
                case 'c':  // computer moves player
                    msg = p->takeComputerChosenTurn();
                    break;
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    p->move(decodeDirection(action[0]));
                    break;
                case 's':
                    if (action.size() < 2)  // if no direction, nobody moves
                    {
                        cout << '\a' << endl;  // beep
                        continue;
                    }
                    switch (action[1])
                {
                    default:   // if bad direction, nobody moves
                        cout << '\a' << endl;  // beep
                        continue;
                    case 'u':
                    case 'd':
                    case 'l':
                    case 'r':
                        if (p->shoot(decodeDirection(action[1])))
                            msg = "Hit!";
                        else
                            msg = "Missed!";
                        break;
                }
                    break;
            }
        }
        m_arena->moveRobots();
    } while ( ! m_arena->player()->isDead()  &&  m_arena->robotCount() > 0);
    m_arena->display(msg);
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
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

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////


#define CHECKTYPE(f, t) { (void)(t)(f); }

void thisFunctionWillNeverBeCalled()
{
    // If the student deleted or changed the interfaces to the public
    // functions, this won't compile.  (This uses magic beyond the scope
    // of CS 31.)
    
    Robot(static_cast<Arena*>(0), 1, 1);
    CHECKTYPE(&Robot::row,               int  (Robot::*)() const);
    CHECKTYPE(&Robot::col,               int  (Robot::*)() const);
    CHECKTYPE(&Robot::move,              void (Robot::*)());
    CHECKTYPE(&Robot::takeDamageAndLive, bool (Robot::*)());
    
    Player(static_cast<Arena*>(0), 1, 1);
    CHECKTYPE(&Player::row,                     int    (Player::*)() const);
    CHECKTYPE(&Player::col,                     int    (Player::*)() const);
    CHECKTYPE(&Player::age,                     int    (Player::*)() const);
    CHECKTYPE(&Player::isDead,                  bool   (Player::*)() const);
    CHECKTYPE(&Player::takeComputerChosenTurn,  string (Player::*)());
    CHECKTYPE(&Player::stand,                   void   (Player::*)());
    CHECKTYPE(&Player::move,                    void   (Player::*)(int));
    CHECKTYPE(&Player::shoot,                   bool   (Player::*)(int));
    CHECKTYPE(&Player::setDead,                 void   (Player::*)());
    
    Arena(1, 1);
    CHECKTYPE(&Arena::rows,          int     (Arena::*)() const);
    CHECKTYPE(&Arena::cols,          int     (Arena::*)() const);
    CHECKTYPE(&Arena::player,        Player* (Arena::*)() const);
    CHECKTYPE(&Arena::robotCount,    int     (Arena::*)() const);
    CHECKTYPE(&Arena::nRobotsAt,     int     (Arena::*)(int,int) const);
    CHECKTYPE(&Arena::display,       void    (Arena::*)(string) const);
    CHECKTYPE(&Arena::addRobot,      bool    (Arena::*)(int,int));
    CHECKTYPE(&Arena::addPlayer,     bool    (Arena::*)(int,int));
    CHECKTYPE(&Arena::damageRobotAt, void    (Arena::*)(int,int));
    CHECKTYPE(&Arena::moveRobots,    bool    (Arena::*)());
    
    Game(1,1,1);
    CHECKTYPE(&Game::play, void (Game::*)());
}

void doBasicTests()
{
    {
        Arena a(10, 20);
        assert(a.addPlayer(2, 6));
        Player* pp = a.player();
        assert(pp->row() == 2  &&  pp->col() == 6  && ! pp->isDead());
        pp->move(UP);
        assert(pp->row() == 1  &&  pp->col() == 6  && ! pp->isDead());
        pp->move(UP);
        assert(pp->row() == 1  &&  pp->col() == 6  && ! pp->isDead());
        pp->setDead();
        assert(pp->row() == 1  &&  pp->col() == 6  && pp->isDead());
    }
    {
        Arena a(2, 2);
        assert(a.addPlayer(1, 1));
        assert(a.addRobot(2, 2));
        Player* pp = a.player();
        assert(a.moveRobots());
        assert( ! pp->isDead());
        for (int k = 0; k < 1000  &&  ! pp->isDead()  &&  a.moveRobots(); k++)
            ;
        assert(pp->isDead());
    }
    {
        Arena a(1, 40);
        assert(a.addPlayer(1, 1));
        assert(a.addRobot(1, 40));
        assert(a.addRobot(1, 40));
        assert(a.addRobot(1, 39));
        assert(a.robotCount() == 3  &&  a.nRobotsAt(1, 40) == 2);
        Player* pp = a.player();
        for (int k = 0; k < 1000  &&  a.robotCount() != 0; k++)
            pp->shoot(RIGHT);
        assert(a.robotCount() == 0);
        assert(a.addRobot(1, 40));
        for (int k = 0; k < 1000  &&  a.robotCount() != 0; k++)
            pp->takeComputerChosenTurn();
        assert(a.robotCount() == 0);
    }
    cout << "Passed all basic tests" << endl;
}

int main()
{
    // Initialize the random number generator.  (You don't need to
    // understand how this works.)
    srand(static_cast<unsigned int>(time(0)));
    
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 3, 2);
    Game g(15, 18, 10);
    
    // Play the game
    g.play();
    //doBasicTests();
    
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