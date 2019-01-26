/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 01:58:34 by cwu               #+#    #+#             */
/*   Updated: 2019/01/17 01:58:35 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	more_setup(t_display *ptr)
{
	SDL_Surface	*tmpsurf;

	tmpsurf = SDL_LoadBMP("tex/done.bmp");
	ptr->done = SDL_CreateTextureFromSurface(ptr->rend, tmpsurf);
	SDL_FreeSurface(tmpsurf);
	tmpsurf = SDL_LoadBMP("tex/life.bmp");
	ptr->life = SDL_CreateTextureFromSurface(ptr->rend, tmpsurf);
	SDL_FreeSurface(tmpsurf);
	tmpsurf = SDL_LoadBMP("tex/time.bmp");
	ptr->time = SDL_CreateTextureFromSurface(ptr->rend, tmpsurf);
	SDL_FreeSurface(tmpsurf);
	tmpsurf = SDL_LoadBMP("tex/background.bmp");
	ptr->back = SDL_CreateTextureFromSurface(ptr->rend, tmpsurf);
	SDL_FreeSurface(tmpsurf);
	tmpsurf = SDL_LoadBMP("tex/table.bmp");
	ptr->table = SDL_CreateTextureFromSurface(ptr->rend, tmpsurf);
	SDL_FreeSurface(tmpsurf);
	tmpsurf = SDL_LoadBMP("tex/chopstick.bmp");
	ptr->chopstick = SDL_CreateTextureFromSurface(ptr->rend, tmpsurf);
	SDL_FreeSurface(tmpsurf);
	tmpsurf = SDL_LoadBMP("tex/bowl.bmp");
	ptr->bowl = SDL_CreateTextureFromSurface(ptr->rend, tmpsurf);
	SDL_FreeSurface(tmpsurf);
}

void	set_up_graphics(t_display *ptr)
{
	SDL_Surface	*tmpsurf;

	srand(time(NULL));
	SDL_Init(SDL_INIT_VIDEO);
	ptr->win = SDL_CreateWindow("Philo", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN);
	ptr->rend = SDL_CreateRenderer(ptr->win, -1, 0);
	ptr->sidelen = MIN(W / (NUM_PHIL - 1), 200);
	tmpsurf = SDL_LoadBMP("tex/eat.bmp");
	ptr->eat = SDL_CreateTextureFromSurface(ptr->rend, tmpsurf);
	SDL_FreeSurface(tmpsurf);
	tmpsurf = SDL_LoadBMP("tex/think.bmp");
	ptr->think = SDL_CreateTextureFromSurface(ptr->rend, tmpsurf);
	SDL_FreeSurface(tmpsurf);
	tmpsurf = SDL_LoadBMP("tex/sleep.bmp");
	ptr->sleep = SDL_CreateTextureFromSurface(ptr->rend, tmpsurf);
	SDL_FreeSurface(tmpsurf);
	tmpsurf = SDL_LoadBMP("tex/dead.bmp");
	ptr->die = SDL_CreateTextureFromSurface(ptr->rend, tmpsurf);
	SDL_FreeSurface(tmpsurf);
	more_setup(ptr);
}

void	set_up_threads(int *ids)
{
	pthread_t	tid[NUM_PHIL];
	int			arr[NUM_PHIL];
	int			i;
	int			j;
	int			t;

	i = -1;
	while (++i < NUM_PHIL && (arr[i] = 1))
		pthread_mutex_init(&(g_chop[i]), NULL);
	i = -1;
	while (++i < NUM_PHIL)
	{
		t = (rand() % 1000) / 1000.0 * (NUM_PHIL - i) + 1;
		j = -1;
		while (t && j++ <= NUM_PHIL)
			if (arr[j] != 0)
				t--;
		arr[j] = 0;
		ids[i] = j;
		pthread_create(&tid[i], NULL, &philo_th, &ids[i]);
		pthread_detach(tid[i]);
	}
}

void	finish(t_display *disp)
{
	int	i;

	i = -1;
	while (++i < NUM_PHIL)
		pthread_mutex_destroy(&(g_chop[i]));
	SDL_DestroyWindow(disp->win);
	SDL_DestroyRenderer(disp->rend);
	exit(0);
}
