#include "Main.h"

int main(int argc, char** argv)
{
	// Your memory is in two parts A and B...
	// 
	// A: For each card you track:
	//   1) The set of possible owners, or
	//   2) The known onwer.
	//
	// B: You also track all refutes.  (e.g., Sally disproved an accusation.  We're not told how, but we know she did.)
	//
	// Anytime the state of A changes, you can reduce B.
	// Reducing B can change the state of A.
	//
	// When a failure to refute occurs, you can update A.
	//
	// A refute is reduced when we know that the disprover doesn't have a card in the disproved accusation.
	// When a refute reduces to one card, then we know the disprover has that card.
	//
	// And of course, we can change A whenever we make an accusation and either receive a refute of it or someone fails to refute it.
	//
	// A note about updating A: We also know the total number of cards in everyone's hand, and that never changes.
	// Therefore, if the total number of remaining unknown cards in a person's hand equals the total number of possible
	// cards the person is assigned to, then we can deduce that they have those cards.

	return 0;
}