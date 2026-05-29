#include "raylib.h"
#include "estado.h"
#include <string.h>

void draw(Estado *e, Datos *d, Inputs *inp, Recursos *r)
{
    // =========================
    // RECTANGULOS
    // =========================

    static Rectangle btn_calcular  = {100, 120, 320, 60};
    static Rectangle btn_necesario = {100, 220, 320, 60};

    static Rectangle btn_parcial1 = {100, 140, 250, 50};
    static Rectangle btn_parcial2 = {100, 220, 250, 50};
    static Rectangle btn_parcial3 = {100, 300, 250, 50};
    static Rectangle btn_final    = {100, 380, 250, 50};

    static Rectangle btn_agregar = {700, 600, 200, 50};

    static Rectangle caja_auto = {700, 180, 150, 50};
    static Rectangle caja_coe  = {700, 280, 150, 50};

    Rectangle cajas_calificaciones[MAX_CALIFICACIONES];
    Rectangle cajas_porcentajes[MAX_CALIFICACIONES];

    int i = 0;

    for (i = 0; i < MAX_CALIFICACIONES; i++)
    {
        cajas_calificaciones[i] =
            (Rectangle){100, 150 + (i * 70), 180, 50};

        cajas_porcentajes[i] =
            (Rectangle){320, 150 + (i * 70), 180, 50};
    }

    // menú principal

    if (e->pantalla == 0)
    {
        DrawTextureEx(r->imagenrei, (Vector2){200, 60}, 0, 1.0f, WHITE);

        DrawTextEx(r->fuente, "Calculadora de Calificaciones UAEH", (Vector2){100, 50}, 30, 0, BLACK);

        DrawRectangleRec(btn_calcular, (Color){255, 255, 255, 100});
        DrawTextEx(r->fuente, "Calcular calificacion final", (Vector2){120, 135}, 22, 0, BLACK);

        DrawRectangleRec(btn_necesario, (Color){255, 255, 255, 100});
        DrawTextEx(r->fuente, "Calificacion necesaria para aprobar", (Vector2){120, 235}, 22, 0, BLACK);   
    }



    // calificación final

    else if (e->pantalla == 1)
    {
        if (e->submenu == 0)
        {
            DrawTextureEx(r->imagenshinji, (Vector2){500, 150}, 0, 0.4f, WHITE);
            DrawTextEx(
                r->fuente,
                "Selecciona un parcial",
                (Vector2){100, 60}, 30, 0, BLACK
            );

            DrawRectangleRec(btn_parcial1, WHITE);
            DrawRectangleRec(btn_parcial2, WHITE);
            DrawRectangleRec(btn_parcial3, WHITE);
            DrawRectangleRec(btn_final, WHITE);

            DrawTextEx(r->fuente, "Parcial 1 (30%)", (Vector2){120, 155}, 20, 0, BLACK);
            DrawTextEx(r->fuente, "Parcial 2 (35%)", (Vector2){120, 235}, 20, 0, BLACK);
            DrawTextEx(r->fuente, "Parcial 3 (35%)", (Vector2){120, 315}, 20, 0, BLACK);
            DrawTextEx(r->fuente, "Ver Final",        (Vector2){120, 395}, 20, 0, BLACK);
        }

        else if (e->submenu >= 1 && e->submenu <= 3)
        {
            int p = e->submenu - 1;

            float parcial_actual = 0;
            if (e->submenu == 1) parcial_actual = d->parcial1;
            if (e->submenu == 2) parcial_actual = d->parcial2;
            if (e->submenu == 3) parcial_actual = d->parcial3;

            DrawTextEx(r->fuente, TextFormat("PARCIAL %d", e->submenu), (Vector2){100, 50}, 35, 0, BLACK);

            DrawTextEx(r->fuente, "Calificacion", (Vector2){120, 110}, 20, 0, BLACK);
            DrawTextEx(r->fuente, "Porcentaje",   (Vector2){340, 110}, 20, 0, BLACK);

            // inputs de calificaciones y porcentajes

            for (i = 0; i < inp->num_campos[p]; i++)
            {
                DrawRectangleRec(cajas_calificaciones[i], WHITE);
                if (e->caja_activa == i)
                    DrawRectangleLinesEx(cajas_calificaciones[i], 2, BLUE);

                DrawRectangleRec(cajas_porcentajes[i], WHITE);
                if (e->caja_activa == i + 100)
                    DrawRectangleLinesEx(cajas_porcentajes[i], 2, BLUE);

                DrawTextEx(r->fuente, inp->texto_calificaciones[p][i], (Vector2){cajas_calificaciones[i].x + 10, cajas_calificaciones[i].y + 10}, 20, 0, BLACK);

                DrawTextEx(r->fuente, inp->texto_porcentajes[p][i], (Vector2){cajas_porcentajes[i].x + 10, cajas_porcentajes[i].y + 10}, 20, 0, BLACK);
            }

            // auto y coevaluacion

            DrawTextEx(r->fuente, "Autoevaluacion", (Vector2){700, 140}, 20, 0, BLACK);
            DrawRectangleRec(caja_auto, WHITE);
            if (e->caja_activa == 1000)
                DrawRectangleLinesEx(caja_auto, 2, BLUE);
            DrawTextEx(r->fuente, inp->texto_auto[p], (Vector2){710, 195}, 20, 0, BLACK);

            DrawTextEx(r->fuente, "Coevaluacion", (Vector2){700, 240}, 20, 0, BLACK);
            DrawRectangleRec(caja_coe, WHITE);
            if (e->caja_activa == 2000)
                DrawRectangleLinesEx(caja_coe, 2, BLUE);
            DrawTextEx(r->fuente, inp->texto_coe[p], (Vector2){710, 295}, 20, 0, BLACK);

            // botón agregar

            DrawRectangleRec(btn_agregar, (Color){180, 255, 180, 255});
            DrawTextEx(r->fuente, "+ Agregar", (Vector2){740, 615}, 20, 0, BLACK);

            // resultado
            DrawTextEx(r->fuente, TextFormat("Resultado: %.2f", parcial_actual), (Vector2){650, 500}, 35, 0, DARKGREEN);

            DrawTextEx(r->fuente, "ENTER para calcular", (Vector2){650, 550}, 20, 0, DARKGRAY);
            DrawTextEx(r->fuente, "ESC para volver",     (Vector2){50,  650}, 15, 0, DARKGRAY);
        }

        // final

        
        else if (e->submenu == 4)
        {
            float final =
                (d->parcial1 * 0.30f) +
                (d->parcial2 * 0.35f) +
                (d->parcial3 * 0.35f);

            DrawTextEx(r->fuente, "CALIFICACION FINAL", (Vector2){100, 80}, 40, 0, BLACK);

            DrawTextEx(r->fuente, TextFormat("Parcial 1: %.2f", d->parcial1), (Vector2){100, 200}, 25, 0, BLACK);
            DrawTextEx(r->fuente, TextFormat("Parcial 2: %.2f", d->parcial2), (Vector2){100, 260}, 25, 0, BLACK);
            DrawTextEx(r->fuente, TextFormat("Parcial 3: %.2f", d->parcial3), (Vector2){100, 320}, 25, 0, BLACK);

            DrawTextEx(r->fuente, TextFormat("FINAL: %.2f", final), (Vector2){100, 450}, 45, 0, DARKGREEN);
        
            if (e->submenu == 4 && final < 7.0f)
        {
            DrawTextureEx(r->gatobaboso, (Vector2){500, 150}, 0, 0.4f, WHITE);
            DrawTextureEx(r->machete, (Vector2){650, 350}, 0, 0.4f, WHITE);
            DrawTextEx(r->fuente, "No pasaste brou", (Vector2){500, 120}, 30, 0, BLACK);
        }
            if (e->submenu == 4 && final >= 7.0f)
        {
            DrawTextureEx(r->perrorayos, (Vector2){500, 150}, 0, 0.4f, WHITE);
            DrawTextEx(r->fuente, "Semestre salvado", (Vector2){500, 120}, 30, 0, BLACK);

        }
    }
    }
 
}
