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

//[BONUS] Sorting algorithm to know which lane is farthest to entrance and will finish at an earlier time, prioritizing the latter.
bool prio_sort_bonus(vlint i, vlint j) {
    if (i[2] == j[2]) {
        return (i[0] > j[0]);
    }
    return (i[2] < j[2]);
}

//[BONUS] Modifies each lane using the parameter T
void prio_lane_bonus(std::vector<vlint> &lane, llint T) {
    int onefilled = 0;
    for (int i = 0; i < lane.size(); i++) { //Loop time complexity is O(L)
        if (lane[i][2] != 0) {
            onefilled += 1;
        }
    }
    for (int i = 0; i < lane.size(); i++) { //Loop time complexity is O(L)
        lane[i][2] -= T;
        if (lane[i][2] < 0 && onefilled != 1) {
            lane[i][2] = 0;
        }
        if (lane[i].size() == 3) {
            continue;
        }
        lane[i][3] -= T;
        if (onefilled != 1) {
            while (lane[i][3] <= 0) {
                if (lane[i].size() == 4) {
                    lane[i].erase(lane[i].begin()+3);
                    break;
                }
                llint temp = lane[i][3];
                lane[i].erase(lane[i].begin()+3);
                lane[i][3] += temp;
            }
        }
    }
    std::sort(lane.begin(), lane.end(), prio_sort_bonus);
}

//[BONUS] Simulation of store Q based from its parameters
std::vector<vlint> sim_store_bonus(int N, int L, llint T, vlint times, vlint cost) {
    std::vector<vlint> lane;
    for (llint i = 0; i < L; i++) {
        vlint temp {L-i, 0, 0};
        lane.push_back(temp);
    }
    for (int i = 0; i < N; i++) {
        
        lane[0][2] += times[i];
        lane[0][1] += cost[i];
        lane[0].push_back(times[i]);
        if (i != N -1) {
            prio_lane_bonus(lane, T);
        }
    }
    for (int i = 0; i < L; i++) {
        if (lane[i].size() < 4) {
            lane[i].push_back(0);
        }
    }
 
    std::cout << "[BONUS] Simulation done.\n";
    
    return lane;
}

//[BONUS] Writes expected output to a text file with minor changes
void output_bonus(std::vector<vlint> vec, llint gap, std::string out) {
    llint max_qtime = 0;
    llint max_crowd = 0;
    llint profit = 0;
    for (int i = 0; i < vec.size(); i++) { //Loop time complexity is O(L)
        max_crowd += vec[i].size();
        profit += vec[i][1];
        if (vec[i][1] == 0 && vec[i][3] == 0) {
            max_crowd -= 1;
        }
        while (vec[i].size() != 3) {
            vec[i][2] += vec[i][3];
            vec[i].erase(vec[i].begin()+3);
        }
        if (vec[i][2] > max_qtime) {
            max_qtime = vec[i][2];
        }
    }
    std::sort(vec.begin(), vec.end());
    max_crowd -= (vec.size()*3);
    max_qtime /= 2;
    std::ofstream outf;
    outf.open(out);
    for (int i = 0; i < vec.size(); i++) {
        outf << vec[i][1] << ' ';
    }
    outf << '\n' << max_qtime+gap << ' ' << max_crowd;
    outf.close();

    std::cout << "[BONUS] Dear diary, today my store sold a few burgers for " 
              << profit << " dollars. See full report on output_bonus.txt.\n";    
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
    std::vector<vlint> out_bonus = sim_store_bonus(N, L, T, orders[0], orders[1]);
    output_bonus(out_bonus, T*(N-1), "output_bonus.txt");
}


