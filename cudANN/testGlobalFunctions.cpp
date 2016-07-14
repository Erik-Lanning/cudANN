#include "testGlobalFunctions.h"

namespace cudANN
{
	void testAllGlobalFunctions()
	{
		testIsEqual();
	}

	void testIsEqual()
	{
		int expectedValue = NULL;
		int nullTest = NULL;
		assert(isEqual(expectedValue, nullTest) == true);

		int chainOfNulls[3] = {NULL};
		assert(isEqual(expectedValue, chainOfNulls[0], chainOfNulls[1], chainOfNulls[2]) == true);

		int notNull = 1;
		assert(isEqual(expectedValue, chainOfNulls[0], chainOfNulls[1], notNull) == false);

		char expectedCharacter = 'A';
		char testCharacterA = 'A';
		char testCharacterB = 'B';
		assert(isEqual(expectedCharacter, testCharacterA) == true);
		assert(isEqual(expectedCharacter, testCharacterA, testCharacterB) == false);
	}
}