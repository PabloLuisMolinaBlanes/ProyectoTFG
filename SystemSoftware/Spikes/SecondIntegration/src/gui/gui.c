// Include gtk
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

void greet() {
    system("../FirstPsychologicalTest/bin/main");
}

static void on_activate (GtkApplication *app) {
  // Create a new window
  GtkWidget *window = gtk_application_window_new (app);
  // Create a new button
  GtkWidget *button = gtk_button_new_with_label ("Test 1");
  // When the button is clicked, close the window passed as an argument
  g_signal_connect(G_OBJECT(button), "clicked", greet, NULL);
  gtk_window_set_child (GTK_WINDOW (window), button);
  gtk_window_present (GTK_WINDOW (window));
}

int main (int argc, char *argv[]) {
  // Create a new application
  GtkApplication *app = gtk_application_new ("com.example.GtkApplication",
                                             G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);
  return g_application_run (G_APPLICATION (app), argc, argv);
}
