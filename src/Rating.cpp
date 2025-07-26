#include "Rating.h"

Rating string_to_rating(const std::string& str) {
    if (str == "Perfect") return Rating::Perfect;
    if (str == "Average") return Rating::Average;
    return Rating::Poor;
}

std::string rating_to_string(Rating r) {
    switch (r) {
        case Rating::Perfect: return "Perfect";
        case Rating::Average: return "Average";
        case Rating::Poor: return "Poor";
    }
    return "";
}