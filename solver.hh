#pragma once

#include <random>

#include "tetravex.hh"

class Solver
{
public:
    Solver(const Tetravex &tetravex);
    Solver(const Solver &) = default;

    void solve();

private:
    const Tetravex &tetravex;
};