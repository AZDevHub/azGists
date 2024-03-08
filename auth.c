#include "qsysinc/H/qsyphandle"
#include "qsysinc/H/qusec"
#include "qsysinc/H/string"
#include "qsysinc/H/stdio"

#define HANDLE_SIZE 12
#define CURRENT_USER "*CURRENT"
#define NOPWD "*NOPWD"

int getProfileHandle(char *profileHandle, char *username, char *password) {
  Qus_EC_t errcode;
  errcode.Bytes_Provided = 0;
  if (strcmp(username, CURRENT_USER) == 0) {
    QsyGetProfileHandleNoPwd(profileHandle, username, password, &errcode);
  } else {
    QsyGetProfileHandle(profileHandle, username, password, strlen(password), 0, &errcode);
  }

  if (errcode.Bytes_Available > 0) {
    printf("Error: %s\n", errcode.Exception_Id);
    return -1;
  }
  return 0;
}

int setProfileHandle(char *profileHandle) {
  Qus_EC_t errcode;
  QsySetToProfileHandle(profileHandle, &errcode);

  if (errcode.Bytes_Available > 0) {
    printf("Error: %s\n", errcode.Exception_Id);
    return -1;
  }
  return 0;
}

int releaseProfileHandle(char *profileHandle) {
  Qus_EC_t errcode;

  QsyReleaseProfileHandle(profileHandle, &errcode);

  if (errcode.Bytes_Available > 0) {
    printf("Error: %s\n", errcode.Exception_Id);
    return -1;
  }
  return 0;
}

int main (int argc, char *argv[]) {

  if (argc < 3) {
    printf("Not enough arguments provided\n");
    return -1;
  }

  char handle[HANDLE_SIZE];

  char pjUser[10];
  strcpy(pjUser, CURRENT_USER);
  char pjPwd[6];
  strcpy(pjPwd, NOPWD);
  char pjHandle[HANDLE_SIZE];

  if(getProfileHandle(pjHandle, pjUser, pjPwd) == -1) {
     return -1;
  }

  if(getProfileHandle(handle, argv[1], argv[2]) == -1) {
    return -1;
  }

  if(setProfileHandle(handle) == -1) {
    return -1;
  }

  if(releaseProfileHandle(pjHandle) == -1) {
    return -1;
  }

  return 0;
}