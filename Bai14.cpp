#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <queue>

using namespace std;

vector<pair<float, float> > node_land;
vector<vector<vector<float> > > center_block;
int m, n;
float width, height;
float d1, d2;
float step_x, step_y;

vector<vector<vector<pair<float, float> > > > boundA;
vector<pair<float, float> > bound_boundA;

void Nhap()
{
    node_land.clear();
    for (int i = 1; i <= 4; i++)
    {
        float x, y;
        cin >> x >> y;
        node_land.push_back(make_pair(x, y));
    }
    cin >> m >> n;
    cin >> width >> height;
}

void Cal_Center()
{
    center_block.clear();
    center_block.resize(n + 1);
    float width_mng = (node_land[1].first - node_land[0].first) / m;
    float height_mng = (node_land[3].second - node_land[0].second) / n;

    for (int i = 1; i <= n; i++)
    {
        float y = node_land[0].second + height_mng / 2 + 1.0 * (i - 1) * height_mng;
        center_block[i].resize(m + 1);
        for (int j = 1; j <= m; j++)
        {
            float x = node_land[0].first + width_mng / 2 + 1.0 * (j - 1) * width_mng;
            center_block[i][j].push_back(x);
            center_block[i][j].push_back(y);
            center_block[i][j].push_back(width_mng);
            center_block[i][j].push_back(height_mng);
        }
    }
}

void sol_a()
{
    Nhap();
    Cal_Center();
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                cout << center_block[i][j][k];
                if (j != m || k != 3)
                    cout << ',';
            }
        }
        cout << '\n';
    }
}

vector<pair<float, float> > nodesquare;
void solb(float i, float j, float d)
{
    float d1 = d + width / 2;
    float d2 = d + height / 2;
    float distant1[4] = {-d1, d1, d1, -d1};
    float distant2[4] = {-d2, -d2, d2, d2};
    for (int k = 0; k < 4; k++)
    {
        pair<float, float> x;
        x.first = i + distant1[k];
        x.second = j + distant2[k];
        nodesquare.push_back(x);
    }
    for (int k = 0; k < 4; k++)
    {
        cout << nodesquare[k].first << "," << nodesquare[k].second << " ";
    }
    nodesquare.clear();
    cout << endl;
}

void sol_b()
{
    float D1, D2;
    cout << "Nhap d1 va d2: ";
    cin >> D1 >> D2;
    cout << "Nhap toa do tam: ";
    float i, j;
    cin >> i >> j;
    solb(i, j, D1);
    solb(i, j, D1 + D2);
}

void sol_c()
{
    Nhap();
    Cal_Center();
    float d1;
    cin >> d1;
    float dist_x = center_block[1][2][0] - center_block[1][1][0] - width - 2 * d1;
    cout << dist_x << '\n';
    if (n <= 1 || m <= 1)
        cout << "undefined\n";
    else
    {
        float dist_y = center_block[2][1][1] - center_block[1][1][1] - height - 2 * d1;
        cout << dist_y << '\n';
    }
}

void sol_d()
{
    Nhap();
    cin >> d1;
    d2 = 2 * d1;
    float node_dx[4] = {d2, -d2, -d2, d2};
    float node_dy[4] = {d2, d2, -d2, -d2};

    for (int i = 0; i < 4; i++)
    {
        float x = node_land[i].first + node_dx[i];
        float y = node_land[i].second + node_dy[i];
        bound_boundA.push_back(make_pair(x, y));
    }

    // 4 hinh vuong ngoai cung
    boundA.clear();
    boundA.resize(n + 1);
    for (int i = 1; i <= n; i++)
    {
        boundA[i].resize(m + 1);
        for (int j = 1; j <= m; j++)
        {
            boundA[i][j].resize(4);
        }
    }

    Cal_Center();

    // boundA[i][j][k]: hang i cot j dinh k

    center_block[1][1][0] = bound_boundA[0].first + d2 + d1 + width / 2;
    center_block[1][1][1] = bound_boundA[0].second + d2 + d1 + height / 2;
    center_block[1][m][0] = bound_boundA[1].first - (d2 + d1 + width / 2);
    center_block[1][m][1] = center_block[1][1][1];
    center_block[n][m][0] = center_block[1][m][0];
    center_block[n][m][1] = bound_boundA[2].second - (d2 + d1 + height / 2);
    center_block[n][1][0] = center_block[1][1][0];
    center_block[n][1][1] = center_block[n][m][1];

    step_x = (center_block[1][m][0] - center_block[1][1][0]) / (m - 1);
    step_y = (center_block[n][1][1] - center_block[1][1][0]) / (n - 1);

    float dx[4] = {-d1 - width / 2, d1 + width / 2, d1 + width / 2, -d1 - width / 2};
    float dy[4] = {-d1 - height / 2, -d1 - height / 2, d1 + height / 2, d1 + height / 2};

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            center_block[i][j][0] = center_block[1][1][0] + step_x * (j - 1);
            center_block[i][j][1] = center_block[1][1][1] + step_y * (i - 1);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                boundA[i][j][k].first = center_block[i][j][0] + dx[k];
                boundA[i][j][k].second = center_block[i][j][1] + dy[k];
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                cout << boundA[i][j][k].first << ',';
                cout << boundA[i][j][k].second << ' ';
            }
            cout << '\n';
        }
    }

    for (int i = 0; i < 4; i++)
    {
        cout << bound_boundA[i].first << ',' << bound_boundA[i].second << ' ';
    }
    cout << '\n';
}

struct duongnoi
{
    pair<float, float> diem1;
    pair<float, float> diem2;
};

vector<duongnoi> intersec;
vector<duongnoi> intersec_bound;

void sol_e()
{
    sol_d();

    // Duong noi bo

    intersec.clear();
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m - 1; j++)
        {
            duongnoi x;
            x.diem1 = boundA[i][j][1];
            x.diem2 = boundA[i][j + 1][0];
            intersec.push_back(x);

            x.diem1 = boundA[i][j][2];
            x.diem2 = boundA[i][j + 1][3];
            intersec.push_back(x);
        }
    }

    for (int i = 1; i <= n - 1; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            duongnoi x;
            x.diem1 = boundA[i][j][3];
            x.diem2 = boundA[i + 1][j][0];
            intersec.push_back(x);

            x.diem1 = boundA[i][j][2];
            x.diem2 = boundA[i + 1][j][1];
            intersec.push_back(x);
        }
    }

    // Duong noi voi bien

    // duong i = 0

    for (int j = 1; j <= m; j++)
    {
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

    // duong i = n - 1

    for (int j = 1; j <= m; j++)
    {
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

    // duong j = 0

    for (int i = 1; i <= n; i++)
    {
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

    // duong j = m - 1;
    for (int i = 1; i <= n; i++)
    {
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

    // Result
    for (int i = 0; i < (int)intersec.size(); i++)
    {
        cout << intersec[i].diem1.first << ',' << intersec[i].diem1.second << ' ';
        cout << intersec[i].diem2.first << ',' << intersec[i].diem2.second << '\n';
    }

    for (int i = 0; i < (int)intersec_bound.size(); i++)
    {
        cout << intersec_bound[i].diem1.first << ',' << intersec_bound[i].diem1.second << ' ';
        cout << intersec_bound[i].diem2.first << ',' << intersec_bound[i].diem2.second << '\n';
    }
}

vector<float> insertline_x;
vector<float> insertline_y;
float d3;
float Y1, Y2, X1, X2;

void insert_y(float y1, float y2)
{
    for (int i = y1 + d3; i < y2; i += d3)
    {
        insertline_y.push_back(i);
    }
}

void insert_x(float x1, float x2)
{
    for (int i = x1 + d3; i < x2; i += d3)
    {

        insertline_x.push_back(i);
    }
}

void insertcolumn()
{
    for (int i = 1; i <= m; i++)
    {
        Y2 = Y1 + d2;
        insert_y(Y1, Y2);
        Y1 = Y2;
        Y2 = Y1 + height + d2;
        insert_y(Y1, Y2);
        Y1 = Y2;
    }
    Y2 = Y1 + d2;
    insert_y(Y1, Y2);
}
void insertrow()
{
    for (int j = 1; j <= m; j++)
    {
        X1 = boundA[1][j][0].first;
        X2 = boundA[1][j][1].first;
        insert_x(X1, X2);
    }
}

void sol_f()
{
    sol_e();
    cin >> d3;
    Y1 = bound_boundA[0].second;
    insertcolumn();
    insertrow();
    for (int j = 1; j <= m - 1; j++)
    {
        for (int k = 0; k < insertline_y.size(); k++)
        {
            duongnoi tmp;
            tmp.diem1.first = boundA[1][j][1].first;
            tmp.diem1.second = insertline_y[k];
            tmp.diem2.first = boundA[1][j + 1][0].first;
            tmp.diem2.second = insertline_y[k];
            intersec.push_back(tmp);

            cout << boundA[1][j][1].first << "," << insertline_y[k] << " ";
            cout << boundA[1][j + 1][0].first << "," << insertline_y[k] << endl;
        }
    }

    for (int k = 0; k < insertline_y.size(); k++)
    {
        duongnoi tmp;
        tmp.diem1.first = bound_boundA[0].first;
        tmp.diem1.second = insertline_y[k];
        tmp.diem2.first = boundA[1][1][0].first;
        tmp.diem2.second = insertline_y[k];
        intersec.push_back(tmp);

        cout << bound_boundA[0].first << "," << insertline_y[k] << " ";
        cout << boundA[1][1][0].first << "," << insertline_y[k] << endl;
    }
    for (int k = 0; k < insertline_y.size(); k++)
    {
        duongnoi tmp;
        tmp.diem1.first = boundA[1][m][1].first;
        tmp.diem1.second = insertline_y[k];
        tmp.diem2.first = bound_boundA[1].first;
        tmp.diem2.second = insertline_y[k];
        intersec.push_back(tmp);

        cout << boundA[1][m][1].first << "," << insertline_y[k] << " ";
        cout << bound_boundA[1].first << "," << insertline_y[k] << endl;
    }

    for (int i = 1; i <= n - 1; i++)
    {
        for (int k = 0; k < insertline_x.size(); k++)
        {
            duongnoi tmp;
            tmp.diem1.first = insertline_x[k];
            tmp.diem1.second = boundA[i][1][3].second;
            tmp.diem2.first = insertline_x[k];
            tmp.diem2.second = boundA[i + 1][1][0].second;
            intersec.push_back(tmp);

            cout << insertline_x[k] << "," << boundA[i][1][3].second << " ";
            cout << insertline_x[k] << "," << boundA[i + 1][1][0].second << endl;
        }
    }
    for (int k = 0; k < insertline_x.size(); k++)
    {
        duongnoi tmp;
        tmp.diem1.first = insertline_x[k];
        tmp.diem1.second = bound_boundA[0].second;
        tmp.diem2.first = insertline_x[k];
        tmp.diem2.second = boundA[1][1][0].second;
        intersec.push_back(tmp);

        cout << insertline_x[k] << "," << bound_boundA[0].second << " ";
        cout << insertline_x[k] << "," << boundA[1][1][0].second << endl;
    }
    for (int k = 0; k < insertline_x.size(); k++)
    {
        duongnoi tmp;
        tmp.diem1.first = insertline_x[k];
        tmp.diem1.second = boundA[n][1][3].second;
        tmp.diem2.first = insertline_x[k];
        tmp.diem2.second = bound_boundA[3].second;
        intersec.push_back(tmp);

        cout << insertline_x[k] << "," << boundA[n][1][3].second << " ";
        cout << insertline_x[k] << "," << bound_boundA[3].second << endl;
    }
}

pair<float, float> find(pair<float, float> point)
{
    for (int i = 0; i < intersec_bound.size(); i++)
    {
        duongnoi tmp = intersec_bound[i];
        if (tmp.diem1.first == point.first && fabs(tmp.diem1.second - point.second) == d2)
        {
            return tmp.diem1;
        }
        if (tmp.diem2.first == point.first && fabs(tmp.diem2.second - point.second) == d2)
        {
            return tmp.diem2;
        }
        if (tmp.diem1.second == point.second && fabs(tmp.diem1.first - point.first) == d2)
        {
            return tmp.diem1;
        }
        if (tmp.diem2.second == point.second && fabs(tmp.diem2.first - point.first) == d2)
        {
            return tmp.diem2;
        }
    }
}

void sol_g()
{
    vector<duongnoi> ans;
    sol_f();
    for (int i = 1; i <= 2; i++)
    {
        char c;
        cin >> c;
        vector<pair<float, float> > point;
        for (int i = 1; i <= 2; i++)
        {
            float x, y;
            cin >> x >> y;
            point.push_back(make_pair(x, y));
        }
        for (int i = 0; i <= 1; i++)
        {
            duongnoi tmp;
            tmp.diem1 = find(point[i]);
            tmp.diem2 = point[i];
            ans.push_back(tmp);
        }
        fflush(stdin);
    }
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i].diem1.first << ',' << ans[i].diem1.second << ' ';
        cout << ans[i].diem2.first << ',' << ans[i].diem2.second << '\n';
    }
}

int cmp(const pair<float, float> &a, const pair<float, float> &b)
{
    if (a.first == b.first)
    {
        return a.second < b.second;
    }
    return a.first < b.first;
}

vector<pair<float, float> > point;

struct edge
{
    int diem1, diem2;
    int d;
};

vector<edge> canh;

void sol_h()
{
    sol_f();
    point.push_back({0, 0});
    for (int i = 0; i < (int)intersec.size(); i++)
    {
        point.push_back(intersec[i].diem1);
        point.push_back(intersec[i].diem2);
    }

    for (int i = 0; i < (int)intersec_bound.size(); i++)
    {
        point.push_back(intersec_bound[i].diem1);
        point.push_back(intersec_bound[i].diem2);
    }

    for (int i = 0; i < 4; i++)
    {
        point.push_back(bound_boundA[i]);
    }

    sort(point.begin(), point.end(), cmp);

    fflush(stdin);

    for (int i = 1; i <= 2; i++)
    {
        char c;
        cin >> c;
        pair<float, float> point1, point2;
        cin >> point1.first >> point1.second >> point2.first >> point2.second;
        point.push_back(point1);
        point.push_back(point2);
    }

    for (int i = 1; i < (int)point.size(); i++)
    {
        if (point[i] == point[i - 1])
        {
            point.erase(point.begin() + i);
            --i;
        }
        else
            cout << "n " << i << " 0 # " << point[i].first << ',' << point[i].second << '\n';
    }
    // them cac canh doc
    vector<int> peakbound;
    peakbound.push_back(1);
    for (int i = 1; i < point.size() - 5; i++)
    {
        if (point[i].first != point[i + 1].first)
        {
            peakbound.push_back(i + 1);
            continue;
        }
        edge x;
        x.diem1 = i;
        x.diem2 = i + 1;
        x.d = point[i + 1].second - point[i].second;
        canh.push_back(x);
    }

    peakbound.push_back(point.size() - 4);

    // them cac canh ngang

    for (int i = 0; i < peakbound.size() - 2; i++)
    {
        int x1 = peakbound[i], x2 = peakbound[i + 1], x3 = peakbound[i + 2];
        if ((x2 - x1) > (x3 - x2))
        {
            for (int k = x1, j = x2; k < x2, j < x3; k++, j++)
            {
                while (point[k].second != point[j].second)
                {
                    k++;
                }
                edge x;
                x.diem1 = j;
                x.diem2 = k;
                x.d = point[j].first - point[k].first;
                canh.push_back(x);
            }
        }
        else if ((x2 - x1) == (x3 - x2))
        {
            for (int k = x1, j = x2; k < x2, j < x3; k++, j++)
            {
                edge x;
                x.diem1 = j;
                x.diem2 = k;
                x.d = point[j].first - point[k].first;
                canh.push_back(x);
            }
        }
        else
        {
            for (int k = x1, j = x2; k < x2, j < x3; k++, j++)
            {
                while (point[k].second != point[j].second)
                {
                    j++;
                }
                edge x;
                x.diem1 = j;
                x.diem2 = k;
                x.d = point[j].first - point[k].first;
                canh.push_back(x);
            }
        }
    }

    // them canh ngoai
	
	
	int diemcuoi = point.size()-1;
    int i = peakbound[0];
    for (; i < peakbound[1]; i++)
    {
        if (point[i].second == point[diemcuoi-3].second)
        {
            edge x;
            x.diem1 = diemcuoi - 3;
            x.diem2 = i;
            x.d = point[i].first - point[diemcuoi - 3].first;
            canh.push_back(x);
            break;
        }
    }
      for (; i < peakbound[1]; i++)
    {
        if (point[i].second == point[diemcuoi-2].second)
        {
            edge x;
            x.diem1 = diemcuoi-2;
            x.diem2 = i;
            x.d = point[i].first - point[diemcuoi-2].first;
            canh.push_back(x);
            break;
        }
    }
    int last = peakbound.size()-1;
    i = peakbound[last-1];
     for (; i < peakbound[last]; i++)
    {
        if (point[i].second == point[diemcuoi -1].second)
        {
            edge x;
            x.diem1 = i;
            x.diem2 = diemcuoi -1;
            x.d = point[diemcuoi -1].first - point[i].first;
            canh.push_back(x);
            break;
        }
    }
      for (; i < peakbound[last]; i++)
    {
        if (point[i].second == point[diemcuoi].second)
        {
            edge x;
            x.diem1 = i;
            x.diem2 = diemcuoi;
            x.d = point[diemcuoi].first - point[i].first;
            canh.push_back(x);
            break;
        }
    }

    for (int i = 0; i < canh.size(); i++)
    {
        cout << "a " << canh[i].diem1 << " " << canh[i].diem2 << " 0 INF " << canh[i].d << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // sol_a();
    // sol_c();
    // sol_d();
    // sol_e();
    // sol_f();
    // sol_g();
    sol_h();
    return 0;
}
