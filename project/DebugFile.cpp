#include "game.cpp"
#include <bits/stdc++.h>

int N, M, Mode, Turns;
pair<int, int> a, b;

Town *town1, *town2;
FirstRegimeGame game1;


void writeRank(int color)
{
    for (int i(1);i<=N;i++)
	{
        for (int j(1);j<=M;j++)
            cout << fixed << setprecision(3) << game1.getRank(i, j, color) << ' ';
        cout << "\n";
	}
}

void writeColor()
{
    for (int i(1);i<=N;i++)
    {
        for (int j(1);j<=M;j++)
            cout << game1.field[i][j].color << ' ';
        cout << "\n";
    }
}

void writeDist()
{
    for (int i(1);i<=N;i++)
    {
        for (int j(1);j<=M;j++)
            cout << dist[i][j] << ' ';
        cout << "\n";
    }
}

void writeBestCell(int color)
{
    pii bestCell = game1.getBestCell(color);
    cout << bestCell.fi << ' ' << bestCell.se;
    cout << "\n";
}

string WhoWin()
{
    int winner = game1.get_current_winner();
    if(winner == 1)
        return "First player win!";
    else if(winner == 2)
        return "Second player win";
    else
        return "Nobody wins! It's draw!";
}

void playFromFile()
{
    freopen(FILENAME".txt","r", stdin);
    cin >> N >> M >> Mode >> a.x >> a.y >> b.x >> b.y;

    town1 = new Town(a.x, a.y, 1);
    town2 = new Town(b.x, b.y, 2);
    game1 = FirstRegimeGame(READ_FROM_FILE, N, M, town1, town2);

    cin >> Turns;
    for(int i = 1; i <= 2 * Turns; i++)
    {
        game1.go();
        cout << "Turn number " << i << endl;
        writeColor();
        cout << endl;
    }

    cout << WhoWin() << "\n";
}

void playWithComputer()
{
    cin >> N >> M >> Mode >> a.x >> a.y >> b.x >> b.y;

    town1 = new Town(a.x, a.y, 1);
    town2 = new Town(b.x, b.y, 2);
    game1 = FirstRegimeGame(PLAYER_COMPUTER, N, M, town1, town2);

    cin >> Turns;
    writeColor();
    cout << endl;
    for(int i = 1; i <= Turns; i++)
    {
        game1.go();
        cout << "Turn number " << i << endl;
        writeColor();
        cout << endl;
    }

    cout << WhoWin() << "\n";

}

int main()
{
	srand(unsigned(time(NULL)));
    cout << "Select mode(1 - FROM_FILE, 2 - WITH COMPUTER) : ";
    int regime;
    cin >> regime;
    if(regime == 1)
        playFromFile();
    else
        playWithComputer();


	system("pause");
    return 0;
}
