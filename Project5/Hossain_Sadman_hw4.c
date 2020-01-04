#include <iostream>
#include <stdlib.h>  using namespace std;

struct Card
{
	char* suit;
	int value;
};

struct BagNode
{
	Card* card;
	BagNode* next;
};

int main(int argc, char** argv)
{

}