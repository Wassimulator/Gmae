#include "main.h"
#include "source.cpp"

void Render(objects *O, rects *R)
{
    SDL_SetRenderDrawColor(Renderer, 25, 25, 25, 255);
    SDL_RenderFillRect(Renderer, &R->PlayfieldRect);
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Renderer, &R->PlayfieldRect);

    SDL_RenderCopy(Renderer, O->Circle.Texture, 0, &R->Circle);

    SetArms(R);

    SDL_SetRenderDrawColor(Renderer, 255, 25, 25, 255);
    SDL_RenderFillRect(Renderer, &R->PlayerOne);
    SDL_RenderDrawLine(Renderer, R->Arms.OneArmLeftX, R->Arms.OneArmLeftY, R->Arms.OneArmRightX, R->Arms.OneArmRightY);
    SDL_RenderDrawLine(Renderer, R->Arms.OneArmUpX, R->Arms.OneArmUpY, R->Arms.OneArmDownX, R->Arms.OneArmDownY);

    SDL_SetRenderDrawColor(Renderer, 25, 25, 255, 255);
    SDL_RenderFillRect(Renderer, &R->PlayerTwo);
    SDL_RenderDrawLine(Renderer, R->Arms.TwoArmLeftX, R->Arms.TwoArmLeftY, R->Arms.TwoArmRightX, R->Arms.TwoArmRightY);
    SDL_RenderDrawLine(Renderer, R->Arms.TwoArmUpX, R->Arms.TwoArmUpY, R->Arms.TwoArmDownX, R->Arms.TwoArmDownY);
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

    R->Circle.h = 15;
    R->Circle.w = 15;

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
        const int FPS = 60;
        const int frameDelay = 1000 / FPS;
        Uint32 frameStart = SDL_GetTicks();

        PollEvents(&Event, &Keys);

        PlayerUpdate(&R, &Keys, &P, Playfield);
        RectsUpdate(&R, &P);

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