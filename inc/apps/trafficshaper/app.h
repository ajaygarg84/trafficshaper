#ifndef I_APP
#define I_APP

/**
 * @file app.h
 */

/**
 * This structure holds the configurable global variables required by
 * the app.
 */
struct Pelion_Globals {

    unsigned int r_request_generation_interval_T1;
    unsigned int R_tokens_per_request;
    unsigned int L_max_unused_tokens;
    unsigned int x_token_generation_interval_T2;
    unsigned int t_time_per_request_S;
};

extern struct Pelion_Globals pelion_globals;
extern PELION_CONDITION_VARIABLE Q2_cond_var;
extern unsigned char terminate_app;

#endif
