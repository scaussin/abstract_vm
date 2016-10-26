#ifndef MAIN_HPP
# define MAIN_HPP

typedef struct	s_token
{
	std::string data;
	struct s_token *down;
	struct s_token *right;
}				t_token;

#endif