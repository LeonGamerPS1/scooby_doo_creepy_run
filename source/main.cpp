#include <citro2d.h>
#include <cstdio>

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

int main(int argc, char* argv[])
{
    gfxInitDefault();

    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    consoleInit(GFX_BOTTOM, nullptr);

    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

    u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
    u32 clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
    u32 clrRed   = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
    u32 clrBlue  = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);

    float x = 25.0f;
    float speed = 2.0f;

    while (aptMainLoop())
    {
        hidScanInput();

        if (hidKeysDown() & KEY_START)
            break;

        printf("\x1b[1;1HSimple citro2d C++ example");
        printf("\x1b[2;1HX: %.2f", x);

        x += speed;

        if (x > SCREEN_WIDTH - 25 || x < 25)
            speed = -speed;

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

        C2D_TargetClear(top, clrWhite);
        C2D_SceneBegin(top);

        C2D_DrawCircle(
            x,
            25,
            0,
            25,
            clrRed,
            clrBlue,
            clrGreen,
            clrWhite
        );

        C3D_FrameEnd(0);
    }

    C2D_Fini();
    C3D_Fini();
    gfxExit();

    return 0;
}