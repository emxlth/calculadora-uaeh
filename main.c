#include "raylib.h"
#include "estado.h"
#include <stdio.h>

int main(void)
{
    // inicialización de la ventana

    const int screenWidth = 1000;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "Calculadora UAEH");
    SetTargetFPS(60);
    SetExitKey(0);

    // structs

    Estado e = {0, 0, -1};

    Datos d = {0};

    Inputs inp = {0};
    inp.num_campos [0] = 3;
    inp.num_campos [1] = 3;
    inp.num_campos [2] = 3;
    
    Inputs2 inp2 = {0};
    inp2.parciales_llevados = 1;

    Recursos r;
    r.fuente = LoadFont("resources/times.ttf");
    r.imagenrei = LoadTexture("resources/rei.png");
    r.imagenshinji = LoadTexture("resources/shinji.png");
    r.gatobaboso = LoadTexture("resources/gatobaboso.png");
    r.machete = LoadTexture("resources/machete.png");
    r.perrorayos = LoadTexture("resources/perrorayos.png");
    r.perrocerebro = LoadTexture("resources/perrocerebro.png");
    r.gatoper = LoadTexture("resources/gatoper.png");

    // loop principal

    while (!WindowShouldClose())
    {
        update(&e, &d, &inp);
        update2(&e, &d, &inp2);
        BeginDrawing();
        ClearBackground((Color){200, 220, 255, 255});
        draw(&e, &d, &inp, &r);
        if (e.pantalla == 2)
            draw2(&e, &d, &inp2, &r);
        EndDrawing();
    }

    // cleanup

    UnloadFont(r.fuente);
    UnloadTexture(r.imagenrei);
    UnloadTexture(r.imagenshinji);
    UnloadTexture(r.gatobaboso);
    UnloadTexture(r.perrocerebro);
    UnloadTexture(r.machete);
    UnloadTexture(r.perrorayos);
    CloseWindow();

    return 0;
}