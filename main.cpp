#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>

void countSort(std::vector<int>& arr,std::vector<std::string> &num)
{
    int max = *max_element(arr.begin(), arr.end());
    int min = *min_element(arr.begin(), arr.end());
    int range = max - min + 1;

    std::vector<std::string>temp_out(arr.size());

    std::vector<int> count(range), output(arr.size());
    for (int i = 0; i < arr.size(); i++) {
        count[arr[i] - min]++;
    }

    for (int i = 1; i < count.size(); i++) {
        count[i] += count[i - 1];
    }

    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        temp_out[count[arr[i] - min] - 1] = num[i];
        count[arr[i] - min]--;
    }



    for (int i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
        std::swap(num[i],temp_out[i]);
    }
}
/////////////////////

void merge(std::vector<int> &arr, int l, int mm, int r,std::vector<std::string> &num) {
    std::vector<int>result;
    std::vector<std::string>result2;

    //getting indexes to divide
    int i = l, j = mm + 1;

    while(i <= mm && j <= r) {
        //pins vector divided into two
        if(arr[i] <= arr[j]) {
            result.push_back(arr[i]);
            result2.push_back(num[i]);
            i++;
        }
        else {
            result.push_back(arr[j]);
            result2.push_back(num[j]);
            j++;
        }

    }

    // pushing back remaining elements
    while(i <= mm) {
        result.push_back(arr[i]);
        result2.push_back(num[i]);
        i++;
    }

    // pushing back remaining elements
    while(j <= r) {
        result.push_back(arr[j]);
        result2.push_back(num[j]);
        j++;
    }

    i = l, j = 0;
    while(i <= r) {
        arr[i] = result[j];
        num[i] = result2[j];
        i++;
        j++;
    }
}

void mergeSort(std::vector<int> &arr, int l, int r,std::vector<std::string>&num) {
    if (l == r) {
        return;
    }
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m,num);
        mergeSort(arr, m + 1, r,num);

        merge(arr, l, m, r,num);

}


/////
void count_given_nunber_of_lines(int lines, std::vector<double>&countsort_time, std::vector<double>&mergesort_time, std::vector<int>&lines_number  ){
    std::string line;
    std::ifstream file;
    file.open("creditcardnumbers.txt");
    std::vector<std::string>cnumber;
    std::vector<int>cpin;
    int count=0;
    if(file.is_open()) {
        //SKIPPING FIRST 2 LINES
        for (int i = 0; i < 2; i++)
            file.ignore(256,'\n');

        while(std::getline(file, line) && count<lines) {
                auto pos = line.find_last_of(' ');
                std::string text = line.substr(0, pos);
                int number = std::stoi(line.substr(pos));
                cnumber.push_back(text);
                cpin.push_back(number);
                count++;
            }

    }
    else{
        std::cout << "wrong";
    }
    file.close();


    std::vector<std::string>cnumber2 = cnumber;
    std::vector<int>cpin2 = cpin;
    double m_time,c_time;
    LARGE_INTEGER t1, t2, f, diff;

    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t1);
    mergeSort(cpin,0,lines-1,cnumber);
    QueryPerformanceCounter(&t2);
    m_time = ((t2.QuadPart - t1.QuadPart) / (double)f.QuadPart);

    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t1);
    countSort(cpin2,cnumber2);
    QueryPerformanceCounter(&t2);
    c_time = ((t2.QuadPart - t1.QuadPart) / (double)f.QuadPart);



    std::cout << "Merge sort time for " << lines << " elements: " << m_time << " seconds"<<std::endl;
    std::cout << "Counting sort time for " << lines <<" elements: " << c_time << " seconds"<<std::endl;
    puts("");
    countsort_time.push_back(c_time);
    mergesort_time.push_back(m_time);
    lines_number.push_back(lines);
}


int main() {

    std::string line;
    std::ifstream file;
    file.open("creditcardnumbers.txt");
    int lines =0;

    std::vector<std::string>cnumber;
    std::vector<int>cpin;
    if(file.is_open()) {
        //SKIPPING FIRST 2 LINES
        for (int i = 0; i < 2; i++)
            file.ignore(256,'\n');

        while(std::getline(file,line)){
            auto pos = line.find_last_of(' ');
            std::string text= line.substr(0, pos);
            int number= std::stoi(line.substr(pos));
            cnumber.push_back(text);
            cpin.push_back(number);
        }
    }
    else{
        std::cout << "wrong";
    }

    std::vector<std::string>cnumber2;
    std::vector<int>cpin2;


    cnumber2=cnumber;
    cpin2 = cpin;
    double m_time,c_time;
    LARGE_INTEGER t1, t2, f, diff;

    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t1);
    mergeSort(cpin,0,20000,cnumber);
    QueryPerformanceCounter(&t2);
    m_time = ((t2.QuadPart - t1.QuadPart) / (double)f.QuadPart);

    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t1);
    countSort(cpin2,cnumber2);
    QueryPerformanceCounter(&t2);
    c_time = ((t2.QuadPart - t1.QuadPart) / (double)f.QuadPart);

    std::vector<double>countsort_time;
    std::vector<double>mergesort_time;
    std::vector<int>lines_number;

    //CONVERTING TO STRING
    std::vector<std::string>pin_string;
    std::vector<std::string>pin_string2;
    for(int i=0;i<cpin.size();i++){
        std::string p = std::to_string(cpin[i]);
        pin_string.push_back(p);
        std::string p2 = std::to_string(cpin2[i]);
        pin_string2.push_back(p2);
    }
    //ADDING 0's
    std::string v1 = "000";
    std::string v2 = "00";
    std::string v3 = "0";
    for(int i=0;i<pin_string.size();i++){
        if (v1.length() == pin_string[i].length())
            pin_string[i].insert(0,v3);
        if(v2.length() == pin_string[i].length())
            pin_string[i].insert(0,v2);
        if(v3.length() == pin_string[i].length())
            pin_string[i].insert(0,v1);
    }

    for(int i=0;i<pin_string2.size();i++){
        if (v1.length() == pin_string2[i].length())
            pin_string2[i].insert(0,v3);
        if(v2.length() == pin_string2[i].length())
            pin_string2[i].insert(0,v2);
        if(v3.length() == pin_string2[i].length())
            pin_string2[i].insert(0,v1);
    }

    puts("MergeSort");
    for(int i=0;i<pin_string.size();i++){
        std::cout << cnumber[i] << " " << pin_string[i] <<std::endl;
    }

    puts("Counting sort");
    for(int i=0;i<pin_string.size();i++){
        std::cout << cnumber2[i] << " " << pin_string2[i] <<std::endl;
    }

    puts("");
    puts("");
    std::cout << "Merge sort time for 20k elements: " << m_time << " seconds"<<std::endl;
    std::cout << "Counting sort time for 20k elements: " << c_time << " seconds"<<std::endl;
    puts("");
    for(int i=10;i<=29;i++)
        count_given_nunber_of_lines(i,countsort_time,mergesort_time,lines_number);

    for(int i=30;i<=1000;i=i+50)
        count_given_nunber_of_lines(i,countsort_time,mergesort_time,lines_number);

    for(int i=1500;i<=15000;i=i+1000)
        count_given_nunber_of_lines(i,countsort_time,mergesort_time,lines_number);


    countsort_time.push_back(c_time);
    mergesort_time.push_back(m_time);
    lines_number.push_back(20000);


    std::ofstream of("t2.txt", std::ofstream::out);
    of << "lines\tmergeSort\tcountSort\n";
    for (int i = 0; i < lines_number.size(); i++) {
        of << lines_number[i]
           << '\t'
           <<std::fixed << mergesort_time[i]
           << '\t'
           <<std::fixed << countsort_time[i]
           << '\n';
    }
    of.close();
    system("START \"\" \"C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE\" t2.txt");

    return 0;
}


