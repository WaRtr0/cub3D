#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include "types.h"

void		prerr(char *msg);
long long	current_time(void);
long long	ft_difftime(long long t1, long long t0);
t_dvector2	dvector2_rotate(t_dvector2 v, int deg);
t_dvector2	dvector2_add(t_dvector2 v1, t_dvector2 v2);
t_dvector2	dvector2_sub(t_dvector2 v1, t_dvector2 v2);

#endif