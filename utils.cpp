#include <cstdlib>
#include <ctime>

#include"utils.h"

int random_at_most(int min, int max)
{
	srand(time(NULL));
	return (min + (rand() % max));
}