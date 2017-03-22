#include <stdlib.h>
#include <argp.h>

#include "dict.h"
#include "helpers.h"
#include "translate.h"
#include "dict_helpers.h"

// The options we understand.
static struct argp_option options[] = {
    {"input",      'i',                 0,  0,
        "Documento de entrada. (Requerido)" },
    {"dictionary", 'd', "FILE_DICTIONARY",  0,
        "Diccionario de traducción." },
    {"ignored",    'g',    "FILE_IGNORED",  0,
        "Diccionario de palabras ignoradas."},
    {"output",     'o',     "FILE_OUTPUT",  0,
        "Archivo de salida."},
    {"reverse",    'r',                 0,  0,
        "Dirección de la traducción. (Por defecto español a inglés)" },
    {0}
};

// Parse a single option.
// Used by main to communicate with parse_opt.
struct arguments {
    char *args[1];              // Arguments.
    int input_file;             // Argument for -i.
    char *dict_file;            // Argument for -d.
    char *dict_ignored_file;    // Argument for -g.
    char *output_file;          // Argument for -o.
    int reverse;                // The -r flag.
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;

    switch (key) {
        case 'i':
            arguments->input_file = 1;
            break;
        case 'd':
            arguments->dict_file = arg;
            break;
        case 'g':
            arguments->dict_ignored_file = arg;
            break;
        case 'o':
            arguments->output_file = arg;
            break;
        case 'r':
            arguments->reverse = 1;
        break;

        case ARGP_KEY_ARG:
            if (state->arg_num >= 1)
                // Too many arguments.
                argp_usage(state);
            arguments->args[state->arg_num] = arg;
            break;

        case ARGP_KEY_END:
            if (state->arg_num < 1)
                // Not enough arguments.
                argp_usage(state);
            break;

        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

// Our argp parser.
static struct argp argp = { options, parse_opt, 0, 0 };

int main(int argc, char **argv) {
    struct arguments arguments;

    // Default values.
    arguments.reverse = 0;
    arguments.input_file = 0;
    arguments.output_file = NULL;
    arguments.dict_file = NULL;
    arguments.dict_ignored_file = NULL;

    // System variables.
    dict_t dict = NULL;
    dict_t dict_temp = NULL;
    dict_t dict_ignored = NULL;

    // Read args.
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    // File input required.
    if (arguments.input_file == 0) {
        printf("File is missing.\n");
        exit(0);
    }

    // Creates a new file of dict if it does not exist.
    if (arguments.dict_file == NULL) {
        arguments.dict_file = "dict_system.txt";
    }
    dict = dict_from_file(arguments.dict_file);

    // Creates a new file of ignored words if it does not exist.
    if (arguments.dict_ignored_file == NULL) {
        arguments.dict_ignored_file = "ignore_system.txt";
    }
    dict_ignored = dict_from_file(arguments.dict_ignored_file);

    // Creates a new file of output if it does not exist.
    if (arguments.output_file == NULL) {
        arguments.output_file = "out_system.txt";
    }

    // Change language of translation.
    if (arguments.reverse) {
        dict_reverse_change(dict);
    }

    dict_temp = dict_empty();
    // Main function.
    translate(dict, dict_temp, dict_ignored,
        arguments.args[0], arguments.output_file, arguments.dict_ignored_file);

    // Dictionary update.
    dict_to_file(dict, arguments.dict_file);

    // Destroy structs.
    dict = dict_destroy(dict);
    dict_temp = dict_destroy(dict_temp);
    dict_ignored = dict_destroy(dict_ignored);

    exit(0);
}
