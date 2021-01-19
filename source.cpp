#pragma once
#include "main.h"

struct surfaces
{
    SDL_Surface *PlayfieldSurface;
};
struct arm
{
    int ArmLength = 10;
    int OneVX1,
        OneVY1,
        OneVX2,
        OneVY2,
        OneHX1,
        OneHY1,
        OneHX2,
        OneHY2,
        TwoVX1,
        TwoVY1,
        TwoVX2,
        TwoVY2,
        TwoHX1,
        TwoHY1,
        TwoHX2,
        TwoHY2;
};
struct rects
{
    SDL_Rect PlayfieldRect;
    SDL_Rect PlayerOne, PlayerTwo;
    SDL_Rect Circle;
    SDL_Rect OneHand[4], TwoHand[4];
    arm Arms;
};
enum num
{
    One,
    Two,
    None
};
struct object
{
    int PosX, PosY;
    int OriginalW, OriginalH;
    SDL_Surface *Surface;
    SDL_Texture *Texture;
    bool ClickableOne, ClickableTwo;
    num AttachedTo = None;
    int By;
    int dx, dy;
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
    object OneHand[4], TwoHand[4];
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
    int PosX, PosY;
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
        if (Event->type == SDL_KEYDOWN)
        {
            if (Event->key.keysym.sym == SDLK_SPACE && Event->key.repeat == false)
            {
                Keys->Space_Key = true;
            }
            if (Event->key.keysym.sym == SDLK_TAB && Event->key.repeat == false)
            {
                Keys->Tab_Key = true;
            }
        }
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

    R->PlayerOne.x = WindowWidth * 0.5f + P->One.PosX;
    R->PlayerOne.y = WindowHeight * 0.5f + P->One.PosY;
    R->PlayerTwo.x = WindowWidth * 0.5f + P->Two.PosX;
    R->PlayerTwo.y = WindowHeight * 0.5f + P->Two.PosY;
}

void ObjectsUpdate(objects *O, players *P, rects *R, keys *K)
{
    bool Past = false;
    int By;

    O->Circle.PosX = R->Circle.x + R->Circle.w / 2 - WindowWidth / 2;
    O->Circle.PosY = R->Circle.y + R->Circle.h / 2 - WindowHeight / 2;
    O->Circle.OriginalW = 16;
    O->Circle.OriginalH = 16;

    R->Circle.w = O->Circle.OriginalW + 0.1f * O->Circle.PosX;
    R->Circle.h = O->Circle.OriginalH + 0.1f * O->Circle.PosX;
    if (R->Circle.h < 3)
    {
        R->Circle.h = 3;
    }
    if (R->Circle.w < 3)
    {
        R->Circle.w = 3;
    }

    if (O->Circle.AttachedTo == One)
    {
        Past = true;
    }
    if (O->Circle.AttachedTo == Two)
    {
        Past = true;
    }

    for (int i = 0; i < 4; i++)
    {
        if (SDL_HasIntersection(&R->OneHand[i], &R->Circle) == SDL_TRUE)
        {
            O->Circle.ClickableOne = true;
            By = i;
            break;
        }
        if (SDL_HasIntersection(&R->OneHand[i], &R->Circle) == SDL_FALSE)
        {
            O->Circle.ClickableOne = false;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (SDL_HasIntersection(&R->TwoHand[i], &R->Circle) == SDL_TRUE)
        {
            O->Circle.ClickableTwo = true;
            By = i;
            break;
        }
        if (SDL_HasIntersection(&R->TwoHand[i], &R->Circle) == SDL_FALSE)
        {
            O->Circle.ClickableTwo = false;
        }
    }
    cout << O->Circle.By << endl;

    if (O->Circle.ClickableOne && K->Space_Key && O->Circle.AttachedTo == None)
    {
        O->Circle.AttachedTo = One;
        O->Circle.dx = R->Circle.x - R->PlayerOne.x;
        O->Circle.dy = R->Circle.y - R->PlayerOne.y;
        O->Circle.By = By;
    }
    if (O->Circle.ClickableTwo && K->Tab_Key && O->Circle.AttachedTo == None)
    {
        O->Circle.AttachedTo = Two;
        O->Circle.dx = R->Circle.x - R->PlayerTwo.x;
        O->Circle.dy = R->Circle.y - R->PlayerTwo.y;
        O->Circle.By = By;
    }

    if (O->Circle.AttachedTo == One)
    {
        /*R->Circle.x = R->PlayerOne.x + O->Circle.dx;
        R->Circle.y = R->PlayerOne.y + O->Circle.dy;*/
        // this one attaches to the point it touches instead of centering on the arm tip

        if (O->Circle.By == 0)
        {
            R->Circle.x = R->Arms.OneHX1 - R->Circle.w / 2;
            R->Circle.y = R->Arms.OneHY1 - R->Circle.h / 2;
        }
        if (O->Circle.By == 1)
        {
            R->Circle.x = R->Arms.OneVX1 - R->Circle.w / 2;
            R->Circle.y = R->Arms.OneVY1 - R->Circle.h / 2;
        }
        if (O->Circle.By == 2)
        {
            R->Circle.x = R->Arms.OneHX2 - R->Circle.w / 2;
            R->Circle.y = R->Arms.OneHY2 - R->Circle.h / 2;
        }
        if (O->Circle.By == 3)
        {
            R->Circle.x = R->Arms.OneVX2 - R->Circle.w / 2;
            R->Circle.y = R->Arms.OneVY2 - R->Circle.h / 2;
        }
    }
    if (O->Circle.AttachedTo == Two)
    {
        if (O->Circle.By == 0)
        {
            R->Circle.x = R->Arms.TwoHX1 - R->Circle.w / 2;
            R->Circle.y = R->Arms.TwoHY1 - R->Circle.h / 2;
        }
        if (O->Circle.By == 1)
        {
            R->Circle.x = R->Arms.TwoVX1 - R->Circle.w / 2;
            R->Circle.y = R->Arms.TwoVY1 - R->Circle.h / 2;
        }
        if (O->Circle.By == 2)
        {
            R->Circle.x = R->Arms.TwoHX2 - R->Circle.w / 2;
            R->Circle.y = R->Arms.TwoHY2 - R->Circle.h / 2;
        }
        if (O->Circle.By == 3)
        {
            R->Circle.x = R->Arms.TwoVX2 - R->Circle.w / 2;
            R->Circle.y = R->Arms.TwoVY2 - R->Circle.h / 2;
        }
    }

    if (Past && O->Circle.AttachedTo == One && K->Space_Key)
    {
        O->Circle.AttachedTo = None;
    }
    if (Past && O->Circle.AttachedTo == Two && K->Tab_Key)
    {
        O->Circle.AttachedTo = None;
    }
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
    R->Arms.OneVX1 = R->PlayerOne.x + R->PlayerOne.w / 2,
    R->Arms.OneVY1 = R->PlayerOne.y - R->Arms.ArmLength,
    R->Arms.OneVX2 = R->PlayerOne.x + R->PlayerOne.w / 2,
    R->Arms.OneVY2 = R->PlayerOne.y + R->PlayerOne.h + R->Arms.ArmLength,
    R->Arms.OneHX1 = R->PlayerOne.x - R->Arms.ArmLength,
    R->Arms.OneHY1 = R->PlayerOne.y + R->PlayerOne.h / 2,
    R->Arms.OneHX2 = R->PlayerOne.x + R->PlayerOne.w + R->Arms.ArmLength,
    R->Arms.OneHY2 = R->PlayerOne.y + R->PlayerOne.h / 2;
    R->Arms.TwoVX1 = R->PlayerTwo.x + R->PlayerTwo.w / 2,
    R->Arms.TwoVY1 = R->PlayerTwo.y - R->Arms.ArmLength,
    R->Arms.TwoVX2 = R->PlayerTwo.x + R->PlayerTwo.w / 2,
    R->Arms.TwoVY2 = R->PlayerTwo.y + R->PlayerTwo.h + R->Arms.ArmLength,
    R->Arms.TwoHX1 = R->PlayerTwo.x - R->Arms.ArmLength,
    R->Arms.TwoHY1 = R->PlayerTwo.y + R->PlayerTwo.h / 2,
    R->Arms.TwoHX2 = R->PlayerTwo.x + R->PlayerTwo.w + R->Arms.ArmLength,
    R->Arms.TwoHY2 = R->PlayerTwo.y + R->PlayerTwo.h / 2;

    R->OneHand[0].x = R->Arms.OneHX1 - R->OneHand[0].w / 2;
    R->OneHand[1].x = R->Arms.OneVX1 - R->OneHand[1].w / 2;
    R->OneHand[2].x = R->Arms.OneHX2 - R->OneHand[2].w / 2;
    R->OneHand[3].x = R->Arms.OneVX2 - R->OneHand[3].w / 2;

    R->OneHand[0].y = R->Arms.OneHY1 - R->OneHand[0].h / 2;
    R->OneHand[1].y = R->Arms.OneVY1 - R->OneHand[1].h / 2;
    R->OneHand[2].y = R->Arms.OneHY2 - R->OneHand[2].h / 2;
    R->OneHand[3].y = R->Arms.OneVY2 - R->OneHand[3].h / 2;

    R->TwoHand[0].x = R->Arms.TwoHX1 - R->TwoHand[0].w / 2;
    R->TwoHand[1].x = R->Arms.TwoVX1 - R->TwoHand[1].w / 2;
    R->TwoHand[2].x = R->Arms.TwoHX2 - R->TwoHand[2].w / 2;
    R->TwoHand[3].x = R->Arms.TwoVX2 - R->TwoHand[3].w / 2;

    R->TwoHand[0].y = R->Arms.TwoHY1 - R->TwoHand[0].h / 2;
    R->TwoHand[1].y = R->Arms.TwoVY1 - R->TwoHand[1].h / 2;
    R->TwoHand[2].y = R->Arms.TwoHY2 - R->TwoHand[2].h / 2;
    R->TwoHand[3].y = R->Arms.TwoVY2 - R->TwoHand[3].h / 2;
}

void InitilizeRects(rects *R)
{
    R->PlayfieldRect.h = R->PlayfieldRect.w = 400;
    R->PlayerOne.h = R->PlayerOne.w = R->PlayerTwo.h = R->PlayerTwo.w = 20;
    R->Arms.ArmLength = 20;

    R->Circle.h = 16;
    R->Circle.w = 16;

    for (int i = 0; i < 4; i++)
    {
        R->OneHand[i].h = R->OneHand[i].w = R->TwoHand[i].h = R->TwoHand[i].w = 10;
    }

    R->OneHand[0].x = R->Arms.OneHX1 - R->OneHand[0].w / 2;
    R->OneHand[1].x = R->Arms.OneVX1 - R->OneHand[1].w / 2;
    R->OneHand[2].x = R->Arms.OneHX2 - R->OneHand[2].w / 2;
    R->OneHand[3].x = R->Arms.OneVX2 - R->OneHand[3].w / 2;

    R->OneHand[0].y = R->Arms.OneHY1 - R->OneHand[0].h / 2;
    R->OneHand[1].y = R->Arms.OneVY1 - R->OneHand[1].h / 2;
    R->OneHand[2].y = R->Arms.OneHY2 - R->OneHand[2].h / 2;
    R->OneHand[3].y = R->Arms.OneVY2 - R->OneHand[3].h / 2;

    R->TwoHand[0].x = R->Arms.TwoHX1 - R->TwoHand[0].w / 2;
    R->TwoHand[1].x = R->Arms.TwoVX1 - R->TwoHand[1].w / 2;
    R->TwoHand[2].x = R->Arms.TwoHX2 - R->TwoHand[2].w / 2;
    R->TwoHand[3].x = R->Arms.TwoVX2 - R->TwoHand[3].w / 2;

    R->TwoHand[0].y = R->Arms.TwoHY1 - R->TwoHand[0].h / 2;
    R->TwoHand[1].y = R->Arms.TwoVY1 - R->TwoHand[1].h / 2;
    R->TwoHand[2].y = R->Arms.TwoHY2 - R->TwoHand[2].h / 2;
    R->TwoHand[3].y = R->Arms.TwoVY2 - R->TwoHand[3].h / 2;

    CenterRectXY(&R->PlayfieldRect);
    CenterRectXY(&R->PlayerOne);
    CenterRectXY(&R->PlayerTwo);
    CenterRectXY(&R->Circle);
}