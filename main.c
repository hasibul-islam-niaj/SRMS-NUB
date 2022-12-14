#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_COURSES "../data/courses.txt"
#define FILE_GRADES "../data/grades.txt"
#define FILE_MENUS "../data/menus.txt"
#define FILE_PROGRAMS "../data/programs.txt"
#define FILE_SEMESTERS "../data/semesters.txt"
#define FILE_STUDENTS "../data/students.txt"
#define FILE_STUDENTS_COURSES "../data/student_courses.txt"

/*Structure Definition Section*/
char pathOfFiles[] = "../data/";

struct SubMenu {
    int sequence;
    char name[30];
    struct SubMenu *next;
};
typedef struct SubMenu SubMenu;

struct Menu {
    int sequence;
    char name[30];
    SubMenu *subMenus;
    struct Menu *next;
};
typedef struct Menu Menu;
Menu *db_menus;

struct ResultGrade {
    int sequence;
    char name[2];
    float point;
    char description[200];
    struct ResultGrade *next;
};
typedef struct ResultGrade ResultGrade;
ResultGrade *db_grades;

struct Program {
    int sequence;
    char code[20];
    char name[100];
    struct Program *next;
};
typedef struct Program Program;
Program *db_programs;

struct Semester {
    int sequence;
    char name[50];
    struct Semester *next;
};
typedef struct Semester Semester;
Semester *db_semesters;

struct Course {
    int sequence;
    char code[50];
    char name[100];
    int credit;
    int programSequence;
    struct Course *next;
};
typedef struct Course Course;
Course *db_courses;

struct StudentCourse {
    char studentId[20];
    char semesterName[50];
    char year[5];
    char subjectCode[50];
    double result;

    Semester *semester;
    Course *course;

    struct StudentCourse *next;
};
typedef struct StudentCourse StudentCourse;

struct Student {
    char id[20];
    char name[50];
    int programSequence;

    Program *program;
    struct Student *next;
    StudentCourse *studentCourse;
};
typedef struct Student Student;
Student *db_students;
/*Structure Definition Section*/

/*Function Definition Section*/
void welcomeMessage() {
    printf("\n\tStudent Result Management System\n");
    printf("\t Northern University Bangladesh\n");
    for (int i = 0; i < 39; i++)
        printf("-");
    printf("\n");
}

void waitForClick() {
    printf("\nPress any key to continue...");
    getchar();
    getchar();
}

void underConstruction() {
    printf("System is under Construction.\n");
    waitForClick();
}

FILE *getFile(char fileName[]) {
    FILE *file;
    file = fopen(fileName, "r");

    if (file == NULL)
        printf("Error in Reading File %s", fileName);

    return file;
}

void initMenu() {
    FILE *file = getFile(FILE_MENUS);

    if (file != NULL) {
        Menu *tempMenu = NULL;
        SubMenu *tempSubMenu = NULL;

        while (!feof(file)) {
            Menu *menu = malloc(sizeof(Menu));
            int isMenu;

            fscanf(file, "%d, %[^,], %d", &menu->sequence, menu->name, &isMenu);
            if (isMenu) {
                if (tempMenu == NULL) {
                    tempMenu = menu;
                    if (db_menus == NULL)
                        db_menus = tempMenu;
                } else {
                    tempMenu->next = menu;
                    tempMenu = tempMenu->next;
                }

                tempSubMenu = NULL;
            } else {
                if (tempSubMenu == NULL) {
                    tempSubMenu = (SubMenu *) menu;

                    if (tempMenu->subMenus == NULL)
                        tempMenu->subMenus = tempSubMenu;
                } else {
                    tempSubMenu->next = (SubMenu *) menu;
                    tempSubMenu = tempSubMenu->next;
                }
            }
        }
    }
}

void initGrades() {
    FILE *file = getFile(FILE_GRADES);
    if (file != NULL) {
        ResultGrade *tempGrade = NULL;

        while (!feof(file)) {
            ResultGrade *grade = malloc(sizeof(ResultGrade));
            fscanf(file, "%d, %[^,], %f, %[^\n]s", &grade->sequence, grade->name, &grade->point, grade->description);

            if (db_grades == NULL) {
                db_grades = grade;
                tempGrade = grade;
            } else {
                tempGrade->next = grade;
                tempGrade = grade;
            }
        }
    }
}

void initPrograms() {
    FILE *file = getFile(FILE_PROGRAMS);

    if (file != NULL) {
        Program *tempProgram = NULL;

        while (!feof(file)) {
            Program *program = malloc(sizeof(Program));
            fscanf(file, "%d, %[^,], %[^\n]s", &program->sequence, program->code, program->name);

            if (db_programs == NULL) {
                db_programs = program;
                tempProgram = program;
            } else {
                tempProgram->next = program;
                tempProgram = program;
            }
        }
    }
}

void initSemesters() {
    FILE *file = getFile(FILE_SEMESTERS);

    if (file != NULL) {
        Semester *tempSemester = NULL;

        while (!feof(file)) {
            Semester *semester = malloc(sizeof(Semester));
            fscanf(file, "%d, %[^\n]s", &semester->sequence, semester->name);

            if (db_semesters == NULL) {
                db_semesters = semester;
                tempSemester = semester;
            } else {
                tempSemester->next = semester;
                tempSemester = semester;
            }
        }
    }
}

void initCourses() {
    FILE *file = getFile(FILE_COURSES);

    if (file != NULL) {
        Course *tempCourse = NULL;

        while (!feof(file)) {
            Course *course = malloc(sizeof(Course));
            fscanf(file, "%d, %[^,], %[^|]| %d, %d", &course->sequence, course->code, course->name, &course->credit,
                   &course->programSequence);

            if (db_courses == NULL) {
                db_courses = course;
                tempCourse = course;
            } else {
                tempCourse->next = course;
                tempCourse = course;
            }
        }
    }
}

void initStudents() {
    FILE *file = getFile(FILE_STUDENTS);

    if (file != NULL) {
        Student *tempStudent = NULL;
        Program *selectedProgram = NULL;

        while (!feof(file)) {
            Student *student = malloc(sizeof(Student));
            fscanf(file, "%d, %[^,], %[^\n]s", &student->programSequence, student->id, student->name);

            if (selectedProgram == NULL || selectedProgram->sequence != student->programSequence) {
                selectedProgram = db_programs;
                while (selectedProgram != NULL && selectedProgram->sequence != student->programSequence) {
                    selectedProgram = selectedProgram->next;
                }

                if (selectedProgram == NULL)
                    printf("\n Wrong program for student %s - %s\n", student->id, student->name);
            }

            student->program = selectedProgram;
            if (db_students == NULL) {
                db_students = student;
                tempStudent = student;
            } else {
                tempStudent->next = student;
                tempStudent = student;
            }
        }
    }
}

void initStudentsCourses() {
    FILE *file = getFile(FILE_STUDENTS_COURSES);

    if (file != NULL) {
        Student *selectedStudent = NULL;
        Semester *selectedSemester = NULL;
        Course *selectedCourse = NULL;

        while (!feof(file)) {
            StudentCourse *studentCourse = malloc(sizeof(StudentCourse));
            int serial;
            fscanf(file, "%d, %[^,], %[^,], %[^,], %[^,], %lf", &serial, studentCourse->studentId,
                   studentCourse->semesterName, studentCourse->year, studentCourse->subjectCode,
                   &studentCourse->result);

            if (selectedStudent == NULL || strcmp(selectedStudent->id, studentCourse->studentId)) {
                selectedStudent = db_students;
                while (selectedStudent != NULL) {
                    if (!strcmp(selectedStudent->id, studentCourse->studentId))
                        break;
                    else
                        selectedStudent = selectedStudent->next;
                }

                if (selectedStudent == NULL)
                    printf("\n No Student with id %s\n", studentCourse->studentId);
            }

            if (selectedSemester == NULL || strcmp(selectedSemester->name, studentCourse->semesterName)) {
                selectedSemester = db_semesters;
                while (selectedSemester != NULL) {
                    if (!strcmp(selectedSemester->name, studentCourse->semesterName))
                        break;
                    else
                        selectedSemester = selectedSemester->next;
                }

                if (selectedSemester == NULL)
                    printf("\n No Semester Found Named %s\n", studentCourse->semesterName);
            }

            if (selectedCourse == NULL || strcmp(selectedCourse->code, studentCourse->subjectCode)) {
                selectedCourse = db_courses;
                while (selectedCourse != NULL) {
                    if (!strcmp(selectedCourse->code, studentCourse->subjectCode))
                        break;
                    else
                        selectedCourse = selectedCourse->next;
                }

                if (selectedCourse == NULL)
                    printf("\n No course found with code %s\n", studentCourse->subjectCode);
            }

            studentCourse->semester = selectedSemester;
            studentCourse->course = selectedCourse;

            if (selectedStudent != NULL) {
                if (selectedStudent->studentCourse == NULL) {
                    selectedStudent->studentCourse = studentCourse;
                } else {
                    StudentCourse *tempStudentCourse = selectedStudent->studentCourse;
                    while (tempStudentCourse->next != NULL)
                        tempStudentCourse = tempStudentCourse->next;
                    tempStudentCourse->next = studentCourse;
                }
            } else
                break;
        }
    }
}

void systemInitialization() {
    initMenu();
    initGrades();
    initPrograms();
    initSemesters();
    initCourses();
    initStudents();
    initStudentsCourses();
}

Menu *getByMenuSequence(int menuSequence) {
    Menu *tempMenu = db_menus;
    while (tempMenu != NULL && tempMenu->sequence != menuSequence)
        tempMenu = tempMenu->next;

    return tempMenu;
}

SubMenu *getBySubMenuSequence(Menu *menu, int subMenuSequence) {
    SubMenu *tempSubmenu = menu->subMenus;
    while (tempSubmenu != NULL && tempSubmenu->sequence != subMenuSequence)
        tempSubmenu = tempSubmenu->next;

    return tempSubmenu;
}

void showMenus() {
    welcomeMessage();
    Menu *tempMenu = db_menus;

    while (tempMenu != NULL) {
        printf("[%d] for '%s'\n", tempMenu->sequence, tempMenu->name);
        tempMenu = tempMenu->next;
    }
}

void showSubMenus(Menu *menu) {
    SubMenu *tempSubMenu = menu->subMenus;
    while (tempSubMenu != NULL) {
        printf("\t[%d] for '%s'\n", tempSubMenu->sequence, tempSubMenu->name);
        tempSubMenu = tempSubMenu->next;
    }
}

void exitProgram() {
    exit(0);
}

void viewAllGrades() {
    ResultGrade *tempGrades = db_grades;
    printf("Sl. \tLetter Grade \tPoint \tDescription\n");
    while (tempGrades != NULL) {
        printf("[%d] \t%s \t\t\t\t%.2f \t%s\n", tempGrades->sequence, tempGrades->name, tempGrades->point,
               tempGrades->description);
        tempGrades = tempGrades->next;
    }
}

void viewAllPrograms() {
    Program *tempPrograms = db_programs;
    printf("Sl. \tProgram\n");
    while (tempPrograms != NULL) {
        printf("[%d] \t%s\n", tempPrograms->sequence, tempPrograms->name);
        tempPrograms = tempPrograms->next;
    }
}

void tasksSwitchPrograms(SubMenu *subMenu) {
    printf("Menu -> %s\n", subMenu->name);

    switch (subMenu->sequence) {
        case 1:
            underConstruction();
            break;
        case 2:
            underConstruction();
            break;
        case 3:
            underConstruction();
            break;
        case 4:
            viewAllPrograms();
            waitForClick();
            break;
    }
}

void viewAllSemesters() {
    Semester *tempSemester = db_semesters;
    printf("Sl. \tSemester\n");
    while (tempSemester != NULL) {
        printf("[%d] \t%s\n", tempSemester->sequence, tempSemester->name);
        tempSemester = tempSemester->next;
    }
}

void tasksSwitchSemesters(SubMenu *subMenu) {
    printf("%s\n", subMenu->name);

    switch (subMenu->sequence) {
        case 1:
            underConstruction();
            break;
        case 2:
            underConstruction();
            break;
        case 3:
            underConstruction();
            break;
        case 4:
            viewAllSemesters();
            waitForClick();
            break;
    }
}

void viewAllCourses() {
    Course *tempCourses = db_courses;
    printf("Sl. \tCode \t\tCredit \tCourse\n");

    while (tempCourses != NULL) {
        printf("[%d] \t%s \t%d \t\t%s \t\n", tempCourses->sequence, tempCourses->code, tempCourses->credit,
               tempCourses->name);
        tempCourses = tempCourses->next;
    }
}

void viewAllCoursesFilteredByProgram() {
    Course *tempCourses = db_courses;
    viewAllPrograms();

    int programSequence, hasCourses = 0, viewAgain = 0;
    printf("\nEnter Program Sl. to View Courses: ");
    scanf("%d", &programSequence);

    printf("\nSl. \tCode \t\tCredit \tCourse\n");
    while (tempCourses != NULL) {
        if (tempCourses->programSequence == programSequence) {
            printf("[%d] \t%s \t%d \t\t%s \t\n", tempCourses->sequence, tempCourses->code, tempCourses->credit,
                   tempCourses->name);
            hasCourses = 1;
        }

        tempCourses = tempCourses->next;
    }

    if (!hasCourses)
        printf("**This program has no Courses.\n");

    viewAgainChoices:
    printf("\nDo you wanna view other programs? [1] for Yes, [0] for No]: ");
    scanf("%d", &viewAgain);

    if (viewAgain == 1)
        viewAllCoursesFilteredByProgram();
    else if (viewAgain != 0)
        goto viewAgainChoices;
}

void tasksSwitchCourses(SubMenu *subMenu) {
    printf("%s\n", subMenu->name);

    switch (subMenu->sequence) {
        case 1:
            underConstruction();
            break;
        case 2:
            underConstruction();
            break;
        case 3:
            underConstruction();
            break;
        case 4:
            viewAllCourses();
            waitForClick();
            break;
        case 5:
            viewAllCoursesFilteredByProgram();
            waitForClick();
            break;
    }
}

void viewAllStudents() {
    Student *tempStudent = db_students;
    printf("ID \t\t\t\tName \t\t\t\t\tProgram\n");

    while (tempStudent != NULL) {
        printf("%s \t%s \t\t\t%s\n", tempStudent->id, tempStudent->name,
               tempStudent->program == NULL ? "" : tempStudent->program->name);
        tempStudent = tempStudent->next;
    }

    waitForClick();
}

void viewAllStudentsFilteredByProgram() {
    Student *tempStudents = db_students;
    viewAllPrograms();

    int programSequence, viewAgain = 0, hasStudents = 0;
    printf("\nEnter Program Sl. to View Students: ");
    scanf("%d", &programSequence);

    printf("ID \t\t\t\tName\n");
    while (tempStudents != NULL) {
        if (tempStudents->programSequence == programSequence) {
            printf("%s \t%s\n", tempStudents->id, tempStudents->name);
            hasStudents = 1;
        }

        tempStudents = tempStudents->next;
    }

    if (!hasStudents)
        printf("**No students are enrolled in this program.\n");

    viewAgainChoices:
    printf("\nDo you wanna view other programs? [1] for Yes, [0] for No]: ");
    scanf("%d", &viewAgain);

    if (viewAgain == 1)
        viewAllStudentsFilteredByProgram();
    else if (viewAgain != 0)
        goto viewAgainChoices;
}

void tasksSwitchStudents(SubMenu *subMenu) {
    printf("%s\n", subMenu->name);

    switch (subMenu->sequence) {
        case 1:
            underConstruction();
            break;
        case 2:
            underConstruction();
            break;
        case 3:
            underConstruction();
            break;
        case 4:
            viewAllStudents();
            break;
        case 5:
            underConstruction();
            break;
        case 6:
            viewAllStudentsFilteredByProgram();
            break;
        case 7:
            underConstruction();
            break;
    }
}

void viewAllCoursesOfStudent() {
    char id[20];
    printf("Enter Student ID: ");
    scanf("%s", id);

    Student *student = db_students;
    while (student != NULL && strcmp(student->id, id))
        student = student->next;

    if (student == NULL)
        printf("No students found with id %s\n", id);
    else {
        printf("\nCourses of %s.\n", student->name);

        StudentCourse *tempCourse = student->studentCourse;
        printf("Semester \t Year \t Credit \t Code \t\t Course\n");

        int i = 1, credit = 0;
        while (tempCourse != NULL) {
            printf("%d. %s\t\t %s\t %d \t\t\t %s\t %s\n", i, tempCourse->semesterName, tempCourse->year,
                   tempCourse->course->credit, tempCourse->course->code, tempCourse->course->name);
            credit += tempCourse->course->credit;
            tempCourse = tempCourse->next;
            i++;
        }
        printf("Total Credit: %d\n", credit);
    }

    int viewAgain = 0;
    viewAgainChoices:
    printf("\nDo you wanna view other students? [1] for Yes, [0] for No]: ");
    scanf("%d", &viewAgain);

    if (viewAgain == 1)
        viewAllCoursesOfStudent();
    else if (viewAgain != 0)
        goto viewAgainChoices;
}

void tasksSwitchStudentCourses(SubMenu *subMenu) {
    printf("%s\n", subMenu->name);

    switch (subMenu->sequence) {
        case 1:
            underConstruction();
            break;
        case 2:
            underConstruction();
            break;
        case 3:
            viewAllCoursesOfStudent();
            break;
    }
}

void viewResultOfStudent() {
    char id[20];
    printf("Enter Student ID: ");
    scanf("%s", id);

    Student *student = db_students;
    while (student != NULL && strcmp(student->id, id))
        student = student->next;

    if (student == NULL)
        printf("No students found with id %s\n", id);
    else {
        printf("\nResult of %s.\n", student->name);

        StudentCourse *tempCourse = student->studentCourse;
        printf("\nSemester \t Year \t Code \t\t Credit \t GP \t TGP \t\t Course\n");

        int i = 1, credit = 0;
        double tgp = 0.00;

        while (tempCourse != NULL) {
            printf("%d. %s\t\t %s\t %s \t\t %d \t\t %.2lf\t %.2lf\t\t %s\n", i, tempCourse->semesterName,
                   tempCourse->year, tempCourse->course->code, tempCourse->course->credit, tempCourse->result,
                   tempCourse->course->credit * tempCourse->result, tempCourse->course->name);
            tgp += (tempCourse->course->credit * tempCourse->result);
            credit += tempCourse->course->credit;
            tempCourse = tempCourse->next;
            i++;
        }

        if (credit != 0) {
            printf("\nTotal Credit: %d\n", credit);
            printf("TGP: %.2lf\n", tgp);
            printf("CGPA: %.2lf\n", tgp/credit);
        }
        else
            printf("Result not published yet.");
    }

    int viewAgain = 0;
    viewAgainChoices:
    printf("\nDo you wanna view other students? [1] for Yes, [0] for No]: ");
    scanf("%d", &viewAgain);

    if (viewAgain == 1)
        viewResultOfStudent();
    else if (viewAgain != 0)
        goto viewAgainChoices;
}

void tasksSwitchResults(SubMenu *subMenu) {
    printf("%s\n", subMenu->name);

    switch (subMenu->sequence) {
        case 1:
            underConstruction();
            break;
        case 2:
            underConstruction();
            break;
        case 3:
            viewResultOfStudent();
            break;
    }
}

void taskSwitch(Menu *menu, SubMenu *subMenu) {
    printf("Menu -> %s\n", menu->name);

    switch (menu->sequence) {
        case 0:
            waitForClick();
            exitProgram();
            break;
        case 1:
            viewAllGrades();
            waitForClick();
            break;
        case 2:
            tasksSwitchPrograms(subMenu);
            break;
        case 3:
            tasksSwitchSemesters(subMenu);
            break;
        case 4:
            tasksSwitchCourses(subMenu);
            break;
        case 5:
            tasksSwitchStudents(subMenu);
            break;
        case 6:
            tasksSwitchStudentCourses(subMenu);
            break;
        case 7:
            tasksSwitchResults(subMenu);
            break;
    }
}

void menuOperations() {
    showMenus();

    int menuSequence, subMenuSequence;
    printf("\nChoose Menu: ");
    scanf("%d", &menuSequence);

    Menu *selectedMenu = getByMenuSequence(menuSequence);

    if (selectedMenu != NULL) {
        SubMenu *selectedSubMenu = NULL;

        if (selectedMenu->subMenus != NULL) {
            subMenuSelection:
            showSubMenus(selectedMenu);
            printf("\nWhat to do: ");
            scanf("%d", &subMenuSequence);

            selectedSubMenu = getBySubMenuSequence(selectedMenu, subMenuSequence);
            if (selectedSubMenu == NULL) {
                printf("\nAn invalid sub-menu is selected.\nPlease choose the correct sub-menu.\n");
                goto subMenuSelection;
            }
        }

        taskSwitch(selectedMenu, selectedSubMenu);
    } else {
        printf("\nAn invalid menu is selected.\nPlease choose the correct menu.\n");
    }
}

/*Function Definition Section*/

int main() {
    systemInitialization();
    while (1) {
        menuOperations();
    }
}