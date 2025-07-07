#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_STACK 50
#define MAX_TOKEN 10
#define MAX_INPUT 50
#define WIDTH_STACK 30
#define WIDTH_INPUT 30
#define WIDTH_OPERATION 20

typedef struct
{
    char left[MAX_TOKEN];
    char right[MAX_TOKEN][MAX_TOKEN];
    int right_count;
} ProductionRule;

// Function to print the current parsing table state
void printTable(char stack[][MAX_TOKEN], int top, char *input_buffer, const char *operation)
{
    char stack_str[MAX_INPUT] = "";
    for (int i = 0; i <= top; i++)
    {
        strcat(stack_str, stack[i]);
        if (i < top)
            strcat(stack_str, " "); // Avoid trailing space
    }

    printf("%-*s%-*s%-*s\n", WIDTH_STACK, "Stack", WIDTH_INPUT, "Input Buffer", WIDTH_OPERATION, "Operation");
    printf("%-*s%-*s%-*s\n", WIDTH_STACK, "------------------------------", WIDTH_INPUT, "------------------------------", WIDTH_OPERATION, "--------------------");
    printf("%-*s%-*s%-*s\n", WIDTH_STACK, stack_str, WIDTH_INPUT, input_buffer, WIDTH_OPERATION, operation);
}

// Function to tokenize the input, including handling commas and parentheses as tokens
void tokenizeInput(char *input, char tokens[][MAX_TOKEN], int *token_count)
{
    int i = 0;
    int len = strlen(input);

    while (i < len)
    {
        if (input[i] == ',' || input[i] == '(' || input[i] == ')')
        {
            // Treat commas and parentheses as tokens
            tokens[*token_count][0] = input[i++];
            tokens[*token_count][1] = '\0'; // Properly null-terminate
            (*token_count)++;
        }
        else if (input[i] == ' ')
        {
            // Skip spaces
            i++;
        }
        else
        {
            // Handle other tokens
            int j = 0;
            while (i < len && input[i] != ' ' && input[i] != ',' && input[i] != '(' && input[i] != ')' && j < MAX_TOKEN - 1)
            {
                tokens[*token_count][j++] = input[i++];
            }
            tokens[*token_count][j] = '\0'; // Properly null-terminate
            (*token_count)++;
        }
    }
}

// Function to update the input buffer (the remaining tokens to be parsed)
void updateInputBuffer(char tokens[][MAX_TOKEN], int token_count, int index, char *input_buffer)
{
    input_buffer[0] = '\0'; // Reset input buffer
    for (int j = index; j < token_count; j++)
    {
        strcat(input_buffer, tokens[j]);
        if (j < token_count - 1)
            strcat(input_buffer, " "); // Avoid trailing space
    }
}

// Function to handle the parsing logic
void parse(char *input)
{
    char stack[MAX_STACK][MAX_TOKEN];
    int top = -1;

    // Define the grammar rules
    ProductionRule rules[] = {
        {"S", {"T", "L"}, 2},       // S -> T L
        {"S", {"S", ",", "L"}, 3},  // S -> S , L
        {"T", {"int"}, 1},          // T -> int
        {"T", {"float"}, 1},        // T -> float
        {"L", {"L", ",", "id"}, 3}, // L -> L , id
        {"L", {"id"}, 1}            // L -> id
    };
    int rule_count = sizeof(rules) / sizeof(rules[0]);

    char tokens[MAX_INPUT][MAX_TOKEN];
    int token_count = 0;
    tokenizeInput(input, tokens, &token_count);

    int i = 0;
    while (i < token_count || top >= 0)
    {
        char input_buffer[MAX_INPUT] = "";
        updateInputBuffer(tokens, token_count, i, input_buffer);

        if (i < token_count)
        {
            strcpy(stack[++top], tokens[i++]);
            updateInputBuffer(tokens, token_count, i, input_buffer); // Update buffer after shift
            printTable(stack, top, input_buffer, "Shift");
        }

        int reduced;
        do
        {
            reduced = 0;
            for (int r = 0; r < rule_count; r++)
            {
                if (top >= rules[r].right_count - 1)
                {
                    int match = 1;
                    for (int k = 0; k < rules[r].right_count; k++)
                    {
                        if (strcmp(stack[top - rules[r].right_count + k + 1], rules[r].right[k]) != 0)
                        {
                            match = 0;
                            break;
                        }
                    }
                    if (match)
                    {
                        top -= rules[r].right_count - 1;
                        strcpy(stack[top], rules[r].left);
                        printTable(stack, top, input_buffer, "Reduce");
                        reduced = 1;
                        break;
                    }
                }
            }
        } while (reduced);

        if (i >= token_count && top == 0 && strcmp(stack[top], "S") == 0)
        {
            printTable(stack, top, "", "Accepted");
            return;
        }

        if (i >= token_count && !reduced)
        {
            printTable(stack, top, "", "Not Accepted");
            return;
        }
    }
}

int main()
{
    char input[MAX_INPUT];

    printf("Enter the input string: ");
    fgets(input, MAX_INPUT, stdin);
    input[strcspn(input, "\n")] = 0; // Removing the newline character

    parse(input);
    return 0;
}
