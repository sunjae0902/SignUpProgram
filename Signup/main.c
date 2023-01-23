//
//  main.c
//  Signup
//
//  Created by SUNJAE on 2023/01/23.
//
#include "Header.h"

int main(void) {
   LOGIN lgUser; //사용자의 로그인 정보를 기록할 구조체
    int temp,endinput=0;
    int num,num2; //로그인에 성공한 사용자의 계정 정보
    FILE *lgf=fopen(LGFNAME, "a+");
    int lgusercnt=GetTotalLine(lgf); //hnguser.txt 파일의 행 수(로그인 정보가 있는 사용자의 수)
    
   //로그인 및 회원가입
    printf("====  << Creating Account and Sign in!>>  ====\n\n");
    printf("1. 로그인 하기\n2. 새로 등록하기\n"); scanf("%d",&temp);
    char *input_id=(char *)malloc(16); char *input_pwd=(char *)malloc(6);
    while(temp!=3){
        switch(temp){
            case 2: //회원가입
                if(NewUser(lgusercnt,lgUser)==0){
                    lgusercnt++;
                    temp=1;
                    break;}
                else{
                    temp=3;
                    break;
                }
                
            case 1: //로그인
                printf("로그인 ID를 입력하세요: "); scanf("%s",input_id);
                num=ExistsId(input_id);
                
                if (num==-1){ //id가 존재하지 않음
                    printf("사용자의 ID를 찾을 수 없음.\n1. 새로 등록하기\n3. 종료하기\n"); scanf("%d",&temp);
                    if (temp==1) NewUser(lgusercnt,lgUser); //회원가입
                    else {
                        printf("게임을 종료합니다 . . .");
                        return 0;}
                }
                else{  //id가 존재함
                    do {
                        printf("PASSWORD를 입력하세요 (종료하려면 -1입력): "); scanf("%s",input_pwd);
                        if (strcmp(input_pwd,"-1")==0) {
                            endinput=1; break;
                        }
                        num2=CheckPwd(input_pwd,num);
                    } while(num2==-1);
                    free(input_pwd);
                    temp=3; //로그인 성공
                }
                break;
        }
    }
    fclose(lgf);
    
    return 0;}
    

