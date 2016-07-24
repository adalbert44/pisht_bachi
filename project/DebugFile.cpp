#include "game.cpp"
#include <bits/stdc++.h>
#define N 10
#define M 10


Town *town1 = new Town(1, 1, 1);
Town *town2 = new Town(3, 3, 2);
FirstRegimeGame game1 = FirstRegimeGame(READ_FROM_FILE,10,10, town1, town2);


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

int main()
{
	srand(unsigned(time(NULL)));

    writeRank(1);
    cout << "\n";
    writeRank(2);
    cout << "\n";
    writeColor();
    cout << "\n";
    writeBestCell(1);
    cout << "\n";
    writeBestCell(2);
    cout << "\n";
	writeDist();

	system("pause");
    return 0;
}
