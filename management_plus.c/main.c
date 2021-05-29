#define _CRT_SECURE_NO_WARNINGS ////추가

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> ////추가

void menu();
void read1(); ////이름 변경
int input();

int view();
void viewAll();
void viewName(char* queryName);

int edit();
void editName(int j);

int delete();
void deleteName(int j);

void newMGT();

struct S {
    char name[20];  //이름
    char dept[20];   //부서
    char telno[15];  //전화번호
    int age;           //나이
    char addr[100];   //주소
};

int cntTot = 0;

struct S data[300];  // 회원수 300명 제한.
FILE* fp;

int main()
{
    while (1)
    {
        menu();
    }

    return 0;

}

void menu()
{

    int i = 0;

    do {

        system("cls");
        printf("\n\n\n\t1) 회원정보 등록\n");
        printf("\t2) 회원정보 조회\n");
        printf("\t3) 회원정보 수정\n");
        printf("\t4) 회원정보 삭제\n");
        printf("\t5) 분석\n");
        printf("\t6) 종료\n");
        printf("\n\n\t메뉴를 입력하세요 : ");
        scanf("%d", &i);

    } while (i < 1 || i > 6);

    switch (i) {

    case 1:
        while (input()) {}    // 한 줄로 표현.  0 리턴 시 while 문 빠져나감.
        break;
    case 2:
        while (view()) {}
        break;
    case 3:
        while (edit()) {}
        break;
    case 4:
        while (delete()) {}
        break;
    case 5:
        newMGT();
        break;
    case 6:
        exit(0);
    }

    return;
}



int input() {

    struct S data;
    //fp = fopen("info.dat", "ab+");
    fp = fopen("info.txt", "a+");

    if (fp == NULL) {
        printf("file open error. \n");
        exit(0);
    }


    printf("\n\n\n\t이름 (종료: end) : ");
    scanf("%s", data.name);

    if (!strcmp(data.name, "end"))
    {
        return 0;  // 종료 숫자
    }


    printf("\t부서 : ");
    scanf("%*c%s", data.dept);   // %*c  : 한 문자(\n)를 무시한다.

    printf("\t전화번호 : ");
    scanf("%*c%s", data.telno);

    printf("\t나이 : ");
    scanf("%*c%d", &data.age);

    printf("\t주소 : ");
    scanf("%*c%[^\n]", data.addr); // "%[^\n]" or "%[^\n]s" : new line 이전의 모든 문자.
    scanf("%*c");    // %*c  : 한 문자(\n)를 무시한다.


    fprintf(fp, "%20s %20s %15s %5d %100s\n", data.name, data.dept, data.telno, data.age, data.addr);

    fclose(fp);

    printf("\n\n\t1 레코드 입력이 완료되었습니다. (엔터)");

    getc(stdin);

    return 1; //  1 리턴 : while 루프 계속 돌리기 위한 숫자.

}


int view() {

    int choice = 0;

    printf("\n\n\n\t조회 방법을 선택하세요 (1 : 전체조회,  2 : 이름조회,  3. 종료) : ");
    scanf("%d", &choice);

    if (choice == 3)
    {
        return 0;  // 0 : while 루프 종료하기 위한 숫자
    }


    if (choice == 1)
    {
        viewAll();
    }

    else if (choice == 2)
    {
        char queryName[20];
        printf("\n\n\n\t조회할 회원이름을 입력하세요 (종료: end) : ");
        scanf("%s", queryName);

        if (!strcmp(queryName, "end"))
        {
            return 0;  // 0 : while 루프 종료하기 위한 숫자
        }

        viewName(queryName);
    }


    return 1;
}


void viewAll() {


    read1();

    for (int j = 0; j < cntTot; ++j)
    {
        printf("%3d, ", j + 1);
        printf("%20s, ", data[j].name);
        printf("%20s, ", data[j].dept);
        printf("%15s, ", data[j].telno);
        printf("%5d, ", data[j].age);
        printf("%100s\n\n", data[j].addr);

    }

    printf("\n\n\t완료되었습니다. (엔터)");

    getc(stdin); getc(stdin);

    return;
}



void viewName(char* queryName) {

    read1();

    for (int j = 0; j < cntTot; ++j)
    {
        if (!strcmp(data[j].name, queryName))
        {
            // 일치하면 수행한다.
            printf("%20s, ", data[j].name);
            printf("%20s, ", data[j].dept);
            printf("%15s, ", data[j].telno);
            printf("%5d, ", data[j].age);
            printf("%100s\n\n", data[j].addr);

            // break;  동명 2인 이상일 경우 끝까지 수행한다.
        }
    }

    printf("\n\n\t완료되었습니다. (엔터)");

    getc(stdin); getc(stdin);

    return;
}


void read1()
{

    fp = fopen("info.txt", "r");

    if (fp == NULL) {
        printf("file open error. \n");
        exit(0);
    }

    cntTot = 0;
    int i = 0;
    while (fscanf(fp, "%20s %20s %15s %5d %[^\n]s",
        data[i].name, data[i].dept, data[i].telno, &data[i].age, data[i].addr) == 5) {

        ++cntTot;
        ++i;
    }

    fclose(fp);
}

int edit() {

    int choice = 0;
    char queryName[20];
    printf("\n\n\n\t수정할 회원이름을 입력하세요 (종료: end) : ");
    scanf("%s", queryName);

    if (!strcmp(queryName, "end"))
    {
        return 0;  // 종료 숫자
    }

    read1();

    for (int j = 0; j < cntTot; ++j)
    {
        if (!strcmp(data[j].name, queryName))  //  strcmp : 두 문자열이 일치하면 0을 리턴함.
        {
            // 일치하면 수행한다.
            printf("%3d", j + 1);
            printf("%20s, ", data[j].name);
            printf("%20s, ", data[j].dept);
            printf("%15s, ", data[j].telno);
            printf("%5d, ", data[j].age);
            printf("%100s\n\n", data[j].addr);

            printf("\n\n\t수정할 회원이 맞습니까? (1. 예,  2. 아니오. 3. 나가기) : ");
            scanf("%d", &choice);

            if (choice == 3)
            {
                return 0;  // 나가기 숫자
            }
            else if (choice == 1)
            {
                // j 번째 회원을 수정한다.   //
                editName(j);

                return 1;
            }

            // break;  동명 2인 이상일 경우 끝까지 수행한다.
        }

    }

    printf("\n\n\t수정을 원하는 회원이 존재하지 않습니다. (엔터)");

    getc(stdin); getc(stdin);


    return 1;
}

void editName(int find)
{

    struct S oneRecord;

    fp = fopen("info.txt", "r+");
    if (fp == NULL) {
        printf("file open error. \n");
        exit(0);
    }


    // 구조체에 수정 내용 넣기

    printf("\n\n\n\t수정할 이름 (종료: end) : ");
    scanf("%20s", oneRecord.name);

    if (!strcmp(oneRecord.name, "end"))
    {
        return;  // 종료 숫자
    }

    printf("\t수정할 부서 : ");
    scanf("%*c%20s", oneRecord.dept);

    printf("\t수정할 전화번호 : ");
    scanf("%*c%15s", oneRecord.telno);

    printf("\t수정할 나이 : ");
    scanf("%*c%5d", &oneRecord.age);


    printf("\t수정할 주소 : ");
    scanf("%*c%[^\n]", oneRecord.addr); // "%[^\n]" or "%[^\n]s" : new line 이전의 모든 문자.
    scanf("%*c");    // %*c  : 한 문자(\n)를 무시한다.


                     // 파일에서 위치 찾고 덮어쓰기
    fseek(fp, find * sizeof(struct S) + (find * 6), SEEK_SET); // 중간 공백 4개
    fprintf(fp, "%20s %20s %15s %5d %100s", oneRecord.name, oneRecord.dept, oneRecord.telno, oneRecord.age, oneRecord.addr);
    printf("\n\n\t수정 완료되었습니다. (엔터)");

    fclose(fp);

    return;
}


int delete() {

    int choice = 0;
    char queryName[20];
    printf("\n\n\n\t삭제할 회원이름을 입력하세요 (종료: end) : ");
    scanf("%s", queryName);

    if (!strcmp(queryName, "end"))
    {
        return 0;  // 종료 숫자
    }

    read1();

    for (int j = 0; j < cntTot; ++j)
    {
        if (!strcmp(data[j].name, queryName)) // strcmp 성공 시 0 리턴
        {
            // 일치하면 수행한다.
            printf("%3d", j + 1);
            printf("%20s, ", data[j].name);
            printf("%20s, ", data[j].dept);
            printf("%15s, ", data[j].telno);
            printf("%d, ", data[j].age);
            printf("%100s\n\n", data[j].addr);

            printf("\n\n\t삭제할 회원이 맞습니까? (1. 예,  2. 아니오. 3. 나가기) : ");
            scanf("%d", &choice);

            if (choice == 3)
            {
                return 0;  // 나가기 숫자
            }
            else if (choice == 1)
            {
                // j 번째 회원을 삭제한다.   //
                deleteName(j);

                return 1;
            }

            // break;  동명 2인 이상일 경우 끝까지 수행한다.
        }

    }

    printf("\n\n\t삭제를 원하는 회원이 존재하지 않습니다. (엔터)");

    getc(stdin); getc(stdin);


    return 1;

}


void deleteName(int find)
{
    fp = fopen("info.txt", "w");

    for (int k = 0; k < cntTot; ++k)
    {
        if (k != find)
        {
            fprintf(fp, "%20s %20s %15s %5d %100s\n", data[k].name, data[k].dept, data[k].telno, data[k].age, data[k].addr);
        }
    }


    printf("\n\n\t삭제 완료되었습니다. (엔터)");

    fclose(fp);

    getc(stdin); getc(stdin);

    return;
}

void newMGT()
{
    read1(); // info.txt에 입력된 
    system("cls");
    
    struct dept{
        int dept_cnt;
        char dept_name[100];
    };
    struct dept dept_find[300]={0}; // 사람 수를 300명 한정시켰기 때문에 각자 다른 부서수도 최대 300개이다.
                                    // 추가로 dept_find 안의 멤버를 모두 0으로 초기화한다.

    bool continueOuterLoop = false;
    int row = 0;
    
    for(int i=0;i<cntTot;i++)
    {
        for(int k=0;k<row;k++)
        {
            if(strcmp(dept_find[k].dept_name,data[i].dept)==0)
                continueOuterLoop = true;
        } // dept_find[k]에서 k=0 부터 k=row-1까지 탐색하며 멤버 dept_name과 data[i].dept 를 비교하여 서로 일치하면 continueOuterLoop을 TRUE로 변경, 즉 바깥 for문을 continue 한다.
        if(continueOuterLoop == true)
        {
            continueOuterLoop = false;
            continue;
        }
        
        strcpy(dept_find[row].dept_name,data[i].dept); // dept_find[row]에 data[i].dept값을 담아둔다.

        for(int j=i;j<cntTot;j++)
        {
            if(strcmp(dept_find[row].dept_name,data[j].dept)==0) // dept_find[row]에 담긴 문자열과 data[j].dept에 담긴 문자열이 일치하면 수행한다.
            {
                dept_find[row].dept_cnt++;
            }
            
        }
        row++; // 위에서 continue 되지 않았다면 row를 1만큼 증가시킨다. (일정하게 카운트하기 위해서)
    }
    printf("-----------------------------------------------------\n");
    printf("  총 회원수: %d\n", cntTot);
    printf("-----------------------------------------------------\n");
    
    for(int i=0; i<row; i++)
    {
        printf("%d. %s :      %d 명\n",i,dept_find[i].dept_name,dept_find[i].dept_cnt);
    }
    
    printf("-----------------------------------------------------\n\n\n");
    
    
    printf("-----------------------------------------------------\n");
    printf("  가로 막대 그래프\n");
    printf("-----------------------------------------------------\n\n\n");
    
    
    
    for(int i=0; i<row; i++)
    {
        printf("%d. %s :  ", i, dept_find[i].dept_name);
        for(int j=0;j<dept_find[i].dept_cnt;j++)
            printf("%c",'*');
        printf("\n");
    }
    
    printf("\n-----------------------------------------------------\n\n\n\n\n");

    
    printf("\t\t분석 완료되었습니다. (엔터)");

    getc(stdin);getc(stdin);
    
    return;
}
