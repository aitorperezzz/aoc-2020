#include <vector>

#include "day11.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

// Checks if an index is valid for a certain size
bool validIndex(const size_t index, const size_t size)
{
    return index >= 0 && index <= (size - 1);
}

ErrorCode Day11::execute(const std::string &filename, unsigned int &result)
{
    // Load input file.
    std::vector<std::string> auxLayout;
    if (FileOpener::loadVector(auxLayout, filename) != Ok)
    {
        Logger::log("Could not read values from file", ERROR);
        return InvalidFile;
    }

    // Transform the grid into enums
    std::vector<std::vector<State>> layout;
    layout.resize(auxLayout.size());
    for (size_t row = 0; row < layout.size(); row++)
    {
        layout[row].resize(auxLayout[row].length());
        for (size_t i = 0; i < auxLayout[row].length(); i++)
        {
            if (auxLayout[row][i] == '.')
            {
                layout[row][i] = FLOOR;
            }
            else if (auxLayout[row][i] == 'L')
            {
                layout[row][i] = EMPTY;
            }
            else if (auxLayout[row][i] == '#')
            {
                layout[row][i] = OCCUPIED;
            }
            else
            {
                return ErrorCode::InvalidFile;
            }
        }
    }

    // Apply rules while needed
    size_t occupied;
    while (applyRules(layout, occupied))
    {
    }

    // The result is the number of occupied seats
    Logger::log("Number of occupied seats: " + std::to_string(occupied), INFO);
    result = occupied;
    return Ok;
}

bool Day11::applyRules(std::vector<std::vector<State>> &layout,
                       size_t &totalOccupied)
{
    const size_t ni = layout.size();
    const size_t nj = layout[0].size();
    bool hasChanged = false;
    totalOccupied = 0;
    std::vector<std::vector<State>> aux(ni, std::vector<State>(nj));
    for (size_t i = 0; i < ni; i++)
    {
        for (size_t j = 0; j < nj; j++)
        {
            // Count number of adjacent occupied
            size_t adjacentOccupied = countAdjacentOccupied(layout, i, j);

            // 1. If a seat is empty (L) and there are no occupied seats
            // adjacent to it, the seat becomes occupied.
            if (layout[i][j] == EMPTY && adjacentOccupied == 0)
            {
                aux[i][j] = OCCUPIED;
                hasChanged = true;
            }
            // 2. If a seat is occupied (#) and four or more seats adjacent to
            // it are also occupied, the seat becomes empty.
            else if (layout[i][j] == OCCUPIED && adjacentOccupied >= 4)
            {
                aux[i][j] = EMPTY;
                hasChanged = true;
            }
            // 3. Otherwise, the seat's state does not change.
            else
            {
                aux[i][j] = layout[i][j];
            }

            // After rules applied, update the occupied counter if needed
            if (aux[i][j] == OCCUPIED)
            {
                totalOccupied++;
            }
        }
    }

    // Copy the aux vector into the provided one and return
    std::copy(aux.cbegin(), aux.cend(), layout.begin());
    return hasChanged;
}

size_t Day11::countAdjacentOccupied(
    const std::vector<std::vector<State>> &layout, const int icenter,
    const int jcenter)
{
    size_t count = 0;
    const size_t numRows = layout.size(), numCols = layout[0].size();
    for (int i = icenter - 1; i < icenter + 2; i++)
    {
        for (int j = jcenter - 1; j < jcenter + 2; j++)
        {
            // Avoid checking in the center cell
            if (i == icenter && j == jcenter)
            {
                continue;
            }
            // Avoid checking if out of bounds
            if (!validIndex(i, numRows) || !validIndex(j, numCols))
            {
                continue;
            }
            // Count if occupied
            if (layout[i][j] == OCCUPIED)
            {
                count++;
            }
        }
    }

    return count;
}