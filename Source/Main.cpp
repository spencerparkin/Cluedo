#include "Main.h"

int main(int argc, char** argv)
{
	// For each person (including the solution) we track...
	//   1) What cards they possibly have, and...
	//   2) What cards we know they have.
	//   When the number of remaining possible cards equals the number of unknown cards (see #4 below), then we know all their cards.  This triggers #2 below.
	//   This is because we know the total number of cards in their hand from the start.
	//
	// For each turn (even if it is not our turn)...
	//   1) We log any refute made, but store it in fully reduced form, unless it reduces to 1 card, in which case go to (#2).
	//   2) Whenever we learn where a card actually is, we reduce all logged refutes as a consequence of this new information.
	//   3) If a refute reduces to 1 card, then we know where that card is, and we repeat the reduction (#2).  (Append to the queue.)
	//   4) We use any failure to refute as another way to reduce the set of possible cards anyone has and again, if we learn where a card is, then (#2).
	//   5) Being dealt a hand triggers this algorithm as well, because we're learning what cards we have.
	//
	// Lastly, treat the solution as a "player".  The only difference is that this "player" is never queried to refute.

	// Knowledge of where a card is goes on a queue to be processed.
	// The algorithm proceeds until the queue in empty.
	// Once empty, check to see if we have the solution.

	return 0;
}