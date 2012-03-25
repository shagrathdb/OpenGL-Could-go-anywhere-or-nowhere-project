/**
 * @class KeysListener
 * @brief Handles keyboard input.
 *
 * Provides key state information to other components/classes, such as player
 * movement, menu system, and the console system. Classes who need on-event
 * keyboard information can derive from this class, and implement KeyDown,
 * KeyUp, etc. functions.
 *
 * @author Simon Manning
 * @version 0.a
 * @date 09-04-2011
 */

#ifndef _KEYS_H_
#define _KEYS_H_


class KeysListener
{
  public:    
    /** 
     * Constructor: Adds object to listen of key listeners 
     */
    KeysListener();
    
    /** 
     * Destructor 
     */
    virtual ~KeysListener();
        
    /**
     * Key press callback.
     *
     * @param key Key pressed.
     * @param x Key press x coordinate.
     * @param y Key press y coordinate.
     */
    virtual void KeyDown(unsigned char key, int x, int y) {}
    
    /**
     * Key release callback.
     *
     * @param key Key released.
     * @param x Key release x coordinate.
     * @param y Key release y coordinate.
     */
    virtual void KeyUp(unsigned char key, int x, int y) {}
    
    /** 
     * Handles special keys being pressed.
     *
     * @param key Special key being pressed.
     * @param x Key release x coordinate.
     * @param y Key release y coordinate.
     */
    virtual void SpecialDown(unsigned char key, int x, int y) {}
    
    /** 
     * Handles special keys being released.
     *
     * @param key Special key being released.
     * @param x Key press x coordinate.
     * @param y Key press y coordinate.
     */
    virtual void SpecialUp(unsigned char key, int x, int y) {}
    
    /**
     * Returns whether the listener is ignoring key repeat.
     */
    bool IgnoreRepeat();
    
    
  protected:
    bool m_ignoreRepeat;
};

#endif
