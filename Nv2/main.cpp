/*
 * It is the main.cpp file to run the nv^2 data structure
 */
#include <iostream>
#include <fstream>
#include <sys/resource.h>
#include <unordered_map>

using namespace std;

void read_file(int pa[], string file, int len);
void generate_query(int *tiny_query, int *med_query, int *huge_query, int query);
double diffUserTime(struct rusage *start, struct rusage *end);
double diffSystemTime(struct rusage *start, struct rusage *end);

int main() {


    int len = 0;
    cout << "please input the length of the array: ";
    //cin >> len;
    //  len = 10000000;
    len = 8571089;
    //   len = 6715122;



    int *pa = new int[len];


    //  string file_in = "/users/grad/liu1/data_book/book_1000.txt";
    string file_in = "/users/grad/liu1/data_ip/ip_857.txt";
    //   string file_in = "/users/grad/liu1/data_text/text_671.txt";
    //    string file_in = "/users/grad/liu1/data_library/lib_1000.txt";
    //  string file_in = "/users/grad/liu1/data_park/park_1000.txt";

    read_file(pa, file_in, len);
    int *tiny_query = new int[2000000];
    int *med_query = new int[2000000];
    int *huge_query = new int[2000000];
    int *result = new int[3000000];
    generate_query(tiny_query, med_query, huge_query, 2000000);

    int start_index = 0;
    int end_index = 0;

    int delta = 0;
    for (int i = 0; i < len; i++) {
        delta = max(delta, pa[i]);
    }

    int *pa_restart = new int[delta + 1];
    int mode = 0;    // save mode
    int maxFreq = 0;   // save the freq of the mode



    struct rusage start, end;





    cout << "Tiny Query is:" <<endl;
    getrusage(RUSAGE_SELF, &start);
    for (int i = 0; i < 2000000; i+=2) {
        start_index = tiny_query[i];
        end_index = tiny_query[i + 1];
        mode = 0;
        maxFreq = 0;
        for (int i = 0; i < delta + 1; i++) {
            pa_restart[i] = 0;
        }

        // nv2: just maintain one counter for each distinct element and traverse the query range once to get the mode

        for (int i = start_index - 1; i < end_index; i++) {
            pa_restart[pa[i]]++;
            if (pa_restart[pa[i]] > maxFreq) {
                maxFreq = pa_restart[pa[i]];
                mode = pa[i];
            }
        }

        result[(i / 2)] = maxFreq;
    }
    getrusage(RUSAGE_SELF, &end);
    cout << " Tiny Query Total Time : " << (double)(diffUserTime(&start, &end) + diffSystemTime(&start, &end)) <<" s " << endl;

    cout << "Med Query is:" <<endl;
    getrusage(RUSAGE_SELF, &start);
    for (int i = 2000000; i < 4000000; i+=2) {
        start_index = med_query[i - 2000000];
        end_index = med_query[i + 1 - 2000000];
        mode = 0;
        maxFreq = 0;
        for (int i = 0; i < delta + 1; i++) {
            pa_restart[i] = 0;
        }

        // nv2: just maintain one counter for each distinct element and traverse the query range once to get the mode

        for (int i = start_index - 1; i < end_index; i++) {
            pa_restart[pa[i]]++;
            if (pa_restart[pa[i]] > maxFreq) {
                maxFreq = pa_restart[pa[i]];
                mode = pa[i];
            }
        }

        result[(i / 2)] = maxFreq;
    }
    getrusage(RUSAGE_SELF, &end);
    cout << " Med Query Total Time : " << (double)(diffUserTime(&start, &end) + diffSystemTime(&start, &end)) <<" s " << endl;

    cout << "Huge Query is:" <<endl;
    getrusage(RUSAGE_SELF, &start);
    for (int i = 4000000; i < 6000000; i+=2) {
        start_index = huge_query[i - 4000000];
        end_index = huge_query[i + 1 - 4000000];
        mode = 0;
        maxFreq = 0;
        for (int i = 0; i < delta + 1; i++) {
            pa_restart[i] = 0;
        }

        // nv2: just maintain one counter for each distinct element and traverse the query range once to get the mode

        for (int i = start_index - 1; i < end_index; i++) {

            pa_restart[pa[i]]++;
            if (pa_restart[pa[i]] > maxFreq) {
                maxFreq = pa_restart[pa[i]];
                mode = pa[i];
            }
        }

        result[(i / 2)] = maxFreq;
    }
    getrusage(RUSAGE_SELF, &end);
    cout << " Huge Query Total Time : " << (double)(diffUserTime(&start, &end) + diffSystemTime(&start, &end)) <<" s " << endl;




    delete[] pa;
    delete[] tiny_query;
    delete[] med_query;
    delete[] huge_query;
    ofstream normal_result("/users/grad/liu1/data_ip/2correct_result.txt");

    for (int i = 0; i < 3000000; i++) {

        normal_result << result[i] << " ";
        if ((i + 1) % 10 == 0) {
            normal_result << endl;
        }
    }
    if (normal_result) {
        cout << endl;
        cout << "create normal result file successfully!" << endl;
    }
    normal_result.close();
    normal_result.clear();
    delete[] result;
}
void generate_query(int *tiny_query, int *med_query, int *huge_query, int query){
    int len = query;
    /*string tiny_file = "/users/grad/liu1/tiny.txt";
    string med_file = "/users/grad/liu1/med.txt";
    string huge_file = "/users/grad/liu1/huge.txt";*/
    string tiny_file = "/users/grad/liu1/data_ip/tinyExact.txt";
    string med_file = "/users/grad/liu1/data_ip/medExact.txt";
    string huge_file = "/users/grad/liu1/data_ip/hugeExact.txt";
    ifstream tiny_in(tiny_file);
    ifstream med_in(med_file);
    ifstream huge_in(huge_file);
    if (!tiny_in.is_open()) {
        cout << " cannot open the tiny file" << endl;
    }
    for (int i = 0; i < len; i++) {
        tiny_in >> tiny_query[i];
    }
    if (!med_in.is_open()) {
        cout << " cannot open the med file" << endl;
    }
    for (int i = 0; i < len; i++) {
        med_in >> med_query[i];
    }
    if (!huge_in.is_open()) {
        cout << " cannot open the huge file" << endl;
    }
    for (int i = 0; i < len; i++) {
        huge_in >> huge_query[i];
    }
    tiny_in.close();
    tiny_in.clear();
    med_in.close();
    med_in.clear();
    huge_in.close();
    huge_in.clear();
}

void read_file(int pa[], string file, int len) {
    ifstream file_in(file);
    if (!file_in.is_open()) {
        cout << " cannot open the file" << endl;
    }
    for (int i = 0; i < len; i++) {
        file_in >> pa[i];
    }

    file_in.close();
    file_in.clear();
}
double diffUserTime(struct rusage *start, struct rusage *end)
{
    return (end->ru_utime.tv_sec - start->ru_utime.tv_sec) +
           1e-6*(end->ru_utime.tv_usec - start->ru_utime.tv_usec);
}

double diffSystemTime(struct rusage *start, struct rusage *end)
{
    return (end->ru_stime.tv_sec - start->ru_stime.tv_sec) +
           1e-6*(end->ru_stime.tv_usec - start->ru_stime.tv_usec);
}