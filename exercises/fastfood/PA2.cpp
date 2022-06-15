//2018-04736
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

typedef long long int llint;
typedef std::vector<llint> vlint;

//Builds the parameters for store Q
void make_store(std::string input, int &L, int &M, int &N, llint &T, vlint &menu_price, vlint &menu_time, vlint &cust_q) {
    llint temp_price = 0;
    llint temp_time = 0;
    llint temp_order = 0;
    std::fstream fh("input.txt", std::ios_base::in);    
    fh >> L >> M >> N >> T;
    for (int i = 0; i < M; i++) {
        fh >> temp_price >> temp_time;
        menu_price.push_back(temp_price);
        menu_time.push_back(temp_time);
    } 
    for (int i = 0; i < N; i++) {
        fh >> temp_order;
        cust_q.push_back(temp_order);
    }
    fh.close();

    std::cout << "Store built. Store Q has " 
              << M << " items in the menu, has " 
              << L << " cashiers and can serve customers every " 
              << T << " seconds.\n";
}

//Simplifies the customer orders into two containers (price and cost)
std::vector<vlint> proc_order(int M, int N, vlint menu_price, vlint menu_times, vlint cust_q) {
    std::vector<vlint> out;
    vlint price(N);
    vlint times(N);
    for (int i = 0; i < N; i++) {
        llint n = cust_q[i];
        for (int j = M; j >= 1; j--) { //Loop time complexity is O(M)
            llint temp = pow(2, j-1);
            if (n - temp <= 0) {
                if (n - temp == 0) {
                    price[i] += menu_price[j-1];
                    times[i] += menu_times[j-1];
                    break;
                }
                continue;
            }
            price[i] += menu_price[j-1];
            times[i] += menu_times[j-1];
            n -= temp;
        }
    }
    out.push_back(times);
    out.push_back(price);

    std::cout << N << " customers have their orders processed.\n";

    return out;
}

//Sorting algorithm to know which lane is nearest to entrance and has less customers, prioritizing the latter.
bool prio_sort(vlint i,vlint j) { 
    if (i.size() == j.size()) {
        return (i[0] < j[0]);
    }
    return (i.size() < j.size()); 
}

//Modifies each lane using the parameter T
void prio_lane(std::vector<vlint> &lane, llint T, int mod) {
    for (int i = 0; i < lane.size(); i++) { //Loop time complexity is O(L)
        if (lane[i].size() == 3) {
            continue;
        }
        lane[i][3] -= T;
        while (lane[i][3] <= 0) {
            //This is not O(N)
            //If gap between T and time per customer order is negligible (significantly small)
            //Then loop will run at most two times
            //Else if gap is large enough (including very large gaps)
            //Then loop will run once
            //Either way loop will have complexity O(1)
            //Sorry if I didn't implement it using two if statements earlier
            if (lane[i].size() == 4) {
                lane[i].erase(lane[i].begin()+3);
                if (!mod) {lane[i][2] -= 1;}
                break;
            }
            llint temp = lane[i][3];
            lane[i].erase(lane[i].begin()+3);
            if (!mod) {lane[i][2] -= 1;}
            lane[i][3] += temp;
        }
    }
    std::sort(lane.begin(), lane.end(), prio_sort);
}

//Simulation of store Q based from its parameters
std::vector<vlint> sim_store(int N, int L, llint T, vlint times, vlint cost) {
    std::vector<vlint> lane;
    for (llint i = 0; i < L; i++) {
        vlint temp {i+1, 0, 0};
        lane.push_back(temp);
    }
    for (int i = 0; i < N; i++) {
        if (i == N - 1 && T!= 0) {
            prio_lane(lane, T, lane[0][3]%T);
        }
        else {prio_lane(lane, T, 0);}
        lane[0].push_back(times[i]);
        lane[0][1] += cost[i];
        lane[0][2] += 1;
    }
    for (int i = 0; i < L; i++) {
        if (lane[i].size() < 4) {
            lane[i].push_back(0);
        }
    }

    std::cout << "Simulation done.\n";

    return lane;
}

//Writes output to a text file
void output(std::vector<vlint> vec, llint gap, std::string out) {
    llint max_qtime = 0;
    llint max_crowd = 0;
    llint profit = 0;
    for (int i = 0; i < vec.size(); i++) { //Loop time complexity is O(L)
        max_crowd += vec[i][2];
        profit += vec[i][1];
        while (vec[i].size() != 4) {
            vec[i][3] += vec[i][4];
            vec[i].erase(vec[i].begin()+ 4);
        }
        if (vec[i][3] > max_qtime) {
            max_qtime = vec[i][3];
        }
    } 
    std::sort(vec.begin(), vec.end());
    std::ofstream outf;
    outf.open(out);
    for (int i = 0; i < vec.size(); i++) {
        outf << vec[i][1] << ' ';
    }
    outf << '\n' << max_qtime+gap << ' ' << max_crowd;
    outf.close();

    std::cout << "Dear diary, today my store sold a few burgers for " 
              << profit << " dollars. See full report on output.txt.\n";    
}

int main() {
    int L = 0; //cashier
    int M = 0; //menu
    int N = 0; //orders
    llint T = 0; //time gap
    vlint menu_price;
    vlint menu_time;
    vlint cust_q; 
    make_store("input.txt", L, M, N, T, menu_price, menu_time, cust_q);
    std::vector<vlint> orders = proc_order(M, N, menu_price, menu_time, cust_q);
    std::vector<vlint> out = sim_store(N, L, T, orders[0], orders[1]);
    output(out, T*(N-1), "output.txt");
}


