#include<stdio.h>
#include <stdlib.h>
#include<string.h>
void saveToFile();
struct student {
    int rno;
    int admn;
    char f_name[15];
    char l_name[15];
    char course[5];
    struct student *next;
} *new = NULL, *temp = NULL, *head = NULL,*prev=NULL,*loaded=NULL;

const char *Studentfile = "student_Record_system.data";

struct student *create()
{
    new = (struct student*)malloc(sizeof(struct student));
    printf("Enter Rollno: ");
    scanf("%d", &new->rno);
    printf("Enter Admission Number: ");
    scanf("%d", &new->admn);
    printf("Enter first name: ");
    scanf("%s", new->f_name);
    printf("Enter last name: ");
    scanf("%s", new->l_name);
    printf("Enter your Course: ");
    scanf("%s", new->course);
    new->next = NULL;
    return new;
}
int precedence(char c) 
{
    return 'Z' - c; 
}
void changeRno()
{
    int rno=1;
	temp=head;
	while(temp!=NULL)
	{
		temp->rno=rno++;
		temp=temp->next;
	}
}
void deleteAt()
{
	int admn;
	printf("Enter admission no: ");
	scanf("%d",&admn);
	if(head==NULL)
	    printf("List is empty...\n");
	 if(head->admn==admn)
	{
		temp=head;
		head=temp->next;
		printf("%d deleted successfully...\n",temp->admn);
		free(temp);
	}
    else
    {
	    temp=head;
	    while(temp->admn!=admn)
	    {
		    prev=temp;
		    temp=temp->next;
	    }
	    if(temp->admn==admn)
	    {
		    prev->next=temp->next;
		    printf("%d deleted successfully...\n",temp->admn);
		    free(temp);
	    }
	    else
	    {
		    printf("%d not found",admn);
	    }
    }
    changeRno();
    saveToFile();
}
void insertAt() 
{
    new = create();
    if (head == NULL) 
    {
        head = new;
    } else if (precedence(new->f_name[0]) >= precedence(head->f_name[0]))
    {
        new->next = head;
        head = new;
    } else 
    {
        temp = head;
        while (temp->next != NULL && precedence(new->f_name[0]) < precedence(temp->next->f_name[0])) 
        {
            temp = temp->next;
        }
        new->next = temp->next;
        temp->next = new;
    }
    changeRno();
    saveToFile();
}
void update()
{
	int admn;
	printf("Enter admission no: ");
	scanf("%d",&admn);
	temp=head;
	if(head==NULL)
	    printf("List is empty...\n");
	if(temp!=NULL)
	{
		while(temp->admn!=admn)
		{
			temp=temp->next;
		}
		printf("Enter new name");
		scanf("%s",temp->f_name);
		printf("%d successfully updated\n",temp->admn);
	    saveToFile();
	}
	else
	{
		printf("%d not found\n",admn);
	}	
}
void saveToFile() 
{
    FILE *file = fopen(Studentfile, "wb");
    if (file == NULL) 
    {
        printf("Error opening file for writing.\n");
        return;
    }
    temp = head;
    while (temp != NULL)
    {
        fwrite(temp, sizeof(struct student), 1, file);
        temp = temp->next;
    }
    fclose(file);
}
void loadFromFile() 
{
    FILE *file = fopen(Studentfile, "rb");
    if (file == NULL)
    {
        printf("No records found. Starting fresh...\n");
        return;
    }
    while(fread(new, sizeof(struct student), 1, file))
    {
        loaded = (struct student *)malloc(sizeof(struct student));
        loaded = new;
        loaded->next = NULL;
        if (head == NULL) 
        {
          head = loaded;
        } 
        else
        {
            temp = head;
            while (temp->next != NULL) 
            {
                temp = temp->next;
            }
            temp->next = loaded;
        }
    }
    fclose(file);
    changeRno();
}
void searchStudent()
{
	int admn;
	printf("Enter admission number: ");
	scanf("%d",&admn);
	temp=head;
	while(temp!=NULL)
	{
		if(temp->admn!=admn)
		{
		    printf("Entered Admission %d not found\n",admn);
		    break;
		}
		else
		{
		    printf("Student Admission No: %d\n", temp->admn);
            printf("Student rollno: %d\n", temp->rno);
            printf("Student First Name: %s\n",temp->f_name);
            printf("Student Last Name: %s\n",temp->l_name);
            printf("Course: %s\n",temp->course);
            temp=temp->next;
		}
	}
}
void display() {
    if (head == NULL) {
        printf("List is empty...\n");
    } else {
        temp = head;
        while (temp != NULL) {
            printf("Student Admission No: %d\n", temp->admn);
            printf("Student rollno: %d\n", temp->rno);
            printf("Student First Name: %s\n",temp->f_name);
            printf("Student Last Name: %s\n",temp->l_name);
            printf("Course: %s\n",temp->course);
            temp = temp->next;
        }
    }
}
void main() 
{
    int choice = 1;
    loadFromFile();
    while (choice > 0 && choice <= 4) {
        printf("1. Upload\n");
        printf("2. Update\n");
        printf("3. Delete\n");
        printf("4. Search\n");
        printf("5. Display\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:insertAt();
                    break;
            case 2:update();
                    break;
            case 3:deleteAt();
                    break;
            case 4:searchStudent();
                    break;
            case 5:display();
                    break;
            default:
                printf("Invalid choice\n");
                break;
        }
    }
}
