#include "basic_classes.cpp"

enum players_regime
{
    READ_FROM_FILE,
    PLAYER_PLAYER,
    PLAYER_COMPUTER
};

///pattern game class

queue < pii > q;
int dist[100][100];
bool vis [100][100];

class FirstRegimeGame
{
public:
    players_regime players;
    int N, M;
	Cell field[100][100];

	vector < pii > turns[100][100];

    ///блок процедур для генерації переходів

    bool inRangeX(int x)
    {
        return 1 <= x and x <= N;
    }
    bool inRangeY(int y)
    {
        return 1 <= y and y <= M;
    }

    bool inRange(pii u)
    {
        return this->inRangeX(u.x) and this->inRangeY(u.y);
    }

    void addTurn(pii u, pii v)
    {
        if(this->inRange(u) && this->inRange(v))
            turns[u.x][u.y].push_back(v);
    }

	void generateTurns()
	{
        pair<int,int> moves_odd[6] =
        {
            {-1, -1}, {-1, 0}, {-1, 1},
            {0 , -1},          {0,  1},
                      { 1, 0}
        };

        pair<int,int> moves_even[6] =
        {
                      {-1, 0},
            {0 , -1},          {0,  1},
            {1,  -1}, { 1, 0}, {1,  1}
        };

        for(int x = 1; x <= this->N; x++)
            {
                for(int y = 1; y <= this->M; y++)
                {
                    if(y % 2 == 1)
                    {
                        for(auto move : moves_odd)
                            this->addTurn({x, y}, {x + move.x, y + move.y});
                    }
                    else
                    {
                        for(auto move : moves_even)
                            this->addTurn({x, y}, {x + move.x, y + move.y});
                    }
                }
            }
	}
    ///set methods
    void setColorAround(int x, int y, int color)
    {
        this->field[x][y].color = color;
        for(auto turn : turns[x][y])
            this->field[turn.x][turn.y].color = color;
    }

    void setTown(Town *town)
    {
        this->field[town->x][town->y].town = town;
        this->setColorAround(town->x, town->y, town->color);
    }
    void setFort(Fort *fort)
    {
        this->field[fort->x][fort->y].fort = fort;
        this->setColorAround(fort->x, fort->y, fort->color);
    }
    void setGeneral(General *general)
    {
        this->field[general->x][general->y].general = general;
    }
    ///end set methods

    ///constructor
	FirstRegimeGame(players_regime players,int width, int height, Town *town1, Town *town2)
	{
        this->players = players;

        this->N = width;
        this->M = height;

        this->setTown(town1);
        this->setTown(town2);
        this->generateTurns();
	}


    /// SART INTELECT METHODS

    // ОЧИСТКА МАСИВУ ДИСТАНЦІЙ
    void clrDist()
    {
        for (int i(0); i < 100; i++)
            for (int j(0); j < 100; j++)
                dist[i][j] = INF;
    }

    void clrVisit()
    {
        for (int i(0); i<100; i++)
            for (int j(0); j<100; j++)
                vis[i][j] = false;
    }

    int priority(int x, int y)
    {
        Cell c = this->field[x][y];
        int priorityEmpty = 5;
        int priorityFull = 10;
        if(c.relief == EMPTY && c.town == NULL && c.fort == NULL)
            return priorityEmpty; else return priorityFull;
    }

    void clrQ()
    {
        while(!q.empty())
        {
            q.pop();
        }
    }

    // ПІДРАХОВУЕМО ВІДСТАНЬ ДО ВЕРШИН

    void bfs(int x, int y)
    {
        pii s = mp(x, y);
        clrQ();
        q.push(s);
        clrDist();
        dist[s.x][s.y] = 0;
        while(!q.empty())
        {
            pii v = q.front();
            for(auto to : turns[v.x][v.y])
            {
                if(dist[to.x][to.y] > dist[v.x][v.y] + 1)
                {
                    q.push(to);
                    dist[to.x][to.y] = dist[v.x][v.y] + 1;
                }
            }
            q.pop();
        }
    }

    // ПІДРАХУНОК ПОТЕНЦІАЛІВ
    double dfs(int x, int y)
    {
        pii v = mp(x, y);
        vis[v.x][v.y] = true;
        double total = priority(v.x, v.y);
        for (auto to : turns[v.x][v.y])
        {
            if(!vis[to.x][to.y] && dist[to.x][to.y] == dist[v.x][v.y] + 1)
                total += dfs(to.x, to.y);
        }
        return total / ( (double)dist[x][y] );
    }

    /*
    */
    double getRank(int x,int y)
    {
        bfs(x,y);
        clrVisit();
        return dfs(x,y);
    }

    /// FINISH INTELECT METHODS

    ///this is empty methods
	void playFromFile() {}
    void playPlayerPlayer() {}
    void playPlayerComputer() {}
    /// end empty methods

	void play()
	{
        switch(players)
        {
            case READ_FROM_FILE :
            {
                this->playFromFile();
                break;
            }
            case PLAYER_PLAYER :
            {
                this->playPlayerPlayer();
                break;
            }
            case PLAYER_COMPUTER :
            {
                this->playPlayerComputer();
                break;
            }
        }
	}
};



int main()
{
	srand(unsigned(time(NULL)));
	printf("Hello world\n");

	Town *town1 = new Town(1, 1, 1);
	Town *town2 = new Town(2, 2, 2);
	FirstRegimeGame game1 = FirstRegimeGame(READ_FROM_FILE,10,10, town1, town2);
	game1.setFort(new Fort(1,2,1));
	game1.play();

	system("pause");
    return 0;
}
