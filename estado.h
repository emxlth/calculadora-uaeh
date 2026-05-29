#ifndef ESTADO_H
#define ESTADO_H

#include "raylib.h"

#define MAX_CALIFICACIONES 10
#define MAX_CARACTERES 10

// =========================
// ESTADO DE NAVEGACIÓN
// =========================

typedef struct
{
    int pantalla;
    int submenu;
    int caja_activa;
} Estado;

// =========================
// RESULTADOS
// =========================

typedef struct
{
    float parcial1;
    float parcial2;
    float parcial3;
    float autoevaluacion;
    float coevaluacion;
    float heteroevaluacion;
    float resultado;
    float calificaciones[MAX_CALIFICACIONES];
    float porcentajes[MAX_CALIFICACIONES];
} Datos;

// =========================
// INPUTS DE TEXTO
// =========================

typedef struct
{
    char texto_calificaciones[3][MAX_CALIFICACIONES][MAX_CARACTERES];
    char texto_porcentajes[3][MAX_CALIFICACIONES][MAX_CARACTERES];
    char texto_auto[3][MAX_CARACTERES];
    char texto_coe[3][MAX_CARACTERES];
    int num_campos[3];
} Inputs;

typedef struct
{
    int parciales_llevados;
    char texto_parciales_llevados[MAX_CARACTERES];

    // datos ingresados
    char texto_hetero[2][MAX_CARACTERES];
    char texto_auto[2][MAX_CARACTERES];
    char texto_coe[2][MAX_CARACTERES];

    // resultados calculados
    float necesario_hetero[3];
    float necesario_auto[3];
    float necesario_coe[3];

    int calculado;
} Inputs2;

// =========================
// RECURSOS GRÁFICOS
// =========================

typedef struct
{
    Font fuente;
    Texture2D imagenrei;
    Texture2D imagenshinji;
    Texture2D gatobaboso;
    Texture2D machete;
    Texture2D perrorayos;
    Texture2D perrocerebro;
    Texture2D gatoper;
} Recursos;

// =========================
// DECLARACIONES
// =========================

void update(Estado *e, Datos *d, Inputs *inp);
void update2(Estado *e, Datos *d, Inputs2 *inp2);
void draw(Estado *e, Datos *d, Inputs *inp, Recursos *r);
void draw2(Estado *e, Datos *d, Inputs2 *inp2, Recursos *r);

#endif