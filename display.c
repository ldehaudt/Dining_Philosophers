/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 02:00:45 by cwu               #+#    #+#             */
/*   Updated: 2019/01/17 02:02:31 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		render(SDL_Rect *rect, int i, t_display *display)
{
	float	theta;

	rect->w = display->sidelen;
	rect->h = display->sidelen;
	theta = 2.0 * PI * i / NUM_PHIL;
	rect->x = cos(theta) * (W / 2 - display->sidelen) + W / 2 - rect->w / 2.0;
	rect->y = sin(theta) * (H / 2 - display->sidelen) + H / 2 - rect->h / 2.0;
	if (g_ph[i].status == IS_EATING)
		SDL_RenderCopy(display->rend, display->eat, NULL, rect);
	if (g_ph[i].status == IS_THINKING)
		SDL_RenderCopy(display->rend, display->think, NULL, rect);
	if (g_ph[i].status == IS_RESTING)
		SDL_RenderCopy(display->rend, display->sleep, NULL, rect);
	if (g_ph[i].status == IS_DEAD)
		SDL_RenderCopy(display->rend, display->die, NULL, rect);
	if (g_ph[i].status == IS_DONE)
		SDL_RenderCopy(display->rend, display->done, NULL, rect);
	rect->w = 15;
	rect->h = (g_ph[i].life / (float)MAX_LIFE) * display->sidelen;
	rect->x += display->sidelen + 10;
	SDL_RenderCopy(display->rend, display->life, NULL, rect);
	return (1);
}

void	set_table(t_display *disp, int i, SDL_Rect *r)
{
	bool	b;
	float	theta;

	b = false;
	if (pthread_mutex_trylock(&g_chop[i]) == 0)
	{
		b = true;
		pthread_mutex_unlock(&g_chop[i]);
	}
	if (b)
	{
		theta = 2.0 * PI * ((float)i - 0.5) / NUM_PHIL;
		r->x = cos(theta) * (disp->rect.w / 2 - r->w) - r->w / 2.0 + W / 2;
		r->y = sin(theta) * (disp->rect.h / 2 - r->h) - r->h / 2.0 + H / 2;
		SDL_RenderCopy(disp->rend, disp->chopstick, NULL, r);
	}
	if (g_ph[i].status != IS_EATING)
	{
		theta = 2.0 * PI * i / NUM_PHIL;
		r->x = cos(theta) * (disp->rect.w / 2 - r->w) - r->w / 2.0 + W / 2;
		r->y = sin(theta) * (disp->rect.h / 2 - r->h) - r->h / 2.0 + H / 2;
		SDL_RenderCopy(disp->rend, disp->bowl, NULL, r);
	}
}

void	draw_background(t_display *disp)
{
	int			i;
	SDL_Rect	r;

	SDL_RenderCopy(disp->rend, disp->back, NULL, NULL);
	disp->rect.w = W - disp->sidelen * 3.4;
	disp->rect.h = H - disp->sidelen * 3.4;
	disp->rect.x = (W - disp->rect.w) / 2;
	disp->rect.y = (H - disp->rect.h) / 2;
	SDL_RenderCopy(disp->rend, disp->table, NULL, &disp->rect);
	i = -1;
	r.w = disp->sidelen / 2;
	r.h = disp->sidelen / 2;
	while (++i < NUM_PHIL)
		set_table(disp, i, &r);
}

int		graphics_refresh(t_display *disp)
{
	static int	curtime = 0;
	int			i;

	while (SDL_PollEvent(&(disp->event)))
		if (disp->event.type == SDL_QUIT ||
			disp->event.key.keysym.sym == SDLK_ESCAPE)
			finish(disp);
	draw_background(disp);
	i = -1;
	while (++i < NUM_PHIL && render(&(disp->rect), i, disp))
		if (curtime + 1 == TIMEOUT)
			g_ph[i].status = IS_DONE;
		else if (g_ph[i].status != IS_EATING && g_ph[i].life-- <= MAX_LIFE)
			if (g_ph[i].life == 0)
				g_ph[i].status = IS_DEAD;
	curtime++;
	disp->rect.w = ((TIMEOUT - curtime) / (float)TIMEOUT) * (W - 60);
	disp->rect.h = 30;
	disp->rect.x = 30;
	disp->rect.y = H - 40;
	SDL_RenderCopy(disp->rend, disp->time, NULL, &disp->rect);
	SDL_RenderPresent(disp->rend);
	SDL_Delay(TO_MS);
	return (curtime == TIMEOUT);
}
