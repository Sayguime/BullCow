/* Это исполняемый консолью файл который использует класс BullCow
* Он действует как вид в шаблоне MVC и отвечает за взаимодействие с пользователем
* Чтобы увидеть логику игры смотрите в класс FBullCowGame  50 
*/ 
#pragma once

#include <iostream>
#include <string> 
#include "FBullCowGame.h"

// to make syntax Unreal friendly 
using FText = std::string; 
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // inistantiate a new game, which we re-use across plays

// the entry point for our application 
int main() 
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 

	while (bPlayAgain);
	return 0; // exit the application
}

void PrintIntro() 
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;	
	std::cout << "Can you huess the " << BCGame.GetHiddenWordLenght();	
	std::cout << " letter isogram I'm thinking of?\n";	
	std::cout << std::endl;
	return;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game
	// is NOT won and there are still tries remanining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// sumbit valid guess to the game, and receive counts 
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

FText GetValidGuess() // loop continually until the user gives a valid guess
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries(); 
		std::cout << ". Enter youre Guess : ";
		std::getline(std::cin, Guess);

		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word witout repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters\n\n";
			break;
		default:
			// assume th guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping until we get no errors 
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}
 
void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else
	{
		std::cout << "Better luck next time\n";
	}
}
