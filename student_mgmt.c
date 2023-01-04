#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student
{
	int rno;
	char name[20];
	struct subject {
		int scode;
		char sname[20];
		float mark;
	}sub[3];
	float total;
	float perc;
};

void create();
void search();
void append();
void delete_rec();
void display();
void srt_name_on_screen();
void srt_name_in_file();
void srt_total_on_screen();
void srt_total_in_file();
int no_of_record();

int main()
{
	int ch;
	do {
		printf("\n\n****Student Management System****");
		printf("\n 1. CREATE");
		printf("\n 2. SEARCH");
		printf("\n 3. APPEND");
		printf("\n 4. DELETE");
		printf("\n 5. DISPLAY");
		printf("\n 6. SORT_BY_NAME_ON_SCREEN");
		printf("\n 7. SORT_BY_NAME_IN_FILE");
		printf("\n 8. SORT_BY_TOTAL_MARKS_ON_SCREEN");
		printf("\n 9. SORT_BY_TOTAL_MARKS_IN_FILE");
		printf("\n10. NO OF RECORDS");
		printf("\n11. EXIT");
		printf("\n\nEnter your choice: ");
		scanf("%d", &ch);
		switch(ch) {
			case 1:
				create();
				break;
			case 2:
				search();
				break;
			case 3:
				append();
				break;
			case 4:
				delete_rec();
				break;
			case 5:
				display();
				break;
			case 6:
				srt_name_on_screen();
				break;
			case 7:
				srt_name_in_file();
				break;
			case 8:
				srt_total_on_screen();
				break;
			case 9:
				srt_total_in_file();
				break;
			case 10:
				printf("\nNo of records: %d", no_of_record());
				break;
			case 11:
				break;
			default:
				printf("\nWrong Choice! Enter again.");
		}
	} while(ch != 11);
	
	return 0;
}

void create()
{
	struct student *s;
	int n, i, j;
	FILE *fp;
	
	fp = fopen("Students_Record.txt", "w");
	printf("\nEnter how many students you want: ");
	scanf("%d", &n);
	s = (struct student *)calloc(n, sizeof(struct student));
	
	for(i=0; i<n; i++) {
		s[i].total = 0;
		printf("\nEnter Student Record[%d]", i+1);
		printf("\nEnter roll no: ");
		scanf("%d", &s[i].rno);
		fflush(stdin);
		printf("\nEnter name: ");
		scanf("%[^\n]s", s[i].name);
		for(j=0; j<3; j++) {
		/*	printf("\nEnter Subject code: ");
			scanf("%d", &s[i].sub[j].scode);
			fflush(stdin);
			printf("\nEnter Subject Name: ");
			scanf("%[^\n]s", s[i].sub[j].sname);*/
			printf("\nEnter mark of subject %d: ", j+1);
			scanf("%f", &s[i].sub[j].mark);
			s[i].total += s[i].sub[j].mark;
		}
		s[i].perc = s[i].total / 3.0;
		fwrite(&s[i], sizeof(struct student), 1, fp);
	}
				
	printf("\nRecord created successfully.\n");
	fclose(fp);
	free(s);
}

void search()
{
	struct student s1;
	int rno, found = 0, j;
	FILE *fp = fopen("Students_Record.txt", "r");
	
	printf("\nEnter roll no to be searched: ");
	scanf("%d", &rno);
	while(fread(&s1, sizeof(struct student), 1, fp)) {
		if(s1.rno == rno) {
			found = 1;
			printf("\n%5d %-20s", s1.rno, s1.name);
			for(j=0; j<3; j++) {
				printf("%6.2f", s1.sub[j].mark);
			}
			printf("%8.2f%8.2f", s1.total, s1.perc);
		}
	}
	if(!found) 
		printf("\nRecord not found.");
	fclose(fp);
}

void append()
{	
	struct student *s;
	int n, i, j;
	FILE *fp;
	
	fp = fopen("Students_Record.txt", "a");
	printf("\nEnter how many new students you want: ");
	scanf("%d", &n);
	s = (struct student *)calloc(n, sizeof(struct student));
	for(i=0; i<n; i++) {
		s[i].total = 0;
		printf("\nEnter Student Record[%d]", i+1);
		printf("\nEnter roll no: ");
		scanf("%d", &s[i].rno);
		fflush(stdin);
		printf("\nEnter name: ");
		scanf("%[^\n]s", s[i].name);
		for(j=0; j<3; j++) {
		/*	printf("\nEnter Subject code: ");
			scanf("%d", &s[i].sub[j].scode);
			fflush(stdin);
			printf("\nEnter Subject Name: ");
			scanf("%[^\n]s", s[i].sub[j].sname);*/
			printf("\nEnter mark of subject %d: ", j+1);
			scanf("%f", &s[i].sub[j].mark);
			s[i].total += s[i].sub[j].mark;
		}
		s[i].perc = s[i].total / 3.0;
		fwrite(&s[i], sizeof(struct student), 1, fp);
	}
				
	printf("\nRecord appended successfully.\n");
	fclose(fp);
	free(s);
}

void delete_rec()
{
	struct student s1;
	int rno, found = 0, j;
	FILE *fp1, *fp2;
	fp1 = fopen("Students_Record.txt", "r");
	fp2 = fopen("Temp.txt", "w");
	
	printf("\nEnter roll no to be deleted: ");
	scanf("%d", &rno);
	while(fread(&s1, sizeof(struct student), 1, fp1)) {
		if(s1.rno == rno) {
			found = 1;
		}
		else {
			fwrite(&s1, sizeof(struct student), 1, fp2);
		}
	}
	
	fclose(fp1);
	fclose(fp2);
			
	if(found) {
		fp1 = fopen("Students_Record.txt", "w");
		fp2 = fopen("Temp.txt", "r");
		while(fread(&s1, sizeof(struct student), 1, fp2)) {
			fwrite(&s1, sizeof(struct student), 1, fp1);
		fclose(fp1);
		fclose(fp2);
		}
	}
	else {
		printf("\nRecord not found.");
	}

	remove("Temp.txt");
}

void display()
{
	struct student s1;
	int j;
	FILE *fp = fopen("Students_Record.txt", "r");
	
	if(ferror(fp)) {
		printf("\nFile does not exit.");
		return;
	}
	
	printf("\nRecords:\n");
	printf(" Roll      Name             Sub1  Sub2  Sub3  Total    %% \n");
	while(fread(&s1, sizeof(struct student), 1, fp)) {
		printf("\n%5d %-20s", s1.rno, s1.name);
		for(j=0; j<3; j++) {
			printf("%6.2f", s1.sub[j].mark);
		}
		printf("%8.2f%8.2f", s1.total, s1.perc);
	}
	
	fclose(fp);
}

int no_of_record()
{
	int n;
	FILE *fp;
	
	fp = fopen("Students_Record.txt", "r");
	fseek(fp, 0, SEEK_END);
	n = ftell(fp) / sizeof(struct student);
	fclose(fp);
	return n;
}

void srt_name_on_screen()
{
	struct student *s;
	int n, i, j, exchange;
	char ch[20];
	
	FILE *fp = fopen("Students_Record.txt", "r");
	n = no_of_record();
	
	s = (struct student *)calloc(n, sizeof(struct student));
	for(i=0; i<n; i++) {
		fread(&s[i], sizeof(struct student), 1, fp);
	}
	
	for(i=0; i<n-1; i++) {
		exchange = 0;
		for(j=0; j<n-1-i; j++) {
			if(strcmp(s[j].name, s[j+1].name) > 0) {
				strcpy(ch, s[j].name);
				strcpy(s[j].name, s[j+1].name);
				strcpy(s[j+1].name, ch);
				exchange=1;
			}
		}
		if(!exchange)	break;
	}
	printf(" Roll      Name             Sub1  Sub2  Sub3  Total    %% \n");
	for(i=0; i<n; i++) {
		printf("\n%5d %-20s", s[i].rno, s[i].name);
		for(j=0; j<3; j++) {
			printf("%6.2f", s[i].sub[j].mark);
		}
		printf("%8.2f%8.2f", s[i].total, s[i].perc);
	}		
	
	fclose(fp);
	free(s);
}

void srt_name_in_file()
{
	struct student *s;
	int n, i, j, exchange;
	char ch[20];
	
	FILE *fp = fopen("Students_Record.txt", "r");
	n = no_of_record();
	
	s = (struct student *)calloc(n, sizeof(struct student));
	for(i=0; i<n; i++) {
		fread(&s[i], sizeof(struct student), 1, fp);
	}
	
	for(i=0; i<n-1; i++) {
		exchange = 0;
		for(j=0; j<n-1-i; j++) {
			if(strcmp(s[j].name, s[j+1].name) > 0) {
				strcpy(ch, s[j].name);
				strcpy(s[j].name, s[j+1].name);
				strcpy(s[j+1].name, ch);
				exchange=1;
			}
		}
		if(!exchange)	break;
	}		
	fclose(fp);
	
	fp = fopen("Students_Record.txt", "w");
	for(i=0; i<n; i++)
		fwrite(&s[i], sizeof(struct student), 1, fp);
	fclose(fp);
	free(s);
}

void srt_total_on_screen()
{
	struct student *s, tmp;
	int n, i, j, exchange;
	
	FILE *fp = fopen("Students_Record.txt", "r");
	n = no_of_record();
	
	s = (struct student *)calloc(n, sizeof(struct student));
	for(i=0; i<n; i++) {
		fread(&s[i], sizeof(struct student), 1, fp);
	}
	
	for(i=0; i<n-1; i++) {
		exchange = 0;
		for(j=0; j<n-1-i; j++) {
			if(s[j].total < s[j+1].total) {
				tmp = s[j];
				s[j] = s[j+1];
				s[j+1] = tmp;
				exchange=1;
			}
		}
		if(!exchange)	break;
	}
	printf(" Roll      Name             Sub1  Sub2  Sub3  Total    %% \n");
	for(i=0; i<n; i++) {
		printf("\n%5d %-20s", s[i].rno, s[i].name);
		for(j=0; j<3; j++) {
			printf("%6.2f", s[i].sub[j].mark);
		}
		printf("%8.2f%8.2f", s[i].total, s[i].perc);
	}		
	
	fclose(fp);
	free(s);
}

void srt_total_in_file()
{
	struct student *s, tmp;
	int n, i, j, exchange;
	
	FILE *fp = fopen("Students_Record.txt", "r");
	n = no_of_record();
	
	s = (struct student *)calloc(n, sizeof(struct student));
	for(i=0; i<n; i++) {
		fread(&s[i], sizeof(struct student), 1, fp);
	}
	
	for(i=0; i<n-1; i++) {
		exchange = 0;
		for(j=0; j<n-1-i; j++) {
			if(s[j].total < s[j+1].total) {
				tmp = s[j];
				s[j] = s[j+1];
				s[j+1] = tmp;
				exchange=1;
			}
		}
		if(!exchange)	break;
	}
	fclose(fp);
	
	fp = fopen("Students_Record.txt", "w");
	for(i=0; i<n; i++)
		fwrite(&s[i], sizeof(struct student), 1, fp);
	fclose(fp);
	free(s);
}

