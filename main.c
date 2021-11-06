#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

typedef long (*operation) (long, long);

bool Reverse = false;

long get_hex_value (const char *string) {
	long value = 0;
	
	if (sscanf (string, "%lx", &value) != 1) {
		fprintf(stderr, "error - not a hex integer");
		exit(EXIT_FAILURE);
	}	
	
	return value;
}

void print_as_hex (long n, FILE *output) {
	const char *format = "0x%lx\n";
	
	fprintf(output, format, n);	
}

long do_addition (long first, long second) {
	long sum = first + second;
	return sum;
}

long do_subtraction (long first, long second) {
	long diff = Reverse ? second - first : first - second;
	return diff;
}

const int needed_args = 6;

// args: first value, second value, a=addition/s=subtraction, r=reverse/n=don't,
// and the name of a file to write to.
int main (int argc, char **argv) {
	if (argc != needed_args) {
		fprintf(stderr, "Need %d args, got %d\n", needed_args, argc);
		exit(EXIT_FAILURE);
	}
	
	long first = get_hex_value(argv[1]);
	long second = get_hex_value(argv[2]);
	operation fn;
	
	if (argv[3][0] == 'a') {
		fn = do_addition;
	} else if (argv[3][0] == 's') {
		fn = do_subtraction;
	} else {
		fprintf(stderr, "Wrong op argument\n");
		exit(EXIT_FAILURE);
	}
	
	if (argv[4][0] == 'r') {
		Reverse = true;
	} else if (argv[4][0] == 'n') {
		Reverse = false;
	} else {
		fprintf(stderr, "Wrong reversing argument\n");
		exit(EXIT_FAILURE);
	}
	
	long result = fn(first, second);
	
	FILE *file = fopen(argv[5], "w");
	print_as_hex(result, file);
	fclose(file);
	
	printf("Standard-output result:\n");
	print_as_hex(result, stdout);
	printf("See also file named %s\n", argv[5]);
	return 0;
}