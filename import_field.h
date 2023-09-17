struct fsize {
    int height;
    int width;
};

struct fsize sz;


// Importing field from a file
short** import_field (char* filepath) {

    // Creating the file reader
    FILE * field;
    field = fopen(filepath, "r");
    char ch;

    // Counters for the number of characters and new lines (quantity of lines)
    int char_count=0;
    int height_count=0;

    // Iterating over field file and counting characters and lines
    while(!feof(field)) {
        ch = fgetc(field);
        if (ch=='0' || ch=='1') char_count++;
        if (ch=='\n') height_count++;
    }

    // Calculating the number of characters per line
    char_count=(char_count+height_count)/height_count;

    // Allocating memory for the field array
    short** field_arr = malloc(sizeof(short*)*height_count);
    for (int i=0; i<height_count; i++)
        field_arr[i] = malloc(sizeof(short)*char_count);


    // Return to file start
    fseek(field, 0, SEEK_SET);

    // Array iterators
    int h=0, w=0;

    // Parse field to array (new lines cause a jump to the next array line)
    while(!feof(field)) {
        ch = fgetc(field);
        if (ch=='0' || ch=='1') field_arr[h][w++] = (short) (ch - 48);
        else if (ch=='\n') {h++; w=0;}
    }

    // Closing the file stream
    fclose(field);

    char_count--;

    // Storing the size of the array in the struct sz
    sz.height = height_count;
    sz.width = char_count;

    // Return the field array
    return field_arr;
}
