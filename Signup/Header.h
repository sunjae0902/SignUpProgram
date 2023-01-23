//
//  Header.h
//  Signup
//
//  Created by SUNJAE on 2023/01/23.
//

#ifndef Header_h
#define Header_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //Sleep()사용
#define MAX_USER 10000 //최대 사용자 수
#define LGFNAME "/Users/sunjae/Mygit/Signup/Signup/user.txt"

typedef struct{ //등록된 사용자의 정보를 user.txt 파일에 기록하기 위한 구조체
    char id[16]; //id: 영문자,숫자 포함 최대 15자리
    char pwd[6]; //password 숫자 최대 5자리
}LOGIN;

// 로그인 및 회원가입 프로그램 함수
int ExistsId(char *);

int NewUser(int usercnt,LOGIN User){
    FILE *f=fopen(LGFNAME, "a+");
    if (f!=NULL){
        do{
            printf("ID를 입력하세요(영어,숫자 포함 15자리 이내): "); scanf("%s",User.id);
            if (ExistsId(User.id)!=-1) printf("이미 존재하는 Id입니다.\n");
        }while(ExistsId(User.id)!=-1);
        printf("PASSWORD를 입력하세요(숫자 5자리 이내): "); scanf("%s",User.pwd);
        fprintf(f,"%s %s\n", User.id, User.pwd); //파일에 구조체 내용 쓰기
        fclose(f);
        usercnt++;
        printf("\n회원가입 완료!.\n");
        return 0;
    }
    else {
        printf("파일 열기 실패\n");
        return -1; //파일 열기 실패
    }
}


int GetTotalLine(FILE *f){ // 파일의 행의 개수를 구하는 함수. 파일 열기 에러 처리 완료
    if (f!=NULL){
        int line=0; char c;
        while((c=fgetc(f))!=EOF)
            if(c=='\n') line++;
        fclose(f);
        return line;
    }
    return -1; //파일 열기 실패
}

int GetletterinOneline(int line){ //파일 내 특정 행의 공백 포함 글자 수를 구하는 함수. 파일 열기 에러 처리 완료
    FILE *f=fopen(LGFNAME, "r");
    if (f!=NULL){
        int count1=0; char buffer[23];
        
        while(fgets(buffer,23,f)!=NULL){
            count1++;
            if (count1==line) break;
        }
        fclose(f);
        return (int) strlen(buffer);
    }
    return -1; //파일 열기 실패
}


int ExistsId(char *input){ // 입력받은 id가 user파일에 존재하는지 검사하는 함수 (없다면 -1반환)
    FILE *f=fopen(LGFNAME, "r");
    char buffer[25]; char *buffer2;
    int i=1;
    int letters=GetletterinOneline(i);
    if (f!=NULL){
        while (fgets(buffer,letters+2, f)!=NULL) {
            buffer2=strtok(buffer," ");
            if (strcmp(buffer2,input)==0) {
                fclose(f);
                return i;}
            else{
                ++i;
                letters=GetletterinOneline(i);
                }
         }
        return -1;
    }
    else printf("파일 열기 실패\n"); return -100;
    }

 


int CheckPwd(char *input,int line){ // 입력이 user파일에서 특정 id와 매칭되는 패스워드와 일치하는지 검사하는 함수 (일치하지 않는다면 -1반환)
    FILE *f=fopen(LGFNAME, "r");
    char *buffer=malloc(25);
    int i=1;
    int letters=GetletterinOneline(i);
    
    while(fgets(buffer,letters+2,f)!=NULL){
        letters=GetletterinOneline(i);
        if (i==line) break;
        i++;
    } //line번째 행에 도달할때까지 각 행을 buffer에 저장함.
    buffer[strlen(buffer)-1]='\0'; //개행문자 제거

    char *pwd=strtok(buffer," "); //strtok: 문자열 분리 함수," "를 기준으로 (id/pwd)를 구분함
    buffer=pwd;
    pwd=strtok(NULL," "); //pwd 문자열이 마지막 토큰이 되고 해당 문자열의 주소를 리턴함
    if(strcmp(pwd,input)==0){
        printf("< %s >님, 반가워요!!\n (loading. .)\n\n",buffer); //login success
        free(buffer);
        sleep(1);
        return line;  //로그인 한 회원의 정보가 저장된 line 리턴
    }
    fclose(f);
    return -1; //불일치
}



#endif /* Header_h */
