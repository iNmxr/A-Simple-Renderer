#pragma once
#include "Mathlib.h"
#include "WindowProcess.h"
#include <fstream>
#include <string>
#include <sstream>

void getvertex(std::string& s, vertex_position& v);

void getsurfaceidx(std::string& s, Indexbuffer& dx);

void Loader();