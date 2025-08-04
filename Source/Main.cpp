#include "Main.h"
#include "Game.h"
#include "ComputerPlayer.h"

int main(int argc, char** argv)
{
	std::shared_ptr<Player> alice = std::make_shared<ComputerPlayer>("Alice");
	std::shared_ptr<Player> bob = std::make_shared<ComputerPlayer>("Bob");
	std::shared_ptr<Player> charles = std::make_shared<ComputerPlayer>("Charles");

	Game game;
	game.AddPlayer(alice);
	game.AddPlayer(bob);
	game.AddPlayer(charles);

	game.Play();

	return 0;
}