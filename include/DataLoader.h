#ifndef DATALOADER_H
#define DATALOADER_H

#include "includes.h"
#include "utils.h"

template <typename T>
class DataLoader
{
public:
    static std::vector<T> load_from_csv(const std::string &file_path)
    {
        std::vector<T> items;
        std::ifstream file(file_path);
        std::string line;

        if (!std::getline(file, line))
        {
            return items;
        }

        while (std::getline(file, line))
        {
            std::vector<std::string> tokens = split(line, CSV_DELIMITER);
            items.emplace_back(tokens);
        }
        return items;
    }
};

#endif
