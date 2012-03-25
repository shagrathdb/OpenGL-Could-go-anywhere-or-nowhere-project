
#include "tokenizer.h"
#include <sstream>


#include <iostream>

/**
 * @fn	StringTokens::StringTokens()
 *
 * @brief	Default constructor.
 *
 * @author	Noel Waghorn
 * @date	10/09/2011
 */

StringTokens::StringTokens() 
	: m_tokens(NULL),m_num_tokens(0),m_itr(0)
{
	delete [] m_tokens;
}

/**
 * @fn	StringTokens::StringTokens(const std::string input, const char deliminator)
 *
 * @brief	Constructor.
 *
 * @author	Noel Waghorn
 * @date	10/09/2011
 *
 * @param	input	   	The input.
 * @param	deliminator	The deliminator.
 */

StringTokens::StringTokens(const std::string input, const char deliminator) 
	: m_tokens(NULL),m_num_tokens(0),m_itr(0)
{
	delete [] m_tokens;
	StringTokens::Count_Tokens(input, deliminator);

	m_tokens = new std::string[m_num_tokens];
	
	std::string temp;
	std::istringstream input_buff(input);
	int i = 0;
	while(std::getline(input_buff,m_tokens[i],deliminator))
	{
		i++;
	}
	Verify_token_integrity(deliminator);
}

/**
 * @fn	void StringTokens::Verify_token_integrity(const char deliminator)
 *
 * @brief	Verify token integrity.
 *
 * @author	Noel Waghorn
 * @date	11/09/2011
 *
 * @param	deliminator	The deliminator.
 */

void StringTokens::Verify_token_integrity(const char deliminator)
{
	std::string del(deliminator+"");
	for(int i=0;i<m_num_tokens;i++)
	{
		// If token is null or the deliminator
		if((m_tokens[i]==del)||(m_tokens[i].empty()))
		{
			// lower number of tokens
			--m_num_tokens;
			// shift all to the left
			for(int j=i;j<m_num_tokens;j++)
			{
				m_tokens[j]=m_tokens[j+1];
			}
		}
	}
}

/**
 * @fn	StringTokens::~StringTokens()
 *
 * @brief	Destructor.
 *
 * @author	Noel Waghorn
 * @date	10/09/2011
 */

StringTokens::~StringTokens()
{
	m_tokens = NULL;
	delete [] m_tokens;
	m_num_tokens = 0;
	m_itr = 0;
}

/**
 * @fn	void StringTokens::Count_Tokens(const std::string input,const char deliminator)
 *
 * @brief	Count tokens.
 *
 * @author	Noel Waghorn
 * @date	10/09/2011
 *
 * @param	input	   	The input.
 * @param	deliminator	The deliminator.
 */

void StringTokens::Count_Tokens(const std::string input,const char deliminator)
{
	std::string temp;
	std::istringstream input_buff(input);
	while(std::getline(input_buff,temp,deliminator))
	{
		m_num_tokens++;
	}
}

/**
 * @fn	bool StringTokens::Has_More_Tokens()
 *
 * @brief	Query if 'input' has more tokens.
 *
 * @author	Noel Waghorn
 * @date	10/09/2011
 *
 * @return	true if more tokens, false if not.
 */

bool StringTokens::Has_More_Tokens() 
{	
	if(m_itr<m_num_tokens)
	{
		return true;
	}
	m_itr = m_num_tokens-1;
	return false;
}

/**
 * @fn	std::string StringTokens::Next_token()
 *
 * @brief	Gets the next token.
 *
 * @author	Noel Waghorn
 * @date	10/09/2011
 *
 * @return	.
 */

std::string StringTokens::Next_token() 
{
	int itr = m_itr++;
	if(itr>=m_num_tokens)
	{
		itr = m_num_tokens-1;
		m_itr = itr;
	}
	return m_tokens[itr];
}

/**
 * @fn	std::string StringTokens::Prev_token()
 *
 * @brief	Gets the previous token.
 *
 * @author	Noel Waghorn
 * @date	10/09/2011
 *
 * @return	.
 */

std::string StringTokens::Prev_token()
{
	if(m_itr>=1)
	{
		--m_itr;
	}
	else
	{
		m_itr = 0;
	}
	return m_tokens[m_itr];
}

/**
 * @fn	std::string StringTokens::operator[](const int i)const
 *
 * @brief	[] casting operator.
 *
 * @author	Noel Waghorn
 * @date	10/09/2011
 *
 * @param	i	The index.
 *
 * @return	The result of the operation.
 */

std::string StringTokens::operator[](const int i)const 
{
	if(i<m_num_tokens)
	{
		return m_tokens[i];
	}

	return NULL;
}

/**
 * @fn	void StringTokens::operator=(std::string* input)
 *
 * @brief	= casting operator.
 *
 * @author	Noel Waghorn
 * @date	10/09/2011
 *
 * @param [in,out]	input	If non-null, the input.
 */

void StringTokens::operator=(std::string* input)
{
	int i = 0;
	m_tokens = input;
	while(!m_tokens[i].empty())
	{
		i++;
		m_num_tokens++;
	}
}

/**
 * @fn	std::string StringTokens::First_token()const
 *
 * @brief	Gets the first token.
 *
 * @author	Noel Waghorn
 * @date	10/09/2011
 *
 * @return	.
 */

std::string StringTokens::First_token()const 
{
	return m_tokens[0];
}

/**
 * @fn	std::string* Tokenize(const std::string input,const char deliminator)
 *
 * @brief	Tokenizes.
 *
 * @author	Noel Waghorn
 * @date	10/09/2011
 *
 * @param	input	   	The input.
 * @param	deliminator	The deliminator.
 *
 * @return	null if it fails, else.
 */

std::string* Tokenize(const std::string input,const char deliminator) 
{
	int length = Count_Tokens(input, deliminator);

	std::string* tokens = new std::string[length+2];
	
	std::string temp;
	std::istringstream input_buff(input);
	int i = 0;
	while(std::getline(input_buff,tokens[i],deliminator))
	{
		i++;
	}
	tokens[i+1] = "";

	return tokens;
}

/**
 * @fn	unsigned int Count_Tokens(const std::string input,const char deliminator)
 *
 * @brief	Count tokens.
 *
 * @author	Noel Waghorn
 * @date	10/09/2011
 *
 * @param	input	   	The input.
 * @param	deliminator	The deliminator.
 *
 * @return	The total number of tokens.
 */

unsigned int Count_Tokens(const std::string input,const char deliminator) 
{
	int count = 0;
	std::string temp;
	std::istringstream input_buff(input);
	while(std::getline(input_buff,temp,deliminator))
	{
		count++;
	}

	return count;
}