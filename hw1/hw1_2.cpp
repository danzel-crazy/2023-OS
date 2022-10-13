#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int main(){
    cout << "Main Process Id : " << getpid() << endl;
    pid_t pid;
    pid = fork();
    wait(NULL);
    if(pid == 0){
      cout << "Fork 1. I'm the child " << getpid() << ", my parent is " << getppid() << endl;
      pid = fork();
      if(pid == 0){
        cout << "Fork 2. I'm the child " << getpid() << ", my parent is " << getppid() << endl;
        pid = fork();
        if(pid == 0)
          cout << "Fork 3. I'm the child " << getpid() << ", my parent is " << getppid() << endl;
      }
    }
    else if(pid > 0){
      pid = fork();
      wait(NULL);
      if(pid == 0){
	cout << "Fork 4. I'm the child " << getpid() << ", my parent is " << getppid() << endl;
      }
      else if(pid > 0){
        pid = fork();
        wait(NULL);
        if(pid == 0)
	  cout << "Fork 6. I'm the child " << getpid() << ", my parent is " << getppid() << endl;
      }
      pid = fork();
      if(pid == 0)
        cout << "Fork 5. I'm the child " << getpid() << ", my parent is " << getppid() << endl;
    }
    return 0;
}
