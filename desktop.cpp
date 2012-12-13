#include <gtk/gtk.h>
int main( int argc, char *argv[])
{
    gtk_init (&argc, &argv);
    GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
    gtk_window_maximize(GTK_WINDOW (window));
    GtkWidget *image=gtk_image_new_from_file("/opt/logo.jpg");
    gtk_container_add(GTK_CONTAINER(window), image);
    gtk_widget_show_all(window);
    gtk_main ();
    return 0;
}
