/**
 * @class CmdSys
 * @brief Command management system.
 *
 * An idea on how commands may be passed and created by separate subsystems
 * and used by the engine by user input and console commands/config files.
 *
 * TODO: Change stringtokenising method from strtok to boost.
 *       Change print/cerr to in-game console printing.
 *
 * @author Simon Manning <simon@ecksd.com>
 * @version 0.1
 * @date 06-04-2011
 */

#ifndef __CMDSYS_H__
#define __CMDSYS_H__

#include <string>
#include <map>
#include <queue>
#include <vector>

typedef void (*Command_t) (void);


class CmdSys
{
  public:
    /** Destructor. */
    ~CmdSys();
    
    /** Returns Singleton instance pointer. */
    static CmdSys* Instance();
    
    /** 
     * Add a command with matching function to the system. 
     *
     * @param cmd Command name (e.g. "+forward")
     * @param function Corresponding C++ function pointer
     */
    void AddCmd(const std::string& cmd, Command_t function);
    
    /** 
     * Remove a command from the system. 
     *
     * @param cmd Command name (e.g. "+forward")
     */
    void RemoveCmd(const std::string& cmd);
    
    /**
     * Adds a command to be processed by the command buffer.
     *
     * Input classes and console should use this to call an action.
     * e.g. QueueCmd("+forward")
     */
    void QueueCmd(const std::string& cmd);
    
    /**
     * Executes commands in the command buffer.
     *
     * Called once each frame from the main loop.
     */
    void ExecBuffer();
    
    /**
     * Executes a parsed string from the buffer.
     *
     * @param text Command string
     */
    void ExecString(std::string& text);

    /**
     * Executes an entire file of commands or cvar settings.
     *
     * @param file path to cfg file name.
     */
    void ExecFile(std::string& file);

    /**
     * Lists available commands via the console.
     */
    void ListCmds();
    
    /**
     * Returns current argv count.
     *
     * This is used by functions that are called from the buffer.
     */
    const int Argc();
    
    /**
     * Returns current argv std::vector.
     *
     * This is used by functions that are called from the buffer.
     */
    std::vector<std::string>& Argv();
    
  private:
    /** Private constructor - singleton initialisation */
    CmdSys();
    
    /** Singleton instance */
    static CmdSys* m_instance;
    
    /** Command map. */
    std::map<std::string, Command_t> m_cmds;
    
    /** Command buffer. */
    std::queue<std::string> m_cmdBuffer;
    
    /** Command arguments - used mostly for setting cvars. */
    std::vector<std::string> m_argv;
};


/**
 * Global CmdSys-related functions.
 *
 * Required for associating commands to CmdSys functions.
 */

void CmdList_f();
void Exec_f();

#endif