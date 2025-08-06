#pragma once

#include "Card.h"
#include <memory>

class Player;

/**
 * This class maintains the shared game state among the players and
 * coordinates the playing of the game.  It makes calls into the
 * participating players.  For secrecy reasons, no player makes a
 * call into the game.  The players are completely reactionary to
 * the game.  Whatever information a player may need to make their
 * decision will be given to them.  A player can make a decision
 * when asked by the game to do so.
 */
class Game
{
public:
	Game();
	virtual ~Game();

	bool AddPlayer(std::shared_ptr<Player> player);
	void Play();

private:

	Accusation correctAccusation;

	std::vector<std::shared_ptr<Player>> playerArray;
};