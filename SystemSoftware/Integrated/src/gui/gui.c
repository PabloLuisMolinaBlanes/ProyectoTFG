#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

void greet() {
    
    system("./first_examination");
}

void greet_2() {
    system("./second_examination");
}

static void on_activate (GtkApplication *app) {
  // Create a new window
  GtkWidget *window = gtk_application_window_new (app);
  // Create a new grid
  GtkWidget *grid;
  // Create a new button
  GtkWidget *button = gtk_button_new_with_label ("Test 1");
  GtkWidget *button_2 = gtk_button_new_with_label ("Test 2");
  // Initialize grid
  grid = gtk_grid_new ();
  gtk_window_set_child (GTK_WINDOW (window), grid);
  // When the button is clicked, close the window passed as an argument
  g_signal_connect(G_OBJECT(button), "clicked", greet, NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);
  g_signal_connect(G_OBJECT(button_2), "clicked", greet_2, NULL);
  gtk_grid_attach (GTK_GRID (grid), button_2, 1, 0, 1, 1);
  gtk_window_present (GTK_WINDOW (window));
}

int main (int argc, char *argv[]) {
  // Create a new application
  GtkApplication *app = gtk_application_new ("com.example.GtkApplication",
                                             G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);
  return g_application_run (G_APPLICATION (app), argc, argv);
}
