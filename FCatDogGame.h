#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FCatDogCount {
	int32 Cats = 0;
	int32 Dogs = 0;
};

enum EWordStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FCatDogGame {
public:
	FCatDogGame(); // constructor
	
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EWordStatus CheckGuess(FString) const;

	void Reset();
	// provide a method for counting cats & dogs, and increase turn #
	FCatDogCount SubmitGuess(FString Guess);

private:
	int32 MyCurrentTry;
	//int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;

};
