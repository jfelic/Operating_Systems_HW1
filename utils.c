// -----------------------------------
// CSCI 340 - Operating Systems I 
// Spring 2025 (Anthony Leclerc)
// utils.c implementation file
// Assignment (Homework) 1
//
// -----------------------------------

// these are the ONLY library header files that can be used. Under no
// circumstances can additional library header files be included.  In
// particular, this restriction means you CANNOT USE any function
// declared in <string.h>, which includes functions such as: strtok(),
// strchr(), strstr(), strlen(), index(), and others.

// NOTE: when you compile, DO NOT IGNORE WARNINGS!  These warnings are
// likely indicating you are doing something wrong, such as using a
// library function that you are not allowed to use or passing the
// wrong type of argument into a function.

#include <stdio.h>	// standard I/O functions
#include <stdlib.h> 	// atof()
#include <math.h>	// math functions

#include "utils.h"	// user defined functions

// see utils.h for the required function prototypes and specifications

// NOTE: you may add any "helper" functions you need to get the job done.
//       for example, if you need to determine the length of a string.

// put your IMPLEMENTATION of the function prototypes below:

int read_lines(char* filename, line_t* line_arr, int n) {
    FILE* fp;
    char line[256];
    int line_count = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Unable to open file %s for reading", filename);
        return 0; // 0 lines read
    }
    
    while(fgets(line, 255, fp) != NULL && line_count < n) {

        // // Grab the first value
        // current_char = line; // current_char now points to first char of line
        // val = atof(current_char); // convert char that current_char points to a double
        // printf("val = %f\n", val);

        // Now that we know how to grab the first value, we can expand upon this

        // Begin Parse:
        char* start = line; // start of current substring
        char* end = line;  // Pointer to find the next comma
        double values[4]; // array to store the 4 parsed values
        int part_count = 0;

        while(*end != '\0' && part_count < 4) {
            if (*end == ',' || *end == '\n') {
                *end = '\0'; // replace comma with null terminator
                printf("Part %d: %s\n", part_count, start);
                values[part_count] = atof(start);
                part_count++;
                start = end + 1; // Move start to the next part
            }
            end++;
        }

        // We need to print the last part manually here because there are no more commas
        if (*start != '\0' && part_count < 4) {
            printf("Part %d: %s\n", part_count, start);
            values[part_count] = atof(start);
            part_count++;
        }

        // Check that we parsed correct # of parts
        if (part_count == 4) {
            // Store parsed values in the line_arr
            line_arr[line_count].p0.x = values[0];
            line_arr[line_count].p0.y = values[1];
            line_arr[line_count].p1.x = values[2];
            line_arr[line_count].p1.y = values[3];
            line_count++; // Now we increment line_count
        } else {
            printf("Warning: line %d did not have exactly 4 values\n", line_count + 1);
        }
    }

    fclose(fp); // Close the file
    return line_count; // Return the total number of lines read
}
