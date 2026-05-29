#include "raylib.h"
#include "estado.h"
#include <stdlib.h>
#include <string.h>

void update(Estado *e, Datos *d, Inputs *inp)
{
    Vector2 mouse = GetMousePosition();

    // rectángulos

    Rectangle btn_calcular  = {100, 120, 320, 60};
    Rectangle btn_necesario = {100, 220, 320, 60};

    Rectangle btn_parcial1 = {100, 140, 250, 50};
    Rectangle btn_parcial2 = {100, 220, 250, 50};
    Rectangle btn_parcial3 = {100, 300, 250, 50};
    Rectangle btn_final    = {100, 380, 250, 50};

    Rectangle btn_agregar = {700, 600, 200, 50};

    Rectangle cajas_calificaciones[MAX_CALIFICACIONES];
    Rectangle cajas_porcentajes[MAX_CALIFICACIONES];

    Rectangle caja_auto = {700, 180, 150, 50};
    Rectangle caja_coe  = {700, 280, 150, 50};

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
        if (CheckCollisionPointRec(mouse, btn_calcular))
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                e->pantalla = 1;

        if (CheckCollisionPointRec(mouse, btn_necesario))
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                e->pantalla = 2;
    }

    // calificación final

    else if (e->pantalla == 1)
    {
        if (e->submenu == 0)
        {
            if (CheckCollisionPointRec(mouse, btn_parcial1))
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    e->submenu = 1;

            if (CheckCollisionPointRec(mouse, btn_parcial2))
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    e->submenu = 2;

            if (CheckCollisionPointRec(mouse, btn_parcial3))
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    e->submenu = 3;

            if (CheckCollisionPointRec(mouse, btn_final))
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    e->submenu = 4;
        }

        else if (e->submenu >= 1 && e->submenu <= 3)
        {
            int p = e->submenu - 1;

            // click en inputs

            for (i = 0; i < inp->num_campos[p]; i++)
            {
                if (CheckCollisionPointRec(mouse, cajas_calificaciones[i]))
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                        e->caja_activa = i;

                if (CheckCollisionPointRec(mouse, cajas_porcentajes[i]))
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                        e->caja_activa = i + 100;
            }

            if (CheckCollisionPointRec(mouse, caja_auto))
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    e->caja_activa = 1000;

            if (CheckCollisionPointRec(mouse, caja_coe))
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    e->caja_activa = 2000;

            if (CheckCollisionPointRec(mouse, btn_agregar))
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    if (inp->num_campos[p] < MAX_CALIFICACIONES)
                        inp->num_campos[p]++;

            // calcular resultado

            if (IsKeyPressed(KEY_ENTER))
            {
                for (i = 0; i < inp->num_campos[p]; i++)
                {
                    d->calificaciones[i] = atof(inp->texto_calificaciones[p][i]);
                    d->porcentajes[i]    = atof(inp->texto_porcentajes[p][i]);
                }

                d->autoevaluacion = atof(inp->texto_auto[p]);
                d->coevaluacion   = atof(inp->texto_coe[p]);

                d->heteroevaluacion = 0;
                float total_porcentaje = 0;

                for (i = 0; i < inp->num_campos[p]; i++)
                {
                    d->heteroevaluacion += d->calificaciones[i] * d->porcentajes[i];
                    total_porcentaje    += d->porcentajes[i];
                }

                if (total_porcentaje > 0)
                    d->heteroevaluacion /= total_porcentaje;

                d->resultado =
                    (d->heteroevaluacion * 0.90f) +
                    (d->autoevaluacion   * 0.05f) +
                    (d->coevaluacion     * 0.05f);

                if (e->submenu == 1) d->parcial1 = d->resultado;
                if (e->submenu == 2) d->parcial2 = d->resultado;
                if (e->submenu == 3) d->parcial3 = d->resultado;
            }

            // input de teclado

            int tecla = GetCharPressed();

            while (tecla > 0)
            {
                if (e->caja_activa >= 0 &&
                    e->caja_activa < MAX_CALIFICACIONES)
                {
                    int len = strlen(inp->texto_calificaciones[p][e->caja_activa]);
                    if ((tecla >= '0' && tecla <= '9') ||
                        (tecla == '.' && !strchr(inp->texto_calificaciones[p][e->caja_activa], '.')))
                        if (len < MAX_CARACTERES - 1)
                        {
                            inp->texto_calificaciones[p][e->caja_activa][len]     = tecla;
                            inp->texto_calificaciones[p][e->caja_activa][len + 1] = '\0';
                        }
                }

                else if (e->caja_activa >= 100 &&
                         e->caja_activa < 100 + MAX_CALIFICACIONES)
                {
                    int indice = e->caja_activa - 100;
                    int len    = strlen(inp->texto_porcentajes[p][indice]);
                    if ((tecla >= '0' && tecla <= '9') ||
                        (tecla == '.' && !strchr(inp->texto_porcentajes[p][indice], '.')))
                        if (len < MAX_CARACTERES - 1)
                        {
                            inp->texto_porcentajes[p][indice][len]     = tecla;
                            inp->texto_porcentajes[p][indice][len + 1] = '\0';
                        }
                }

                else if (e->caja_activa == 1000)
                {
                    int len = strlen(inp->texto_auto[p]);
                    if ((tecla >= '0' && tecla <= '9') ||
                        (tecla == '.' && !strchr(inp->texto_auto[p], '.')))
                        if (len < MAX_CARACTERES - 1)
                        {
                            inp->texto_auto[p][len]     = (char)tecla;
                            inp->texto_auto[p][len + 1] = '\0';
                        }
                }

                else if (e->caja_activa == 2000)
                {
                    int len = strlen(inp->texto_coe[p]);
                    if ((tecla >= '0' && tecla <= '9') ||
                        (tecla == '.' && !strchr(inp->texto_coe[p], '.')))
                        if (len < MAX_CARACTERES - 1)
                        {
                            inp->texto_coe[p][len]     = (char)tecla;
                            inp->texto_coe[p][len + 1] = '\0';
                        }
                }

                tecla = GetCharPressed();
            }

            // backspace

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                if (e->caja_activa >= 0 &&
                    e->caja_activa < MAX_CALIFICACIONES)
                {
                    int len = strlen(inp->texto_calificaciones[p][e->caja_activa]);
                    if (len > 0)
                        inp->texto_calificaciones[p][e->caja_activa][len - 1] = '\0';
                }

                else if (e->caja_activa >= 100 &&
                         e->caja_activa < 100 + MAX_CALIFICACIONES)
                {
                    int indice = e->caja_activa - 100;
                    int len    = strlen(inp->texto_porcentajes[p][indice]);
                    if (len > 0)
                        inp->texto_porcentajes[p][indice][len - 1] = '\0';
                }

                else if (e->caja_activa == 1000)
                {
                    int len = strlen(inp->texto_auto[p]);
                    if (len > 0)
                        inp->texto_auto[p][len - 1] = '\0';
                }

                else if (e->caja_activa == 2000)
                {
                    int len = strlen(inp->texto_coe[p]);
                    if (len > 0)
                        inp->texto_coe[p][len - 1] = '\0';
                }
            }
        }
    }

    // esc para volver

    if (IsKeyPressed(KEY_ESCAPE))
    {
        if (e->submenu != 0)
            e->submenu = 0;
        else
            e->pantalla = 0;

        e->caja_activa = -1;
    }
}