#include <bits/stdc++.h>
using namespace std;

#include "step1_csv.hpp"
#include "step2_stats.hpp"
#include "step3_pathfinding.hpp"
#include "step4_result.hpp"

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    auto elevation = load_csv("elevation.csv");
    auto illumination = load_csv("illumination.csv");
    auto water_ice = load_csv("water_ice.csv");
    auto signal_occultation = load_csv("signal_occultation.csv"); 

    int R = elevation.size(), C = elevation[0].size();
    print_sample(elevation, "elevation");
    print_sample(illumination, "illumination");
    print_sample(water_ice, "water_ice");
    print_sample(signal_occultation, "signal_occultation");




    Prefix2D P_illum(illumination), P_water(water_ice), P_elev(elevation);


    const int K_keep = 3000;     
    const int clusterSize = 25;  

    auto hab_pool = select_candidates(P_illum, P_elev, R, C, K_keep, clusterSize);
    auto min_pool = select_candidates(P_water, P_elev, R, C, K_keep, clusterSize);

    auto byAvg = [](const Candidate& a, const Candidate& b){
        if (a.avg==b.avg) return a.rough<b.rough;
        return a.avg>b.avg;
    };
    sort(hab_pool.begin(), hab_pool.end(), byAvg);
    sort(min_pool.begin(), min_pool.end(), byAvg);


    write_candidates_to_file(hab_pool, min_pool, 20); //most promising candidates go to candidates.txt

    cout << "\nTop 5 Habitat Candidates:\n";
    for(int i=0; i<min(5,(int)hab_pool.size()); i++){
        cout << "  (" << hab_pool[i].r << "," << hab_pool[i].c << ") "
             << "Illum=" << hab_pool[i].avg << " Rough=" << hab_pool[i].rough << "\n";
    }
    cout << "\nTop 5 Mining Candidates:\n";
    for(int i=0; i<min(5,(int)min_pool.size()); i++){
        cout << "  (" << min_pool[i].r << "," << min_pool[i].c << ") "
             << "Water=" << min_pool[i].avg << " Rough=" << min_pool[i].rough << "\n";
    }


    const int NH = min<int>(50, hab_pool.size());
    const int NM = min<int>(50, min_pool.size());


    auto manhattan = [](int r1,int c1,int r2,int c2){
        return abs(r1-r2) + abs(c1-c2);
    };

    float bestScore = -1e9f;
    int bestPath = INT_MAX;
    Candidate bestHab{}, bestMin{};
    const int MAX_EVAL = 2000; // cap A* runs
    int evals = 0;



    //candidate pairs check
    for(int hi=0; hi<NH; ++hi){
        for(int mi=0; mi<NM; ++mi){
            if(evals >= MAX_EVAL) break;

            const auto& Hc = hab_pool[hi];
            const auto& Mc = min_pool[mi];

            int lb = manhattan(Hc.r, Hc.c, Mc.r, Mc.c);
            float optimistic = 0.5f*Hc.avg + 0.5f*Mc.avg - 0.001f*float(lb);
            if (optimistic <= bestScore) continue;

            int path_len = (int)astar_path(elevation, make_pair(Hc.r, Hc.c), make_pair(Mc.r, Mc.c));
            evals++;

            if(path_len >= 1e8f) continue; // no path
            float sc = score_pair(Hc, Mc, path_len);
            if(sc > bestScore){
                bestScore = sc;
                bestPath  = path_len;
                bestHab   = Hc;
                bestMin   = Mc;
            }
        }
        if(evals >= MAX_EVAL) break;
    }

    //  Output
    if(bestScore < -1e8f){
        cout << "\nNo valid pair found under slope constraint.\n";
        ofstream out("result.txt", ios::trunc);
        if(out.is_open()){
            out << "No valid pair found under slope constraint.\n";
            out.close();
            cout << "Fallback result.txt written.\n";
        }
        return 0;
    }

    cout << "\nCombined Score = " << bestScore << "\n";
    cout << "Result written to result.txt\n";
    write_result("result.txt", bestScore, bestHab, bestMin, bestPath);
    return 0;
}
