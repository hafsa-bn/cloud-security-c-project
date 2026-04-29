#include <stdio.h>
#include <string.h>
#include <time.h>
/* COLORS */
#define PINK "\033[95m"
#define YELLOW "\033[93m"
#define CYAN "\033[96m"
#define GREEN "\033[92m"
#define RED "\033[91m"
#define RESET "\033[0m"
/* Binary alert decoration */
#define BINARY_FRAME
"011100001010110001010101110000001101011010100100101110001010010010010
    1010 "
    /* Global state for IDS */
    int ids_alert = 0;
/* Log function */
void addLog(const char *msg)
{
    FILE *f = fopen("security_logs.txt", "a");
    if (!f)
        return;
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    fprintf(f, "[%02d-%02d-%d %02d:%02d] %s\n",
            tm_info->tm_mday,
            tm_info->tm_mon + 1,
            tm_info->tm_year + 1900,
            tm_info->tm_hour,
            tm_info->tm_min,
            msg);
    fclose(f);
}
/* ================= PASSWORD CHECKER ================= */
void passwordChecker()
{
    char pass[100];
    int len, hasUpper = 0, hasLower = 0, hasNum = 0;
    printf(PINK "\nPASSWORD STRENGTH CHECKER\n" RESET);
    printf(YELLOW "Enter password: " RESET);
    fflush(stdout);
    scanf("%s", pass);
    len = strlen(pass);
    for (int i = 0; i < len; i++)
    {
        if (pass[i] >= 'A' && pass[i] <= 'Z')
            hasUpper = 1;
        else if (pass[i] >= 'a' && pass[i] <= 'z')
            hasLower = 1;
        else if (pass[i] >= '0' && pass[i] <= '9')
            hasNum = 1;
    }
    int score = 0;
    if (len >= 8)
        score++;
    if (hasUpper)
        score++;
    if (hasLower)
        score++;
    if (hasNum)
        score++;
    if (score == 1)
    {
        printf(RED "[WEAK] Password\n" RESET);
    }
    else if (score == 2)
    {
        printf(YELLOW "[MEDIUM] Password\n" RESET);
    }
    else if (score == 3)
    {
        printf(GREEN "[STRONG] Password\n" RESET);
    }
    else
    {
        printf(GREEN "[VERY STRONG] Password\n" RESET);
    }
    printf(PINK "Suggestions: " RESET);
    if (len < 8)
        printf("add length ");
    if (!hasUpper)
        printf("add uppercase ");
    if (!hasLower)
        printf("add lowercase ");
    if (!hasNum)
        printf("add numbers ");
    printf("\n");
    addLog("Password strength checked");
}
/* ================= ENCRYPTION ================= */
void encryptText()
{
    char text[200];
    int key;
    printf(PINK "\nENCRYPTION TOOL\n" RESET);
    printf(YELLOW "Enter text: " RESET);
    fflush(stdout);
    getchar();
    fgets(text, sizeof(text), stdin);
    printf(YELLOW "Enter key number: " RESET);
    fflush(stdout);
    scanf("%d", &key);
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] != '\n')
            text[i] += key;
    }
    printf(GREEN "Encrypted text: %s\n" RESET, text);
    addLog("Text encrypted");
}
/* ================= LOGIN SYSTEM ================= */
int loginSystem()
{
    char pass[20];
    int attempts = 3;
    printf(PINK "\nLOGIN SYSTEM\n" RESET);
    while (attempts > 0)
    {
        printf(YELLOW "Enter password: " RESET);
        fflush(stdout);
        scanf("%s", pass);
        if (strcmp(pass, "Cywork") == 0)
        {
            printf(GREEN "Access granted\n" RESET);
            addLog("Login success");
            return 1;
        }
        attempts--;
        printf(RED "Wrong password. Attempts left: %d\n" RESET, attempts);
    }
    ids_alert = 1;
    printf(RED "\n%s\n[ALERT] Too many login failures\n%s\n" RESET,
           BINARY_FRAME, BINARY_FRAME);
    addLog("IDS alert: login brute-force detected");
    return 0;
}
/* ================= IDS + FIREWALL ================= */
void idsFirewall()
{
    char ip[30];
    printf(PINK "\nIDS + FIREWALL\n" RESET);
    printf(YELLOW "Enter IP address: " RESET);
    fflush(stdout);
    scanf("%s", ip);
    if (strcmp(ip, "192.168.1.100") != 0 &&
        strcmp(ip, "10.0.0.99") != 0)
    {
        ids_alert = 1;
        printf(RED "\n%s\n" RESET, BINARY_FRAME);
        printf(RED "[IDS ALERT] Suspicious IP detected: %s\n" RESET, ip);
        printf(RED "%s\n" RESET, BINARY_FRAME);
        printf(RED "[FIREWALL] Access BLOCKED\n" RESET);
        addLog("IDS alert + Firewall block (unauthorized IP)");
    }
    else
    {
        printf(GREEN "[IDS] Normal activity\n" RESET);
        printf(GREEN "[FIREWALL] Access allowed\n" RESET);
        addLog("IDS normal + Firewall allowed access");
    }
}
/* ================= VIEW LOGS ================= */
void viewLogs()
{
    FILE *f = fopen("security_logs.txt", "r");
    char line[300];
    printf(PINK "\nSECURITY SUMMARY\n" RESET);
    if (!f)
    {
        printf("No logs yet.\n");
        return;
    }
    while (fgets(line, sizeof(line), f))
    {
        printf(YELLOW "%s" RESET, line);
    }
    fclose(f);
}
/* ================= MAIN MENU ================= */
int main()
{
    int choice;
    while (1)
    {
        printf(CYAN "\n========== SECURITY SYSTEM ==========\n" RESET);
        printf("1) Password Strength Check\n");
        printf("2) Encrypt Text\n");
        printf("3) Login System\n");
        printf("4) IDS + Firewall\n");
        printf("5) View Security Logs\n");
        printf("6) Exit\n");
        printf(YELLOW "Choose option: " RESET);
        fflush(stdout);
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            passwordChecker();
            break;
        case 2:
            encryptText();
            break;
        case 3:
            loginSystem();
            break;
        case 4:
            idsFirewall();
            break;
        case 5:
            viewLogs();
            break;
        case 6:
            printf(GREEN "Session ended. Stay secure.\n" RESET);
            return 0;
        default:
            printf(RED "Invalid option\n" RESET);
        }
    }
}
