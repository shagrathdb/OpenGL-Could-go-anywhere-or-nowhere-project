#include "CmdSys.h"
#include <cstring>
#include <iostream>
#include <fstream>



CmdSys* CmdSys::m_instance = NULL;

CmdSys::CmdSys()
{
    // Register command system commands
    AddCmd("cmdlist", CmdList_f);
    AddCmd("exec", Exec_f);
}

CmdSys* CmdSys::Instance()
{
    if (m_instance == NULL)
    {
        m_instance = new CmdSys();
    }

    return m_instance;
}

void CmdSys::AddCmd(const std::string& cmd, Command_t function)
{
    // Check command isn't already registered first
    std::map<std::string, Command_t>::iterator itr = m_cmds.find(cmd);
    if (itr != m_cmds.end())
    {
        std::cerr << "CmdSys::AddCmd: command already registered" << std::endl;
        return;
    }
    
    // Check command is valid one-word string
    if (cmd.find(' ') != std::string::npos)
    {
        std::cerr << "CmdSys::AddCmd: invalid cmd name" << std::endl;
        return;
    }
    
    // Command not registered, so add to map
    m_cmds.insert(std::map<std::string, Command_t>::value_type(cmd, function));
}

void CmdSys::RemoveCmd(const std::string& cmd)
{
    std::map<std::string, Command_t>::iterator itr;
    
    itr = m_cmds.find(cmd);
    if (itr == m_cmds.end())
    {
        std::cerr << "CmdSys::RemoveCmd: command not found" << std::endl;
        return;
    }
    
    m_cmds.erase(itr);
}

void CmdSys::QueueCmd(const std::string& cmd)
{
    m_cmdBuffer.push(cmd);
}

void CmdSys::ExecBuffer()
{
    if (m_cmdBuffer.empty()) return;
    
    while (!m_cmdBuffer.empty())
    {
        ExecString(m_cmdBuffer.front());
        m_cmdBuffer.pop();
    }
}

void CmdSys::ExecString(std::string& text)
{
    // Clear old argv
    m_argv.clear();
    
    // Check if we need to tokenize string
    size_t found;
    found = text.find(' ');

    // If we found a space, we need to tokenize
    if (found != std::string::npos)
    {
        char* cStr;
		cStr = new char[text.length() + 1];
		strcpy(cStr, text.c_str());
        char* arg = strtok(cStr, " ");
        
        while(arg != NULL)
        {
            arg = strtok(NULL, " ");
            
            if (arg != NULL) 
            {
                m_argv.push_back(arg);
            }
        }
        
        // Get rid of argv from initial cmd and append null terminator
        text = text.substr(0, found);
		delete[] cStr;
    }
 
    // Check command given is valid/registered
    std::map<std::string, Command_t>::iterator itr = m_cmds.find(text);
    
    if (itr == m_cmds.end())
    {
        std::cerr << "CmdSys::ExecString: command not found" << std::endl;
		std::cerr << "cmd: " << text << std::endl;
        return;
    }

    // Command exists, so execute associated function
    itr->second();
}

const int CmdSys::Argc()
{
    return m_argv.size();
}

std::vector<std::string>& CmdSys::Argv()
{
    return m_argv;
}

void CmdSys::ExecFile(std::string& file)
{
    std::string line;
    std::string msg = "execing ";
    std::ifstream cfg(file);
    
    if (cfg.is_open())
    {
        msg.append(file);
 
        while (cfg.good())
        {
            std::getline(cfg, line);
            QueueCmd(line);
        }

        cfg.close();
    }
    else
    {
       return;
    }
}

void CmdSys::ListCmds()
{
    if (m_cmds.empty())
    {
        return;
    }

    std::map<std::string, Command_t>::iterator itr;
    int count = 0;
    std::string temp;

    for (itr = m_cmds.begin(); itr != m_cmds.end(); itr++)
    {
        count++;
        std::map<std::string, Command_t>::iterator tempIt = itr;
        tempIt++;
        temp.append(itr->first);
        temp.append(" ");

        if (count == 4 || tempIt == m_cmds.end())
        {
            temp = "";
            count = 0;
        }
    }
}
/**
 * Global CmdSys functions
 *
 * Provide in-game access to CmdSys functions.
 */

void CmdList_f()
{
    CmdSys::Instance()->ListCmds();
}

void Exec_f()
{
    if (CmdSys::Instance()->Argc() == 0)
    {
        return;
    }

    CmdSys::Instance()->ExecFile(CmdSys::Instance()->Argv().at(0));
}
