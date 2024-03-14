#include <iostream>
#include <vector>

using namespace std;

vector <pair<float, float>> node_land;
vector <vector <vector <float>>> center_block;
int m, n;
float width, height;

void Nhap(){
    node_land.clear();
    for (int i = 1; i <= 4; i++){
        float x, y;
        cin >> x >> y;
        node_land.push_back(make_pair(x, y));
    }
    cin >> m >> n;
    cin >> width >> height;

    center_block.clear();
    center_block.resize(n);
    float width_mng = (node_land[1].first - node_land[0].first)/m;
    float height_mng = (node_land[3].second - node_land[0].second)/n;
    for (int i = 0; i < n; i++){
        float y = node_land[0].second + (node_land[3].second - node_land[0].second)/(2 * n) + 1.0 * i * (node_land[3].second - node_land[0].second)/n;
        center_block[i].resize(m);
        for (int j = 0; j < m; j++){
            float x = node_land[0].first + (node_land[1].first - node_land[0].first)/(2 * m) + 1.0 * j * (node_land[1].first - node_land[0].first)/m;
            center_block[i][j].push_back(x);
            center_block[i][j].push_back(y);
            center_block[i][j].push_back(width_mng);
            center_block[i][j].push_back(height_mng);
        }
    }
}

void sol_a(){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            for (int k = 0; k < 4; k++){
                cout << center_block[i][j][k];
                if (j != m - 1 || k != 3) cout << ',';
            }
        }
        cout << '\n';
    }
}

void sol_b(){

}

void sol_c(){
    Nhap();
    float d1;
    cin >> d1;
    float dist_x = center_block[0][1][0] - center_block[0][0][0] - width - 2 * d1;
    cout << dist_x << '\n';
    if (n <= 1) cout << "undefined\n";
    else{
        float dist_y = center_block[1][0][1] - center_block[0][0][1] - height - 2 * d1;
        cout << dist_y << '\n';
    }
}

int main(){
    //sol_a();
    sol_c();
    return 0;
}