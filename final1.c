#include<stdio.h>
#include<stdlib.h>

int get_offset(FILE* image_offset) {
        fseek(image_offset,10,0);
        int offset;
        offset=(int)fgetc(image_offset);
        return offset;
}

long binary(char ch){
        long num = ch;
        long remainder = 0,base = 1,binary=0;
        while(num > 0)
        {
                remainder = num % 2;
                binary = binary + remainder * base;
                num = num / 2;
                base = base * 10;
        }
        //printf("%ld\n",binary);
        return binary;
}

long reverse(long temp) {
        long lol=0;
        while(temp>0) {
                lol = lol * 10 + (temp % 10);
                temp = temp / 10;
        }
        return lol;
}


int power(int x, unsigned int y) {
        if( y == 0)
                return 1;
        else if (y%2 == 0)
                return power(x, y/2)*power(x, y/2);
        else
                return x*power(x, y/2)*power(x, y/2);
}

int decimal(long bin) {
        int num=0,temp;
        for(int i=0;i<8;i++) {
                temp = bin % 10;
                bin = bin / 10;
                num = num + (temp * power(2,i));
        }
        return num;
}

int get_len(long bin) {
        int i;
        while(bin>0) {
                i++;
                bin = bin/10;
        }
        return i;
}

int length(char temp[20]) {
        int cnt = 0;
        for(int i=0;temp[i] != '\0'; i++) {
                cnt++;
        }
        return cnt;
}


int main() {
	a:
	//int choice;
	printf("\n\n\t\t\tSteganography");
	printf("\n\t\t1) Encrypt Image");
	printf("\n\t\t2) Decrypt Image");
	printf("\n\t\t3) Exit");
	printf("\n\n\t\tYour choice: ");
	int choice;
	scanf("%d",&choice);
	switch(choice) {
		case 1:
		{
			FILE *image,*stego_image,*text_file;
			char input[20],output[20],file[20],pass[20];
			printf("Enter the input image :");
			scanf("%s",&input);
			//input = "marbles.bmp";
			printf("Enter the output image :");
			scanf("%s",&output);
			//output[] = "ghanta.bmp";
			printf("Enter the text file :");
			scanf("%s",&file); 
			//file[] = "text.txt";
			printf("Enter the password :");
			scanf("%s",&pass);
			image = fopen(input,"r");
			if(image == NULL) {
				printf("The image didn't open");
			}
			stego_image = fopen(output,"w");
		        if(stego_image == NULL) {
		                printf("The output image didn't open");
		        }
			text_file = fopen(file,"r");
		        if(text_file == NULL) {
		                printf("The text file didn't open");
		        }
		
			 char data,data_text,data1;
		       	 long data_text_bin,data_image_bin;
		         int temp,len,flag=0;
		         long cnt=0;
		         char tmp_sig_cpy;
		         int offset=get_offset(image);
		         long text_len=0,start= 0 ;
		         rewind(image);
	
	
			fseek(text_file,0,SEEK_END);
		        text_len = ftell(text_file);
		        //printf("text len =%ld ",text_len);
		        rewind(text_file);
		
		        for(int i=0;i<offset;i++) {
		                tmp_sig_cpy=fgetc(image);
		                fputc(tmp_sig_cpy,stego_image);
		        }
			
			//rewind(image);
			int ij = 0,temp1 = 0;
			/*for(int j=0;j<length(pass);j++) {
				temp1 = pass[j];
				printf("%d\n",temp1);
			}*/
			int back = 0;
			//printf("%d",length(pass));
			do {
			        if(!feof(text_file)) {
				//printf("\npehla if");
			                if(flag==0) {
						//printf("\ndusra if");
			                        data_text = (char)(text_len);
		                                //printf("\n%c",data_text);
						flag = 1;
		                        	
						/*if(pass[ij] == '\0') {
		                    	        	ij = 0 ;
		                        	}
		                        	temp1 = (int)pass[ij];
		                        	for(int x =0;x<temp1;x++) {
		                        	        data = fgetc(image);
		                        	        fputc(data,stego_image);
		                        	}*/
					}
		                        else {
			                        data_text = fgetc(text_file);
						//printf("\n\n%c",data_text);
		                  	        if(pass[ij] == '\0') {
		                        	        ij = 0 ;
		                        	}
		                        	temp1 = (int)pass[ij];
						start = ftell(image);
						//printf("\nstart:%ld,,,,,,,temp1:%d",start,temp1);
		                        	for(int x =0;x<temp1;x++) {
		                        	        data = fgetc(image);
		                        	        fputc(data,stego_image);
		                        	}
						start = ftell(image);
		                		//printf("\nend: %ld",start);
						ij++;
					}
		                        data_text_bin = binary(data_text);
					//printf("\n%ld",data_text_bin);
					
					for(int i=0;i<8;i++) {
		                                data = fgetc(image);
		                                data1 = data;
						start = ftell(image);
		//printf("\n%ld",start);
		                                data_image_bin = binary(data);
		//printf("\n%ld\t",data_image_bin);
		                                temp = data_text_bin % 10;
		                                data_text_bin /= 10;
		//cnt++;
		                                data_image_bin = data_image_bin / 10;
		                                data_image_bin = (data_image_bin * 10) + temp;
		//printf("\n%ld",data_image_bin);
		                                data = decimal(data_image_bin);
		                                fputc(data,stego_image);
		//printf("\n\n\n");
		                        }
		
					/*
					for(int i=0;i<8;i++) {
		                                data = fgetc(image);
		                                printf("\n%ld",data);
						data1 = data;
		                                data_image_bin = binary(data);
		                                printf("\n%ld",data_image_bin);
						temp = data_text_bin % 10;
		                                data_text_bin /= 10;
		                                data_image_bin = data_image_bin / 10;
		                                data_image_bin = (data_image_bin * 10) + temp;
		                                printf("\n%ld",data_image_bin);
						data = decimal(data_image_bin);
		                                fputc(data,stego_image);
		                        }*/
					//fseek(image,-temp1,SEEK_CUR);
				}
		                else {
		                        data=fgetc(image);
		                        fputc(data,stego_image);
		                }
		        } while(!feof(image));
		        fclose(image);
		        fclose(stego_image);
			break;
		}	//---------------------------------------------------------//
		case 2:
		{
			FILE *image;
		        FILE *text_file;
        		int x,i;
        		char input[20],output[20],pass[20];
        		printf("Enter the input image : ");
        		scanf("%s",&input);
        		image = fopen(input,"r");
        		if( image == NULL ) {
        		        printf("Image didn't open");
        			        exit(1);
        		}
        		printf("Enter the password :");
		        scanf("%s",&pass);
		        printf("Enter the output file: ");
		        scanf("%s",&output);
		        text_file = fopen(output,"w");
		        fgetc(image);
		        x = ftell(image);
		        int offset,cnt=0;
		        offset = get_offset(image);
		        fseek(image,offset,0);
		        int temp;
		        unsigned long image_bin,data=0,lol;
		        char ch,ch1;
		
		        long len,start = 0;
		        int text_len=0;
		        for(i=0;i<8;i++) {
				ch = fgetc(image);
		       		start = ftell(image);
				//printf("\n%ld",start);
				image_bin = binary(ch);
		                temp = image_bin % 10;
		                data = data * 10 + temp;
		                if(temp == 0 && data == 0) {
		                	cnt++;
		                }
			}
		        len = reverse(data);
			if(cnt !=0) {
		        	len = len * power(10,cnt);
		        }
		        //printf("len :%ld",len);
		        text_len = decimal(len);
		        //printf("\nlaaaaaal :%d",text_len);
		        temp =0;
		        data = 0;
			
			start = ftell(image);
		        //printf("\nghanta :%ld",start);
			//fseek(image,6,SEEK_CUR);
			int ij = 0,xf,temp1 = 0,ab = 0;
			cnt = 0;
			for(i=1;i<=(text_len*8)-8;i++) {
		        	//ch = fgetc(image);
				
				if(pass[ij] == '\0') {
		                        ij = 0 ;
		                }
		                temp1 = (int)pass[ij];
				//ij++;
				//printf("\ntemp1: %d,,,,,,ij : %d",temp1,ij);
		                if(ab==0) {
					for(xf=0;xf<temp1;xf++) {
						fgetc(image);
					}
					ab = 1;
				}
					ch = fgetc(image);
				start = ftell(image);
				//printf("\n%ld",start);
				image_bin = binary(ch);
		                temp = image_bin % 10;
		                data = data * 10 + temp;
		                if(temp == 0 && data == 0) {
		                	cnt++;
		                }
		                //printf("\ntemp :%d\tdata:%ld",temp,data);
		                if(i%8 == 0) {
					start = ftell(image);
					//printf("\nif ke andar start :%ld",start);
		                	//printf("cnt :%d\n",cnt);
		                        //printf("%ld\n",data);
		                        lol = reverse(data);
		                        //printf("%ld\n",lol);
		                        if(cnt !=0) {
		                	        lol = lol * power(10,cnt);
		                        }
		                        ///printf("lol: %ld\n",lol);
		                        data = 0;
		                        ch1 = (char)decimal(lol);
		                        //printf("%c\n\n",ch1);
		                        fputc(ch1,text_file);
		                        cnt = 0;
					ab = 0;
		                	ij++;
				}
			        //printf("%ld",data);
			}
			break;
		}
		case 3:
			printf("Thank You!!!");
			break;
		default: 
			printf("Wrong choice");
	}
	return 0;
}
