/*��¼Դ�����嵥��*/

#include<string.h>
#include<stdio.h>

#define   MAX 22             /*����}����������*/
#define   RES_MAX   10        /*�ؼ��ֵ���󳤶�*/
#define   MAXBUF 255         /*�������Ĵ�С*/

char ch = ' ';             /*��Ŷ��뵱ǰ�������ַ�*/
int Line_NO;                /*��¼�к�*/

struct keywords    /*�ؼ���*/
{
    char lexptr[MAXBUF];
    int token;
};
struct keywords symtable[MAX];
char str[MAX][10] = {"int", "char", "float", "main", "double", "case", "for", "if", "auto", "else", "do", "while",
                     "void", "static", "return", "break", "struct", "const", "union", "switch", "typedef", "enum"};

/*�Թؼ��ֱ���г�ʼ����div,mod,and,orҲ��Ϊ�ؼ��ִ���*/
/*��С��token��program��3������token��or��24*/
void init() {
    int j;
    for (j = 0; j < MAX; j++) {
        strcpy(symtable[j].lexptr, str[j]);
        symtable[j].token = j + 3;
    }
}

/***************�Թؼ��ֽ�������**************/
int Iskeyword(char *is_res) {
    int i;
    for (i = 0; i < MAX; i++) {
        if ((strcmp(symtable[i].lexptr, is_res)) == 0) break;
    }
    if (i < MAX) return symtable[i].token;
    else return 0;
}

/*****************�ж��Ƿ�Ϊ��ĸ*****************/
int IsLetter(char c) {
    if (((c <= 'z') && (c >= 'a')) || ((c <= 'Z') && (c >= 'A'))) return 1;
    else return 0;
}

/*************�ж��Ƿ�Ϊ����**************/
int IsDigit(char c) {
    if (c >= '0' && c <= '9') return 1;
    else return 0;
}

/***************��������**************/
void analyse(FILE *fpin, FILE *fpout) {
    /* ���뻺���������һ�����ʷ��� */
    char arr[MAXBUF];
    int j = 0;
    while ((ch = fgetc(fpin)) != EOF) {
        /*�����ո�tab������*/
        if (ch == ' ' || ch == '\t') {}
        else if (ch == '\n') { Line_NO++; }
/*********************�ַ����Ĵ���*************************/
        else if (IsLetter(ch)) {
            while (IsLetter(ch) | IsDigit(ch) | ch == '_') {
                if ((ch <= 'Z') && (ch >= 'A'))
                    ch = ch + 32;   /*���Դ�Сд*/
                arr[j] = ch;
                j++;
                ch = fgetc(fpin);
            }
            /*����ָ�����һ���ַ�*/
            fseek(fpin, -1L, SEEK_CUR);
            arr[j] = '\0';
            j = 0;
            if (Iskeyword(arr)) {   /*����ǹؼ���*/
                fprintf(fpout, "%s\t\t%d\t\t�ؼ���\n", arr, Iskeyword(arr));
            } else
                fprintf(fpout, "%s\t\t%d\t\t��ʶ��\n", arr, 1); /*��ͨ��ʶ��*/
/*************************���ֵĴ���****************************/
        } else if (IsDigit(ch)) {
            int s = 0;
            while (IsDigit(ch) | IsLetter(ch)) {
                if (IsLetter(ch)) {
                    arr[j] = ch;
                    j++;
                    ch = fgetc(fpin);
                    s = 1;
                } else if (IsDigit(ch)) {
                    arr[j] = ch;
                    j++;
                    ch = fgetc(fpin);
                }
            }
            fseek(fpin, -1L, SEEK_CUR);
            arr[j] = '\0';
            j = 0;
            if (s == 0)
                fprintf(fpout, "%s\t\t%d\t\t�޷�������\n", arr, 2);
            else if (s == 1)
                fprintf(fpout, "%s\t\t%d\t\t����\n", arr, 3);
        } else
            switch (ch) {
                case '+' :
                    ch = fgetc(fpin);
                    if (ch == '+') {
                        fprintf(fpout, "%s\t\t%d\t\t�Լ������\n", "++", 41);
                        break;
                    } else if (ch == '=') {
                        fprintf(fpout, "%s\t\t%d\t\t�����\n", "+=", 42);
                        break;
                    } else
                        fseek(fpin, -1L, SEEK_CUR);
                    fprintf(fpout, "%s\t\t%d\t\t�����\n", "+", 43);
                    break;
                case '-' :
                    ch = fgetc(fpin);
                    if (ch == '-') {
                        fprintf(fpout, "%s\t\t%d\t\t�Լ������\n", "--", 44);
                        break;
                    } else if (ch == '=') {
                        fprintf(fpout, "%s\t\t%d\t\t�����\n", "-=", 45);
                        break;
                    } else
                        fseek(fpin, -1L, SEEK_CUR);
                    fprintf(fpout, "%s\t\t%d\t\t�����\n", "-", 46);
                    break;
                case '*' :
                    fprintf(fpout, "%s\t\t%d\t\t�����\n", "*", 47);
                    break;
                case '(' :
                    fprintf(fpout, "%s\t\t%d\t\t�ֽ��\n", "(", 25);
                    break;
                case ')' :
                    fprintf(fpout, "%s\t\t%d\t\t�ֽ��\n", ")", 26);
                    break;
                case '[' :
                    fprintf(fpout, "%s\t\t%d\t\t�ֽ��\n", "[", 27);
                    break;
                case ']' :
                    fprintf(fpout, "%s\t\t%d\t\t�ֽ��\n", "]", 28);
                    break;
                case ';' :
                    fprintf(fpout, "%s\t\t%d\t\t�ֽ��\n", ";", 29);
                    break;
                case '=' :
                    fprintf(fpout, "%s\t\t%d\t\t�����\n", "=", 48);
                    break;
                case '.' :
                    fprintf(fpout, "%s\t\t%d\t\t�ֽ��\n", ".", 30);
                    break;
                case ',' :
                    fprintf(fpout, "%s\t\t%d\t\t�ֽ��\n", ",", 31);
                    break;
                case ':' :
                    fprintf(fpout, "%s\t\t%d\t\t�ֽ��\n", ":", 32);
                    break;
                case '{' :
                    fprintf(fpout, "%s\t\t%d\t\t�ֽ��\n", "{", 33);
                    break;
                case '}' :
                    fprintf(fpout, "%s\t\t%d\t\t�ֽ��\n", "}", 34);
                    break;
                case '%' :
                    fprintf(fpout, "%s\t\t%d\t\t�ֽ��\n", "%", 35);
                    break;
                case '\"' :
                    fprintf(fpout, "%s\t\t%d\t\t�ֽ��\n", "\"", 36);
                    break;
                case '\\' :
                    fprintf(fpout, "%s\t\t%d\t\t�ֽ��\n", "\\", 37);
                    break;
                case '#' :
                    fprintf(fpout, "%s\t\t%d\t\t�ֽ��\n", "#", 38);
                    break;
                case '>' : {
                    ch = fgetc(fpin);
                    if (ch == '=')
                        fprintf(fpout, "%s\t\t%d\t\t�����\n", ">=", 49);
                    else {
                        fprintf(fpout, "%s\t\t%d\t\t�����\n", ">", 50);
                        fseek(fpin, -1L, SEEK_CUR);
                    }
                }
                    break;

                case '<' : {
                    ch = fgetc(fpin);
                    if (ch == '=')
                        fprintf(fpout, "%s\t\t%d\t\t�����\n", "<=", 51);
                    else if (ch == '>')
                        fprintf(fpout, "%s\t\t%d\n", "<>", 52);
                    else {
                        fprintf(fpout, "%s\t\t%d\t\t�����\n", "<", 53);
                        fseek(fpin, -1L, SEEK_CUR);
                    }
                }
                    break;
                    /***************������/  /֮���ȫ����Ϊע�Ͳ��ִ���*******************/
                case '/' : {
                    ch = fgetc(fpin);
                    if (ch == '/') {
                        while (ch != '\n') {
                            ch = fgetc(fpin);
                        }
                    } else if (ch == '*') {
                        while (ch != '/' && ch != EOF) {
                            ch = fgetc(fpin);
                        }
                        if (ch == EOF)
                            fprintf(fpout, "ȱ��һ��'/'");
                    } else {
                        fprintf(fpout, "%s\t\t%d\t\t�����\n", "/", 39);
                        fseek(fpin, -1L, SEEK_CUR);
                    }
                    break;
                }
                    /***************�Ƿ��ַ�*******************/
                default :
                    fprintf(fpout, "�ڵ�%d���޷�ʶ����ַ�\t%c\n", Line_NO, ch);
            }
    }
}

/**********����������ɶ���������ļ��Ķ�д***********/
int main() {
    char in_fn[25], out_fn[25];
    FILE *fpin, *fpout;
    printf("<<<<<<<<<<<<<<<<<<WELCOME>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("..............�ʷ���������ʵ��......................\n");
    printf("\n");
    printf(".....Ŀǰ���дʷ���������   1��   \n");
    printf(".....������1��data.txt \n");
    printf(".....����һ�����еĳ���:\n");
    scanf("%s", in_fn);
    printf(".....��������Ҫ���������Ŀ���ļ���:\n");
    scanf("%s", out_fn);
    fpin = fopen(in_fn, "r");
    fpout = fopen(out_fn, "w");
    fprintf(fpout, "���ʷ�\t\t�������\t\t����\n");
    init();
    analyse(fpin, fpout);
    fclose(fpin);
    fclose(fpout);
    printf(".....�����ѷ�����ɷ�����������Ŀ���ļ�\n");
    printf("........<ллʹ��>......\n");
    return 0;
}

