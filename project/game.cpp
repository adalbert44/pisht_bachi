#include "basic_classes.cpp"

///pattern game class
class FirstRegimeGame
{
public:
    players_regime players;

	Cell field[100][100];

    ///set methods
    void setColorAround(int x, int y, int color)
    {
        this->field[x][y].color = color;
        for(auto move : moves)
            this->field[x + move.first][y + move.second].color = color;
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
	FirstRegimeGame(players_regime players, Town *town1, Town *town2)
	{
        this->players = players;

        this->setTown(town1);
        this->setTown(town2);
	}

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
	FirstRegimeGame game1 = FirstRegimeGame(READ_FROM_FILE, town1, town2);
	game1.setFort(new Fort(1,2,1));
	game1.play();

	system("pause");
    return 0;
}
