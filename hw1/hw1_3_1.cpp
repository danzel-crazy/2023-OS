#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <vector>

using namespace std;

int main(){
    int n;
    char buf[80];
    int should_run = 1;
    string tmp = "";
    vector <string> arg;
    int argc;
    char** argv;
    pid_t pid;
    while(should_run){
	cout<<"osh>";
	fflush(stdout);
        n = read(STDIN_FILENO, buf ,80);
	for(int i=0; i<n; i++){
	    if(buf[i]==' ' || i==n-1){
                if(tmp.size()>0)
		    arg.push_back(tmp);
                tmp = "";
	    }
	    else{
	        tmp = tmp + buf[i];
	    }
	}
        argc = arg.size();
        argv = new char*[argc+1];
	for(int i=0;i<argc;i++){
	    argv[i]=new char[arg[i].size()];
	    strcpy(argv[i], arg[i].c_str());
	}
	argv[argc] = new char;
	argv[argc] = NULL;
	//cout << argv[0] << arg[0].size();
	if(strcmp(argv[0], "exit") == 0){
	    should_run = 0;
	    break;
	}
	else{
	    pid = fork();
            if(pid == 0){
                execvp(argv[0], argv);
            }
	    else if(pid < 0){
	        cout << "Fork Wrong" << endl;
 		return 1;
	    }
            else{
	        wait(NULL);
            }
	}
	arg.clear();
	//argv_t.clear();
	for(int i=0; i<argc;i++){
	    delete [] argv[i];
	}
	delete argv;
    }
    return 0;
}
