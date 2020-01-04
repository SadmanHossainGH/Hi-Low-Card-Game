// ------------------------------------------------------------------------------------------------------------
// Assignment 4: Sadman Hossain
// ID:1212998226
// Class Time : MWF 2:00-2:50
// The goal of this program is to implment a linked list strucuture to create a Hi-Low card game.
// A player must continue to guess the value of the card to gain points. If the player fails to guess
// the value of a card, the game stops and the program exits.
// ------------------------------------------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <stdlib.h>  


// STRUCTURES---------------------------------------------------------------------------------------------------
//Struct for Card Type
struct Card
{
	char suit;
	int value;
};

// Struct for Node,holds place for Card in bag
struct BagNode
{
	Card* card;
	BagNode* next;
};
// ------------------------------------------------------------------------------------------------------------

// PROTOTYPES--------------------------------------------------------------------------------------------------
bool HiLoMenu(Card grabbedCards[], int& points, int& count);

// Prototypes-diffrent paths bassed on Card value
bool higherCard(Card grabbedCards[], int& points, int turns);
bool lowerCard(Card grabbedCards[], int& points, int turns);
bool equalCard(Card newCard, int& points, int numChoice);

// Prototypes-maintains Linked List
int getCurrentSize();
bool isEmpty();
void add(BagNode* newItem);
Card grab(BagNode*& head);
int getFrequencyOf(int value);
void empty();

// Prototypes-alters Linked List properties
void fillWithCards();
void printProbability(Card item, int count);
void printCard(Card item);
// ------------------------------------------------------------------------------------------------------------

// head and tail node instantation for public use
BagNode* head = new BagNode();
BagNode* tail = new BagNode();

int main(int argc, char** argv)
{
	int turns = 0; //maintains number of turns
	int points = 0;// number of points
	bool contin = true;// indicates Hi-Low continuation
	Card grabbedCards[34];//array for grabbed cards

	empty();
	fillWithCards();

	Card newCard = grab(head);
	grabbedCards[turns] = newCard;
	turns++;

	do
	{
		std::cout << "Cards drawn ";
		for (int i = 0; i < turns; i++)
		{
			printCard(grabbedCards[i]);
		}

		std::cout << "Cards left in deck: " << getCurrentSize()<<"\n";
		printProbability(grabbedCards[turns - 1], turns);

		std::cout << "Last Card:";
		printCard(grabbedCards[turns-1]);
		std::cout << "\n";

		contin = HiLoMenu(grabbedCards,points,turns);

		//refills deck if 2/3 of cards have been used
		if (turns >= 34 && contin==true)
		{
			empty();
			fillWithCards();
			turns = 0;

			// grabs new card after refill
			Card newCard = grab(head);
			grabbedCards[turns] = newCard;
			turns++;
		
			std::cout << "1/3 or cards were left, deck has reset\n";
		}

	} while (contin==true);

	// GAME OVER situation, players is informed and final points displayed
	std::cout << "GAME OVER\n";
	std::cout << "Points: " << points<<"\n";

	return 0;
}

//Menu for player's guess in H-=Low Game, returns Hi-Low continuation
bool HiLoMenu(Card grabbedCards[], int& points,int& turns)
{
	Card newCard; //stores card variable post grab()
	char charChoice = '0'; //stores user input
	int  numChoice = 0; //stores specifc guess for Case 3
	bool contin = true;// used for return value

	//points and choice display
	std::cout << "Points: " << points<<"\n Choose option: \n";
	std::cout << "1 - Next card will be higher \n";
	std::cout << "2 - Next card will be lower \n";
	std::cout << "3 - Guess exact value\n";

	//gets and checks validty of user input
	do
	{
		std::cin >> charChoice;
		if (charChoice < '1' || charChoice>'3')
		{
			std::cout << "Invalid choice.Try Again";
		}
	} while (charChoice < '1' || charChoice>'3');

	// switches based on user choice
	switch (charChoice)
	{
	 // higher option , graps card and calls higherCard function
	case '1':
		newCard = grab(head);
		grabbedCards[turns] = newCard;
		turns++;
		contin=higherCard(grabbedCards,points, turns);
		break;

	// lower option , graps card and calls lowerCard function
	case '2':
		newCard = grab(head);
		grabbedCards[turns] = newCard;
		turns++;
		contin = lowerCard(grabbedCards, points, turns);
		break;

	// exact option,grabs card, asks for user value,and calls equalCard function
	case '3':
		//prompts for and gains user input
		std::cout << "Choose a number...\n";
		std::cin >> numChoice;

		//checks validity of user input
		while (numChoice<1||numChoice>13)
		{
			std::cout << "Invalid choice.Try Again\n";
			std::cin >> numChoice;
		}

		newCard = grab(head);
		grabbedCards[turns] = newCard;
		turns++;
		contin=equalCard(newCard,points,numChoice);
		break;
	}

	return contin;
}

//checks values of previous and new drawn card, awards points based on 
//higher card values
bool higherCard(Card grabbedCards[],int& points, int turns)
{
	int newVal = grabbedCards[turns - 1].value; //new card values
	int preVal = grabbedCards[turns - 2].value; //previous card value
	bool result = true; // used for return values

	//user was correct
	if (newVal > preVal)
	{
		points+=1;
		result=true;
	}
	//user was incorrect
	else if (newVal < preVal)
	{
		result=false;

	}
	//values were the same
	else if (newVal== preVal)
	{
		std::cout << "Same Card\n";
		result=true;
	}

	return result;
}

//checks values of previous and new drawn card, awards points based on 
//lower card values
bool lowerCard(Card grabbedCards[],int& points, int turns)
{

	int newVal = grabbedCards[turns - 1].value;//new card value
	int preVal = grabbedCards[turns - 2].value;//previous card value
	bool result = true;//used for return value

	//user was correct
	if (preVal > newVal)
	{
		points += 1;
		result=true;
	}
	//user was incorrect
	else if (preVal < newVal)
	{
		result=false;
	}
	//values were the same
	else if (preVal == newVal)
	{
		std::cout << "Same Card\n";
		result=true;
	}
	return result;
}

//checks values of previous and new drawn card, awards points based on 
// user inputted guess
bool equalCard(Card newCard, int& points, int numChoice)
{
	int newVal = newCard.value;//new card value

	//user was somehow correct
	if (numChoice == newVal)
	{
		points+=5;
		return true;
	}
	//user was incorrect
	else
	{
		return false;
	}
}

//returns current size of Linked List
int getCurrentSize()
{
	int count = 0; //current size of array
	BagNode* temp = head; //traversal node
	
	//temp travels the entire list
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}

	return count;
}

//returns wheter list is empty or not
bool isEmpty()
{
	//head is empty=no other nodes are connected
	if(head==NULL)
	{
		return true;
	}
	
	return false;
}

//adds node to head
void add(BagNode* newItem)
{
	//empty case
	if (head == NULL)
	{
		head = newItem;
		tail = newItem;
	}
	//connects to current head and gains head postion
	else
	{
		newItem->next = head;
		head = newItem;
	}
}

//randomly takes node from bag
Card grab(BagNode*& head)
{
	int size = getCurrentSize();//size of Linked List

	//Traversal node
	BagNode* temp = new BagNode();
	Card* newCard = new Card();
	temp->card = newCard;

	//holds node that will be grabbed
	BagNode* grabbed = new BagNode();
	Card* newCard2 = new Card();
	grabbed->card = newCard2;

	//empty case
	if (size == 0)
	{
		std::cout << "Empty List" ;
	}

	// calculates random postion for grab target
	int randVal = (rand() % size) + 1;

	// head case
	if (randVal == 1) 
	{
		temp = head;
		head = head->next;
		grabbed = temp;
		grabbed->card = temp->card;
		temp = NULL;
		delete(temp);
	}
	// tail case
	else if (randVal == size && size>1) 
	{
		temp = head;
		while (temp->next->next != NULL)
		{
			temp = temp->next;
		}
        
		grabbed = tail;
		grabbed->card = tail->card;
		tail = temp;
		tail->next = NULL;
		delete(tail->next);
	}
	//normal case, not head or tail
	else
	{
		//traversal node targeting random position
		BagNode* removed = new BagNode();
		Card* newCard3 = new Card();
		removed->card = newCard3;

		removed = head;
		int i = 1; // the removal node already starts at head

		//removed=removal postion, temp=node before removal
		while (removed->next != NULL && i != randVal)
		{
			temp = removed;
			removed = temp->next;
			i++;
		}

		temp->next=removed->next;
		grabbed->card= removed->card;
		removed->next = NULL;
		delete(removed);
	}

	return *grabbed->card;
}

//returns frequency of card value in Linked List
int getFrequencyOf(int value)
{
	int count = 0;//counts number of card value instances
	BagNode* temp = new BagNode();//traversal node

	//creates card type to hold and determine card values
	Card* newCard = new Card();
	temp->card = newCard;

	temp = head;
	temp->card = head->card;

	while (temp!=NULL)
	{
		int test = temp->card->value;
		if(test==value)
		{
			count++;
		}

		temp = temp->next;
	}

	return count;
}

//empties Linked List
void empty()
{

	BagNode* temp = new BagNode();//travrsal node

	while (head != NULL)
	{
		temp = head->next;
		delete(head);
		head = temp;
	}

	head = NULL;
}

//fils bags with 52 new cards
void fillWithCards()
{
	// used create and fill heart cards
	for (int i = 0; i <13; i++)
	{
		BagNode* newItem = new BagNode();

		Card* newCard = new Card();
		newItem->card = newCard;
		newItem->card->suit = 'H';
		newItem->card->value = i+1;

		add(newItem);
	}

	// used create and fill diamond cards
	for (int i = 0; i < 13; i++)
	{
		BagNode* newItem = new BagNode();

		Card* newCard = new Card();
		newItem->card = newCard;
		newItem->card->suit = 'D';
		newItem->card->value = i+1;

		add(newItem);
	}

	// used create and fill spade cards
	for (int i = 0; i < 13; i++)
	{
		BagNode* newItem = new BagNode();

		Card* newCard = new Card();
		newItem->card = newCard;
		newItem->card->suit = 'S';
		newItem->card->value = i+1;

		add(newItem);
	}

	// used create and fill club cards
	for (int i = 0; i < 13; i++)
	{
		BagNode* newItem = new BagNode();

		Card* newCard = new Card();
		newItem->card = newCard;
		newItem->card->suit = 'C';
		newItem->card->value = i+1;

		add(newItem);
	}

}

//prints probabilty of choosing cards values within deck
void printProbability(Card item, int count)
{
	//holds probabilites of different cases
	float higher = 0.00;
	float lower = 0.00;
	float equal = 0.00;
	
	float cardVal = item.value;//values of previous card
	float prob[13];// holds probabilities of each specific card
	int i;//counter variable

	//propability of cards lower than previous
	for (i = 0; i+1 < cardVal; i++)
	{
		prob[i] = (((float)getFrequencyOf(i+1) / (float)getCurrentSize()) * 100.00);
		lower = lower + prob[i];
	}

	//propability of cards equal to previous
	prob[i] = (((float)getFrequencyOf(i + 1) / (float)getCurrentSize()) * 100.00);
	equal = prob[i];

	//propability of cards higher than previous
	for (i=i+1; i < 13; i++)
	{
		prob[i] = (((float)getFrequencyOf(i+1) / (float)getCurrentSize()) * 100.00);
		higher = higher + prob[i];
	}

	std::cout << std::setprecision(3);//concaves decimals to three places

	//displays probabilities of each case
	std::cout <<"Probability of next card being higher: "  << higher << "%\n";
	std::cout << "Probability of next card being lower: " << lower << "%\n";
	std::cout << "Probability of next card being the same: " << equal << "%\n";
	std::cout << "\n";

	std::cout << "Probability of next card being : \n";
	for (int i = 0; i < 13; i++)
	{
		// used for specifc card types
		switch (i)
		{
		case 0:
			std::cout << "A  " << prob[i] << "%\n";
			break;
		case 10:
			std::cout << "J  " << prob[i] << "%\n";
			break;
		case 11:
			std::cout << "Q  " << prob[i] << "%\n";
			break;
		case 12:
			std::cout << "K  " << prob[i] << "%\n";
			break;
		default:
			std::cout << i+1 << "  " << prob[i] << "%\n";
			break;
		}
	}

 }

//prints properites of Card in paramter , usually from grabbed array
void printCard(Card item)
{
	//properties of card
	char suitType = item.suit;
	int  cardVal = item.value;

	//used for specifc card types
	switch (cardVal)
	{
	case 1:
		std::cout << "[A-"<<suitType<<"] ";
		break;
	case 11:
		std::cout << "[J-" << suitType << "] ";
		break;
	case 12:
		std::cout << "[Q-" << suitType << "] ";
		break;
	case 13:
		std::cout << "[K-" << suitType << "] ";
		break;
	default:
		std::cout << "["<<cardVal<< "-" << suitType << "] ";
	    break;

	}
}