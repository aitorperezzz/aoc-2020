#include <vector>

#include "day11.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

// Checks if an index is valid for a certain size
bool validIndex(const size_t index, const size_t size)
{
    return index >= 0 && index <= (size - 1);
}

ErrorCode Day11::execute(const std::string &filename, unsigned int &result1,
                         unsigned int &result2)
{
    // Load input file.
    std::vector<std::string> auxLayout;
    if (FileOpener::loadVector(auxLayout, filename) != Ok)
    {
        Logger::log("Could not read values from file", ERROR);
        return InvalidFile;
    }

    // Transform the grid into enums, build 2 grids to solve both problems
    std::vector<std::vector<State>> layout1, layout2;
    layout1.resize(auxLayout.size());
    layout2.resize(auxLayout.size());
    for (size_t row = 0; row < auxLayout.size(); row++)
    {
        layout1[row].resize(auxLayout[row].length());
        layout2[row].resize(auxLayout[row].length());
        for (size_t i = 0; i < auxLayout[row].length(); i++)
        {
            if (auxLayout[row][i] == '.')
            {
                layout1[row][i] = FLOOR;
                layout2[row][i] = FLOOR;
            }
            else if (auxLayout[row][i] == 'L')
            {
                layout1[row][i] = EMPTY;
                layout2[row][i] = EMPTY;
            }
            else if (auxLayout[row][i] == '#')
            {
                layout1[row][i] = OCCUPIED;
                layout2[row][i] = OCCUPIED;
            }
            else
            {
                return ErrorCode::InvalidFile;
            }
        }
    }

    // Solve part 1
    size_t occupied1;
    while (applyRules(1, layout1, occupied1))
    {
    }
    Logger::log("Number of occupied seats in part one is: " +
                    std::to_string(occupied1),
                INFO);
    result1 = occupied1;

    // Solve part 2
    size_t occupied2;
    while (applyRules(2, layout2, occupied2))
    {
    }
    Logger::log("Number of occupied seats in part two is: " +
                    std::to_string(occupied2),
                INFO);
    result2 = occupied2;

    return Ok;
}

bool Day11::applyRules(const size_t part,
                       std::vector<std::vector<State>> &layout,
                       size_t &totalOccupied)
{
    const size_t ni = layout.size();
    const size_t nj = layout[0].size();
    bool hasChanged = false;
    totalOccupied = 0;
    std::vector<std::vector<State>> aux(ni, std::vector<State>(nj));
    const size_t occupiedThreshold = part == 1 ? 4 : 5;
    for (size_t i = 0; i < ni; i++)
    {
        for (size_t j = 0; j < nj; j++)
        {
            // Count number of adjacent occupied
            size_t occupied;
            if (part == 1)
            {
                occupied = countAdjacentOccupied(layout, i, j);
            }
            else
            {
                occupied = countLinedOccupied(layout, i, j);
            }

            // 1. If a seat is empty (L) and there are no occupied seats
            // adjacent to it, the seat becomes occupied.
            if (layout[i][j] == EMPTY && occupied == 0)
            {
                aux[i][j] = OCCUPIED;
                hasChanged = true;
            }
            // 2. If a seat is occupied (#) and four or more seats adjacent to
            // it are also occupied, the seat becomes empty.
            else if (layout[i][j] == OCCUPIED && occupied >= occupiedThreshold)
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

size_t Day11::countLinedOccupied(const std::vector<std::vector<State>> &layout,
                                 const int icenter, const int jcenter)
{
    size_t count = 0;
    const size_t numRows = layout.size(), numCols = layout[0].size();
    for (int i = icenter - 1; i < icenter + 2; i++)
    {
        for (int j = jcenter - 1; j < jcenter + 2; j++)
        {
            // Avoid checking the center cell
            if (i == icenter && j == jcenter)
            {
                continue;
            }
            // Avoid checking if out of bounds
            if (!validIndex(i, numRows) || !validIndex(j, numCols))
            {
                continue;
            }

            // Go through the line defined by the offsets
            int ioffset = i - icenter, joffset = j - jcenter;
            int iline = i, jline = j;
            while (true)
            {
                // Check the index is valid
                if (!validIndex(iline, numRows) || !validIndex(jline, numCols))
                {
                    break;
                }
                // If the seat is empty, break
                if (layout[iline][jline] == EMPTY)
                {
                    break;
                }
                // If the seat is occupied, count it and break
                if (layout[iline][jline] == OCCUPIED)
                {
                    count++;
                    break;
                }
                iline += ioffset;
                jline += joffset;
            }
        }
    }

    return count;
}