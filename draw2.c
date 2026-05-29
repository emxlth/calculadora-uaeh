#include "raylib.h"
#include "estado.h"
#include <string.h>

void draw2(Estado *e, Datos *d, Inputs2 *inp2, Recursos *r)
{
// rectángulos

   
    Rectangle caja_heteroevaluacion_d[2] = {
    {110, 170, 150, 50},
    {400, 170, 150, 50}
    };

    Rectangle caja_auto_d[2] = {
    {110, 250, 150, 50},
    {400, 250, 150, 50}
    };

    Rectangle caja_coe_d[2] = {
    {110, 320, 150, 50},
    {400, 320, 150, 50}
    };
    Rectangle btn_agregar = {110, 550, 200, 50};
    Rectangle btn_eliminar = {350, 550, 200, 50};
   

    if (e->pantalla == 2)
    {
        DrawTextEx(r->fuente, "ESC para volver", (Vector2){50, 650}, 15, 0, DARKGRAY);
        DrawTextureEx(r->perrocerebro, (Vector2){650, 370}, 0, 0.5f, WHITE);
        DrawTextEx(r->fuente, "Calculadora de Calificacion Necesaria", (Vector2){50, 50}, 30, 0, BLACK);
        DrawTextEx(r->fuente, "Primer parcial", (Vector2){120, 110}, 20, 0, BLACK);
        DrawTextEx(r->fuente, "Heteroevaluacion", (Vector2){120, 150}, 20, 0, BLACK);
        DrawRectangleRec(caja_heteroevaluacion_d[0], (Color){255, 255, 255, 100});
        if (e->caja_activa == 3000)
        DrawRectangleLinesEx(caja_heteroevaluacion_d[0], 2, BLUE);
        DrawTextEx(r->fuente, inp2->texto_hetero[0], (Vector2){120, 175}, 20, 0, BLACK);



        DrawTextEx(r->fuente, "Autoevaluacion", (Vector2){120, 220}, 20, 0, BLACK);
        DrawRectangleRec(caja_auto_d[0], (Color){255, 255, 255, 100});
        if (e->caja_activa == 3001)
        DrawRectangleLinesEx(caja_auto_d[0], 2, BLUE);
        DrawTextEx(r->fuente, inp2->texto_auto[0], (Vector2){120, 255}, 20, 0, BLACK);

        DrawTextEx(r->fuente, "Coevaluacion", (Vector2){120, 300}, 20, 0, BLACK);
        DrawRectangleRec(caja_coe_d[0], (Color){255, 255, 255, 100});
        if (e->caja_activa == 3002)
        DrawRectangleLinesEx(caja_coe_d[0], 2, BLUE);
        DrawTextEx(r->fuente, inp2->texto_coe[0], (Vector2){120, 325}, 20, 0, BLACK);
    }
    if (inp2->parciales_llevados < 2)
    {
        DrawRectangleRec(btn_agregar, (Color){180, 255, 180, 255});
        DrawTextEx(r->fuente, "+ Agregar parcial", (Vector2){120, 560}, 20, 0, BLACK);
    }

    if (inp2->parciales_llevados == 2)
    {
    DrawTextEx(r->fuente, "Segundo parcial", (Vector2){410, 110}, 20, 0, BLACK);
    DrawTextEx(r->fuente, "Heteroevaluacion", (Vector2){410, 150}, 20, 0, BLACK);
    DrawRectangleRec(caja_heteroevaluacion_d[1], (Color){255, 255, 255, 100});
    if (e->caja_activa == 3010)
        DrawRectangleLinesEx(caja_heteroevaluacion_d[1], 2, BLUE);
    DrawTextEx(r->fuente, inp2->texto_hetero[1], (Vector2){410, 175}, 20, 0, BLACK);

    DrawTextEx(r->fuente, "Autoevaluacion", (Vector2){410, 220}, 20, 0, BLACK);
    DrawRectangleRec(caja_auto_d[1], (Color){255, 255, 255, 100});
    if (e->caja_activa == 3011)
        DrawRectangleLinesEx(caja_auto_d[1], 2, BLUE);
    DrawTextEx(r->fuente, inp2->texto_auto[1], (Vector2){410, 255}, 20, 0, BLACK);

    DrawTextEx(r->fuente, "Coevaluacion", (Vector2){410, 300}, 20, 0, BLACK);
    DrawRectangleRec(caja_coe_d[1], (Color){255, 255, 255, 100});
    if (e->caja_activa == 3012)
        DrawRectangleLinesEx(caja_coe_d[1], 2, BLUE);
    DrawTextEx(r->fuente, inp2->texto_coe[1], (Vector2){410, 325}, 20, 0, BLACK);

    DrawRectangleRec(btn_eliminar, (Color){255, 180, 180, 255});
    DrawTextEx(r->fuente, "- Eliminar parcial", (Vector2){350, 560}, 20, 0, BLACK);
    }
    

    if (inp2->calculado == 1)
    {
    if (inp2->parciales_llevados == 2)
    {
    DrawTextEx(r->fuente, "Necesitas en parcial 3:", (Vector2){580, 110}, 20, 0, BLACK);
    DrawTextEx(r->fuente, TextFormat("Hetero: %.2f", inp2->necesario_hetero[2]), (Vector2){580, 140}, 20, 0, DARKGREEN);
    DrawTextEx(r->fuente, TextFormat("Auto:   %.2f", inp2->necesario_auto[2]),   (Vector2){580, 170}, 20, 0, DARKGREEN);
    DrawTextEx(r->fuente, TextFormat("Coe:    %.2f", inp2->necesario_coe[2]),    (Vector2){580, 200}, 20, 0, DARKGREEN);
    }
    else if (inp2->parciales_llevados == 1)
    {
    DrawTextEx(r->fuente, "Necesitas en parcial 2 y 3:", (Vector2){580, 110}, 20, 0, BLACK);
    DrawTextEx(r->fuente, TextFormat("Hetero: %.2f", inp2->necesario_hetero[1]), (Vector2){580, 140}, 20, 0, DARKGREEN);
    DrawTextEx(r->fuente, TextFormat("Auto:   %.2f", inp2->necesario_auto[1]),   (Vector2){580, 170}, 20, 0, DARKGREEN);
    DrawTextEx(r->fuente, TextFormat("Coe:    %.2f", inp2->necesario_coe[1]),    (Vector2){580, 200}, 20, 0, DARKGREEN);
    }
    }
    if (inp2->necesario_hetero[1] > 10.0f || inp2->necesario_hetero[2] > 10.0f)
    {
    DrawTextureEx(r->gatoper, (Vector2){570, 110}, 0, 0.7f, WHITE);
    DrawTextEx(r->fuente, "No es posible aprobar...", (Vector2){600, 80}, 20, 0, RED);
    }
}