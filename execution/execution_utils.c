#include "execution.h"

int		check_type(t_cmnd *node)
{
	if (node->redirs.i_r_type == 2)
		return (APPEND);
	else if (node->redirs.i_r_type == 1)
		return (TRUNC);
	
}	
