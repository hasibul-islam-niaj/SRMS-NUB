#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Structure Definition Section*/
char pathOfFiles[] = "../";

struct SubMenu {
    int sequence;
    char name[30];
    struct SubMenu * next;
};
typedef struct SubMenu SubMenu;

struct Menu {
    int sequence;
    char name[30];
    SubMenu * subMenus;
    struct Menu *next;
};
typedef struct Menu Menu;
Menu * allMenus;

struct ResultGrade {
    char name[2];
    double maxPoint;
    double minPoint;
};
typedef struct ResultGrade ResultGrade;
/*Structure Definition Section*/

/*Function Definition Section*/
FILE * getFile (char fileToRead[]) {
    FILE * file;

    char fileName[strlen(fileToRead) + strlen(pathOfFiles)];
    strcat(fileName, pathOfFiles);
    strcat(fileName, fileToRead);

    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error in Reading File %s", fileToRead);
    }

    return file;
}

void readMenu() {
    FILE * file = getFile("menus.txt");

    if (file != NULL) {
        Menu * tempMenu = NULL;
        SubMenu * tempSubMenu = NULL;

        while (!feof(file)) {
            Menu* menu = malloc(sizeof (Menu));
            int isMenu;

            fscanf(file, "%d, %[^,], %d", &menu->sequence, &menu->name, &isMenu);
            if (isMenu) {
                if (tempMenu == NULL) {
                    tempMenu = menu;
                    if (allMenus == NULL)
                        allMenus = tempMenu;
                }
                else {
                    tempMenu->next = menu;
                    tempMenu = tempMenu->next;
                }

                tempSubMenu = NULL;
            }
            else {
                if (tempSubMenu == NULL) {
                    tempSubMenu = menu;

                    if (tempMenu->subMenus == NULL)
                        tempMenu->subMenus = tempSubMenu;
                }
                else {
                    tempSubMenu->next = menu;
                    tempSubMenu = tempSubMenu->next;
                }
            }
        }
    }
}

void printMenus() {
    Menu *tempMenu = allMenus;
    while (tempMenu != NULL){
        printf("[%d] for '%s'\n", tempMenu->sequence, tempMenu->name);

        /*SubMenu *tempSubMenu = tempMenu->subMenus;
        while (tempSubMenu != NULL){
            printf("\t[%d] for '%s'\n", tempSubMenu->sequence, tempSubMenu->name);
            tempSubMenu = tempSubMenu->next;
        }*/

        tempMenu = tempMenu->next;
    }
}

void menuOperations() {
    printMenus();

    printf("\nChoose Menu: ");
}
/*Function Definition Section*/


int main() {
    readMenu();
    while (1) {
        menuOperations();
    }
    return 0;
}