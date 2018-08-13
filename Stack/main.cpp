#include <iostream>
#include "Stack.h"

using namespace std;

#define N_OPRT 9
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator;
typedef enum { AVAILABLE, ROUTE, BACKTRACKED, WALL } Status;
typedef enum {UNKNOW, EAST, SOUTH, WEST, NORTH, NO_WAY } ESWN;
inline  ESWN nextESWN(ESWN eswn)
{
    return ESWN(eswn + 1);
}

void convert(Stack<char> &, __int64, int);
float evaluate(char *, char *&);
void placeQueens(int);
//以下不做实现
void readNumber(char *, Stack<float> &);
void append(char *&, float &);
void append(char *&, char &);
char orderBetween(char &, char &);
float calcu(char &, float &);
float calcu(float &, char &, float &);

const char pri[N_OPRT][N_OPRT] =
{
	'>', '>', '<', '<', '<', '<', '<', '>', '>',
	'>', '>', '<', '<', '<', '<', '<', '>', '>',
	'>', '>', '>', '>', '<', '<', '<', '>', '>',
	'>', '>', '>', '>', '<', '<', '<', '>', '>',
	'>', '>', '>', '>', '>', '<', '<', '>', '>',
	'>', '>', '>', '>', '>', '>', ' ', '>', '>',
	'<', '<', '<', '<', '<', '<', '<', '=', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	'<', '<', '<', '<', '<', '<', '<', ' ', '='
};

struct Queen
{
    int x, y;
    Queen(int xx = 0, int yy = 0) : x(xx), y(yy) {};
    bool operator==(const Queen &q) const
    {
        return (x == q.x) || (y == q.y) || (x + y == q.x + q.y) || (x - y == q.x - q.y);
    }
    bool operator!=(const Queen &q) const
    {
        return !(*this == q);
    }
};

struct Cell
{
    int x, y;
    Status status;
    ESWN incoming, ouotgoing;
    bool operator==(Cell &c) const
    {
        return x == c.x && y == c.y;
    }
};
#define LABY_MAX 24
Cell laby[LABY_MAX][LABY_MAX];
inline Cell *neighbor(Cell *cell)
{
    switch (cell->ouotgoing)
    {
    case EAST:
        return cell + LABY_MAX;
    case SOUTH:
        return cell + 1;
    case WEST:
        return cell - LABY_MAX;
    case NORTH:
        return cell - 1;
    default:
        exit(-1);
    }
}

inline Cell *advance(Cell *cell)
{
    Cell *next;
    switch (cell->ouotgoing)
    {
    case EAST:
        next = cell + LABY_MAX;
        next->incoming = WEST;
        break;
    case SOUTH:
        next = cell + 1;
        next->incoming = NORTH;
        break;
    case WEST:
        next = cell - LABY_MAX;
        next->incoming = EAST;
        break;
    case NORTH:
        next = cell - 1;
        next->incoming = SOUTH;
        break;
    default:
        exit(-1);
    }
    return next;
}

bool labyrinth(Cell Laby[LABY_MAX][LABY_MAX], Cell *s, Cell *t)
{
    if ((AVAILABLE != s->status) || (AVAILABLE != t->status))
    {
        return false;
    }
    Stack<Cell *> path;
    s->incoming = UNKNOW;
    s->status = ROUTE;
    path.push(s);
    do
    {
        Cell *c = path.top();
        if (c == t)
        {
            return true;
        }
        while (NO_WAY > (c->ouotgoing = nextESWN(c->ouotgoing)))
        {
            if (AVAILABLE == neighbor(c)->status)
            {
                break;
            }
        }
        if (NO_WAY == c->ouotgoing)
        {
            c->status = BACKTRACKED;
            c = path.pop();
        }
        else
        {
            path.push(c = advance(c));
            c->ouotgoing = UNKNOW;
            c->status = ROUTE;
        }
    }
    while (!path.empty());
    return false;
}

int main(int argc, char* argv[])
{
	Stack<char> s;
	convert(s, 12345, 8);
	system("pause");
	return 0;
}

void convert(Stack<char> &S, __int64 n, int base)
{
	static char digit[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	while (0 < n)
	{
		S.push(digit[n % base]);
		n /= base;
	}
	while (S.top() != NULL)
	{
		cout << S.pop();
	}
	cout << endl;
}

float evaluate(char *S, char *&RPN)
{
	Stack<float> opnd;
	Stack<char> optr;
	optr.push('\0');
	while (!optr.empty())
	{
		if (isdigit(*S))
		{
			readNumber(S, opnd);
			append(RPN, opnd.top());
		}
		else
		{
			switch (orderBetween(optr.top(), *S))
			{
			case '<':
				optr.push(*S);
				S++;
				break;
			case '=':
				optr.pop();
				S++;
				break;
			case '>':
			{
				char op = optr.pop();
				append(RPN, op);
				if ('!' == op)
				{
					float pOpnd = opnd.pop();
					opnd.push(calcu(op, pOpnd));
				}
				else
				{
					float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop();
					opnd.push(calcu(pOpnd1, op, pOpnd2));
				}
				break;
			}
			default: 
				return -1;
			}
		}
	}
	return opnd.pop();
}

void placeQueens(int N)
{
    Stack<Queen> solu;
    Queen q(0, 0);
    int nSolu = 0;
    do
    {
        if (N <= solu.size() || N <= q.y)
        {
            q = solu.pop();
            q.y++;
        }
        else
        {
            while ((q.y < N) && (0 <= solu.find(q)))
            {
                q.y++;
            }
            if (N > q.y)
            {
                solu.push(q);
                if (N == solu.size())
                {
                    nSolu++;
                }
                q.x++;
                q.y = 0;
            }
        }
    }
    while ((0 < q.x) || (q.y < N));
}
