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

        this->generateTurns();

        this->setTown(town1);
        this->setTown(town2);
	}


    /// SART INTELECT METHODS

    // ОЧИСТКА МАСИВУ ДИСТАНЦІЙ
    void clrDist()
    {
        for (int i(0); i < 100; i++)
            for (int j(0); j < 100; j++)
                dist[i][j] = INF;
    }
    // ОЧИСТКА МАСИВУ ВІДВІДАНИХ ВЕРШИН
    void clrVisit()
    {
        for (int i(0); i<100; i++)
            for (int j(0); j<100; j++)
                vis[i][j] = false;
    }

    // ОЧИСТКА ЧЕРГИ
    void clrQ()
    {
        while(!q.empty())
        {
            q.pop();
        }
    }

    bool isEmpty(Cell c)
    {
         if(c.town!=NULL||c.fort!=NULL||c.relief!=EMPTY)
            return false;
         return true;
    }

    bool canGo(int x, int y, int color)
    {
        if(this->field[x][y].color == color)
            return true;
        for (auto to : turns[x][y])
            if(this->field[to.x][to.y].color == color)
                return true;
        return false;
    }

    // ПІДРАХУНОК ПРІОРИТЕТУ КЛІТИНКИ
    int priority(int x, int y, int color)
    {
        Cell c = this->field[x][y];
        if(!isEmpty(c))
            return 0;
        int priorityEmpty = 5;
        int priorityFull = 10;
        int penalty = -3;
        int total = 0;
        for (auto to : turns[x][y])
        {
            Cell v = this->field[to.x][to.y];
            if(!isEmpty(v))
                total += priorityFull + (penalty*(color == v.color));
            else total += priorityEmpty + (penalty*(color == v.color));
        }
        return total;
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
            if(isEmpty(this->field[v.x][v.y]))
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
    double dfs(int x, int y, int color)
    {
        pii v = mp(x, y);
        if(!isEmpty(this->field[v.x][v.y]))
            return 0;
        vis[v.x][v.y] = true;
        double total = priority(v.x, v.y ,color);
        for (auto to : turns[v.x][v.y])
        {
            if(!vis[to.x][to.y] && dist[to.x][to.y] == dist[v.x][v.y] + 1)
                total += dfs(to.x, to.y, color);
        }
        if(dist[x][y]!=0)
            return total / ( (double)dist[x][y] );
        else return total;
    }

    /*
    ОСКІЛЬКИ ПЕРЕД ПІДРАХУНКОМ ПОТЕНЦІАЛУ НАМ ПОТРІБНО ОБРАХУВАТИ ВІДСТАНІ,
    МИ ЗАПУСКАЕМО БФС І ОБРАХОВУЕМО ПОТЕНЦІАЛ КЛІТИНКИ
    */
    double getRank(int x,int y, int color)
    {
        bfs(x,y);
        clrVisit();
        return dfs(x, y, color);
    }

    pii getBestCell(int color)
    {
        vector < pair < double, pii > > Ranks;
        for (int i(1);i<=this->N;i++)
            for (int j(1);j<=this->M;j++)
                if(canGo(i,j,color))
                    Ranks.pb(mp(getRank(i,j,color), mp(i,j)));

        sort(Ranks.begin(),Ranks.end());
        return Ranks.back().second;
    }

    /// FINISH INTELECT METHODS

    ///TODO : дописати процедури гри
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
