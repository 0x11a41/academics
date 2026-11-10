%{
    int vowels = 0;
    int consonants = 0;
%}

%%
[aeiouAEIOU] { vowels++; }
[a-zA-Z]     { consonants++; }
[\n]         { return 0; }
[.]          { }
%%

int main(void)
{
    printf("Enter input: ");
    yylex();

    printf("consonants: %d\n", consonants);
    printf("vowels: %d\n", vowels);
    return 0;
}

int yywrap()
{
    return 1;    
}
