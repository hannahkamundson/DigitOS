#include "commands.h"
#include <stdio.h>
#include <unistd.h>
#include "shared.h"

void command_cd(struct Command *cmd) {
    printf("\n[cd] command executing.");

    if (cmd->args.size != 2) {
      write_error("You must have exactly one directory.\n");
    }

    int result = chdir(cmd->args.array[1]);

    if (result != 0) {
      write_error("chdir had an error");
    }

}