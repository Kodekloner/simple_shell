#ifndef _SIMPLESHELL_H_
#define _SIMPLESHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>


/* read and write buffers */
#define FETCH_BUFF_SIZE 1024
#define RECORD_BUFF_SIZE 1024
#define FLUSH_BUFF -1

/* command chaining */
#define BSH_NORM_CMD	 0
#define BSH_OR_CMD		 1
#define BSH_AND_CMD	 2
#define BSH_CHAIN_CMD 3

/* bsh_conv_num() */
#define TO_LOWERCASE	1
#define TO_UNSIGNED	2

/* returns 1 if using getline() function from system */
#define USING_GET_LINE 0
#define USING_STR_TOK 0

#define HISTORY_FILE	".bill_shell_history"
#define MAX_HISTORY	4096

extern char **environ;


/**
 * struct linkedlist - linked list
 * @number: the number field
 * @strg: string
 * @next_node: next node
 */
typedef struct linkedlist
{
	int number;
	char *strg;
	struct linkedlist *next_node;
} ll_t;

/**
 * struct passed_params - contains arguements to be passed into a function.
 * @gtl_arg: getline string containing arguements
 * @gtl_str: strings generated from gtl_arg
 * @curr_path: relative path for current command
 * @arc: argument count
 * @err_cnt: error count
 * @exit_err:  exit() error code
 * @flaged_line: flaged line of stdi on count
 * @bsh_fname: program filename
 * @bsh_env: simple shell local copy of environ
 * @environ: modified copy of environ from LL bsh_env
 * @bsh_history: simple shell history node
 * @bsh_alias: simple shell alias
 * @bsh_env_changed: simple shell environ changed
 * @cmd_status: cmd_status of the last exec'd command
 * @cmd_buff: cmd_buff, on if chaining
 * @cmd_buff_types: cmd_type ||, &&, ;
 * @readfiledir: file directory to read line stdi from
 * @history_cnt: history count
 */
typedef struct passed_params
{
	char *gtl_arg;
	char **gtl_str;
	char *curr_path;
	int arc;
	unsigned int err_cnt;
	int exit_err;
	int flaged_line;
	char *bsh_fname;
	ll_t *bsh_env;
	ll_t *bsh_history;
	ll_t *bsh_alias;
	char **environ;
	int bsh_env_changed;
	int cmd_status;

	char **cmd_buff;
	int cmd_buff_types;
	int readfiledir;
	int history_cnt;
} params_t;

#define PARAMS_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct inbuilt - an inbuilt string and function
 * @inbuilt_type: inbuilt command flag
 * @inbuilt_func: function
 */
typedef struct inbuilt
{
	char *inbuilt_type;
	int (*inbuilt_func)(params_t *);
} inbuilt_tbl;

/* environ.c */
char *_bshgetenv(params_t *, const char *);
int _bshenv(params_t *);
int _setbshenv(params_t *);
int _bshunsetenv(params_t *);
int bsh_pop_env(params_t *);

/* bsh_errs.c */
void _bsheputs(char *);
int _bsheputchar(char);
int _bshputfdir(int fdir, char ch);
int _bshputsfdir(int fdir, char *strg);

/* bsh_errs1.c */
int bsh_errstrgtoi(char *);
void bsh_echo_err(params_t *, char *);
int bsh_echo_d(int, int);
char *bsh_conv_num(long int, int, int);
void bsh_rmv_cmts(char *);

/* bsh_exits.c */
char *_bshstrgncpy(char *, int, char *);
char *_bshstrgncat(char *, int, char *);
char *_bshstrgchr(char, char *);

/* bsh_getenv.c */
char **_get_bshenviron(params_t *);
int _unsetbshenv(params_t *, char *);
int _bshsetenv(params_t *, char *, char *);

/*bsh_getline.c */
ssize_t _bsh_input(params_t *);
int _bshgetline(params_t *, char **, size_t *);
void bsh_sgintHdler(int);

/* bsh_getparams.c */
void bsh_clr_params(params_t *);
void bsh_set_params(params_t *, char **);
void bsh_free_params(params_t *, int);

/* bsh_hist.c */
char *bsh_get_hist_file(params_t *params);
int bsh_wr_hist(params_t *params);
int bsh_rd_hist(params_t *params);
int bsh_bld_hist_list(params_t *params, char *buffer, int line_cnt);
int bsh_renum_hist(params_t *params);

/* bsh_inbuilt.c */
int _bshexit(params_t *);
int _bshcd(params_t *);
int _bshhelp(params_t *);

/* bsh_inbuilt1.c */
int _bshhistory(params_t *);
int _bshalias(params_t *);

/* bsh_loop.c */
int bsh(char **, params_t *);
int bsh_inbuilt_fd(params_t *);
void bsh_cmd_fd(params_t *);
void bsh_cmd_fk(params_t *);

/* bsh_lsts.c */
ll_t *bsh_nod_add(ll_t **, const char *, int);
ll_t *bsh_nod_add_end(ll_t **, const char *, int);
size_t bsh_prt_lstr(const ll_t *);
int bsh_del_nod_at_idx(ll_t **, unsigned int);
void bsh_frlst(ll_t **);

/* bsh_lsts1.c */
size_t bsh_lst_len(const ll_t *);
char **bsh_ll_to_strg(ll_t *);
size_t _bsh_prt_lst(const ll_t *);
ll_t *bsh_nod_sw(ll_t *, char *, char);
ssize_t bsh_nod_idx(ll_t *, ll_t *);

/* bsh_mem.c */
int bshbfree(void **);

/* bsh_parser.c */
int is_bsh_cmd(char *, params_t *);
char *bsh_dp_char(int, char *, int);
char *bsh_fi_path(char *, params_t *, char *);

/* bsh_realloc.c */
char *_bshmemset(char *, unsigned int, char);
void bshfree(char **);
void *_bshrealloc(unsigned int, void *, unsigned int);

/* bsh_strg.c */
int _bshstrglen(char *);
int _bshstrgcmp(char *, char *);
char *bsh_sw(const char *, const char *);
char *_bshstrgcat(char *, char *);

/* bsh_strg1.c */
char *_bshstrgcpy(char *, char *);
char *_bshstrgdup(const char *);
void _bshputs(char *);
int _bshputchar(char);

/* bsh_strgtoi.c */
int bsh_interactive_mode(params_t *);
int bsh_is_str_delim(char *, char);
int bsh_char_alpha(int);
int bsh_strgtoi(char *);

/* bsh_token.c */
char **bshstrgtow(char *, char *);
char **bshstrgtow2(char, char *);

/* bsh_var.c */
int bsh_is_chn(params_t *, char *, size_t *);
void bsh_chk_chn(params_t *, char *, size_t *, size_t, size_t);
int bsh_rplc_alias(params_t *);
int bsh_rplc_vars(params_t *);
int bsh_rplc_strg(char **, char *);

/* loopbsh.c */
/* int loopbsh(char **); */

#endif

