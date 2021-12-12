// Course:				IGME 309-05
// Student Name:		Kyle James
// Assignment Number:	01

// General Inclusions
#include <iostream>

// Memory Leak Detection Inclusions
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

// Using statements
using namespace std;

// Declare functions
/// <summary>
/// Generates a random number between 1 and 100.
/// </summary>
/// <returns>A random number between 1 and 100.</returns>
int generateRandom();

/// <summary>
/// Runs the Hi-Lo game.
/// </summary>
void gameWrapper();

/// <summary>
/// The main method to run the program.
/// </summary>
/// <returns>0 - The Console Application</returns>
int main()
{
	// Fields
	bool ready = false;
	char input;

	// Seed random with the currrent time
	srand(time(NULL));

	// Introduce the game to the user with instructions
	cout << "Welcome to Hi-Lo!" << endl;
	cout << "Your goal is to guess the number between 1 and 100 in as few guess as possible." << endl << endl;

	// Ask the player to start the game
	cout << "Ready to play? (y/n): ";
	while (!ready)
	{
		// Get the user's input
		cin >> input;
		input = tolower(input);

		// Check the state of input
		switch (input)
		{
			// If input is y (yes)
			case 'y':
				ready = true;
				break;
			// If input is n (no)
			case 'n':
				cout << "Maybe next time. Thanks for stopping by!" << endl;
				return 0;
				break;
			// Invalid input
			default:
				cout << "Invalid input.\n\nReady to play? (y/n): ";
		}
	}

	// Now that the player is ready, start the game
	while (ready)
	{
		// Fields
		bool inputCheck = false;

		// Run the game
		gameWrapper();

		// Prompt user input
		cout << "Would you like to play again? (y/n): ";

		while (!inputCheck)
		{
			// Get the user's input
			cin >> input;
			input = tolower(input);

			// Check the state of input
			switch (input)
			{
				// If input is y (yes)
				case 'y':
					inputCheck = true;
					break;
				// If input is n (no)
				case 'n':
					cout << "\nMaybe next time. Thanks for playing!" << endl;
					inputCheck = true;
					ready = false;
					return 0;
					break;
				// Invalid input
				default:
					cout << "Invalid input.\n\nWould you like to play again? (y/n): ";
			}
		}
	}

	// Check for memory leaks
	_CrtDumpMemoryLeaks();
}

/// <summary>
/// Runs the Hi-Lo game.
/// </summary>
void gameWrapper()
{
	// Fields
	bool guessed = false;
	int guess;
	int guesses = 0;
	int random;

	// Inform the user
	cout << "\n\n\nGame starting..." << endl;
	cout << "You may give up at any point by guessing -1." << endl << endl;

	// Generate random number
	cout << "Generating a random number..." << endl;
	random = generateRandom();
	cout << "I've thought of a number!" << endl << endl;

	// DEBUG--
	//cout << "NUMBER: " << random << endl;

	// Loop while the answer hasn't been guessed
	while (!guessed)
	{
		// Prompt the user to guess
		cout << "Enter a number: ";

		// Clear stream in case user tries to enter letters
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		// Store the guess
		cin >> guess;

		// Check the user's guess
		if (guess == -1)
		{
			cout << "\nGiving up so soon?" << endl;
			cout << "The number was " << random << ".\nYou guessed " << guesses << " time(s)." << endl << endl;
			guessed = true;
		}
		else if (guess < random)
		{
			guesses++;
			cout << "Your guess is low." << endl << endl;
		}
		else if (guess > random)
		{
			guesses++;
			cout << "Your guess is high." << endl << endl;
		}
		else
		{
			guesses++;
			cout << "Congratulations! You guessed the number in " << guesses << " guess(es)!" << endl << endl;
			guessed = true;
		}
	}
}

/// <summary>
/// Generates a random number between 1 and 100.
/// </summary>
/// <returns>A random number between 1 and 100.</returns>
int generateRandom()
{
	return rand() % 100 + 1;
}