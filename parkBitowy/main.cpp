#include <iostream>
#include <cmath>
#include <assert.h>

using namespace std;

int n;
int log2_n_floor;

// index - numer polanki
// tree[index][0] - numer lewego syna
// tree[index][1] - numer prawego syna
// tree[index][2] - numer ojca (dla index == 1 wartość -1)
int tree[500001][3];

int depth[500001];

//log 500001 = 18,....
int links[19][500001];

//far[index][0] = odległość
//far[index][1] = wierzchołek
int far[500001][2];

//far[index][0] = odległość
//far[index][1] = wierzchołek
int farDown[500001][2];

//far[index][0] = odległość
//far[index][1] = wierzchołek
int farUp[500001][2];


void buildTree() {
    cin >> n;
    log2_n_floor = floor(log2(n));

    tree[1][2] = -1;

    int left;
    int right;

    for (int i = 1; i <= n; i++) {
        cin >> left;
        tree[i][0] = left;
        if (left != -1) {
            tree[left][2] = i;
        }

        cin >> right;
        tree[i][1] = right;
        if (right != -1) {
            tree[right][2] = i;
        }
    }

}

void buildDepthArray(int i) {

    int left = tree[i][0];
    int right = tree[i][1];

    if (left != -1) {
        depth[left] = depth[i] + 1;
        buildDepthArray(left);
    }
    if (right != -1) {
        depth[right] = depth[i] + 1;
        buildDepthArray(right);
    }

}

void buildDepthArray() {
    depth[1] = 0;

    buildDepthArray(1);
}

void buildLinksArray(int v) {

    links[0][v] = tree[v][2];
    for (int i = 1; i < 19; i++) {
        if (links[i - 1][v] != -1) {
            links[i][v] = links[i - 1][links[i - 1][v]];
        } else {
            links[i][v] = -1;
        }
    }

    int left = tree[v][0];
    if (left != -1) {
        buildLinksArray(left);
    }
    int right = tree[v][1];
    if (right != -1) {
        buildLinksArray(right);
    }
}

void buildLinksArray() {

    buildLinksArray(1);
}

int ancestor(int v, int h) {
    int result = v;
    int i = log2_n_floor;
    while (h > 0) {
        int pow = 1 << i;
        if (pow > h) {
            i--;
        } else {
            result = links[i][result];
            h -= pow;
        }
    }

    return result;
}

int lca(int u, int v) {
    int du = depth[u];
    int dv = depth[v];

    if (du < dv) {
        v = ancestor(v, dv - du);
        dv = depth[v];
    } else if (du > dv) {
        u = ancestor(u, du - dv);
        du = depth[u];
    }
    assert (du == dv);
    if (u == v) {
        return u;
    }

    int i = log2_n_floor;
    while (i >= 0) {
        if (links[i][u] != links[i][v]) {
            u = links[i][u];
            v = links[i][v];
        }
        i--;
    }
    return tree[u][2];
}

int maximum( int a, int b, int c )
{
    int max = ( a < b ) ? b : a;
    return ( ( max < c ) ? c : max );
}

void buildFarDown(int u) {
    int d_1 = 0;
    int v_1 = u;
    int d_2 = -1;
    int v_2;
    int d_3 = -1;
    int v_3;

    int left = tree[u][0];
    int right = tree[u][1];

    if (left != -1) {
        buildFarDown(left);
        d_2 = farDown[left][0] + 1;
        v_2 = farDown[left][1];
    }
    if (right != -1) {
        buildFarDown(right);
        d_3 = farDown[right][0] + 1;
        v_3 = farDown[right][1];
    }

    int max = maximum(d_1, d_2, d_3);

    if (max == d_1) {
        farDown[u][0] = d_1;
        farDown[u][1] = v_1;
    } else if (max == d_2) {
        farDown[u][0] = d_2;
        farDown[u][1] = v_2;
    } else {
        farDown[u][0] = d_3;
        farDown[u][1] = v_3;
    }
}

void buildFarUp(int u) {
    int d_1 = 0;
    int v_1 = u;
    int d_2 = -1;
    int v_2;
    int d_3 = -1;
    int v_3;

    int parent = tree[u][2];
    int sibling = -1;

    if (parent != -1) {
        if (tree[parent][0] == u) {
            sibling = tree[parent][1];
        } else {
            sibling = tree[parent][0];
        }
    }

    if (parent != -1) {
        d_2 = farUp[parent][0] + 1;
        v_2 = farUp[parent][1];
    }
    if (sibling != -1) {
        d_3 = farDown[sibling][0] + 2;
        v_3 = farDown[sibling][1];
    }

    int max = maximum(d_1, d_2, d_3);

    if (max == d_1) {
        farUp[u][0] = d_1;
        farUp[u][1] = v_1;
    } else if (max == d_2) {
        farUp[u][0] = d_2;
        farUp[u][1] = v_2;
    } else {
        farUp[u][0] = d_3;
        farUp[u][1] = v_3;
    }


    int left = tree[u][0];
    int right = tree[u][1];

    if (left != -1) {
        buildFarUp(left);
    }
    if (right != -1) {
        buildFarUp(right);
    }

}

void buildFar() {
    buildFarDown(1);
    buildFarUp(1);

    for (int u = 1; u <= n; u++) {
        if (farUp[u][0] > farDown[u][0]) {
            far[u][0] = farUp[u][0];
            far[u][1] = farUp[u][1];
        } else {
            far[u][0] = farDown[u][0];
            far[u][1] = farDown[u][1];
        }
    }
}

int getDistantNode(int u, int d) {
    int d_max = far[u][0];
    int v = far[u][1];

    if (d > d_max) {
        return -1;
    }
    int l = lca(u, v);
    int d1 = depth[u] - depth[l];
    if (d <= d1) {
        return ancestor(u, d);
    } else {
        return ancestor(v, d_max - d);
    }
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    buildTree();
    buildDepthArray();
    buildLinksArray();
    buildFar();

    int m;
    cin >> m;

    int node;
    int distance;

    for (int i = 0; i < m; i++) {
        cin >> node;
        cin >> distance;
        cout << getDistantNode(node, distance) << endl;
    }

    return 0;
}