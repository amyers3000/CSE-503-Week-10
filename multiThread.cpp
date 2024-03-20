#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <pthread.h> 
#define NumberOfThreads 20
#define InputSize 100000

std::vector<std::string> input;
int sum = 0;

struct thread_data {
    int thread;
    int start;
    int end;
    int sum;
};

void *runner(void *param) {
    thread_data *data = (thread_data *) param;
    for (int i = data->start; i < data->end && i < (int)input.size(); i++) {
         data->sum += atoi(input[i].c_str());
    }
    pthread_exit(0);
}

int main(int argc, const char * argv[]) {
    pthread_t tid[NumberOfThreads];
    pthread_attr_t attr;
    thread_data data[NumberOfThreads];

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

    for(int i = 0; i < NumberOfThreads; i++){
      data[i].thread = i;
      data[i].start = i * (input.size() / NumberOfThreads);
      data[i].end = (i + 1) * (input.size() / NumberOfThreads);
      data[i].sum = 0;
      pthread_create(&tid[i], &attr, runner, &data[i]);
    }

    for(int i = 0; i < NumberOfThreads; i++){
      pthread_join(tid[i], NULL);
      sum += data[i].sum;
    }

    std::cout << " Sum: " << sum << std::endl;


    return 0;
}
