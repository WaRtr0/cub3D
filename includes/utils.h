#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include "types.h"

void		prerr(char *msg);
t_dvector2	dvector2_rotate(t_dvector2 v, int deg);
t_dvector2	dvector2_add(t_dvector2 v1, t_dvector2 v2);
t_dvector2	dvector2_sub(t_dvector2 v1, t_dvector2 v2);

#endif