#pragma once

#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly 
#define TMap std::map 
using int32 = int;

FBullCowGame::FBullCowGame() {	Reset();	} // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLenght() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const {	return bGameIsWon;	} 

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordlenghtToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordlenghtToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "plane"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) 	// if the guess isn't an isogram, return an error
	{
		return EGuessStatus::Not_Isogram;
	} 
	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase, return an error
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLenght()) // if the guess length is wrong, return error
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;	// otherwise, return ok
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		for(int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++; // incriment bulls 
				}

				else
				{
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter word as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word) // for all letters of the word 
	{
		Letter = tolower(Letter); // handle mixed case 
		if (LetterSeen[Letter])
		{
			return false; // we do NOT have an isogram
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		return false;
	}
	return true;
}
