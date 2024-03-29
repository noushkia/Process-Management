#include "libs.hpp"
#include "defs.hpp"
#include "utilities.hpp"

using namespace std;

int count_digit(int number) {
   int count = 0;
   while(number != 0) {
      number = number / 10;
      count++;
   }
   return count;
}

bool get_files(vector<string> &files)
{
    DIR *dir;
    struct dirent *ent;
    regex file_name_regex("[1-9][0-9]*\\.csv");

    if ((dir = opendir(FILES_DIR)) == NULL)
    {
        cerr << "Directory non-existent!\n";
        return 0;
    }

    while ((ent = readdir(dir)) != NULL)
    {
        if ( regex_match(ent->d_name, file_name_regex) )
            files.push_back(ent->d_name);
    }
    
    closedir (dir);

    return 1;
}

void write_output(const map<string, int> &words)
{
    ofstream output_file;
    output_file.open(OUTPUT_FILENAME);
    
    for (auto word: words)
        output_file << word.first << ": " << word.second << endl;

    output_file.close();
}

int main(int argc, char *argv[])
{
    vector<string> files;

    if (!get_files(files))
    {
        cerr << "Could not open directory" << endl;
        return 1;
    }

    //call mapper proceses
    for (int i = 0; i < files.size(); i++)
    {
        int fd[2]; // unnamed pipe for mappers (?: why vector didn't work)
        int digit_count = count_digit(i);

        if (pipe(fd) == -1)
        {
            cerr << "Pipe for mapper " << i << " failed!" << endl;
            return 0;
        }

        pid_t pid = fork();
        if (pid < 0)
        {
            cerr << "Mapper " << i << " failed to start!" << endl;
            return 0;
        }

        if (pid == 0) //child process
        {
            close(fd[WRITE]);

            char file[FILES_DIR_LEN + digit_count + 4];
            bzero(file, FILES_DIR_LEN + digit_count + 4);
            read(fd[READ], file, FILES_DIR_LEN + digit_count + 4 + 1); // 4 for .csv 1 for NULL
            close(fd[READ]);

            char* args[] = {"./mapper.out", file, NULL}; 
            execv("./mapper.out", args);
        }
        else //parent process
        {
            //give the i'th csv file to child process
            close(fd[READ]);

            cout << "main sending file " << files[i] << " for mapper " << i << endl;

            string file = FILES_DIR + files[i];

            write(fd[WRITE], file.c_str(), FILES_DIR_LEN + digit_count + 4 + 1); // 4 for .csv
            
            close(fd[WRITE]);
       }
    }

    //start reducer process
    int fd[2]; // unnamed pipe for reducer
    if (pipe(fd) == -1)
    {
        cerr << "Pipe for reducer failed!" << endl;
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        cerr << "Reducer failed to start!" << endl;
        return 1;
    }
    if (pid == 0) //child process
    {
        close(fd[READ]);
        char fdwrite[count_digit(fd[WRITE])+1];
        sprintf(fdwrite, "%d", fd[WRITE]);
        char map_count[count_digit(files.size())+1];
        sprintf(map_count, "%d", int(files.size()));

        char* args[] = {"./reducer.out", fdwrite, map_count, NULL}; 
        if (execv("./reducer.out", args))
            cout << "Main called reducer process" << endl;
    }
    else //parent process
    {
        map<string, int> words;
        close(fd[WRITE]);
        wait(NULL);
        // while (wait(NULL) != -1);
        char word_count[MAX_LEN];
        bzero(word_count, MAX_LEN);
        read(fd[READ], word_count, MAX_LEN);
        decode_dict(word_count, words);
        close(fd[READ]);
        write_output(words);
        cout << "Finished map reducing!" << endl;
    }
    
    return 0;
}
