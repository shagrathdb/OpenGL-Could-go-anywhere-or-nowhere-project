/**
 * @file GameState.h
 * @brief Defines a number of game states for use with various components.
 * 
 * Used by console, input, and game logic components to tell what state
 * the game is in (i.e. paused, in console, in menus, playing).
 *
 * @author Simon Manning
 * @version 0.a
 * @date Tue 12 Apr 2011
 */

#pragma once

namespace Honir {
namespace Core {

enum GameState
{
    Loading,
    Live,
    Paused,
    InMenu,
    InConsole,
    Quit,
    FinishedGame
};

}
}