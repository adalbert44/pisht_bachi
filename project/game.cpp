#include "basic_classes.cpp"

#define FILENAME "file_with_turns"

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
	int current_player;///позначає номер гравця, який тепер ходить(1 або 2)

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
        if(this->field[x][y].town == nullptr) this->field[x][y].color = color;
        for(auto turn : turns[x][y])
            if(this->field[turn.x][turn.y].town == nullptr)
                this->field[turn.x][turn.y].color = color;
    }

    bool setTown(Town *town)
    {
        if(this->field[town->x][town->y].town != nullptr) return false;

        this->setColorAround(town->x, town->y, town->color);
        this->field[town->x][town->y].town = town;

        return true;
    }

    bool setFort(Fort *fort)
    {
        if(this->field[fort->x][fort->y].fort != nullptr) return false;

        this->field[fort->x][fort->y].fort = fort;
        this->setColorAround(fort->x, fort->y, fort->color);

        return true;
    }
    void setGeneral(General *general)
    {
        this->field[general->x][general->y].general = general;
    }
    ///end set methods

    ///constructors
	FirstRegimeGame() {}
	FirstRegimeGame(players_regime players,int width, int height, Town *town1, Town *town2)
	{
        this->players = players;

        this->N = width;
        this->M = height;

        this->current_player = 1;

        this->generateTurns();

        this->setTown(town1);
        this->setTown(town2);
	}


    /// START INTELECT METHODS

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
        if(this->field[x][y].fort != nullptr) return false;
        if(this->field[x][y].town != nullptr) return false;
        if(this->field[x][y].relief != EMPTY) return false;

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

        return max_element(Ranks.begin(), Ranks.end()) -> second;
    }

    /// FINISH INTELECT METHODS

    ///TODO : дописати процедури гри

	void goFromFile()
	{

        int x, y;
        cin >> x >> y;

        this->setFort(new Fort(x, y, current_player));
        this->current_player = 3 - this->current_player;
	}

    void goPlayerPlayer()
    {

        this->current_player = 3 - current_player;
    }

    void goPlayerComputer()
    {
        int x, y, iterations;
        do
        {
            if(iterations > 0) cout << "Incorrect turn! Try again\n";
            cin >> x >> y;
            iterations++;
        }
        while(!canGo(x, y, current_player) || !this->setFort(new Fort(x, y, current_player)));

        this->current_player = 3 - current_player;

        pii computer_going = this->getBestCell(current_player);

        this->setFort(new Fort(computer_going.x, computer_going.y, current_player));
        this->current_player = 3 - this->current_player;
    }
    /// end empty methods

	void go()
	{
        switch(players)
        {
            case READ_FROM_FILE :
            {
                this->goFromFile();
                break;
            }
            case PLAYER_PLAYER :
            {
                this->goPlayerPlayer();
                break;
            }
            case PLAYER_COMPUTER :
            {
                this->goPlayerComputer();
                break;
            }
        }
	}

	int get_current_winner()
	{
        int score1 = 0, score2 = 0;
        for(int i = 1; i <= this->N; i++)
            for(int j = 1; j <= this->M; j++)
                if(this->field[i][j].color == 1)
                    score1++;
                else
                    score2++;
        return (score1 > score2 ? 1 :(score1 < score2 ? 2 : 0));
	}
};
