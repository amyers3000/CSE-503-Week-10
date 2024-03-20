#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <pthread.h> 
#define InputSize 100000

std::vector<std::string> input;
int sum = 0;

struct thread_data {
    int thread_id;
    int start;
    int end;
};

void *runner(void *param) {
    thread_data *data = (thread_data *) param;
    for (int i = data->start; i < data->end && i < (int)input.size(); i++) {  
        sum += atoi(input[i].c_str());
    }
    pthread_exit(0);
}

int main(int argc, const char * argv[]) {
    pthread_t tid;
    pthread_attr_t attr;
    thread_data data;

    pthread_attr_init(&attr);

    std::ifstream myfile("input.txt");
    std::string myline;

    if (myfile.is_open()) {
        while (std::getline(myfile, myline)) {
            input.push_back(myline);
        }
        myfile.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
        return 1;
    }

    data.thread_id = 0;
    data.start = 0;
    data.end = 100000;
    pthread_create(&tid, &attr, runner, &data);

    pthread_join(tid, NULL);

    std::cout << " Sum: " << sum << std::endl;

    return 0;
}
