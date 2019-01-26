/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 01:40:00 by cwu               #+#    #+#             */
/*   Updated: 2019/01/17 01:40:01 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		philo_dead(void)
{
	int	i;

	i = -1;
	while (++i < NUM_PHIL)
		if (g_ph[i].status == IS_DEAD)
			return (1);
	return (0);
}

t_pair	init_philosopher(int id)
{
	t_pair	indexes;

	g_ph[id].life = MAX_LIFE;
	g_ph[id].status = IS_RESTING;
	indexes.c1 = id;
	indexes.c2 = (id + 1) % NUM_PHIL;
	return (indexes);
}

int		do_stuff(int id, t_pair indexes)
{
	g_ph[id].status = IS_RESTING;
	pthread_mutex_lock(&g_chop[MIN(indexes.c1, indexes.c2)]);
	if (g_ph[id].status == IS_DONE)
		return (0);
	if (g_ph[id].status == IS_DEAD)
		return (-1);
	g_ph[id].status = IS_THINKING;
	pthread_mutex_lock(&g_chop[MAX(indexes.c1, indexes.c2)]);
	if (g_ph[id].status == IS_DONE)
		return (0);
	if (g_ph[id].status == IS_DEAD)
		return (-1);
	g_ph[id].status = IS_EATING;
	SDL_Delay(EAT_T * TO_MS);
	g_ph[id].life = MAX_LIFE;
	pthread_mutex_unlock(&g_chop[indexes.c1]);
	pthread_mutex_unlock(&g_chop[indexes.c2]);
	if (g_ph[id].status == IS_DONE || g_ph[id].status == IS_DEAD)
		return (-1);
	g_ph[id].status = IS_RESTING;
	SDL_Delay(REST_T * TO_MS);
	return (1);
}

void	*philo_th(void *args)
{
	int		id;
	t_pair	indexes;
	int		ret;

	id = *((int*)args);
	indexes = init_philosopher(id);
	while (g_ph[id].status != IS_DONE && g_ph[id].status != IS_DEAD)
	{
		ret = do_stuff(id, indexes);
		if (ret == -1)
			return (NULL);
		if (ret == 0)
			break ;
	}
	pthread_mutex_unlock(&g_chop[indexes.c1]);
	pthread_mutex_unlock(&g_chop[indexes.c2]);
	return (NULL);
}

int		main(void)
{
	int			i;
	t_display	disp;
	int			ids[NUM_PHIL];

	set_up_graphics(&disp);
	set_up_threads(&ids[0]);
	while (!philo_dead())
		if (graphics_refresh(&disp))
			break ;
	draw_background(&disp);
	i = -1;
	while (++i < NUM_PHIL)
		render(&(disp.rect), i, &disp);
	SDL_RenderPresent(disp.rend);
	while (1)
		while (SDL_PollEvent(&(disp.event)))
			if (disp.event.type == SDL_QUIT ||
				disp.event.key.keysym.sym == SDLK_ESCAPE)
				finish(&disp);
	return (0);
}
