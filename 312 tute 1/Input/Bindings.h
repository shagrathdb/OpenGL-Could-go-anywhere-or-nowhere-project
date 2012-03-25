/**
 * @class Bindings
 *
 * Binds keyboard and mouse actions to commands, as registered in and by
 * the CmdSys class. 
 *
 * Commands that begin with '+' mean their + commands will be called on 
 * key press until they are released. For example, if w is bound to +forward,
 * +forward will continue to be passed to the CmdSys class for processing
 * until w is released.
 *
 * Other commands (i.e. weapon3) will be called only once on keypress, and
 * their associated keys will be set to their released state after the
 * command has been sent to the command system (CmdSys) queue.
 *
 * Note: Bindings is a MouseListener class as it requires information about
 * mouse clicks (mouse1/2/3 binds) from GLUT.
 *
 * At the moment, a map is used to map keys to commands (strings). However,
 * as there are a fixed amount of keys for binding, an STL std::vector may be an
 * option, as it's faster (O(1) lookup), but larger space requirement.
 *
 * @author Simon Manning
 * @version 0.a
 * @date 09-04-2011
 */

#ifndef _BINDINGS_H_
#define _BINDINGS_H_

#include "../input/KeysListener.h"
#include "../input/MouseListener.h"

#include <string>
#include <map>


class Bindings : public KeysListener, public MouseListener
{
  public:
    /** 
     * Destructor 
     */
    ~Bindings();
    
    /** 
     * Singleton instance access 
     */
    static Bindings* Instance();
    
    /**
     * Binds a key to a command registered with CmdSys.
     *
     * @param key key to bind.
     * @param cmd CmdSys registered command.
     */
    void BindKey(unsigned char key, const std::string& cmd);
    
    /**
     * Unbinds a key.
     *
     * @param key key to unbind.
     */
    void UnbindKey(unsigned char key);
    
    /**
     * Binds a mouse button to a command.
     *
     * @param mb mouse button to bind (MOUSE_LEFT, MOUSE_MIDDLE, MOUSE_RIGHT)
     */
    void BindMouse(MouseButton mb, const std::string& cmd);
    
    /**
     * Unbinds mouse button.
     *
     * @param mb mouse button to unbind.
     */
    void UnbindMouse(MouseButton mb);
    
    /**
     * KeyListener callback: on normal key press.
     *
     * @param key key being pressed.
     * @param x key press x coordinate.
     * @param y key press y coordinate.
     */
    void KeyDown(unsigned char key, int x, int y);
    
    /**
     * KeyListener callback: on normal key release.
     *
     * @param key key being released.
     * @param x key release x coordinate.
     * @param y key release y coordinate.
     */
    void KeyUp(unsigned char key, int x, int y);
    
    /**
     * KeyListener callback: on special key press.
     *
     * @param key key being pressed.
     * @param x key press x coordinate.
     * @param y key press y coordinate.
     */
    void SpecialDown(unsigned char key, int x, int y);
    
    /**
     * KeyListener callback: on special key release.
     *
     * @param key key being released.
     * @param x key release x coordinate.
     * @param y key release y coordinate.
     */
    void SpecialUp(unsigned char key, int x, int y);

    /**
     * MouseListener callback: on mouse click.
     *
     * @param button mouse button being clicked.
     * @param x x-location.
     * @param y y-location.
     */
    void ClickEvent(MouseButton button, int x, int y);

    /**
     * MouseListener callback: on mouse click release.
     *
     * @param button mouse button being released.
     * @param x x-location.
     * @param y y-location.
     */
    void ReleaseEvent(MouseButton button, int x, int y);

	/**
	 * Performs key bind action associated to given key.
	 *
     * @param key key whose bind should be called.
	 */
	void DoKeyBind(unsigned char key);

	/**
     * Gets key bind associated to given key.
	 * 
	 * @param key key to return bind of
	 */
	const std::string GetKeyBind(unsigned char key);

	/**
	 * Called each frame to perform actions on keys being held down.
	 */ 
	void Update();

  private:
	Bindings();
	static Bindings* m_instance;
    std::map<char, std::string> m_binds;
    std::map<MouseButton, std::string> m_mouseBinds;
	std::map<char, bool> m_heldKey;
    bool m_mouseHeldKey[3];
	bool m_waiting[256];
    bool m_mouseWait[3];
};


/**
    * In-game command for binding keys.
    *
    * Gets called, and gets args from CmdSys.
    * format: bind <key> <command string>
    */
void Bind_f();
    
/**
    * In-game command for unbinding keys.
    *
    * Gets called, and gets args from CmdSys.
    * format: bind <key> <command string>
    */
void Unbind_f();

#endif