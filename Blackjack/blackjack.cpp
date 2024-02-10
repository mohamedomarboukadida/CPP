#include <iostream> // For basic input/output
#include <ctime>    // Used to get time for seeding random number
#include <cctype>   // Used for 'toupper' function

// Black Jack Game By Cody Ray Miller
std::string versionNumber = "1.0"; // Dynamic Version Number

// Card array variables
// Constant set of 52 cards used for "resetting" the 'cards' array
const char permaCards[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K',
                           'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K',
                           'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K',
                           'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};

// Array used as a temporary pool of cards when shuffling
char cards[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K',
                'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K',
                'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K',
                'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};

// Represents a shuffled deck of 52 cards
char deck[52];

// The player's active hand, filled with card chars
char playerHand[12];

// An array to store the individual point values of each card in the player's hand
int playerHandScore[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Total value if the player's hand in a single int
int playerHandTotal;

// The player's active hand, filled with card chars
char dealerHand[12];

// An array to store the individual point values of each card in the player's hand
int dealerHandScore[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Total value if the player's hand in a single int
int dealerHandTotal;

// Counting variables
int i;                   // Integer used as a counter for 'for' loops
int a;                   // Counter for ace 'for' loop
int dealerHandCount = 0; // Used to keep track of the number of cards in dealer's hand
int playerHandCount = 0; // Used to keep track of the number of cards in player's hand
int deckCount = 1;       // Used to keep track of how many cards have been pulled from the deck

// Logic variables
bool validCard;          // Used by 'shuffle' function to determine if card "drawn" is a non-repeat
bool playerDone;         // Is the player DONE making moves?
bool dealerDone;         // Is the dealer DONE making moves?
bool playerBust;         // Has the player gone BUST?
bool dealerBust;         // Has the dealer gone BUST?
bool gameOver;           // Is the game OVER?
bool keepPlaying = true; // Keep playing or exit the game?

// Other variables
int randNum;              // Integer used for random number assignment
int aceSelect = 1;        // Used with 'cin' to receive user input for the desired value of an Ace card
char hitSelect = 'Q';     // Used with 'cin' to determine if the player wants to HIT or STAY
char playAgainChar = 'Q'; // Used win 'cin' to determine if the player wants to play another hand

// Money variables
int playerChips = 1000; // Number of chips (dollars) the player starts with
int playerBet;          // The amount the player wants to bet per hand

void updatePlayerHandTotal()
{
    playerHandTotal = playerHandScore[0] + playerHandScore[1] + playerHandScore[2] + playerHandScore[3] + playerHandScore[4] + playerHandScore[5] + playerHandScore[6] + playerHandScore[7] + playerHandScore[8] + playerHandScore[9] + playerHandScore[10] + playerHandScore[11] + playerHandScore[12] + playerHandScore[13] + playerHandScore[14] + playerHandScore[15];
}

void updateDealerHandTotal()
{
    dealerHandTotal = dealerHandScore[0] + dealerHandScore[1] + dealerHandScore[2] + dealerHandScore[3] + dealerHandScore[4] + dealerHandScore[5] + dealerHandScore[6] + dealerHandScore[7] + dealerHandScore[8] + dealerHandScore[9] + dealerHandScore[10] + dealerHandScore[11] + dealerHandScore[12] + dealerHandScore[13] + dealerHandScore[14] + dealerHandScore[15];
}

void updatePlayerHandValues()
{
    if (!playerDone)
    {
        for (i = 0; i < 16; i++)
        {
            switch (playerHand[i])
            {
            case 'K':
            case 'Q':
            case 'J':
            case 'T':
                playerHandScore[i] = 10;
                break;

            case '9':
                playerHandScore[i] = 9;
                break;

            case '8':
                playerHandScore[i] = 8;
                break;

            case '7':
                playerHandScore[i] = 7;
                break;

            case '6':
                playerHandScore[i] = 6;
                break;

            case '5':
                playerHandScore[i] = 5;
                break;

            case '4':
                playerHandScore[i] = 4;
                break;

            case '3':
                playerHandScore[i] = 3;
                break;

            case '2':
                playerHandScore[i] = 2;
                break;

            case 'A':
                // Display cards in the player's current hand
                std::cout << "\nYour hand: ";
                for (a = 0 - playerHandCount; a < 0; a++)
                {
                    std::cout << playerHand[a + playerHandCount];
                    if (a < -1)
                    {
                        std::cout << ", ";
                    } // Display a comma if NOT the last card of the hand
                }
                std::cout << "\n\nCard #" << i + 1 << " in your hand is an Ace.\n"
                          << "Should it be counted as 1 or 11?\n";
                std::cin >> aceSelect;
                if (aceSelect == 1)
                {
                    std::cout << "Using the Ace as a 1 . . .";
                    playerHandScore[i] = 1;
                }
                else if (aceSelect == 11)
                {
                    std::cout << "Using the Ace as an 11 . . .";
                    playerHandScore[i] = 11;
                }
                break;

            case 'x':
                playerHandScore[i] = 0;
            }
        }
    }
}

void updateDealerHandValues()
{
    if (!dealerDone)
    {
        for (i = 0; i < 16; i++)
        {
            switch (dealerHand[i])
            {
            case 'A':
                // An Ace will always be used as an 11 by the dealer.
                //  This has to be improved later because it's unrealistic.
                dealerHandScore[i] = 11;
                break;

            case 'K':
            case 'Q':
            case 'J':
            case 'T':
                dealerHandScore[i] = 10;
                break;

            case '9':
                dealerHandScore[i] = 9;
                break;

            case '8':
                dealerHandScore[i] = 8;
                break;

            case '7':
                dealerHandScore[i] = 7;
                break;

            case '6':
                dealerHandScore[i] = 6;
                break;

            case '5':
                dealerHandScore[i] = 5;
                break;

            case '4':
                dealerHandScore[i] = 4;
                break;

            case '3':
                dealerHandScore[i] = 3;
                break;

            case '2':
                dealerHandScore[i] = 2;
                break;

            case 'x':
                dealerHandScore[i] = 0;
            }
        }
    }
}

void playerTurn()
{
    if (!playerDone)
    {
        hitSelect = 'Q';
        while (hitSelect == 'Q')
        {
            std::cout << "\n\nDo you want to HIT or STAY? (Please enter 'H' or 'S'): ";
            std::cin >> hitSelect;
            hitSelect = toupper(hitSelect); // Convert character entered to UPPERCASE.
            if (hitSelect == 'H')
            {
                std::cout << "\nDealing card " << deckCount << " to player . . .\n";
                playerHand[playerHandCount] = deck[deckCount];
                deck[deckCount] = 'x';
                playerHandCount++;
                deckCount++;

                updatePlayerHandValues();
                updatePlayerHandTotal();
                std::cout << "\nYour hand: ";
                for (i = 0 - playerHandCount; i < 0; i++)
                {
                    std::cout << playerHand[i + playerHandCount];
                    if (i < -1)
                    {
                        std::cout << ", ";
                    } // Display a comma if NOT the last card of the hand
                }
                std::cout << "\n\nThe total of your current hand is . . . " << playerHandTotal << ".";

                if (playerHandTotal > 21)
                {
                    playerDone = true;
                    playerBust = true;
                }
            }
            else if (hitSelect == 'S')
            {
                std::cout << "\nPlayer will STAY with " << playerHandTotal << ".";
                playerDone = true;
            }
            else
            {
                std::cout << "Invalid entry. Please enter 'H' or 'S' when prompted.";
                hitSelect = 'Q';
            }
        }
    }
}

void dealerTurn()
{
    updateDealerHandTotal();

    if (!dealerDone)
    {
        if (dealerHandTotal < 17)
        {
            std::cout << "\n\nDealing card " << deckCount << " to dealer . . .\n";
            dealerHand[dealerHandCount] = deck[deckCount];
            deck[deckCount] = 'x';
            dealerHandCount++;
            deckCount++;
            updateDealerHandValues();
            updateDealerHandTotal();
            std::cout << "\nDealer's hand: ";
            for (i = 0 - dealerHandCount + 1; i < 0; i++)
            {
                std::cout << dealerHand[i + dealerHandCount];
                if (i < -1)
                {
                    std::cout << ", ";
                } // Display a comma if NOT the last card of the hand
            }
        }
        else
        {
            std::cout << "\nDealer will STAY.";
            dealerDone = true;
        }
    }
}

void exitPrompt()
{
    playAgainChar = 'Q';
    while (playAgainChar == 'Q')
    {
        std::cout << "\n\nDo you want to play again?\n";
        std::cin >> playAgainChar;
        playAgainChar = toupper(playAgainChar);
        if (playAgainChar == 'Y')
        {
            keepPlaying = true;
            // Reset variables
            playerDone = false;
            dealerDone = false;
            playerBust = false;
            dealerBust = false;
            gameOver = true;
            dealerHandTotal = 0;
            playerHandTotal = 0;
            deckCount = 1;
            dealerHandCount = 0;
            playerHandCount = 0;
            a = 0;

            // Reset player and dealer hand scores,
            for (i = 0; i < 16; i++)
            {
                playerHandScore[i] = 0;
                playerHand[i] = 'x';
            }
            for (i = 0; i < 16; i++)
            {
                dealerHandScore[i] = 0;
                dealerHand[i] = 'x';
            }
        }
        else if (playAgainChar == 'N')
        {
            keepPlaying = false;
        }
        else
        {
            std::cout << "Invalid Input! Please select either 'Y' or 'N'!";
            playAgainChar = 'Q';
        }
    }
}

void checkWin()
{
    updatePlayerHandTotal();
    updateDealerHandTotal();
    if (playerHandTotal > 21)
    {
        playerBust = true;
    }
    if (dealerHandTotal > 21)
    {
        dealerBust = true;
    }

    if (playerBust && !dealerBust)
    {
        std::cout << "\n\nPlayer went BUST with " << playerHandTotal << ". Dealer WINS.";
        playerChips = playerChips - playerBet;
        gameOver = true;
        exitPrompt();
    }
    else if (playerDone && !playerBust && dealerBust)
    {
        std::cout << "\n\nDealer went BUST with " << dealerHandTotal << ". Player WINS!";
        std::cout << "\nDealer's hand: ";
        for (i = 0 - dealerHandCount; i < 0; i++)
        {
            std::cout << dealerHand[i + dealerHandCount];
            if (i < -1)
            {
                std::cout << ", ";
            } // Display a comma if NOT the last card of the hand
        }
        playerChips = playerChips + playerBet;
        gameOver = true;
        exitPrompt();
    }
    else if (playerBust && dealerBust)
    {
        std::cout << "\n\nPlayer and Dealer both went BUST. Dealer WINS.";
        playerChips = playerChips - playerBet;
        gameOver = true;
        exitPrompt();
    }
    else if (playerDone && dealerDone)
    {
        if (playerHandTotal > dealerHandTotal)
        {
            std::cout << "\n\nDealer had " << dealerHandTotal << ". Player wins with "
                      << playerHandTotal << "!";
            playerChips = playerChips + playerBet;
            gameOver = true;
            exitPrompt();
        }
        else if (playerHandTotal < dealerHandTotal)
        {
            std::cout << "\n\nDealer wins with " << dealerHandTotal << ". (Player had "
                      << playerHandTotal << ".)";
            playerChips = playerChips - playerBet;
            gameOver = true;
            exitPrompt();
        }
        else if (playerHandTotal == dealerHandTotal)
        {
            std::cout << "\n\nDealer has " << dealerHandTotal << ". Player has "
                      << playerHandTotal << ". PUSH!";
            gameOver = true;
            exitPrompt();
        }
    }
}

void shuffle()
{
    std::cout << "Shuffling deck of cards . . .";

    for (i = 0; i < 52; i++)
    {
        validCard = false;
        while (!validCard)
        {

            randNum = (rand() % 52);

            if (cards[randNum] != 'x')
            {
                deck[i] = cards[randNum];
                validCard = true;
                cards[randNum] = 'x';
            }
        }
    }

    // Reset cards
    for (i = 0; i < 52; i++)
    {
        cards[i] = permaCards[i];
    }
}

void game()
{
    gameOver = false;
    // Shuffle the deck of cards and begin the game!
    shuffle();

    // Betting
    std::cout << "\n\nYou have $" << playerChips << ". How much do you want to bet?\n";
    std::cin >> playerBet;
    std::cout << "\nBetting $" << playerBet << ". . .\n";

    // Deal the initial cards to the player and dealer
    for (i = 0; i < 3; i++)
    {
        std::cout << "\nDealing card " << i + 1 << " to player . . .";
        playerHand[playerHandCount] = deck[i];
        deck[i] = 'x';
        playerHandCount++;
        i++;
        deckCount++;
        std::cout << "\nDealing card " << i + 1 << " to dealer . . .";
        dealerHand[dealerHandCount] = deck[i];
        deck[i] = 'x';
        dealerHandCount++;
        deckCount++;
    }

    // Show cards to the player
    std::cout << "\nYour hand: " << playerHand[0] << ", " << playerHand[1];
    std::cout << "\nDealer's hand: "
              << "[?]"
              << ", " << dealerHand[1];

    // Update values related to cards in hand and card totals
    updatePlayerHandValues();
    updateDealerHandValues();
    updatePlayerHandTotal();
    // Show the player their hand total
    std::cout << "\n\nThe total of your current hand is . . . " << playerHandTotal << ".";

    while (!gameOver)
    {

        playerTurn();
        checkWin();
        if (!gameOver)
        {
            dealerTurn();
            checkWin();
        }
    }
}

int main()
{
    // Seed the random number
    srand((int)time(0));

    while (keepPlaying)
    {
        game();
    }
    return 0;
}
