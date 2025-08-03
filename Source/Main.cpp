#include "Main.h"
#include "BoardGraph.h"

int main(int argc, char** argv)
{
	BoardGraph boardGraph;

	boardGraph.Regenerate();

	// The goal here initially is to simulate the game with the most basic statagy.
	// Specifically, a player does nothing more than try to get to every room and
	// elimate possabilities based only on what information they get by making
	// accusations.  The goal then is to improve upon this basic stratagy by making
	// a player that observes every other player's turn, gleaning what additional
	// information can be gathered in doing so.  For example, if I observe a player
	// make an accusation that is disproved, then I don't know how it was disproved,
	// unless I hold in my hand two of the three elements of the accusation.  This
	// then lets me know what card was in the disprover's hand even though it was
	// not my turn to play, and even though such information is not shared with me.
	// There are probably many other ways to get information when it is not my turn.
	// I think the general idea is to not just eliminate possabilities, but also to
	// learn what cards are in other people's hands.

	return 0;
}