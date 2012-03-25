/**
 * @class MenuSystem
 * @brief Menu System class
 * @version 0.2
 * @author Simon Manning
 * @date 14-04-2011
 *
 * Allows the player to change game settings, access information about
 * the game, as well as quit the game. Accessed by pressing
 * the ESC key while in game. Menu control is done through the
 * arrow and enter keys.
 *
 * You add your own title, then add selections with an associated
 * passable function that gets called when that menu selection is
 * selected and the user presses enter on it.
 *
 * TODO: Grow menu height automatically by how many selections there
 * are in the system (for final project).
 */

#ifndef __MENUSYSTEM_H__
#define __MENUSYSTEM_H__

#include "../Input/KeysListener.h"

#include <string>
#include <map>
#include <vector>

using namespace Honir::Input;

namespace Honir {
namespace Core {

typedef void (*Fn_t) (void);

class MenuSystem : public KeysListener
{
  public:
    /** Constructor. */
    MenuSystem();

    /** Constructor giving menu width */
    MenuSystem(int width, int height);

    /** Destructor. */
    ~MenuSystem();

    /** Draws HUD. */
    void Process();

    /** For calling on initialisation (loading textures before running). */
    void Init();

    /** Draw base */
    void DrawBase();
    
    /** Adds a title image to the menu system */
    void SetTitle(std::string titleImg);

    /** Adds a selection and associated function */
    void AddFunction(std::string name, Fn_t);

    /** Sets menu width (height depends on menu options) */
    void SetDimensions(int width, int height);

    /** Returns if menu is currently active */
    bool IsActive() { return m_active; }

	/** Input */
	void KeyDown(unsigned char key, int, int);

	/** Special key input */
	void SpecialDown(unsigned char key, int, int);

    /** Activate menu otherwise than by input. */
    void Activate() { m_active = true; }

  private:
    /** Menu variables. */
    int m_width;
    int m_height;
    std::string m_title;
    std::string m_prompt;
    std::string m_gap;
    std::map<std::string, Fn_t>::iterator m_selection;
    int m_selectIndex;
    std::vector<std::map<std::string, Fn_t>::iterator> m_order;

    /** Menu state machine. */
    int m_state;

    bool m_active;

    /** Maps menu selections to functions */
    std::map<std::string, Fn_t> m_funcs;
};
}
}

#endif

