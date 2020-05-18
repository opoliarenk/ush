#include "../inc/ush.h"

static void print_env(char **env) {
	for (int i = 0; env[i]; i++)
		printf("%s\n",env[i]);
}

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

static void helper(char **environ, char **arr, t_trig *trig, t_env *env) {
	char **copy = mx_env_var(&environ, arr);
	int i = 1;
	int j = 1;
	pid_t pid;
	int status = 1;

	while (arr[i]) {
		is_flag(arr, &j, i, env);
		if (is_done(env, arr, trig, copy) == 0) {
			mx_del_strarr(&copy);
			return ;
		}
		i++;
	}
	pid = fork();
	if (pid == 0) {
		if (mx_env_exe(arr, copy, trig) == 1)
			print_env(copy);
		exit(0);
	} 
	else {
		waitpid(pid, &status, WUNTRACED);
		trig->err = status;
	}
	mx_del_strarr(&copy);
}

void mx_builtin_env(char **environ, char **arr, t_trig *trig) {
	int i = 1;
	t_env *env = (t_env *)malloc(sizeof(t_env));
	
	trig->err = 0;
	memset(env, 0, sizeof(t_env));
	if (arr[i]) 
		helper(environ, arr, trig, env);
	else
		print_env(environ);
	free(env);
    env = NULL;
}
