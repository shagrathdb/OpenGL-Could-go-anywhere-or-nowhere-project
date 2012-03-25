

#ifndef __STRINGTOKENIZER_H__
#define __STRINGTOKENIZER_H__

#include <string>

/**
 * @class	StringTokens
 *
 * @brief	String tokens. 
 *
 * @author	Noel Waghorn
 * @date	10/09/2011
 */
class StringTokens
{
public:

	/**
	 * @fn	StringTokens::StringTokens();
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	10/09/2011
	 */

	StringTokens();

	/**
	 * @fn	StringTokens::StringTokens(const std::string input,const char deliminator);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	10/09/2011
	 *
	 * @param	input	   	The input.
	 * @param	deliminator	The deliminator.
	 */

	StringTokens(const std::string input,const char deliminator);

	/**
	 * @fn	StringTokens::~StringTokens();
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Noel Waghorn
	 * @date	10/09/2011
	 */

	~StringTokens();

	/**
	 * @fn	bool StringTokens::Has_More_Tokens();
	 *
	 * @brief	Query if this object has more tokens.
	 *
	 * @author	Noel Waghorn
	 * @date	10/09/2011
	 *
	 * @return	true if more tokens, false if not.
	 */

	bool Has_More_Tokens();

	/**
	 * @fn	std::string StringTokens::First_token()const;
	 *
	 * @brief	Gets the first token.
	 *
	 * @author	Noel Waghorn
	 * @date	10/09/2011
	 *
	 * @return	.
	 */

	std::string First_token()const;

	/**
	 * @fn	std::string StringTokens::Next_token();
	 *
	 * @brief	Gets the next token.
	 *
	 * @author	Noel Waghorn
	 * @date	10/09/2011
	 *
	 * @return	.
	 */

	std::string Next_token();

	/**
	 * @fn	std::string StringTokens::Prev_token();
	 *
	 * @brief	Gets the previous token.
	 *
	 * @author	Noel Waghorn
	 * @date	10/09/2011
	 *
	 * @return	.
	 */

	std::string Prev_token();

	/**
	 * @fn	unsigned int StringTokens::Get_num_tokens()const
	 *
	 * @brief	Gets the number tokens.
	 *
	 * @author	Noel Waghorn
	 * @date	10/09/2011
	 *
	 * @return	The number tokens.
	 */

	unsigned int Get_num_tokens()const{return m_num_tokens;}

	/**
	 * @fn	std::string StringTokens::operator[](const int i)const;
	 *
	 * @brief	Array indexer operator.
	 *
	 * @author	Noel Waghorn
	 * @date	10/09/2011
	 *
	 * @param	i	The index.
	 *
	 * @return	The indexed value.
	 */

	std::string operator [](const int i)const;

	/**
	 * @fn	void StringTokens::operator=(std::string* input);
	 *
	 * @brief	Assignment operator.
	 *
	 * @author	Noel Waghorn
	 * @date	10/09/2011
	 *
	 * @param [in,out]	input	If non-null, the input.
	 */

	void operator=(std::string* input);

private:
	///< The tokens
	std::string* m_tokens;
	///< Number of tokens
	int m_num_tokens;
	///< The itr
	int m_itr;

	/**
	 * @fn	void StringTokens::Count_Tokens(const std::string input,const char deliminator);
	 *
	 * @brief	Count tokens.
	 *
	 * @author	Noel Waghorn
	 * @date	10/09/2011
	 *
	 * @param	input	   	The input.
	 * @param	deliminator	The deliminator.
	 */

	void Count_Tokens(const std::string input,const char deliminator);

	/**
	 * @fn	void StringTokens::Verify_token_integrity(const char deliminator);
	 *
	 * @brief	Verify token integrity.
	 *
	 * @author	Noel Waghorn
	 * @date	11/09/2011
	 *
	 * @param	deliminator	The deliminator.
	 */

	void Verify_token_integrity(const char deliminator);
};

/**
 * @fn	std::string* Tokenize(const std::string input,const char deliminator);
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

std::string* Tokenize(const std::string input,const char deliminator);

/**
 * @fn	unsigned int Count_Tokens(const std::string input,const char deliminator);
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

unsigned int Count_Tokens(const std::string input,const char deliminator);

#endif