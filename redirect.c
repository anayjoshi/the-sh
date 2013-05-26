#include"cmd.h"
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>

void is_redirect(Command cmd,int* fd_in,int* fd_out,int *npipes )
{
struct arg* c = cmd;
struct arg* d = NULL;
int flag = 0;
	
	while(c->next!=NULL) {
		if(!strcmp(c->next->string,">")) {
			if(c->next->next!=NULL){
			*fd_out = open(c->next->next->string,O_WRONLY|O_CREAT,0666);
				if(flag==0) {
				d = c;
				flag = 1;
				}				
			}
			else {
			printf("jash: syntax error\n");
			}
		}
		if(!strcmp(c->next->string,"<")) {
			if(c->next->next!=NULL){
			*fd_in = open(c->next->next->string,O_RDONLY|O_CREAT,0666);		
				if(flag==0) {
				d = c;
				flag = 1;
				}
			}
			else {
			printf("jash: syntax error\n");
			}
		}
		if(!strcmp(c->string,"|")) {
		*npipes = *npipes+1;
		}
	c = c->next;	
	}
	if(d!=NULL){
	d->next = NULL;
	}
		
}