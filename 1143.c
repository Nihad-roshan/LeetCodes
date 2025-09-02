
int longestCommonSubsequence(char* text1, char* text2) 
{
    int n = strlen(text1);
    int m = strlen(text2);

    // Allocate DP table
    int **dp = (int**)malloc((n+1) * sizeof(int*));
    for (int i = 0; i <= n; i++) 
    {
        dp[i] = (int*)calloc(m+1, sizeof(int));
    }

    // Fill DP table
    for (int i = 1; i <= n; i++) 
    {
        for (int j = 1; j <= m; j++) 
        {
            if (text1[i-1] == text2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = (dp[i-1][j] > dp[i][j-1]) ? dp[i-1][j] : dp[i][j-1];
        }
    }

    int result = dp[n][m];

    // Free memory
    for (int i = 0; i <= n; i++) 
        free(dp[i]);
    free(dp);

    return result;
}

