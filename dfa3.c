#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int ac, char **av){
    if(ac != 2)
        return(printf("Enter command with commit comment only\n"), 1);

    printf("\e[1;33mCleaning Project...🧹\n");
    system("make fclean");
    printf("\e[1;36mAdding...\n");
    printf("\e[1;36mAdding...\e[1;35m\n");
    system("git add .");
    char commit_msg[3000];
    strcpy(commit_msg, "git commit -m \"");
    strcat(commit_msg, av[1]);
    strcat(commit_msg, "\"");
    printf("\e[1;36mCommitting...\n");
    printf("\e[1;36mCommitting...\e[1;35m\n");
    system(commit_msg);
    printf("\e[1;36mPushing...\n");
    printf("\e[1;36mPushing...\e[1;35m\n");
    system("git push");
    printf("\e[1;32mDone! ✅\n");
    return 0;
}