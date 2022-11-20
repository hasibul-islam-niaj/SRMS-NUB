#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
/*Structure Definition Section*/

/*Function Definition Section*/
void welcomeMessage() {
    printf("\n\tStudent Result Management System\n");
    printf("\t Northern University Bangladesh\n");
    for (int i=0; i<39; i++)
        printf("-");
    printf("\n");
}

void underConstruction() {
    printf("System is under Construction.\n");
}

FILE *getFile(char fileToRead[]) {
    FILE *file;

    char fileName[strlen(fileToRead) + strlen(pathOfFiles)];
    strcat(fileName, pathOfFiles);
    strcat(fileName, fileToRead);

    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error in Reading File %s", fileToRead);
    }

    return file;
}

void initMenu() {
    FILE *file = getFile("menus.txt");

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
    FILE *file = getFile("grades.txt");
    if (file != NULL) {
        ResultGrade *tempGrade = NULL;

        while (!feof(file)) {
            ResultGrade *grade = malloc(sizeof(ResultGrade));
            fscanf(file, "%d, %[^,], %f, %[^\n]s", &grade->sequence, grade->name, &grade->point, grade->description);

            if (db_grades == NULL) {
                db_grades = grade;
                tempGrade = grade;
            }
            else {
                tempGrade->next = grade;
                tempGrade = grade;
            }
        }
    }
}

void systemInitialization() {
    initMenu();
    initGrades();
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
    while (tempGrades != NULL){
        printf("[%d] \t%s \t\t\t\t%.2f \t%s\n", tempGrades->sequence, tempGrades->name, tempGrades->point, tempGrades->description);
        tempGrades = tempGrades->next;
    }
}

void taskSwitch(Menu *menu, SubMenu *subMenu) {
    switch (menu->sequence) {
        case 0:
            exitProgram();
            break;
        case 1:
            viewAllGrades();
            break;
        case 2:
            underConstruction();
            break;
        case 3:
            underConstruction();
            break;
        case 4:
            underConstruction();
            break;
        case 5:
            underConstruction();
            break;
        case 6:
            underConstruction();
            break;
        case 7:
            underConstruction();
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