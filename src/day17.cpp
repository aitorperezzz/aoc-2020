#include <iostream>
#include <map>
#include <numeric>

#include "day17.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

namespace day17
{

struct Boundary
{
    int min;
    int max;
};

template <size_t n> using Coordinates = std::array<int, n>;
template <size_t n> using Boundaries = std::array<Boundary, n>;

// Update to the next coordinate value within the provided boundaries.
// Return true if the boundaries have not been reached
template <size_t n>
bool updateCoordinates(const Boundaries<n> &boundaries,
                       Coordinates<n> &coordinates)
{
    // Find the dimension that still has not reached the max value
    int dimension = n - 1;
    while (coordinates[dimension] == boundaries[dimension].max + 1 &&
           dimension >= 0)
    {
        dimension--;
    }

    // If the dimension that has not reached the max value is in the middle,
    // update it and bring the rest of dimensions to the right to the min value
    // allowed by the boundaries
    bool result = false;
    if (dimension >= 0)
    {
        coordinates[dimension]++;
        for (size_t nextDimension = dimension + 1; nextDimension < n;
             nextDimension++)
        {
            coordinates[nextDimension] = boundaries[dimension].min - 1;
        }
        result = true;
    }

    return result;
}

// Provide the minimal coordinates inside the boundaries
template <size_t n>
Coordinates<n> getFirstCoordinates(const Boundaries<n> &boundaries)
{
    Coordinates<n> coordinates;
    for (size_t i = 0; i < n; i++)
    {
        coordinates[i] = boundaries[i].min - 1;
    }
    return coordinates;
}

// Provided a 2 dimensional initial shape, set initial boundaries
template <size_t n>
Boundaries<n> setInitialBoundaries(const std::array<size_t, 2> &shape2d)
{
    Boundaries<n> boundaries;
    for (size_t i = 0; i < n; i++)
    {
        boundaries[i].min = 0;
        boundaries[i].max = 0;
        if (i == 0 || i == 1)
        {
            boundaries[i].max = shape2d[i] - 1;
        }
    }
    return boundaries;
}

// Perform one iteration of the conway algorithm. The algorithm updates the
// boundaries for the next iteration
template <size_t n>
std::vector<Coordinates<n>> performIteration(
    const std::vector<Coordinates<n>> &activeCubes, Boundaries<n> &boundaries)
{
    std::vector<Coordinates<n>> result;

    // Get the first coordinates (minimal values allowed)
    auto coordinates = getFirstCoordinates(boundaries);
    int active;
    bool myselfActive;
    bool equal, neighbors;
    do
    {
        active = 0; // number of active cubes around the current coordinate
        myselfActive = false; // if this coordinate is an active cube

        // Loop over all the active cubes
        for (const auto &cube : activeCubes)
        {
            equal = true;
            neighbors = true;
            for (size_t i = 0; i < n; i++)
            {
                equal = equal && cube[i] == coordinates[i];
                neighbors = neighbors && coordinates[i] - 1 <= cube[i] &&
                            cube[i] <= coordinates[i] + 1;
            }
            if (equal)
            {
                myselfActive = true;
                continue;
            }
            if (neighbors)
            {
                active++;
            }
        }

        // If I am active and have 2 or 3 active neighbors, I remain active
        if (myselfActive)
        {
            if (active == 2 || active == 3)
            {
                result.push_back(coordinates);
            }
        }
        // If I am not active but have 3 active neighbors, I become active
        else
        {
            if (active == 3)
            {
                result.push_back(coordinates);
            }
        }

    } while (updateCoordinates(boundaries, coordinates));

    // Update boundaries for the next iteration
    for (size_t i = 0; i < n; i++)
    {
        boundaries[i].min--;
        boundaries[i].max++;
    }

    return result;
}

// Solve the problem, for a specific dimension, provided an initial input
template <size_t n> size_t solveProblem(const std::vector<std::string> &input)
{
    // Parse the input lines
    std::vector<Coordinates<n>> activeCubes;
    for (size_t line = 0; line < input.size(); line++)
    {
        for (size_t i = 0; i < input[line].length(); i++)
        {
            if (input[line][i] == '#')
            {
                // The cube is active
                activeCubes.push_back(Coordinates<n>(
                    {static_cast<int>(line), static_cast<int>(i)}));
            }
        }
    }

    // Create the boundaries according to the size of the input
    Boundaries<n> boundaries =
        setInitialBoundaries<n>({input.size(), input[0].length()});

    // Iterate while requested
    const size_t numIterations = 6;
    size_t currentIteration = 0;
    while (currentIteration < numIterations)
    {
        activeCubes = performIteration(activeCubes, boundaries);
        currentIteration++;
    }

    Logger::log("Number of active cubes after 6 iterations (" +
                    std::to_string(n) +
                    "D): " + std::to_string(activeCubes.size()),
                INFO);
    return activeCubes.size();
}

ErrorCode execute(const std::string &filename, size_t &result1, size_t &result2)
{
    // Load input
    std::vector<std::string> input;
    if (FileOpener::loadVector(input, filename) != Ok)
    {
        Logger::log("Could not read values from file", ERROR);
        throw std::invalid_argument("");
    }

    // Solve 3d problem
    result1 = solveProblem<3>(input);

    // Solve 4d problem
    result2 = solveProblem<4>(input);

    return ErrorCode::Ok;
}
} // namespace day17