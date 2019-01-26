/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 01:39:50 by cwu               #+#    #+#             */
/*   Updated: 2019/01/17 01:39:52 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <SDL2/SDL.h>
# include <math.h>

# define NUM_PHIL 7
# define MIN(x, y) (x < y ? x : y)
# define MAX(x, y) (x < y ? y : x)
# define TO_MS 1000

# define MAX_LIFE 7
# define EAT_T 2
# define REST_T 1
# define THINK_T 1
# define TIMEOUT 30

# define IS_RESTING 0
# define IS_THINKING 1
# define IS_EATING 2
# define IS_DEAD 3
# define IS_DONE 4

# define W 1200
# define H 1200

# define PI 3.1415926

typedef struct	s_pair
{
	int c1;
	int c2;
}				t_pair;

typedef struct	s_philo
{
	char	status;
	int		life;
}				t_philo;

typedef struct	s_display
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Texture		*eat;
	SDL_Texture		*sleep;
	SDL_Texture		*die;
	SDL_Texture		*think;
	SDL_Texture		*done;
	SDL_Texture		*back;
	SDL_Texture		*table;
	SDL_Texture		*life;
	SDL_Texture		*time;
	SDL_Texture		*chopstick;
	SDL_Texture		*bowl;
	SDL_Event		event;
	SDL_Rect		rect;
	int				sidelen;
}				t_display;

pthread_mutex_t	g_chop[NUM_PHIL];
t_philo			g_ph[NUM_PHIL];

void			set_up_graphics(t_display *ptr);
void			set_up_threads(int *ids);
void			*philo_th(void *args);
void			finish(t_display *disp);
int				render(SDL_Rect *rect, int i, t_display *display);
void			set_table(t_display *disp, int i, SDL_Rect *r);
void			draw_background(t_display *disp);
int				graphics_refresh(t_display *disp);

#endif
