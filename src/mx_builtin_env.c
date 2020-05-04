#include "../inc/ush.h"

static void print_env(char **env) {
	for (int i = 0; env[i]; i++)
		printf("%s\n",env[i]);
}

// static void printerr_usage() {
// 	mx_printerr("usage: env [-i] [-P utilpath] [-u name]\n");
// 	mx_printerr("           ");//11probelov
// 	mx_printerr("[name=value ...] [utility [argument ...]]\n");
// }

static void is_flag(char **arr, int *j, int i, t_env *env) {
	if (arr[i][0] == '-') {
		(*j) = 1;
		while (arr[i][(*j)]) {
			if (arr[i][(*j)] == 'i')
				env->i = 1;
			if (arr[i][(*j)] == 'u')
				env->u = 1;
			if (arr[i][(*j)] == 'P')
				env->P = 1;
			(*j)++;
		}
	}
}

static int is_done(t_env *env, char **arr, t_trig *trig, char **environ) {
	if (env->i == 1) {
		mx_env_i(arr, trig);
		return 0;
	} 
	else if (env->u == 1) {
		mx_env_u(arr, trig, environ);
		return 0;
	}
	if (env->P == 1) {
		mx_env_P(arr, trig, environ);
		return 0;
	}
	return 1;
}

void mx_builtin_env(char **environ, char **arr, t_trig *trig) {
	int i = 1;
	int j = 1;
	t_env *env = (t_env *)malloc(sizeof(t_env));
	
	trig->err = 0;
	memset(env, 0, sizeof(t_env));
	//printerr_usage();
	if (arr[i]) {
		while (arr[i]) {
			is_flag(arr, &j, i, env);
			if (is_done(env, arr, trig, environ) == 0)
				return;
			i++;
		}
	}
	else
		print_env(environ);
}
