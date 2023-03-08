// importing libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h> //for loading images
#include <SDL/SDL_ttf.h>   //for loading fonts
#include <SDL/SDL_mixer.h> //for loading sounds
//#include <SDL/SDL_rotozoom.h> //for rotating images
// including the headers

#include "../include/menu.h"     //menu header
#include "../include/music.h"    //music header
#include "../include/text.h"     //text header
#include "../include/stars.h"    //stars header
#include "../include/settings.h" //settings header
#include "../include/enigma.h"   //enigma header

// screen
SDL_Surface *screen;
#define SCREEN_W 1280
#define SCREEN_H 720 // screen height and width

#define STARS_COUNT 100 // number of stars //! need locking
#define STARS_LAYERS 4  // number of stars variations
#define DELTA_TIME 16   // 1000ms / 60fps = 16.6666

//* regular ->'then' hovered ->'then' clicked
// images (_C for clicked) (_H for hovered)
// main menu images
image background;
image gametitle;
image playButton;
image playButton_C;
image playButton_H;
image settingsButton;
image settingsButton_C;
image settingsButton_H;
image exitButton;
image exitButton_C;
image exitButton_H;

// settings menu images
image settingsBackground;
image volumeButtonUP;
image volumeButtonUP_H;
image volumeButtonDOWN;
image volumeButtonDOWN_H;
image volumeButtonMUTE;
image volumeButtonMUTE_H;
image backButton;
image backButton_H;
image fullscreenButton;
image fullscreenButton_H;

// start game images
image startMenuTitle;
image lvl1;

// music
Mix_Music *music;
Mix_Chunk *clickFX;

// text
text author;

// logic
SDL_Event event;
int loop = 1;               // game loop
int anim_B = 0;             // animation for the buttons
int isButtonAnimated = 0;   // check if the button animated (to prevent FX spam)
int selectedButton = 0;     // selected button (keyboard)
int lastHoveredButton = -1; // last hovered button (keyboard and mouse) but made for keyboard
int StopTheGame = 0;        // stop the game, if StopTheGame = 1 -> loop = 0
int UI = 0;                 // UI = 0 -> main menu, UI = 1 -> settings menu, UI = 2 -> game
int volume = 64;            // volume of the music (0 - 128)
bool muteButtonOn = false;  // mute button state
bool enigma = false ;      // enigma state

/*
********************
*****GAME BEGIN*****
********************
*/

int main()
{
    // initializing SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL_Init Error: %s.\n", SDL_GetError());
        return 1;
    }

    // creating the window
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL)
    {
        printf("Error creating the screen: %s\n", SDL_GetError());
        return 1;
    }

    // loading stars layers
    SDL_Surface *star_images[STARS_LAYERS];
    star_images[0] = IMG_Load("../assets/img/star1.png");
    star_images[1] = IMG_Load("../assets/img/star2.png");
    star_images[2] = IMG_Load("../assets/img/star3.png");
    star_images[3] = IMG_Load("../assets/img/star4.png");

    Star stars[STARS_COUNT];

    for (int i = 0; i < STARS_COUNT; i++)
    {
        int layer = rand() % STARS_LAYERS;
        int x = rand() % SCREEN_W;
        int y = rand() % SCREEN_H;
        int speed = 50 + rand() % 150;
        init_star(&stars[i], star_images[layer], x, y, speed);
    }

    imageLoad_gametitle(&gametitle);

    // loading buttons
    imageLoad_playbutton(&playButton);
    imageLoad_settingsbutton(&settingsButton);
    imageLoad_quitbutton(&exitButton);

    // loading clicked buttons
    imageLoadClicked_playbutton(&playButton_C);
    imageLoadClicked_settingsbutton(&settingsButton_C);
    imageLoadClicked_quitbutton(&exitButton_C);

    // loading hovered buttons
    imageLoadHovered_playbutton(&playButton_H);
    imageLoadHovered_settingsbutton(&settingsButton_H);
    imageLoadHovered_quitbutton(&exitButton_H);

    // loading music
    musicLoad(music);

    // loading text
    textLoad(&author);

    //* loading settings menu images
    //? maybe add background instead of solid color for settings menu

    imageLoad_sounddown(&volumeButtonDOWN);
    imageLoad_soundup(&volumeButtonUP);
    imageLoad_soundmute(&volumeButtonMUTE);
    imageLoad_fullscreen(&fullscreenButton);
    imageLoad_backbutton(&backButton);

    imageLoadHovered_soundmute(&volumeButtonMUTE_H);
    imageLoadHovered_backbutton(&backButton_H);

    //* loading start (play) menu images
    imageLoad_lvlmenutitle(&startMenuTitle);
    imageLoad_lvl1(&lvl1);

    // loading enigma


    // uint32 return time in milliseconds
    Uint32 last_time = SDL_GetTicks();

    /*
     ********************
     *****GAME LOOP******
     ********************
     */

    while (loop)
    {
        Uint32 current_time = SDL_GetTicks();
        Uint32 delta_time = current_time - last_time;
        last_time = current_time;

        switch (UI)
        {
        case 0:
            // main menu
            // drawing background and game title
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); // black background

            for (int i = 0; i < STARS_COUNT; i++)
            {
                move_star(&stars[i], delta_time);
                draw_star(screen, &stars[i]);
            }

            imageDraw_gametitle(screen, gametitle);

            // drawing intial buttons
            imageDraw_playbutton(screen, playButton);
            imageDraw_settingsbutton(screen, settingsButton);
            imageDraw_quitbutton(screen, exitButton);

            // drawing text
            textDraw(screen, author, "KingsMan Team, 2023");

            // events
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                // controlling the buttons by arrow keys
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_f:
                        SDL_WM_ToggleFullScreen(screen);
                        break;
                    case SDLK_UP:
                        selectedButton = (selectedButton - 1 + 3) % 3;
                        anim_B = selectedButton;
                        break;
                    case SDLK_DOWN:
                        selectedButton = (selectedButton + 1) % 3;
                        anim_B = selectedButton;
                        break;
                    case SDLK_g:
                    enigma = true;
                        break;   
                    case SDLK_RETURN:
                        switch (selectedButton)
                        {
                        case 0:
                            // start button pressed
                            imageDrawClicked_playbutton(screen, playButton_C);
                            FXLoad(clickFX);
                            UI = 2;
                            break;
                        case 1:
                            // settings button pressed
                            imageDrawClicked_settingsbutton(screen, settingsButton_C);
                            FXLoad(clickFX);
                            UI = 1;
                            break;
                        case 2:
                            // exit button pressed
                            imageDrawClicked_quitbutton(screen, exitButton_C);
                            FXLoad(clickFX);
                            StopTheGame = 1;
                            break;
                        }
                        break;
                    default:
                        break;
                    }
                    break; // this break for preventing the mouse motion event from being triggered

                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button)
                    {
                    case SDL_BUTTON_LEFT:
                        if (event.button.x >= playButton.img_pos.x && event.button.x <= playButton.img_pos.x + playButton.img_size.w && event.button.y >= playButton.img_pos.y && event.button.y <= playButton.img_pos.y + playButton.img_size.h)
                        {
                            imageDrawClicked_playbutton(screen, playButton_C);
                            FXLoad(clickFX);
                            UI = 2;
                        }
                        else if (event.button.x >= settingsButton.img_pos.x && event.button.x <= settingsButton.img_pos.x + settingsButton.img_size.w && event.button.y >= settingsButton.img_pos.y && event.button.y <= settingsButton.img_pos.y + settingsButton.img_size.h)
                        {
                            imageDrawClicked_settingsbutton(screen, settingsButton_C);
                            FXLoad(clickFX);
                            UI = 1;
                        }
                        else if (event.button.x >= exitButton.img_pos.x && event.button.x <= exitButton.img_pos.x + exitButton.img_size.w && event.button.y >= exitButton.img_pos.y && event.button.y <= exitButton.img_pos.y + exitButton.img_size.h)
                        {
                            imageDrawClicked_quitbutton(screen, exitButton_C);
                            FXLoad(clickFX);
                            StopTheGame = 1;
                        }
                        break;

                    default:
                        break;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    // highlighting the button when the mouse is over it
                    if (event.motion.x >= playButton.img_pos.x && event.motion.x <= playButton.img_pos.x + playButton.img_size.w && event.motion.y >= playButton.img_pos.y && event.motion.y <= playButton.img_pos.y + playButton.img_size.h)
                    {
                        if (isButtonAnimated != 0)
                        {
                            anim_B = 0;
                            FXLoad(clickFX);
                        }
                    }
                    else if (event.motion.x >= settingsButton.img_pos.x && event.motion.x <= settingsButton.img_pos.x + settingsButton.img_size.w && event.motion.y >= settingsButton.img_pos.y && event.motion.y <= settingsButton.img_pos.y + settingsButton.img_size.h)
                    {
                        if (isButtonAnimated != 1)
                        {
                            anim_B = 1;
                            FXLoad(clickFX);
                        }
                    }
                    else if (event.motion.x >= exitButton.img_pos.x && event.motion.x <= exitButton.img_pos.x + exitButton.img_size.w && event.motion.y >= exitButton.img_pos.y && event.motion.y <= exitButton.img_pos.y + exitButton.img_size.h)
                    {
                        if (isButtonAnimated != 2)
                        {
                            anim_B = 2;
                            FXLoad(clickFX);
                        }
                    }
                    else
                    {
                        anim_B = -1;
                    }
                    break;

                case SDL_QUIT: // if the user clicks on the close button
                    StopTheGame = 1;
                    break;
                default:
                    break;
                }
            }

            // button hover logic
            if (anim_B == 0)
            {
                imageDrawHovered_playbutton(screen, playButton_H);
                lastHoveredButton = 0; // remember that the play button was last hovered
            }
            else if (anim_B == 1)
            {
                imageDrawHovered_settingsbutton(screen, settingsButton_H);
                lastHoveredButton = 1; // remember that the settings button was last hovered
            }
            else if (anim_B == 2)
            {
                imageDrawHovered_quitbutton(screen, exitButton_H);
                lastHoveredButton = 2; // remember that the quit button was last hovered
            }
            else
            {
                // if no button is currently hovered, but we remember the last one, draw it as hovered
                if (lastHoveredButton == 0)
                {
                    imageDrawHovered_playbutton(screen, playButton_H);
                }
                else if (lastHoveredButton == 1)
                {
                    imageDrawHovered_settingsbutton(screen, settingsButton_H);
                }
                else if (lastHoveredButton == 2)
                {
                    imageDrawHovered_quitbutton(screen, exitButton_H);
                }
            }
            // checking which button is animated
            isButtonAnimated = anim_B;

            break;
        case 1:
            // settings menu
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

            // drawing the buttons
            imageDraw_sounddown(screen, volumeButtonDOWN);
            imageDraw_soundup(screen, volumeButtonUP);
            if (muteButtonOn)
            {
                imageDrawHovered_soundmute(screen, volumeButtonMUTE_H);
            }
            else
            {
                imageDraw_soundmute(screen, volumeButtonMUTE);
            }
            imageDraw_fullscreen(screen, fullscreenButton);
            imageDraw_backbutton(screen, backButton);

            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT: // if the user clicks on the close button
                    StopTheGame = 1;
                    break;
                default:
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button)
                    {
                    case SDL_BUTTON_LEFT:
                        if (event.button.x >= backButton.img_pos.x && event.button.x <= backButton.img_pos.x + backButton.img_size.w && event.button.y >= backButton.img_pos.y && event.button.y <= backButton.img_pos.y + backButton.img_size.h)
                        {
                            FXLoad(clickFX);
                            UI = 0;
                        }
                        else if (event.button.x >= volumeButtonDOWN.img_pos.x && event.button.x <= volumeButtonDOWN.img_pos.x + volumeButtonDOWN.img_size.w && event.button.y >= volumeButtonDOWN.img_pos.y && event.button.y <= volumeButtonDOWN.img_pos.y + volumeButtonDOWN.img_size.h)
                        {
                            FXLoad(clickFX);
                            if (volume > 0)
                            {
                                volume -= 10;
                            }
                            Mix_VolumeMusic(volume);
                        }
                        else if (event.button.x >= volumeButtonUP.img_pos.x && event.button.x <= volumeButtonUP.img_pos.x + volumeButtonUP.img_size.w && event.button.y >= volumeButtonUP.img_pos.y && event.button.y <= volumeButtonUP.img_pos.y + volumeButtonUP.img_size.h)
                        {
                            FXLoad(clickFX);
                            if (volume < 128)
                            {
                                volume += 10;
                            }
                            Mix_VolumeMusic(volume);
                        }
                        else if (event.button.x >= volumeButtonMUTE.img_pos.x && event.button.x <= volumeButtonMUTE.img_pos.x + volumeButtonMUTE.img_size.w && event.button.y >= volumeButtonMUTE.img_pos.y && event.button.y <= volumeButtonMUTE.img_pos.y + volumeButtonMUTE.img_size.h)
                        {
                            FXLoad(clickFX);
                            muteButtonOn = !muteButtonOn; // toggle the mute button state

                            // draw the appropriate image based on the mute button state
                            if (muteButtonOn)
                            {
                                volume = 128;
                            }
                            else
                            {
                                volume = 0;
                            }
                            Mix_VolumeMusic(volume);
                        }
                        else if (event.button.x >= fullscreenButton.img_pos.x && event.button.x <= fullscreenButton.img_pos.x + fullscreenButton.img_size.w && event.button.y >= fullscreenButton.img_pos.y && event.button.y <= fullscreenButton.img_pos.y + fullscreenButton.img_size.h)
                        {
                            FXLoad(clickFX);
                            SDL_WM_ToggleFullScreen(screen);
                        }
                        break;

                    default:
                        break;
                    }
                    break;
                }
            }
            break;
        case 2:
            // start (play) menu
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 179, 254, 254)); // light blue
            imageDraw_lvlmenutitle(screen, startMenuTitle);
            imageDraw_lvl1(screen, lvl1);
            imageDraw_backbutton(screen, backButton); //! used twice, but it's ok for now (universal fucntion)

            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT: // if the user clicks on the close button
                    StopTheGame = 1;
                    break;
                default:
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button)
                    {
                    case SDL_BUTTON_LEFT:
                        if (event.button.x >= backButton.img_pos.x && event.button.x <= backButton.img_pos.x + backButton.img_size.w && event.button.y >= backButton.img_pos.y && event.button.y <= backButton.img_pos.y + backButton.img_size.h)
                        {
                            FXLoad(clickFX);
                            UI = 0;
                        }
                    default:
                        break;
                    }
                    break;
                }
            }
            break;
        }
        /*
         *********************************
         *****logic variable control******
         *********************************
         */

        // rereshing the screen
        SDL_Flip(screen);

        // limiting the frame rate
        SDL_Delay(DELTA_TIME);

        // stop the game
        if (StopTheGame == 1)
        {
            loop = 0;
        }
    }
    // free memory
    imageFree(background);
    imageFree(playButton);
    imageFree(playButton_C);
    imageFree(playButton_H);
    imageFree(settingsButton);
    imageFree(settingsButton_C);
    imageFree(settingsButton_H);
    imageFree(exitButton);
    imageFree(exitButton_C);
    imageFree(exitButton_H);
    musicFree(music);
    SDL_FreeSurface(star_images[0]);
    SDL_FreeSurface(star_images[1]);
    SDL_FreeSurface(star_images[2]);
    SDL_FreeSurface(star_images[3]);
    // todo add missing frees

    SDL_Quit();
    return 0;
}