#include "includes.h"
#include "constants.h"
#include "Film.h"
#include "User.h"
#include "Rating.h"
#include "Recommender.h"

int main(int argc, char *argv[])
{
    Recommender application;
    application.run(argv[1], argv[2]);
    return 0;
}