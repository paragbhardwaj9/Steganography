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

int main() {
	int choice;
	a:
	printf("\n\n\t\t\tSteganography");
	printf("\n\t\t1) Encrypt Image");
	printf("\n\t\t2) Decrypt Image");
	printf("\n\t\t3) Exit");
	printf("\n\n\t\tYour choice: ");
	scanf("%d",&choice);
	switch(choice) {
		case 1:{
			FILE *image;
        		FILE *stego_image;
        		FILE *text_file;
        		char output[20],input[20],text[20];
        		int i;
        		printf("Enter the Input Image :");
        		scanf("%s",&input);
        		//char input[20] = "marbles.bmp";
        		printf("Enter the name of the output Image :");
        		scanf("%s",&output);
	
        		printf("Enter the name of the text file :");
        		scanf("%s",&text);
        		//char text[20] = "text.txt";
        		image=fopen(input,"r");
        		if (image == NULL) {
                		printf("Can't open input file\n");
                		exit(1);
        		}
			stego_image=fopen(output,"w");
        		if (stego_image== NULL) {
                		printf("Cannot create output file\n");
                		exit(1);
        		}

        		text_file = fopen(text,"r");
        		if (text_file== NULL) {
                		printf("Cannot open text file \n");
                		exit(1);
        		}

			char data,data_text,data1;
		        long data_text_bin,data_image_bin;
		        int temp,len;
			long cnt=0;
		        char tmp_sig_cpy;
		        int offset=get_offset(image);
			long text_len=0;
		        rewind(image);

			fseek(text_file,0,SEEK_END);
			text_len = ftell(text_file);
			//printf("text len =%ld ",text_len);
			rewind(text_file);

	       		for(i=0;i<offset;i++) {
        		        tmp_sig_cpy=fgetc(image);
        		        fputc(tmp_sig_cpy,stego_image);
        		}
			
			int flag=0;
			//fputc((char)(text_len),stego_image);
			//printf("Back :%c",(char)(text_len));
			do {
		                if(!feof(text_file)) {
					if(flag==0) {
						data_text = (char)(text_len);
						flag = 1;
					}
					else {
        	        	        	data_text = fgetc(text_file);
        	        	        }
					data_text_bin = binary(data_text);
        	        	        for(i=0;i<8;i++) {
                		                data = fgetc(image);
                		                data1 = data;
                		                data_image_bin = binary(data);
                		                temp = data_text_bin % 10;
                		                data_text_bin /= 10;
                		                data_image_bin = data_image_bin / 10;
                		                data_image_bin = (data_image_bin * 10) + temp;
                		                data = decimal(data_image_bin);
                		                fputc(data,stego_image);
                		        }
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
		case 2:{
			FILE *image;
		        FILE *text_file;
        		int x,i;
			char input[20],output[20];
        		printf("Enter the input image : ");
			scanf("%s",&input);
			image = fopen(input,"r");
        		if( image == NULL ) {
                		printf("Image didn't open");
                		exit(1);
        		}
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
			long len;
			int text_len=0;
			for(i=0;i<8;i++) {
				ch = fgetc(image);
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
			//printf("laaaaaal :%d",text_len);
			temp =0;
			data = 0;
			for(i=1;i<=(text_len*8)-8;i++) {
                		ch = fgetc(image);
                		image_bin = binary(ch);
                		temp = image_bin % 10;
                		data = data * 10 + temp;
                		if(temp == 0 && data == 0) {
                        		cnt++;
                		}
                		//printf("temp :%d\tdata:%ld\n",temp,data);
                		if(i%8 == 0) {
                		        //printf("cnt :%d\n",cnt);
                		        //printf("%ld\n",data);
                		        lol = reverse(data);
                	       		//printf("%ld\n",lol);
                	        	if(cnt !=0) {
                	        	        lol = lol * power(10,cnt);
                	        	}
                	        	//printf("%ld\n",lol);
               		         	data = 0;
                	        	ch1 = (char)decimal(lol);
                	        	//printf("%c\n\n",ch1);
                	        	fputc(ch1,text_file);
                	        	cnt = 0;
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
