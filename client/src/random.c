#include "../inc/client.h"

void avatar_random() {
    int pick = rand() % 14 + 1;         // Returns a pseudo-random integer between 0 and RAND_MAX.
    t_avatar.avatar_num = pick;
    t_avatar.avatar_generated = mx_strjoin(t_avatar.avatar_generated, mx_itoa(pick));
    t_avatar.avatar_generated = mx_strjoin(t_avatar.avatar_generated, ".png");
}

char *get_avatar_by_number(int num)
{
    DIR* dir = NULL;
    struct dirent *sd = NULL;
    char *path = "client/data/avatars/";
    char *error_avatar = "client/data/images/group-people.png";

    dir = opendir(path);
    if(dir == NULL) return error_avatar;

    int max = 0;
    while ((sd = readdir(dir)) != NULL)
        if (sd->d_type == DT_REG)       /* If the entry is a regular file */
            max++;
    closedir(dir);
    if(num > max)
        return error_avatar;

    path = mx_strjoin(path, mx_itoa(num));
    return mx_strjoin(path, ".png");
}


