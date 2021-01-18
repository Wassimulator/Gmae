#pragma once
#include "main.h"

struct surfaces
{
    SDL_Surface *PlayfieldSurface;
};
struct arm
{
    int ArmLength = 10;
    int OneArmUpX,
        OneArmUpY,
        OneArmDownX,
        OneArmDownY,
        OneArmLeftX,
        OneArmLeftY,
        OneArmRightX,
        OneArmRightY,
        TwoArmUpX,
        TwoArmUpY,
        TwoArmDownX,
        TwoArmDownY,
        TwoArmLeftX,
        TwoArmLeftY,
        TwoArmRightX,
        TwoArmRightY;
};
struct rects
{
    SDL_Rect PlayfieldRect;
    SDL_Rect PlayerOne, PlayerTwo;
    SDL_Rect Circle;
    arm Arms;
};
struct object
{
    float PosX, PosY;
    SDL_Surface* Surface;
    SDL_Texture *Texture;
};

object LoadObject(char *TextureFile)
{
    object Result;
    Result.Surface = IMG_Load(TextureFile);
    Result.Texture = SDL_CreateTextureFromSurface(Renderer, Result.Surface);
    return Result;
}
struct objects
{
    object Circle = LoadObject("data/textures/circle.png");
};

struct fonts
{
    TTF_Font *Regular, *RegularS, *Bold, *Bold2, *Title1B,
        *Title1, *Title2B, *Title2, *Title3B, *Title3, *MonospaceS;

    SDL_Surface *TextSurface;
};

fonts LoadFonts()
{
    fonts Result;
    Result.Regular = TTF_OpenFont("data/fonts/PTSans-Regular.ttf", 20);
    Result.RegularS = TTF_OpenFont("data/fonts/PTSans-Regular.ttf", 17);
    Result.Bold = TTF_OpenFont("data/fonts/PTSans-Bold.ttf", 20);
    Result.Bold2 = TTF_OpenFont("data/fonts/PTSans-Bold.ttf", 24);
    Result.Title1B = TTF_OpenFont("data/fonts/PTSans-Bold.ttf", 60);
    Result.Title1 = TTF_OpenFont("data/fonts/PTSans-Regular.ttf", 60);
    Result.Title2B = TTF_OpenFont("data/fonts/PTSans-Bold.ttf", 40);
    Result.Title2 = TTF_OpenFont("data/fonts/PTSans-Regular.ttf", 40);
    Result.Title3B = TTF_OpenFont("data/fonts/PTSans-Bold.ttf", 30);
    Result.Title3 = TTF_OpenFont("data/fonts/PTSans-Regular.ttf", 30);
    Result.MonospaceS = TTF_OpenFont("data/fonts/VeraMono.ttf", 17);

    return Result;
}

struct keys
{
    bool RightButton = false;
    bool LeftButton = false;
    bool UpButton = false;
    bool DownButton = false;
    bool W_Key = false;
    bool A_Key = false;
    bool S_Key = false;
    bool D_Key = false;
    bool Shift = false;
    bool F_Key = false;
    bool H_Key = false;
    bool E_Key = false;
    bool Tab_Key = false;
    bool Space_Key = false;
};
struct player
{
    float PosX, PosY;
};
struct players
{
    player One;
    player Two;
    float Speed;
};
struct playfield
{
    int limitX0, limitX1, limitY0, limitY1;
};

void CenterRectX(SDL_Rect *Rect)
{
    Rect->x = (WindowWidth - Rect->w) * 0.5f;
}
void CenterRectY(SDL_Rect *Rect)
{
    Rect->y = (WindowHeight - Rect->h) * 0.5f;
}
void CenterRectXY(SDL_Rect *Rect)
{
    Rect->x = (WindowWidth - Rect->w) * 0.5f;
    Rect->y = (WindowHeight - Rect->h) * 0.5f;
}

void PollEvents(SDL_Event *Event, keys *Keys)
{
    while (SDL_PollEvent(Event))
    {
        if (Event->type == SDL_QUIT)
        {
            Running = false;
        }
        if (Event->type == SDL_KEYDOWN || Event->type == SDL_KEYUP)
        {
            bool KeyState = Event->type == SDL_KEYDOWN ? true : false;

            switch (Event->key.keysym.sym)
            {
            case SDLK_UP:
                Keys->UpButton = KeyState;
                break;
            case SDLK_DOWN:
                Keys->DownButton = KeyState;
                break;
            case SDLK_LEFT:
                Keys->LeftButton = KeyState;
                break;
            case SDLK_RIGHT:
                Keys->RightButton = KeyState;
                break;
            case SDLK_LSHIFT:
                Keys->Shift = KeyState;
                break;
            case SDLK_RSHIFT:
                Keys->Shift = KeyState;
                break;
            case SDLK_h:
                Keys->H_Key = KeyState;
                break;
            case SDLK_w:
                Keys->W_Key = KeyState;
                break;
            case SDLK_a:
                Keys->A_Key = KeyState;
                break;
            case SDLK_s:
                Keys->S_Key = KeyState;
                break;
            case SDLK_d:
                Keys->D_Key = KeyState;
                break;
            default:
                break;
            }
        }
    }
}

void PlayerUpdate(rects *R, keys *K, players *P, playfield Playfield)
{
    P->Speed = 3;
    /*float dl = sqrtf(dx * dx + dy * dy);
    if (dl != 0)
    {
        dx = dx / dl;
        dy = dy / dl;
    }*/
    if (K->RightButton)
    {
        P->One.PosX += P->Speed;
    }
    if (K->LeftButton)
    {
        P->One.PosX -= P->Speed;
    }
    if (K->UpButton)
    {
        P->One.PosY -= P->Speed;
    }
    if (K->DownButton)
    {
        P->One.PosY += P->Speed;
    }

    if (P->One.PosX > R->PlayfieldRect.w / 2 - R->PlayerOne.w - 1 - R->Arms.ArmLength)
    {
        P->One.PosX = R->PlayfieldRect.w / 2 - R->PlayerOne.w - 1 - R->Arms.ArmLength;
    }
    if (P->One.PosX < -R->PlayfieldRect.w / 2 + 1 + R->Arms.ArmLength)
    {
        P->One.PosX = -R->PlayfieldRect.w / 2 + 1 + R->Arms.ArmLength;
    }
    if (P->One.PosY > R->PlayfieldRect.h / 2 - R->PlayerOne.h - 1 - R->Arms.ArmLength)
    {
        P->One.PosY = R->PlayfieldRect.h / 2 - R->PlayerOne.h - 1 - R->Arms.ArmLength;
    }
    if (P->One.PosY < -R->PlayfieldRect.h / 2 + 1 + R->Arms.ArmLength)
    {
        P->One.PosY = -R->PlayfieldRect.h / 2 + 1 + R->Arms.ArmLength;
    }

    if (K->D_Key)
    {
        P->Two.PosX += P->Speed;
    }
    if (K->A_Key)
    {
        P->Two.PosX -= P->Speed;
    }
    if (K->W_Key)
    {
        P->Two.PosY -= P->Speed;
    }
    if (K->S_Key)
    {
        P->Two.PosY += P->Speed;
    }

    if (P->Two.PosX > R->PlayfieldRect.w / 2 - R->PlayerTwo.w - 1 - R->Arms.ArmLength)
    {
        P->Two.PosX = R->PlayfieldRect.w / 2 - R->PlayerTwo.w - 1 - R->Arms.ArmLength;
    }
    if (P->Two.PosX < -R->PlayfieldRect.w / 2 + 1 + R->Arms.ArmLength)
    {
        P->Two.PosX = -R->PlayfieldRect.w / 2 + 1 + R->Arms.ArmLength;
    }
    if (P->Two.PosY > R->PlayfieldRect.h / 2 - R->PlayerTwo.h - 1 - R->Arms.ArmLength)
    {
        P->Two.PosY = R->PlayfieldRect.h / 2 - R->PlayerTwo.h - 1 - R->Arms.ArmLength;
    }
    if (P->Two.PosY < -R->PlayfieldRect.h / 2 + 1 + R->Arms.ArmLength)
    {
        P->Two.PosY = -R->PlayfieldRect.h / 2 + 1 + R->Arms.ArmLength;
    }
}

void RectsUpdate(rects *R, players *P)
{
    R->PlayerOne.x = WindowWidth * 0.5f + P->One.PosX;
    R->PlayerOne.y = WindowHeight * 0.5f + P->One.PosY;
    R->PlayerOne.x = WindowWidth * 0.5f + P->One.PosX;
    R->PlayerOne.y = WindowHeight * 0.5f + P->One.PosY;

    R->PlayerTwo.x = WindowWidth * 0.5f + P->Two.PosX;
    R->PlayerTwo.y = WindowHeight * 0.5f + P->Two.PosY;
    R->PlayerTwo.x = WindowWidth * 0.5f + P->Two.PosX;
    R->PlayerTwo.y = WindowHeight * 0.5f + P->Two.PosY;
}

void RenderText(TTF_Font *Font, char *text, Uint8 R, Uint8 G, Uint8 B,
                int PosX, int PosY, SDL_Surface *TextSurface, SDL_Surface *WindowSurface,
                int WindowWidth, int WindowHight)
{

    SDL_Color TextColor = {R, G, B};
    SDL_Surface *Surface = TTF_RenderText_Solid(Font, text, TextColor);
    SDL_Texture *Texture = SDL_CreateTextureFromSurface(Renderer, Surface);

    SDL_Rect TextRect1;
    TextRect1.h = Surface->h;
    TextRect1.w = Surface->w;
    TextRect1.x = PosX;
    TextRect1.y = PosY;
    //SDL_BlitSurface(TextSurface, 0, WindowSurface, &TextRect1);
    SDL_RenderCopy(Renderer, Texture, 0, &TextRect1);

    SDL_FreeSurface(Surface);
}
void SetArms(rects *R)
{
    R->Arms.OneArmUpX = R->PlayerOne.x + R->PlayerOne.w / 2,
    R->Arms.OneArmUpY = R->PlayerOne.y - R->Arms.ArmLength,
    R->Arms.OneArmDownX = R->PlayerOne.x + R->PlayerOne.w / 2,
    R->Arms.OneArmDownY = R->PlayerOne.y + R->PlayerOne.h + R->Arms.ArmLength,
    R->Arms.OneArmLeftX = R->PlayerOne.x - R->Arms.ArmLength,
    R->Arms.OneArmLeftY = R->PlayerOne.y + R->PlayerOne.h / 2,
    R->Arms.OneArmRightX = R->PlayerOne.x + R->PlayerOne.w + R->Arms.ArmLength,
    R->Arms.OneArmRightY = R->PlayerOne.y + R->PlayerOne.h / 2;
    R->Arms.TwoArmUpX = R->PlayerTwo.x + R->PlayerTwo.w / 2,
    R->Arms.TwoArmUpY = R->PlayerTwo.y - R->Arms.ArmLength,
    R->Arms.TwoArmDownX = R->PlayerTwo.x + R->PlayerTwo.w / 2,
    R->Arms.TwoArmDownY = R->PlayerTwo.y + R->PlayerTwo.h + R->Arms.ArmLength,
    R->Arms.TwoArmLeftX = R->PlayerTwo.x - R->Arms.ArmLength,
    R->Arms.TwoArmLeftY = R->PlayerTwo.y + R->PlayerTwo.h / 2,
    R->Arms.TwoArmRightX = R->PlayerTwo.x + R->PlayerTwo.w + R->Arms.ArmLength,
    R->Arms.TwoArmRightY = R->PlayerTwo.y + R->PlayerTwo.h / 2;
}