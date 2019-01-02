#include<stdio.h>
#include<stdlib.h>

typedef struct Student{
	char* name;
	char rollno[9];
	char branch[4];
	char section[3];
}Student;

typedef struct Course{
	char* title;
	char courseno[6];
	char department[4];
	char credit[2];
}Course;

typedef struct Section{
	char sectionno[3];
	char courseno[6];
	char semester[2];
	char year[5];
	char *faculty;
}Section;

typedef struct Grade{
	char rollno[9];
	char courseno[6];
	char grade[2];
}Grade;

int IsRollAlreadyUsed(Student* students,char* roll,int size){
	int i,j;
	int count;
	for(i=0;i<size;i++){						//checking for each used roll number
		count=0;	
		for(j=0;j<9;j++){						//9 is length of roll number string
			if(students[i].rollno[j]==roll[j])
				count++;
		}
		if(count==9)
			return 1;
	}
	return 0;
}

int IsCourseNoAlreadyUsed(Course* courses,char* coursenum,int size){
	int i,j;
	int count;
	for(i=0;i<size;i++){								//checking for each used course number
		count=0;
		for(j=0;j<6;j++){								// 6 is length of coursenumber string
			if(courses[i].courseno[j]==coursenum[j])
				count++;
		}
		if(count==6)
			return 1;
	}
	return 0;
}

int DoesSectionNumMatch(char* secnum, Student* students,int size){
	int i,j;
	int count;
	for(i=0;i<size;i++){
		count=0;
		for(j=0;j<3;j++){
			if(students[i].section[j]==secnum[j])
				count++;
		}
		if(count==3)
			return 1;
	}
	return 0;
}

int DoesCourseNumMatch(char* coursenum, Course* courses, int size){
	int i,j;
	int count;
	for(i=0;i<size;i++){
		count=0;
		for(j=0;j<6;j++){
			if(courses[i].courseno[j]==coursenum[j])
				count++;
		}
		if(count==6)
			return 1;
	}
	return 0;
}

int IsRollNumValid(char* rollnum,Student* students,int size){
	int i,j;
	int count;
	for(i=0;i<size;i++){						//checking for each used roll number
		count=0;	
		for(j=0;j<9;j++){						//9 is length of roll number string
			if(students[i].rollno[j]==rollnum[j])
				count++;
		}
		if(count==9)
			return 1;
	}
	return 0;
}

int IsCourseNumValid(Course* courses,char* coursenum,int size){
	int i,j;
	int count;
	for(i=0;i<size;i++){								//checking for each used course number
		count=0;
		for(j=0;j<6;j++){								// 6 is length of coursenumber string
			if(courses[i].courseno[j]==coursenum[j])
				count++;
		}
		if(count==6)
			return 1;
	}
	return 0;
}

Student AddStudentRecord(FILE* file,Student* students,int size){
	Student stu;
	char nme[50];
	int len=0,i=0;
	printf("Enter name:");
	scanf(" %[^\n]s",nme); 
	printf("Enter roll no:");
	scanf("%s",&stu.rollno);
	while(IsRollAlreadyUsed(students,stu.rollno,size)==1){
		printf("Roll number already in use. Please enter a different one!!\n");
		printf("Enter roll no:");
		scanf("%s",&stu.rollno);
	}
	printf("Enter branch:");
	scanf("%s",&stu.branch);
	printf("Enter section:");
	scanf("%s",&stu.section);

	while (nme[i]!=0){
		len++;
		i++;
	}

	stu.name=malloc(sizeof(char)*len);				

	for(i=0;i<len;i++){
		stu.name[i]=nme[i];						//stu.name is created with length len
	}

	fwrite(stu.name,sizeof(char),len+1,file);   //writing stuff on file
	fwrite(stu.rollno,sizeof(char),9,file);
	fwrite(stu.branch,sizeof(char),4,file);
	fwrite(stu.section,sizeof(char),3,file);
	fprintf(file, "\n");

	return stu;

}

Course AddCourseRecord(FILE* file, Course* courses, int size){
	Course course;
	char title[50];
	int len=0,i=0;
	printf("Enter course title:");
	scanf(" %[^\n]s",title); 
	printf("Enter course no:");
	scanf("%s",&course.courseno);
	while(IsCourseNoAlreadyUsed(courses,course.courseno,size)==1){
		printf("Course number already in use. Please enter a different one!!\n");
		printf("Enter course no:");
		scanf("%s",&course.courseno);
	}
	printf("Enter department:");
	scanf("%s",&course.department);
	printf("Enter credits:");
	scanf("%s",&course.credit);

	//printf("Here\n");

	while (title[i]!=0){
		len++;
		i++;
	}

	//printf("Here\n");

	course.title=malloc(sizeof(char)*len);

	for(i=0;i<len;i++){
		course.title[i]=title[i];
	}

	//printf("Here\n");

	fwrite(course.title,sizeof(char),len+1,file);
	fwrite(course.courseno,sizeof(char),6,file);
	fwrite(course.department,sizeof(char),4,file);
	fwrite(course.credit,sizeof(char),2,file);
	fprintf(file, "\n");

	return course;
}


Section AddSectionRecord(FILE* file, Student* students,Course* courses,int size){
	Section sec;
	char faculty[50];
	int len=0,i=0;

	//taking stuff
	printf("Enter section number:");
	scanf("%s",&sec.sectionno);
	while(DoesSectionNumMatch(sec.sectionno,students,size)==0){
		printf("Section number invalid. Please enter a different one!!\n");
		printf("Enter section number:");
		scanf("%s",&sec.sectionno);
	}
	printf("Enter course number:");
	scanf("%s",&sec.courseno);
	while(DoesCourseNumMatch(sec.courseno,courses,size)==0){
		printf("Course number invalid. Please enter a different one!!\n");
		printf("Enter course number:");
		scanf("%s",&sec.courseno);
	}
	printf("Enter semester:");
	scanf("%s",&sec.semester);
	printf("Enter year:");
	scanf("%s",&sec.year);
	printf("Enter faculty name:");
	scanf(" %[^\n]s",faculty);

	while(faculty[i]!=0){
		len++;
		i++;
	}

	sec.faculty=malloc(sizeof(char)*len);

	for(i=0;i<len;i++){
		sec.faculty[i]=faculty[i];
	}

	//writing stuff
	fwrite(sec.sectionno,sizeof(char),3,file);
	fwrite(sec.courseno,sizeof(char),6,file);
	fwrite(sec.semester,sizeof(char),2,file);
	fwrite(sec.year,sizeof(char),5,file);
	fwrite(sec.faculty,sizeof(char),len+1,file);
	fprintf(file, "\n");

	return sec;

}

Grade AddGradeRecord(FILE* file, Student* students, Course* courses, int size){
	Grade grade;

	//taking suff
	printf("Enter roll number:");
	scanf("%s",&grade.rollno);
	while(IsRollNumValid(grade.rollno,students,size)==0){
		printf("Roll number invalid. Please enter a different one!!\n");
		printf("Enter roll number:");
		scanf("%s",&grade.rollno);
	}
	printf("Enter course number:");
	scanf("%s",&grade.courseno);
	while(IsCourseNumValid(courses,grade.courseno,size)==0){
		printf("Course number invalid. Please enter a different one!!\n");
		printf("Enter course number:");
		scanf("%s",&grade.courseno);
	}
	printf("Enter grade:");
	scanf("%s",&grade.grade);

	//writing stuff
	fwrite(grade.rollno,sizeof(char),9,file);
	fwrite(grade.courseno,sizeof(char),6,file);
	fwrite(grade.grade,sizeof(char),2,file);
	fprintf(file, "\n");

}

void DeleteStudentRecord(Student* students,Grade* grades,int records){
	/*delete record from students array
	  open Students.dat with w format
	  write the new records again*/

	char roll[9];
	printf("Enter roll number of student to delete record of:");
	scanf("%s",&roll);
	while(IsRollNumValid(roll,students,records)==0){
		printf("Roll number invalid. Please enter a different one!!\n");
		printf("Enter roll number:");
		scanf("%s",&roll);
	}


}



int main(int argc, char const *argv[])
{
	

	Student* students=malloc(5*sizeof(Student));
	Grade* grades=malloc(5*sizeof(Grade));
	Section* sections=malloc(5*sizeof(Section));
	Course* courses=malloc(5*sizeof(Course));


	FILE* fstudent;
	FILE* fcourse;
	FILE* fsection;
	FILE* fgrades;
	int i;

	fstudent=fopen("Student.dat","w");
	fcourse=fopen("Course.dat","w");
	fsection=fopen("Section.dat","w");
	fgrades=fopen("Grades.dat","w");

	printf("Students:\n");
	for(i=0;i<2;i++){
		printf("%d.",i+1);
		students[i]=AddStudentRecord(fstudent,students,i+1);
	}

	printf("\nCourses:\n");
	for(i=0;i<2;i++){
		printf("%d.",i+1);
		courses[i]=AddCourseRecord(fcourse,courses,i+1);
	}

	printf("\nSections:\n");
	for(i=0;i<2;i++){
		printf("%d.",i+1);
		sections[i]=AddSectionRecord(fsection,students,courses,2);
	}

	printf("\nGrades:\n");
	for(i=0;i<2;i++){
		printf("%d.",i+1);
		grades[i]=AddGradeRecord(fgrades,students,courses,2);
	}

	DeleteStudentRecord(students,grades,2);
	DeleteCourseRecord();

	return 0;
}