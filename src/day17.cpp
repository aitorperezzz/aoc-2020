#include <iostream>
#include <map>
#include <numeric>

#include "day17.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

namespace day17
{

struct Coords3D
{
    Coords3D(const int inX, const int inY, const int inZ)
    {
        x = inX;
        y = inY;
        z = inZ;
    }

    int x;
    int y;
    int z;
};

struct Coords4D
{
    Coords4D(const int inx, const int iny, const int inz, const int inw)
    {
        x = inx;
        y = iny;
        z = inz;
        w = inw;
    }

    int x;
    int y;
    int z;
    int w;
};

struct Boundary
{
    int min;
    int max;
};

struct Boundaries3D
{
    Boundary x;
    Boundary y;
    Boundary z;
};

struct Boundaries4D
{
    Boundary x;
    Boundary y;
    Boundary z;
    Boundary w;
};

std::vector<Coords3D> performIteration3D(const std::vector<Coords3D> &original,
                                         Boundaries3D &boundaries)
{
    std::vector<Coords3D> result;
    for (int x = boundaries.x.min - 1; x <= boundaries.x.max + 1; x++)
    {
        for (int y = boundaries.y.min - 1; y <= boundaries.y.max + 1; y++)
        {
            for (int z = boundaries.z.min - 1; z <= boundaries.z.max + 1; z++)
            {
                // Go through the neighbors of the current cube and count the
                // active ones. In parallel, try to find myself
                int active = 0;
                bool myselfActive = false;
                for (const auto &coord : original)
                {
                    // Check if this cube is me
                    if (coord.x == x && coord.y == y && coord.z == z)
                    {
                        // I am active, and no need to continue checking
                        myselfActive = true;
                        continue;
                    }

                    const bool xneighbor = x - 1 <= coord.x && coord.x <= x + 1;
                    const bool yneighbor = y - 1 <= coord.y && coord.y <= y + 1;
                    const bool zneighbor = z - 1 <= coord.z && coord.z <= z + 1;
                    if (xneighbor && yneighbor && zneighbor)
                    {
                        // There is an active neighbor, so add 1 to the number
                        // of active neighbors
                        active++;
                    }
                }

                // Decide depending on the number of active neighbors
                if (myselfActive)
                {
                    if (active == 2 || active == 3)
                    {
                        // I remain active in the next iteration
                        result.push_back(Coords3D(x, y, z));
                    }
                }
                else
                {
                    if (active == 3)
                    {
                        result.push_back(Coords3D(x, y, z));
                    }
                }
            }
        }
    }

    // Update boundaries
    boundaries.x.min--;
    boundaries.y.min--;
    boundaries.z.min--;
    boundaries.x.max++;
    boundaries.y.max++;
    boundaries.z.max++;

    return result;
}

int solve3DProblem(const std::vector<std::string> &input)
{
    // Parse the input lines
    std::vector<Coords3D> activeCubes;
    for (size_t line = 0; line < input.size(); line++)
    {
        for (size_t i = 0; i < input[line].length(); i++)
        {
            if (input[line][i] == '#')
            {
                // The cube is active
                activeCubes.push_back(Coords3D(line, i, 0));
            }
        }
    }

    // Set the initial conditions, which reflect the boundaries
    Boundaries3D boundaries;
    boundaries.x.min = 0;
    boundaries.x.max = static_cast<int>(input.size()) - 1;
    boundaries.y.min = 0;
    boundaries.y.max = static_cast<int>(input[0].length()) - 1;
    boundaries.z.min = 0;
    boundaries.z.max = 0;

    // Iterate while requested
    const size_t numIterations = 6;
    size_t currentIteration = 0;
    while (currentIteration < numIterations)
    {
        activeCubes = performIteration3D(activeCubes, boundaries);
        currentIteration++;
    }

    Logger::log("Number of active cubes (3D): " +
                    std::to_string(activeCubes.size()),
                INFO);
    return static_cast<int>(activeCubes.size());
}

std::vector<Coords4D> performIteration4D(const std::vector<Coords4D> &original,
                                         Boundaries4D &boundaries)
{
    std::vector<Coords4D> result;
    for (int x = boundaries.x.min - 1; x <= boundaries.x.max + 1; x++)
    {
        for (int y = boundaries.y.min - 1; y <= boundaries.y.max + 1; y++)
        {
            for (int z = boundaries.z.min - 1; z <= boundaries.z.max + 1; z++)
            {
                for (int w = boundaries.w.min - 1; w <= boundaries.w.max + 1;
                     w++)
                {
                    // Go through the neighbors of the current cube and count
                    // the active ones. In parallel, try to find myself
                    int active = 0;
                    bool myselfActive = false;
                    for (const auto &coord : original)
                    {
                        // Check if this cube is me
                        if (coord.x == x && coord.y == y && coord.z == z &&
                            coord.w == w)
                        {
                            // I am active, and no need to continue checking
                            myselfActive = true;
                            continue;
                        }

                        const bool xneighbor =
                            x - 1 <= coord.x && coord.x <= x + 1;
                        const bool yneighbor =
                            y - 1 <= coord.y && coord.y <= y + 1;
                        const bool zneighbor =
                            z - 1 <= coord.z && coord.z <= z + 1;
                        const bool wneighbor =
                            w - 1 <= coord.w && coord.w <= w + 1;
                        if (xneighbor && yneighbor && zneighbor && wneighbor)
                        {
                            // There is an active neighbor, so add 1 to the
                            // number of active neighbors
                            active++;
                        }
                    }

                    // Decide depending on the number of active neighbors
                    if (myselfActive)
                    {
                        if (active == 2 || active == 3)
                        {
                            // I remain active in the next iteration
                            result.push_back(Coords4D(x, y, z, w));
                        }
                    }
                    else
                    {
                        if (active == 3)
                        {
                            result.push_back(Coords4D(x, y, z, w));
                        }
                    }
                }
            }
        }
    }

    // Update boundaries
    boundaries.x.min--;
    boundaries.y.min--;
    boundaries.z.min--;
    boundaries.w.min--;
    boundaries.x.max++;
    boundaries.y.max++;
    boundaries.z.max++;
    boundaries.w.max++;

    return result;
}

int solve4DProblem(const std::vector<std::string> &input)
{
    // Parse the input lines
    std::vector<Coords4D> activeCubes;
    for (size_t line = 0; line < input.size(); line++)
    {
        for (size_t i = 0; i < input[line].length(); i++)
        {
            if (input[line][i] == '#')
            {
                // The cube is active
                activeCubes.push_back(Coords4D(line, i, 0, 0));
            }
        }
    }

    // Set the initial conditions, which reflect the boundaries
    Boundaries4D boundaries;
    boundaries.x.min = 0;
    boundaries.x.max = static_cast<int>(input.size()) - 1;
    boundaries.y.min = 0;
    boundaries.y.max = static_cast<int>(input[0].length()) - 1;
    boundaries.z.min = 0;
    boundaries.z.max = 0;
    boundaries.w.min = 0;
    boundaries.w.max = 0;

    // Iterate while requested
    const size_t numIterations = 6;
    size_t currentIteration = 0;
    while (currentIteration < numIterations)
    {
        activeCubes = performIteration4D(activeCubes, boundaries);
        currentIteration++;
    }

    Logger::log("Number of active cubes (4D): " +
                    std::to_string(activeCubes.size()),
                INFO);
    return static_cast<int>(activeCubes.size());
}

ErrorCode execute(const std::string &filename, int &result1, int &result2)
{
    // Load input
    std::vector<std::string> input;
    if (FileOpener::loadVector(input, filename) != Ok)
    {
        Logger::log("Could not read values from file", ERROR);
        throw std::invalid_argument("");
    }

    // Solve 3d problem
    result1 = solve3DProblem(input);

    // Solve 4d problem
    result2 = solve4DProblem(input);

    return ErrorCode::Ok;
}
} // namespace day17