#ifndef I_PELION_CMD_ARGS
#define I_PELION_CMD_ARGS

struct Arg_Type {

    char id;
    char *user_friendly_name;
    int *value;
};

struct Pelion_Globals {
    unsigned int r_request_rate_T1;
    unsigned int R_tokens_per_request;
    unsigned int L_max_unused_tokens;
    unsigned int x_tokens_rate_T2;
    unsigned int t_time_per_request_T3;
};

extern struct Pelion_Globals pelion_globals;

void parse_cmd_line_args();

#endif
