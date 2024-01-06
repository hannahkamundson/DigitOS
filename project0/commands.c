#include "commands.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "shared.h"

void command_cd(struct Command *cmd) {
    if (cmd->args.size != 2) {
      write_error("You must have exactly one directory.\n");
    }

    int result = chdir(cmd->args.array[1]);

    if (result != 0) {
      write_error("chdir had an error");
    }
}

void command_exit(struct Command *cmd) {
    if (cmd->args.size != 1) {
      write_error("You should not have any added arguments.\n");
    }
    exit(0);
}

void command_path(struct Command* cmd) {
    (void)cmd;
    // TODO
}