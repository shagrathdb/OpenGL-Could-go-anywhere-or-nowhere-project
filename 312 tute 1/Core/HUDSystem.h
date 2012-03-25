/**
 * @class HUDSystem
 * @brief Draws and manages a heads-up disable (health, score, etc.)
 *
 * Uses FreeType font rendering to draw all HUD info. Singleton as there
 * should only ever be one HUD in the game.
 *
 * @author Simon Manning
 * @date 24-05-2011
 */

#ifndef _HUDSYSTEM_H_
#define _HUDSYSTEM_H_

#include "../Utility/Vec2f.h"

using namespace Honir::Utility;

class HUDSystem
{
  public:
    /** Destructor. */
    ~HUDSystem();

    /** Returns pointer to singleton instance. */
    static HUDSystem* Instance();

    /** Draws HUD. Retrives information from Player class. */
    void Render();

    /** Draws base of HUD. */
    void DrawBase();

    /** Initialises HUD. */
    void Init();

    /** Sets game as won (draw win screen!) */
    void WonGame() { m_wonGame = true; }

    /** Unsets game as won (revert etc.) */
    void NotWonGame() { m_wonGame = false; }

    /** Sets game as lost */
    void LostGame() { m_lostGame = true; }

    /** Sets game as not lost */
    void NotLostGame() { m_lostGame = false; }

  private:
    /** Singleton instance so private constructor. */
    HUDSystem();

    /** Drawing info. */
    Vec2f m_scoreLblLoc;
    Vec2f m_scoreLoc;
    Vec2f m_healthLblLoc;
    Vec2f m_numExtents;
    Vec2f m_winLoc;

    /** Crosshair information. */
    int m_xhairSize;
    int m_xhairX;
    int m_xhairY;

    bool m_wonGame;
    bool m_lostGame;

    /** Instance pointer. */
    static HUDSystem* m_instance;
};

#endif