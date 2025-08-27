
bool isValid(char *s) {
    char stack[100000];  
    int top = -1;      

    // Empty string is valid
    if (strlen(s) == 0) {
        return true;
    }

    for (int i = 0; s[i] != '\0'; i++) {
        char ch = s[i];

        // Push opening brackets
        if (ch == '(' || ch == '[' || ch == '{') {
            stack[++top] = ch;
        }
        // Closing brackets — check top and pop if matches
        else if ((ch == ')' && top >= 0 && stack[top] == '(') ||
                 (ch == '}' && top >= 0 && stack[top] == '{') ||
                 (ch == ']' && top >= 0 && stack[top] == '[')) {
            top--; // pop
        }
        else {
            return false; // mismatch or empty stack
        }
    }

    // Valid if stack is empty
    return top == -1;
}
