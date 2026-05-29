#include "raylib.h"
#include "estado.h"
#include <stdlib.h>
#include <string.h>

void update2(Estado *e, Datos *d, Inputs2 *inp2)
{

    Vector2 mouse = GetMousePosition();
    
    // rectángulos
    
   Rectangle caja_heteroevaluacion[2] = {{110, 170, 150, 50}, {400, 170, 150, 50} };

    Rectangle caja_auto[2] = {{110, 250, 150, 50}, {400, 250, 150, 50} };

    Rectangle caja_coe[2] = {{110, 320, 150, 50}, {400, 320, 150, 50} };

    Rectangle btn_agregar = {110, 550, 200, 50};
    Rectangle btn_eliminar = {350, 550, 200, 50};

    // click en cajas

    if (e->pantalla == 2)
    {
        if (CheckCollisionPointRec(mouse, caja_heteroevaluacion[0]))
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                e->caja_activa = 3000;
        
        if (CheckCollisionPointRec(mouse, caja_auto[0]))
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                e->caja_activa = 3001;
        
        if (CheckCollisionPointRec(mouse, caja_coe[0]))
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        e->caja_activa = 3002;

        // parcial 2
        if (CheckCollisionPointRec(mouse, caja_heteroevaluacion[1]))
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        e->caja_activa = 3010;

        if (CheckCollisionPointRec(mouse, caja_auto[1]))
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        e->caja_activa = 3011;

        if (CheckCollisionPointRec(mouse, caja_coe[1]))
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        e->caja_activa = 3012;

        if (CheckCollisionPointRec(mouse, btn_agregar))
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        if (inp2->parciales_llevados < 2)
            inp2->parciales_llevados++;

        if (CheckCollisionPointRec(mouse, btn_eliminar))
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        if (inp2->parciales_llevados > 0)
        {
            inp2->parciales_llevados--;
            // limpiar datos del parcial eliminado
            inp2->texto_hetero[1][0] = '\0';
            inp2->texto_auto[1][0]   = '\0';
            inp2->texto_coe[1][0]    = '\0';
        }
    
            if (IsKeyPressed(KEY_ENTER))
        {
        float hetero1 = atof(inp2->texto_hetero[0]);
        float auto1   = atof(inp2->texto_auto[0]);
        float coe1    = atof(inp2->texto_coe[0]);
        float p1      = hetero1 * 0.90f + auto1 * 0.05f + coe1 * 0.05f;

        if (inp2->parciales_llevados == 2)
        {
        float hetero2 = atof(inp2->texto_hetero[1]);
        float auto2   = atof(inp2->texto_auto[1]);
        float coe2    = atof(inp2->texto_coe[1]);
        float p2      = hetero2 * 0.90f + auto2 * 0.05f + coe2 * 0.05f;

        float necesario_p3 = (7.0f - p1 * 0.30f - p2 * 0.35f) / 0.35f;

        inp2->necesario_hetero[2] = (necesario_p3 - 1.0f) / 0.90f;
        inp2->necesario_auto[2]   = 10.0f;
        inp2->necesario_coe[2]    = 10.0f;
        }
        else if (inp2->parciales_llevados == 1)
        {
        float necesario_p2_y_p3 = (7.0f - p1 * 0.30f) / 0.70f;

        inp2->necesario_hetero[1] = (necesario_p2_y_p3 - 1.0f) / 0.90f;
        inp2->necesario_hetero[2] = inp2->necesario_hetero[1];
        inp2->necesario_auto[1]   = 10.0f;
        inp2->necesario_auto[2]   = 10.0f;
        inp2->necesario_coe[1]    = 10.0f;
        inp2->necesario_coe[2]    = 10.0f;
        }

        inp2->calculado = 1;
       
        }      
        //input de teclado para cajas de texto
        
        int tecla = GetCharPressed();
        while (tecla > 0)
        {
        if (e->caja_activa == 3000)
        {
        int len = strlen(inp2->texto_hetero[0]);
        if ((tecla >= '0' && tecla <= '9') ||
            (tecla == '.' && !strchr(inp2->texto_hetero[0], '.')))
            if (len < MAX_CARACTERES - 1)
            {
                inp2->texto_hetero[0][len]     = (char)tecla;
                inp2->texto_hetero[0][len + 1] = '\0';
            }
        }
        else if (e->caja_activa == 3001)
        {
        int len = strlen(inp2->texto_auto[0]);
        if ((tecla >= '0' && tecla <= '9') ||
            (tecla == '.' && !strchr(inp2->texto_auto[0], '.')))
            if (len < MAX_CARACTERES - 1)
            {
                inp2->texto_auto[0][len]     = (char)tecla;
                inp2->texto_auto[0][len + 1] = '\0';
            }
        }
        else if (e->caja_activa == 3002)
        {
        int len = strlen(inp2->texto_coe[0]);
        if ((tecla >= '0' && tecla <= '9') ||
            (tecla == '.' && !strchr(inp2->texto_coe[0], '.')))
            if (len < MAX_CARACTERES - 1)
            {
                inp2->texto_coe[0][len]     = (char)tecla;
                inp2->texto_coe[0][len + 1] = '\0';
            }
        }
        else if (e->caja_activa == 3010)
        {
        int len = strlen(inp2->texto_hetero[1]);
        if ((tecla >= '0' && tecla <= '9') ||
            (tecla == '.' && !strchr(inp2->texto_hetero[1], '.')))
            if (len < MAX_CARACTERES - 1)
            {
                inp2->texto_hetero[1][len]     = (char)tecla;
                inp2->texto_hetero[1][len + 1] = '\0';
            }
        }
        else if (e->caja_activa == 3011)
        {
        int len = strlen(inp2->texto_auto[1]);
        if ((tecla >= '0' && tecla <= '9') ||
            (tecla == '.' && !strchr(inp2->texto_auto[1], '.')))
            if (len < MAX_CARACTERES - 1)
            {
                inp2->texto_auto[1][len]     = (char)tecla;
                inp2->texto_auto[1][len + 1] = '\0';
            }
        }
        else if (e->caja_activa == 3012)
        {
        int len = strlen(inp2->texto_coe[1]);
        if ((tecla >= '0' && tecla <= '9') ||
            (tecla == '.' && !strchr(inp2->texto_coe[1], '.')))
            if (len < MAX_CARACTERES - 1)
            {
                inp2->texto_coe[1][len]     = (char)tecla;
                inp2->texto_coe[1][len + 1] = '\0';
            }
        }
        tecla = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE))
        {
        if (e->caja_activa == 3000)
        {
        int len = strlen(inp2->texto_hetero[0]);
        if (len > 0) inp2->texto_hetero[0][len - 1] = '\0';
        }
        else if (e->caja_activa == 3001)
        {
        int len = strlen(inp2->texto_auto[0]);
        if (len > 0) inp2->texto_auto[0][len - 1] = '\0';
        }
        else if (e->caja_activa == 3002)
        {
        int len = strlen(inp2->texto_coe[0]);
        if (len > 0) inp2->texto_coe[0][len - 1] = '\0';
        }
        else if (e->caja_activa == 3010)
        {
        int len = strlen(inp2->texto_hetero[1]);
        if (len > 0) inp2->texto_hetero[1][len - 1] = '\0';
        }
        else if (e->caja_activa == 3011)
        {
        int len = strlen(inp2->texto_auto[1]);
        if (len > 0) inp2->texto_auto[1][len - 1] = '\0';
        }
        else if (e->caja_activa == 3012)
        {
        int len = strlen(inp2->texto_coe[1]);
        if (len > 0) inp2->texto_coe[1][len - 1] = '\0';
    }
    }
    }    
    if (IsKeyPressed(KEY_ESCAPE))
    {
    // limpiar todos los datos
    inp2->texto_hetero[0][0] = '\0';
    inp2->texto_hetero[1][0] = '\0';
    inp2->texto_auto[0][0]   = '\0';
    inp2->texto_auto[1][0]   = '\0';
    inp2->texto_coe[0][0]    = '\0';
    inp2->texto_coe[1][0]    = '\0';
    inp2->necesario_hetero[1] = 0;
    inp2->necesario_hetero[2] = 0;
    inp2->necesario_auto[1]   = 0;
    inp2->necesario_auto[2]   = 0;
    inp2->necesario_coe[1]    = 0;
    inp2->necesario_coe[2]    = 0;
    inp2->calculado           = 0;
    inp2->parciales_llevados  = 1;
    e->pantalla = 0;
    e->caja_activa = -1;
    }
}