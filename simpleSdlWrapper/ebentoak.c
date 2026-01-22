#include "ebentoak.h"

POSIZIOA saguPos;
SDL_Event event;

POSIZIOA saguarenPosizioa()
{
    return saguPos;
}

// Teklatu bidezko mugimendua (WASD / Geziak)
void saguBirtualaKudeatu(void)
{
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);

    // Y Ardatza
    if (keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_W])
    {
        saguPos.y -= SAGU_ABIADURA;
    }
    if (keystates[SDL_SCANCODE_DOWN] || keystates[SDL_SCANCODE_S])
    {
        saguPos.y += SAGU_ABIADURA;
    }

    // X Ardatza
    if (keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_A])
    {
        saguPos.x -= SAGU_ABIADURA;
    }
    if (keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D])
    {
        saguPos.x += SAGU_ABIADURA;
    }

    // Mugak
    if (saguPos.x < 0)
    {
        saguPos.x = 0;
    }
    if (saguPos.x > 640)
    {
        saguPos.x = 640;
    }
    if (saguPos.y < 0)
    {
        saguPos.y = 0;
    }
    if (saguPos.y > 480)
    {
        saguPos.y = 480;
    }
}

char textoEvento[64]; // Donde se copia el texto de cada event

char *devolverTextoIntroducido() //devolver la posición de textEvento q es la variable donde guardamos el texto metido por el usuario
{
    return textoEvento;
}


int ebentuaJasoGertatuBada(void)
{
    int ret = 0;
    if (SDL_PollEvent(&event))
    {
        /* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                ret = TECLA_LEFT;
                // actualizaPlayer(-15);
                break;
            case SDLK_RIGHT:
                ret = TECLA_RIGHT;
                // actualizaPlayer(15);
                break;
            case SDLK_DOWN:
                ret = TECLA_DOWN;
                break;
            default:
                ret = event.key.keysym.sym;
                break;
            }
            break;
        case SDL_QUIT:
            ret = GERTAERA_IRTEN;
            break;
        case SDL_MOUSEBUTTONUP:
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                ret = SAGU_BOTOIA_EZKERRA;
                break;
            case SDL_BUTTON_RIGHT:
                ret = SAGU_BOTOIA_ESKUINA;
                break;
            default:
                ret = event.button.button;
                break;
            }
            break;
        case SDL_MOUSEMOTION:
            // ALDAGIA OROKOR BATEN EZARRIK ODUGU X ETA Y GERO FUNZTIO BATEKIN IRAKURTZEKO AZKEN EBENTUAREN POSIZIOA
            saguPos.x = event.motion.x;
            saguPos.y = event.motion.y;
            ret = SAGU_MUGIMENDUA;
            break;
        case SDL_TEXTINPUT:
                // Copiar el texto del evento para usarlo después
                strcpy(textoEvento, event.text.text);
                ret = EBENTU_TESTU_SARRERA;
                break;
            
        default:
            break;
        }
    }
    return ret;
}
