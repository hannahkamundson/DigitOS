#include "shared.h"

void eval(struct Command *cmd);
int try_exec_builtin(struct Command *cmd);
void exec_external_cmd(struct Command *cmd);