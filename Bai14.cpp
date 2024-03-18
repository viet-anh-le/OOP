#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

vector <pair<float, float>> node_land;
vector <vector <vector <float>>> center_block;
int m, n;
float width, height;
float d1, d2;
float step_x, step_y;

vector<vector<vector <pair<float, float>>>> boundA;
vector<pair<float,float>> bound_boundA;

void Nhap(){
    node_land.clear();
    for (int i = 1; i <= 4; i++){
        float x, y;
        cin >> x >> y;
        node_land.push_back(make_pair(x, y));
    }
    cin >> m >> n;
    cin >> width >> height;
}

void Cal_Center(){
    center_block.clear();
    center_block.resize(n + 1);
    float width_mng = (node_land[1].first - node_land[0].first)/m;
    float height_mng = (node_land[3].second - node_land[0].second)/n;

    for (int i = 1; i <= n; i++){
        float y = node_land[0].second + height_mng/2 + 1.0 * (i - 1) * height_mng;
        center_block[i].resize(m + 1);
        for (int j = 1; j <= m; j++){
            float x = node_land[0].first + width_mng/2 + 1.0 * (j - 1) * width_mng;
            center_block[i][j].push_back(x);
            center_block[i][j].push_back(y);
            center_block[i][j].push_back(width_mng);
            center_block[i][j].push_back(height_mng);
        }
    }
}

void sol_a(){
    Nhap();
    Cal_Center();
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            for (int k = 0; k < 4; k++){
                cout << center_block[i][j][k];
                if (j != m || k != 3) cout << ',';
            }
        }
        cout << '\n';
    }
}

void sol_b(){

}

void sol_c(){
    Nhap();
    Cal_Center();
    float d1;
    cin >> d1;
    float dist_x = center_block[1][2][0] - center_block[1][1][0] - width - 2 * d1;
    cout << dist_x << '\n';
    if (n <= 1 || m <= 1) cout << "undefined\n";
    else{
        float dist_y = center_block[2][1][1] - center_block[1][1][1] - height - 2 * d1;
        cout << dist_y << '\n';
    }
}

void sol_d(){
    Nhap();
    cin >> d1;
    d2 = 2 * d1;
    float node_dx[4] = { d2, -d2, -d2, d2 };
    float node_dy[4] = { d2, d2, -d2, -d2 };

    for (int i = 0; i < 4; i++) {
        float x = node_land[i].first + node_dx[i];
        float y = node_land[i].second + node_dy[i];
        bound_boundA.push_back(make_pair(x, y));
    }

    //4 hinh vuong ngoai cung
    boundA.clear();
    boundA.resize(n + 1);
    for (int i = 1; i <= n; i++){
        boundA[i].resize(m + 1);
        for (int j = 1; j <= m; j++){
            boundA[i][j].resize(4);
        }
    }

    Cal_Center();

    //boundA[i][j][k]: hang i cot j dinh k
    
    center_block[1][1][0] = bound_boundA[0].first + d2 + d1 + width/2;
    center_block[1][1][1] = bound_boundA[0].second + d2 + d1 + height/2;
    center_block[1][m][0] = bound_boundA[1].first - (d2 + d1 + width/2);
    center_block[1][m][1] = center_block[1][1][1];
    center_block[n][m][0] = center_block[1][m][0];
    center_block[n][m][1] = bound_boundA[2].second - (d2 + d1 + height/2);
    center_block[n][1][0] = center_block[1][1][0];
    center_block[n][1][1] =  center_block[n][m][1];


    step_x = (center_block[1][m][0] - center_block[1][1][0] ) / (m - 1);
    step_y = (center_block[n][1][1] - center_block[1][1][0]) / (n - 1);

    float dx[4] = {-d1 - width/2, d1 + width/2, d1 + width/2, -d1 - width/2};
    float dy[4] = {-d1 - height/2, -d1 - height/2, d1 + height/2, d1 + height/2};

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            center_block[i][j][0] = center_block[1][1][0] + step_x * (j - 1);
            center_block[i][j][1] = center_block[1][1][1] + step_y * (i - 1);
        }
    }

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            for (int k = 0; k < 4; k++){
                boundA[i][j][k].first = center_block[i][j][0] + dx[k];
                boundA[i][j][k].second = center_block[i][j][1] + dy[k];
            }
        }
    }

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            for (int k = 0; k < 4; k++){
                cout << boundA[i][j][k].first << ',';
                cout << boundA[i][j][k].second << ' ';
            }
            cout << '\n';
        }
    }

    for (int i = 0; i < 4; i++){
        cout << bound_boundA[i].first << ',' << bound_boundA[i].second << ' ';
    }
    cout << '\n';
}

struct duongnoi{
    pair <float,float> diem1;
    pair <float,float> diem2;
};

vector <duongnoi> intersec;
vector <duongnoi> intersec_bound;

int cmp(const duongnoi &a, const duongnoi &b){
    if (a.diem1.second == b.diem1.second){
        return a.diem1.first < b.diem1.first;
    }
    return a.diem1.second < b.diem1.second;
}

void sol_e(){
    sol_d();

    //Duong noi bo

    intersec.clear();
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m - 1; j++){
            duongnoi x;
            x.diem1 = boundA[i][j][1];
            x.diem2 = boundA[i][j + 1][0];
            intersec.push_back(x);

            x.diem1 = boundA[i][j][2];
            x.diem2 = boundA[i][j + 1][3];
            intersec.push_back(x);
        }
    }

    for (int i = 1; i <= n - 1; i++){
        for (int j = 1; j <= m; j++){
            duongnoi x;
            x.diem1 = boundA[i][j][3];
            x.diem2 = boundA[i + 1][j][0];
            intersec.push_back(x);

            x.diem1 = boundA[i][j][2];
            x.diem2 = boundA[i + 1][j][1];
            intersec.push_back(x);
        }
    }

    //Duong noi voi bien

    //duong i = 0

    for (int j = 1; j <= m; j++){
        duongnoi x;
        x.diem2 = boundA[1][j][0];
        x.diem1.first = x.diem2.first;
        x.diem1.second = x.diem2.second - 2 * d1;
        intersec_bound.push_back(x);

        x.diem2 = boundA[1][j][1];
        x.diem1.first = x.diem2.first;
        x.diem1.second = x.diem2.second - 2 * d1;
        intersec_bound.push_back(x);
    }

    //duong i = n - 1

    for (int j = 1; j <= m; j++){
        duongnoi x;
        x.diem1 = boundA[n][j][2];
        x.diem2.first = x.diem1.first;
        x.diem2.second = x.diem1.second + 2 * d1;
        intersec_bound.push_back(x);

        x.diem1 = boundA[n][j][3];
        x.diem2.first = x.diem1.first;
        x.diem2.second = x.diem1.second + 2 * d1;
        intersec_bound.push_back(x);
    }

    //duong j = 0

    for (int i = 1; i <= n; i++){
        duongnoi x;
        x.diem2 = boundA[i][1][0];
        x.diem1.first = x.diem2.first - 2 * d1;
        x.diem1.second = x.diem2.second;
        intersec_bound.push_back(x);

        x.diem2 = boundA[i][1][3];
        x.diem1.first = x.diem2.first - 2 * d1;
        x.diem1.second = x.diem2.second;
        intersec_bound.push_back(x);
    }

    //duong j = m - 1;
    for (int i = 1; i <= n; i++){
        duongnoi x;
        x.diem1 = boundA[i][m][1];
        x.diem2.first = x.diem1.first + 2 * d1;
        x.diem2.second = x.diem1.second;
        intersec_bound.push_back(x);

        x.diem1 = boundA[i][m][2];
        x.diem2.first = x.diem1.first + 2 * d1;
        x.diem2.second = x.diem1.second;
        intersec_bound.push_back(x);
    }

    //Result
    for (int i = 0; i < (int)intersec.size(); i++){
        cout << intersec[i].diem1.first << ',' << intersec[i].diem1.second << ' ';
        cout << intersec[i].diem2.first << ',' << intersec[i].diem2.second << '\n';
    }

    for (int i = 0; i < (int)intersec_bound.size(); i++){
        cout << intersec_bound[i].diem1.first << ',' << intersec_bound[i].diem1.second << ' ';
        cout << intersec_bound[i].diem2.first << ',' << intersec_bound[i].diem2.second << '\n';
    }    
}

vector <duongnoi> p_intersec;

void sol_f(){
    sol_d();
    float d3;
    cin >> d3;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m - 1; j++){
            for (int d = d3; d < height + d2; d += d3){
                duongnoi x;
                x.diem1.first = boundA[i][j][1].first;
                x.diem1.second = boundA[i][j][1].second + d;
                x.diem2.first = boundA[i][j + 1][0].first;
                x.diem2.second = x.diem1.second;
                p_intersec.push_back(x);
            }
        }
    }

    for (int i = 1; i <= n - 1; i++){
        for (int j = 1; j <= m; j++){
            for (int d = d3; d < width + d2; d+= d3){
                duongnoi x;
                x.diem1.first = boundA[i][j][3].first + d;
                x.diem1.second = boundA[i][j][3].second;
                x.diem2.first = x.diem1.first;
                x.diem2.second = boundA[i + 1][j][0].second;
                p_intersec.push_back(x);
            }
        }
    }

    
    //i = 1
    for (int j = 1; j <= m; j++){
        for (int d = d3; d < width + d2; d += d3){
            duongnoi x;
            x.diem1.first = boundA[1][j][0].first + d;
            x.diem1.second = bound_boundA[0].second;
            x.diem2.first = x.diem1.first;
            x.diem2.second = x.diem1.second + d2;
            p_intersec.push_back(x);
        }
    }

    //i = n
    for (int j = 1; j <= m; j++){
        for (int d = d3; d < width + d2; d += d3){
            duongnoi x;
            x.diem1.first = boundA[n][j][3].first + d;
            x.diem1.second = boundA[n][j][3].second;
            x.diem2.first = x.diem1.first;
            x.diem2.second = x.diem1.second + d2;
            p_intersec.push_back(x);
        }
    }

    //i = 0
    

    for (int i = 0; i < (int)p_intersec.size(); i++){
        cout << p_intersec[i].diem1.first << ',' << p_intersec[i].diem1.second << ' ';
        cout << p_intersec[i].diem2.first << ',' << p_intersec[i].diem2.second << '\n';
    }
}

struct Point{
    float x, y;
};

void sol_g(){
    vector <duongnoi> ans;
    sol_e();
    float d3;
    cin >> d3;
    fflush(stdin);
    vector <duongnoi> intersec_bound_x;
    vector <duongnoi> intersec_bound_y;
    for (int i = 0; i < (int)intersec_bound.size(); i++){
        duongnoi tmp = intersec_bound[i];
        if (tmp.diem1.first == tmp.diem2.first){
            intersec_bound_y.push_back(tmp);
        }
        else intersec_bound_x.push_back(tmp);
    }
    char c;
    cin >> c;
    Point point1, point2;
    cin >> point1.x >> point1.y >> point2.x >> point2.y;
    fflush(stdin);
    if (point1.x == point2.x){
        for (int i = 0; i < intersec_bound_x.size(); i++){
            duongnoi tmp = intersec_bound_x[i];
            duongnoi able;
            if (tmp.diem1.second == point1.y && (tmp.diem1.first == point1.x + d2 || tmp.diem1.first == point1.x - d2)){
                able.diem1 = tmp.diem1;
                able.diem2.first = point1.x;
                able.diem2.second = point1.y;
                ans.push_back(able);

                able.diem1.first = tmp.diem1.first;
                able.diem1.second = tmp.diem1.second + point2.y - point1.y;
                able.diem2.first = point2.x;
                able.diem2.second = point2.y;
                ans.push_back(able);
                break;
            }
            else{
                if (tmp.diem2.second == point1.y && (tmp.diem2.first == point1.x + d2 || tmp.diem2.first == point1.x - d2)){
                able.diem1 = tmp.diem2;
                able.diem2.first = point1.x;
                able.diem2.second = point1.y;
                ans.push_back(able);

                able.diem1.first = tmp.diem2.first;
                able.diem1.second = tmp.diem2.second + point2.y - point1.y;
                able.diem2.first = point2.x;
                able.diem2.second = point2.y;
                ans.push_back(able);
                break;
                }
            }
        }
    }
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //sol_a();
    //sol_c();
    //sol_d();
    //sol_e();
    //sol_f();
    return 0;
}