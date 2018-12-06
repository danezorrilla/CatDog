#include <iostream>
#include <string>
#include "FCatDogGame.h"

// using UnReal coding standard
using FText = std::string;
using int32 = int;

// function prototype
void PlayGame();
bool PlayAgain();
void PrintGameSummary();

FCatDogGame BCGame; // instantiate a new game

// Introduction
void PrintIntro() {

// constexpr does computation on compile time as oppose to run time
	//constexpr int32 Word_Length = 7;

	std::cout << "Welcome to Cats and Dogs" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram that I am thinking of?" << std::endl;
	std::cout << std::endl;
	std::cout << "/\\,,,/\\      //^ ^\\\\" << std::endl;
	std::cout << "(=';'=)     (/(_o_)\\)" << std::endl;
	std::cout << " /*@@*\\      _/'*'\\_" << std::endl;
	std::cout << "(.|.|.|)   (,,,)^(,,,)" << std::endl;

}

// loop continually until the user gives a valid guess
FText GetValidGuess() {
	FText Guess = "";
	EWordStatus Status = EWordStatus::Invalid_Status;

	do {
	
		int32 CurrentTry = BCGame.GetCurrentTry();

		// get a guess from the player
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries(); 
		std::cout << ". Enter your guess: ";
		
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuess(Guess);
		switch (Status) {
		case EWordStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
		//std::cout << std::endl;
	} while (Status != EWordStatus::OK); // keep looping until we get valid input
	return Guess;

}

int main() {

	bool bPlayAgain = false;

	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = PlayAgain();
		std::cout << std::endl;
	
	} while (bPlayAgain);


	return 0;

}

void PlayGame()
{

	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();

	// constexpr int Max_Guess = 5;

	// loop for the number of guess
	// TODO change from FOR to WHILE loop once we are validating tries
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();	// TODO make loop checking valid guess



		// submit valid guess to the game
		FCatDogCount CatDogCount = BCGame.SubmitGuess(Guess);
		// print number of cats and dogs
		std::cout << "Cats = " << CatDogCount.Cats;
		std::cout << " Dogs = " << CatDogCount.Dogs << std::endl;

		std::cout << std::endl;

	}

	PrintGameSummary();
	return;
}

bool PlayAgain() {

	std::cout << "Do you want to play again (y/n)?" << std::endl;
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');

}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Well Done - You Won!\n";
	}
	else {
		std::cout << "Better luck next time!\n";
	}
}
