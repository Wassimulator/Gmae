#include "main.h"
#include "source.cpp"

void Render(objects *O, rects *R)
{
    SDL_SetRenderDrawColor(Renderer, 25, 25, 25, 255);
    SDL_RenderFillRect(Renderer, &R->PlayfieldRect);
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, &R->PlayfieldRect);

    SDL_RenderCopy(Renderer, O->Circle.Texture, 0, &R->Circle);

    SDL_SetRenderDrawColor(Renderer, 255, 25, 25, 255);
    SDL_RenderFillRect(Renderer, &R->PlayerOne);
    SDL_RenderDrawLine(Renderer, R->Arms.OneHX1, R->Arms.OneHY1, R->Arms.OneHX2, R->Arms.OneHY2);
    SDL_RenderDrawLine(Renderer, R->Arms.OneVX1, R->Arms.OneVY1, R->Arms.OneVX2, R->Arms.OneVY2);

    SDL_SetRenderDrawColor(Renderer, 25, 25, 255, 255);
    SDL_RenderFillRect(Renderer, &R->PlayerTwo);
    SDL_RenderDrawLine(Renderer, R->Arms.TwoHX1, R->Arms.TwoHY1, R->Arms.TwoHX2, R->Arms.TwoHY2);
    SDL_RenderDrawLine(Renderer, R->Arms.TwoVX1, R->Arms.TwoVY1, R->Arms.TwoVX2, R->Arms.TwoVY2);

    for (int i = 0; i < 4; i++)
    {
        SDL_RenderCopy(Renderer, O->OneHand[i].Texture, 0, &R->OneHand[i]);
        SDL_RenderCopy(Renderer, O->TwoHand[i].Texture, 0, &R->TwoHand[i]);
    }
}

void RenderDebugInfo(players *P, fonts *Fonts)
{
    char DebugPlayerOneXY[30];
    sprintf(DebugPlayerOneXY, "Player One: %i, %i", (int16_t)P->One.PosX, (int16_t)P->One.PosY);
    RenderText(Fonts->MonospaceS, DebugPlayerOneXY, 170, 170, 170, 5, 0, Fonts->TextSurface,
               WindowSurface, WindowWidth, WindowHeight);
    char DebugPlayerTwoXY[30];
    sprintf(DebugPlayerTwoXY, "Player Two: %i, %i", (int16_t)P->Two.PosX, (int16_t)P->Two.PosY);
    RenderText(Fonts->MonospaceS, DebugPlayerTwoXY, 170, 170, 170, 5, 17 * 1, Fonts->TextSurface,
               WindowSurface, WindowWidth, WindowHeight);
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

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    int ResolutionMultiplier = 60;
    WindowWidth = 16 * ResolutionMultiplier;
    WindowHeight = 9 * ResolutionMultiplier;

    Window = SDL_CreateWindow("Gmae", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight, 0);
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(Renderer, 70, 70, 70, 255);
    SDL_RenderClear(Renderer);

    surfaces S;
    rects R;
    keys Keys;
    fonts Fonts = LoadFonts();
    players P;
    playfield Playfield;
    objects O;
    for (int i = 0; i < 4; i++)
    {
        O.OneHand[i] = LoadObject("data/textures/circle_red.png");
        O.TwoHand[i] = LoadObject("data/textures/circle_blue.png");
    }

    InitilizeRects(&R);

    P.One.PosX = 100;
    P.One.PosY = 0;
    P.Two.PosX = -100;
    P.Two.PosY = 0;

    Playfield.limitX0 = WindowWidth / 2 - R.PlayfieldRect.w / 2;
    Playfield.limitX1 = WindowWidth / 2 + R.PlayfieldRect.w / 2;
    Playfield.limitY0 = WindowHeight / 2 - R.PlayfieldRect.h / 2;
    Playfield.limitY1 = WindowHeight / 2 + R.PlayfieldRect.h / 2;

    SDL_Event Event;
    while (Running)
    {
        Keys.Space_Key = false;
        Keys.Tab_Key = false;

        const int FPS = 60;
        const int frameDelay = 1000 / FPS;
        Uint32 frameStart = SDL_GetTicks();

        PollEvents(&Event, &Keys);

        PlayerUpdate(&R, &Keys, &P, Playfield);
        ObjectsUpdate(&O, &P, &R, &Keys);
        SetArms(&R);
        Render(&O, &R);

        int frameEnd = SDL_GetTicks();
        int frameTime = frameEnd - frameStart;
        if (frameTime < frameDelay)
        {
            SDL_Delay(frameDelay - frameTime);
        }
        RenderDebugInfo(&P, &Fonts);
        SDL_RenderPresent(Renderer);
        SDL_SetRenderDrawColor(Renderer, 70, 70, 70, 255);
        SDL_RenderClear(Renderer);
    }

    return 0;
}