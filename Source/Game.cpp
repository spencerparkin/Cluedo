#include "Game.h"
#include "Player.h"
#include "Card.h"

Game::Game()
{
}

/*virtual*/ Game::~Game()
{
}

bool Game::AddPlayer(std::shared_ptr<Player> player)
{
	for (std::shared_ptr<Player>& existingPlayer : this->playerArray)
		if (existingPlayer->GetName() == player->GetName())
			return false;

	this->playerArray.push_back(player);
	return true;
}

void Game::Play()
{
	std::vector<Card> cardArray;
	Card::GenerateDeck(cardArray);
	Card::ShuffleDeck(cardArray);

	// Remove the solution cards and remember the correct accusation.
	Card roomCard, weaponCard, characterCard;
	Card::FindAndRemoveCardOfType(cardArray, Card::Type::RoomType, roomCard);
	Card::FindAndRemoveCardOfType(cardArray, Card::Type::WeaponType, weaponCard);
	Card::FindAndRemoveCardOfType(cardArray, Card::Type::CharacterType, characterCard);
	this->correctAccusation.room = characterCard.room;
	this->correctAccusation.weapon = characterCard.weapon;
	this->correctAccusation.character = characterCard.character;

	// Deal out the remainder of the cards to the players.
	int i = 0;
	while (cardArray.size() > 0)
	{
		Card card = cardArray.back();
		cardArray.pop_back();

		std::shared_ptr<Player> player = this->playerArray[i];
		player->TakePossessionOfCard(card);

		i = (i + 1) % int(this->playerArray.size());
	}

	// Introduce the players to each others.
	for (i = 0; i < (int)this->playerArray.size(); i++)
	{
		std::shared_ptr<Player> playerA = this->playerArray[i];

		for (int j = 0; j < (int)this->playerArray.size(); i++)
		{
			if (i == j)
				continue;

			std::shared_ptr<Player> playerB = this->playerArray[j];
			playerA->BeIntroducedTo(playerB.get());
		}
	}

	// Let each player prepare for the game.
	for (i = 0; i < (int)this->playerArray.size(); i++)
		this->playerArray[i]->PrepareForGame();

	// Play can now begin.  Players take turns.  Some turns require one or more players to participate in the turn.
	i = 0;
	while (true)
	{
		// Get the next player whose turn it now is.
		std::shared_ptr<Player> player = this->playerArray[i];

		// If the player is disqualified, then they're no longer allowed to play,
		// but they still need to be around to answer questions from other players.
		if (!player->isDisqualified)
		{
			// We're not playing the game on an actual clue board.  Instead, we're
			// approximating the idea of going from room to room.  Ask the player what
			// room they want to be in.
			Room desiredRoom = player->GetDesiredRoom();

			// It is then by chance that they make it to the room or not.  There is no
			// need to consider the player as being in the hallway.  They either get to
			// the desired room or they don't.  If they do, then their turn can continue.
			if (Card::RandomInteger(0, 100) > 50)
			{
				// They made it to the desired room.  Ask the player to make an accusation.
				// Note that we ignore any accusation that is not in the desired room.
				Accusation accusation;
				player->MakeAccusation(accusation);
				if (accusation.room == desiredRoom)
				{
					// We then ask all other players in turn to refute the accusation.
					// We stop when a refute is obtained.  Note that if a player can
					// refute an accusation, they must, or else they are in violation
					// of the rules of the game.  They can choose choose how to refute
					// the accusation, but they cannot refuse to do so if they can.
					int j;
					for (j = 0; j < int(this->playerArray.size()); j++)
					{
						std::shared_ptr<Player> otherPlayer = this->playerArray[(i + j + 1) % int(this->playerArray.size())];
						
						Card cardToShowAccuser;
						if (otherPlayer->RefuteAccusation(accusation, player.get(), cardToShowAccuser))
						{
							// Note that everyone gets to know that the accusation was disproved,
							// but only the accuser gets to see the card that the disprover used
							// to disprove the accusation.
							for (int k = 0; k < int(this->playerArray.size()); k++)
								if (this->playerArray[k].get() != otherPlayer.get())
									this->playerArray[k]->AccusationDisproved(accusation, otherPlayer.get(), (k == i) ? &cardToShowAccuser : nullptr);

							break;
						}
						else
						{
							// Let everyone know, including the accuser, that a player could not disprove it.
							for (int k = 0; k < int(this->playerArray.size()); k++)
								if (this->playerArray[k].get() != otherPlayer.get())
									this->playerArray[k]->PlayerCouldNotRefuteAccusation(otherPlayer.get(), accusation, player.get());
						}
					}

					// If no one could refute the player's accusation, let everyone know.
					// Note that this does not imply that the accusation is the solution,
					// because the accuser may have named a card in their own hand.
					if (j == (int)this->playerArray.size())
					{
						for (int k = 0; k < int(this->playerArray.size()); k++)
							this->playerArray[k]->AccusationCouldNotBeRefutedByAnyone(accusation, player.get());
					}
				}
			}

			// Lastly, before a player ends their turn, give them a chance to win the game.
			Accusation finalAccusation;
			if (player->SolveMurderMsytery(finalAccusation))
			{
				if (finalAccusation == this->correctAccusation)
				{
					// TODO: Announce the winner here.
					break;
				}
				else
				{
					player->isDisqualified = true;
					// TODO: Announce that the player is disqualified here.
				}
			}
		}

		// Let it be the next player's turn.
		i = (i + 1) % int(this->playerArray.size());
	}
}