// Showing the help dialog (gameoflife.help)
void show_help() {
    FILE * help_file;
    help_file = fopen("/usr/share/ccgol/ccgol.help", "r");

    while(!feof(help_file))
        printf("%c", fgetc(help_file));
}
