#include "Rating.h"
#include "constants.h"


Rating string_to_rating(const std::string& str) {
    if (str == PERFECT) return Rating::Perfect;
    if (str == AVERAGE) return Rating::Average;
    return Rating::Poor;
}

std::string rating_to_string(Rating r) {
    switch (r) {
        case Rating::Perfect: return PERFECT;
        case Rating::Average: return AVERAGE;
        case Rating::Poor: return POOR;
    }
    return NO_RATING;
}