#include "FCatDogGame.h"
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

FCatDogGame::FCatDogGame() { Reset(); }

void FCatDogGame::Reset() {

	constexpr int32 Max_Tries = 8;
	const FString Hidden_Word = "daniel";

	//MyMaxTries = Max_Tries;
	MyHiddenWord = Hidden_Word;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;

}

int32 FCatDogGame::GetCurrentTry() const{ return MyCurrentTry; }

int32 FCatDogGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FCatDogGame::IsGameWon() const{ return bGameIsWon; }

int32 FCatDogGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,3}, {4,4}, {5,5}, {6,6} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

EWordStatus FCatDogGame::CheckGuess(FString Guess) const{
	// if the guess isn't an isogram, return an error
	if (!IsIsogram(Guess)) {
		return EWordStatus::Not_Isogram;
	}	// if the guess isn't all lowercase, return an error
	else if (!IsLowerCase(Guess)) {
		return EWordStatus::Not_Lowercase;
	}	// if the guess length is wrong, return error
	else if(Guess.length() != GetHiddenWordLength()){
		return EWordStatus::Wrong_Length;
	}	// otherwise, return OK
	else {
		return EWordStatus::OK;
	}
	
}

// recieves a VALID guess, increments turn, returns count
FCatDogCount FCatDogGame::SubmitGuess(FString Guess) {
	// increment the turn number
	MyCurrentTry++;

	// setup a return variable
	FCatDogCount CatDogCount;

	// loop through all letters in the guess
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 MyHiddenChar = 0; MyHiddenChar < HiddenWordLength; MyHiddenChar++) {
		// compare letter against the hidden word
		for (int32 GuessChar = 0; GuessChar < HiddenWordLength; GuessChar++) {
			// if they match then
			if (Guess[GuessChar] == MyHiddenWord[MyHiddenChar]) {
				// if they're in the same place
				if (MyHiddenChar == GuessChar) {
					CatDogCount.Cats++;	// increment cats
				}
				else {
					CatDogCount.Dogs++;	// increment dogs
				}

			}
					
		}
	}
	if (CatDogCount.Cats == HiddenWordLength) {
	
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return CatDogCount;
}

bool FCatDogGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter word as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	// loop through all the letters of the word
	for (auto Letter : Word) {
		Letter = tolower(Letter);
		// if the letter is in the map
		if (LetterSeen[Letter]) { return false; }	// we do NOT have an isogram
		else {
			// add the letter to the map as seen
			LetterSeen[Letter] = true;
		}

	}
			
	return true;
}

bool FCatDogGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter)) { return false; }
	}
	return true;
}

