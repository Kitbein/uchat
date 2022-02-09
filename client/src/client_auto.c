#include "../inc/client.h"

void test_autofill()
{
    t_avatar.avatar_generated = "client/data/avatars/";
    avatar_random();

    t_msg.current = "here..."; // Имя выбранного пользователя в плейсхолдере
    msg_data.content = NULL;

    t_application.app = "GeekChat stable 1.0.0";
    t_application.user = getenv("USER");
    t_application.id = "org.ucode.uchat";
    t_application.application = g_application_new(t_application.id, G_APPLICATION_FLAGS_NONE);
    g_application_register(t_application.application, NULL, NULL);
}
