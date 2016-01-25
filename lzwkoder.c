#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#define DICTIONARY_SIZE 65536
#define NULL_NODE -1

typedef struct _bit_buffer
{
  unsigned int buffer;
  unsigned int size;
}
bit_buffer_t;

typedef struct _node
{
  unsigned int next;
  unsigned int previous;
  unsigned int first;
  char symbol;
}
node_t;

typedef struct _context
{
  node_t dictionary[DICTIONARY_SIZE];
  unsigned int biggest;
  unsigned int code_size;
  bit_buffer_t bit_buffer;
  FILE *output_file;
  unsigned int buffer_byte_count;
  unsigned char buffer[256];
}
context_t;


int encode(FILE *input_file, FILE *output_file);
void init_context(context_t *context, FILE *output_file);
unsigned int find_string_in_context(
  context_t context, unsigned int code, unsigned int charactere
);
int write_context(context_t context, FILE *output_file);

int main(int argc, char* argv[])
{
  FILE *input, *output;

  if (argc < 3)
  {
    printf("Usage: lzwkoder <input_file> <outpu_file>");
    return -1;
  }

  if ( !(input = fopen(argv[1], "rb")) )
  {
    printf("Can't open %s/n", argv[1]);
    return -2;
  }

  if ( !(output = fopen(argv[2], "+wb")) )
  {
    printf("Can't open %s/n", argv[2]);
    return -3;
  }

  encode(input, output);

  fclose(input);
  fclose(output);

  return 0;
}

int encode(FILE *input_file, FILE *output_file)
{
  unsigned int code;
  unsigned int index_size = 0;
  unsigned int string_length = 0;
  int charactere;

  context_t context;
  init_context(&context, output_file);

  if ( (charactere = fgetc(input_file)) == EOF )
  {
    return -1;
  }

  code = charactere;
  index_size++;
  string_length++;

  while ( (charactere = fgetc(input_file)) != EOF )
  {
    unsigned int new_charactere;

    index_size++;

    new_charactere = find_string_in_context(context, code, charactere);

    if (new_charactere == NULL_NODE)
    {
      unsigned int temporary_charactere;

      // TODO: Save state

      temporary_charactere = add_code_to_dictionary(context, code, charactere);

      if (temporary_charactere == NULL_NODE)
      {
        printf("ERROR: dictionary is full, input %d/n", index_size);
        break;
      }

      code = charactere;
      string_length = 1;
    }
    else
    {
      code = new_charactere;
      string_length++;
    }
  }

  return write_context(context, output_file);
}

void init_context(context_t *context, FILE *output_file)
{
  int i = 0;
  node_t *dictionary;

  memset(context, 0, sizeof(*context));

  dictionary = context->dictionary;

  for (i = 0; i < 256; i++)
  {
    dictionary->next = NULL_NODE;
    dictionary->previous = NULL_NODE;
    dictionary->first = NULL_NODE;
    dictionary->symbol = i;
  }

  context->biggest = i - 1;
  context->code_size = 8;
  context->output_file = output_file;
}

unsigned int find_string_in_context(
  context_t context, unsigned int code, unsigned int charactere
)
{

}
