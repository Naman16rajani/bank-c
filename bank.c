#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #define Acc struct Account
typedef struct account
{
    int accNum;
    int accBal;
    char name[10];
} Acc;

int searchAcc(int accn, FILE *acct)
{
    Acc sear;
    int y = 0;
    char c;
    fseek(acct, 0, SEEK_SET);
    c = fgetc(acct);
    while (1)
    {
        fscanf(acct, "%s %d %d", sear.name, &sear.accNum, &sear.accBal);
        c = fgetc(acct);
        if (accn == sear.accNum)
        {
            y = 1;
            break;
        }
        else
        {
            y = 0;
        }
        if (c == EOF)
        {
            break;
        }
    }
    // printf("y=%d\n", y);
    fseek(acct, 0, SEEK_SET);
    return y;
}
int accCreate(FILE *acct)
{
    int accNum, r = 1;
    while (r--)
    {
        srand(time(0));
        accNum = rand() % 100000 + 1;
        printf("%d\n", accNum);
        if (searchAcc(accNum, acct))
        {
            r = 1;
        }
        else
        {
            r = 0;
        }
    }

    return accNum;
}
Acc searcacco(int accn, FILE *acct)
{
    Acc sear;
    int y = 0;
    char c;
    fseek(acct, 0, SEEK_SET);
    while (1)
    {
        fscanf(acct, "%s %d %d", sear.name, &sear.accNum, &sear.accBal);
        c = fgetc(acct);
        if (accn == sear.accNum)
        {
            y = 1;
            break;
        }
        else
        {
            y = 0;
        }
        if (c == EOF)
        {
            break;
        }
    }
    fseek(acct, 0, SEEK_END);
    return sear;
}
void copyf(FILE *acco, long long int pos, int balance)
{
    FILE *fptr;
    fclose(acco);
    acco = fopen("acounts.txt", "r");
    Acc sam;
    fseek(acco, 0, SEEK_SET);
    char c;
    fptr = fopen("copy.txt", "w+");
    // while (1)
    // {
    //     long long int p = ftell(fptr);
    //     if (p == pos)
    //     {
    //         fscanf(acco, "%s %d %d", sam.name, &sam.accNum, &sam.accBal);
    //         fprintf(fptr, "%s\t%d\t%d\n", sam.name, sam.accNum, balance);
    //         printf("%s\t%d\t%d\n", sam.name, sam.accNum, balance);
    //     }
    //     else if ((c = fgetc(acco)) == EOF)
    //     {
    //         break;
    //     }
    //     // printf("c1=%c\n", c);
    //     else
    //     {
    //         fscanf(acco, "%s %d %d", sam.name, &sam.accNum, &sam.accBal);
    //         fprintf(fptr, "%s\t%d\t%d\n", sam.name, sam.accNum, sam.accBal);
    //     }
    // }
    while ((c = fgetc(acco)) != EOF)
    {
        long long int p = ftell(fptr);
        if (p == pos)
        {
            fscanf(acco, "%s %d %d", sam.name, &sam.accNum, &sam.accBal);
            fprintf(fptr, "%c%s\t%d\t%d", c, sam.name, sam.accNum, balance);
            // printf("%s\t%d\t%d\n", sam.name, sam.accNum, balance);
        }
        else
        {
            fputc(c, fptr);
        }
    }
    fclose(acco);
    fseek(fptr, 0, SEEK_SET);
    acco = fopen("acounts.txt", "w+");
    while ((c = fgetc(fptr)) != EOF)
    {
        fputc(c, acco);
    }
    // while (1)
    // {
    //     printf("c2=%c\n", c);

    //     long long int p = ftell(fptr);
    //     fscanf(fptr, "%s %d %d", sam.name, &sam.accNum, &sam.accBal);
    //     fprintf(acco, "%s\t%d\t%d\n", sam.name, sam.accNum, sam.accBal);
    //      printf("%s\t%d\t%d\n", sam.name, sam.accNum, sam.accBal);
    //     if ((c = fgetc(fptr)) == EOF)
    //     {
    //         break;
    //     }
    // }
    fclose(acco);
    fclose(fptr);
}
void deposit(int accNum, FILE *acct, int balance)
{
    Acc sear;
    int y = 0;
    char c;
    fseek(acct, 0, SEEK_SET);
    while (1)
    {
        long long int pos = ftell(acct);
        // printf("pos=%d\n", ftell(acct));
        fscanf(acct, "%s %d %d", sear.name, &sear.accNum, &sear.accBal);
        c = fgetc(acct);
        if (accNum == sear.accNum)
        {
            int balacc;
            balacc = sear.accBal + balance;
            copyf(acct, pos, balacc);
            break;
        }
        if (c == EOF)
        {
            break;
        }
    }
    fseek(acct, 0, SEEK_SET);
}
void withdraw(int accNum, FILE *acct, int balance)
{
    Acc sear;
    int y = 0;
    char c;
    fseek(acct, 0, SEEK_SET);
    while (1)
    {
        long long int pos = ftell(acct);
        // printf("pos=%d\n", ftell(acct));
        fscanf(acct, "%s %d %d", sear.name, &sear.accNum, &sear.accBal);
        c = fgetc(acct);
        if (accNum == sear.accNum)
        {
            int balacc;
            balacc = sear.accBal - balance;
            copyf(acct, pos, balacc);
            break;
        }
        if (c == EOF)
        {
            break;
        }
    }
    fseek(acct, 0, SEEK_SET);
}
int lastMove()
{
    int lastmove = 0;
    printf("main menu 1\n");
    scanf("%d", &lastmove);
    if (lastmove != 1)
    {
        printf("thanks\n");
        lastmove = 0;
    }

    return lastmove;
}
int main()
{
    int t = 1;
    while (t--)
    {
        FILE *acct, *trant;
        acct = fopen("acounts.txt", "a+");
        trant = fopen("transcation.txt", "a+");
        Acc seaAcc, res, creaacc, tranAcc, passAcc;

        int move1, an;
        printf("account create 1\n");
        printf("Check balance 2\n");
        printf("passbook 3\n");
        printf("Transection 4\n");
        scanf("%d", &move1);
        switch (move1)
        {
        case 1:
            printf("Enter name:\n");
            scanf("%s", creaacc.name);
            creaacc.accNum = accCreate(acct);
            creaacc.accBal = 0;
            fprintf(acct, "%s\t%d\t%d\n", creaacc.name, creaacc.accNum, creaacc.accBal);
            printf("Your acc num=%d\nYour balance is %d\n", creaacc.accNum, creaacc.accBal);
            fclose(acct);
            fclose(trant);
            t = lastMove();
            break;
        case 2:
            printf("Enter acc num:\n");
            scanf("%d", &seaAcc.accNum);
            res = searcacco(seaAcc.accNum, acct);
            if (!searchAcc(seaAcc.accNum, acct))
            {
                printf("invalid\n");
            }
            else
            {
                printf("Name:%s\nAcc num:%d\nAcc bal:%d\n", res.name, res.accNum, res.accBal);
            }
            fclose(acct);
            fclose(trant);
            t = lastMove();
            break;
        case 4:
            printf("withdraw:1\ndeposit:2\n");
            int move2;
            scanf("%d", &move2);
            switch (move2)
            {
            case 1:
                printf("Enter acc num:\n");
                scanf("%d", &tranAcc.accNum);
                // withdraw(tranAcc.accNum);
                if (!searchAcc(tranAcc.accNum, acct))
                {
                    printf("invalid\n");
                }
                else
                {
                    printf("enter ammount withdraw\n");
                    scanf("%d", &tranAcc.accBal);
                    withdraw(tranAcc.accNum, acct, tranAcc.accBal);
                    fprintf(trant, "-\t%d\t%d\n", tranAcc.accNum, tranAcc.accBal);
                }
                fclose(acct);
                fclose(trant);
                break;
            case 2:
                printf("Enter acc num:\n");
                scanf("%d", &tranAcc.accNum);
                // withdraw(tranAcc.accNum);
                if (!searchAcc(tranAcc.accNum, acct))
                {
                    printf("invalid\n");
                }
                else
                {
                    printf("enter ammount withdraw\n");
                    scanf("%d", &tranAcc.accBal);
                    deposit(tranAcc.accNum, acct, tranAcc.accBal);
                    fprintf(trant, "+\t%d\t%d\n", tranAcc.accNum, tranAcc.accBal);
                }
                fclose(acct);
                fclose(trant);
                break;
            default:
                printf("!!!!!      Invalid input    !!!!!\n");
                break;
            }
            t = lastMove();
            break;
        case 3:
            printf("enter acc num3:\n");
            scanf("%d", &an);
            if (!searchAcc(an, acct))
            {
                printf("invalid acc num\n");
            }
            else
            {
                printf("f\n");
                if (searchAcc(an, trant))
                {
                    char c;
                    printf("c=%c\n", fgetc(trant));
                    printf("No transection\n");
                }
                else
                {
                    char c;
                    while ((c = fgetc(trant)) != EOF)
                    {
                        // long int posi = ftell(trant);
                        // fseek(trant, posi - 1, SEEK_CUR);
                        fscanf(trant, "%c %d %d", passAcc.name, &passAcc.accNum, &passAcc.accBal);
                        // printf("c1=%c\n", fgetc(trant));
                        // fscanf(trant, "%d %d", &passAcc.accNum, &passAcc.accBal);
                        if (passAcc.accNum == an)
                        {
                            if (passAcc.name[0] == '-' || c == '-')
                            {
                                printf("Withdraw:\t");
                            }
                            else if (passAcc.name[0] == '+' || c == '+')
                            {
                                printf("Deposit:\t");
                            }
                            printf("%d %d\n", passAcc.accNum, passAcc.accBal);
                        }
                        c = fgetc(trant);
                        // if ((c = fgetc(trant)) == EOF)
                        // {
                        //     break;
                        // }
                    }
                }
            }
            fclose(acct);
            fclose(trant);
            t = lastMove();
            break;
        default:
            t = lastMove();
            break;
        }
        fclose(acct);
        fclose(trant);
    }

    return 0;
}
