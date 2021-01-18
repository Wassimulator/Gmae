#pragma once
#include <stdio.h>
#include <SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <fstream>
#include <string>
#include <lexer.h>
#include <iostream>
#include <SDL_image.h>
#include <cstdlib>

using namespace std;


SDL_Surface *WindowSurface;
SDL_Window *Window;
SDL_Renderer *Renderer;
int WindowWidth;
int WindowHeight;
bool Running = true;
