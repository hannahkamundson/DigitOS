#include "shared.h"

struct Command read_user_input();
char* read_raw();
struct StringArrayAndSize tokenize_command_line(char *cmdline);
struct Command parse_command(struct StringArrayAndSize tokensAndSize);