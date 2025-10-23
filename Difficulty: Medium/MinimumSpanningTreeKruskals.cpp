class Solution {
  public:

    int getParent(vector<int> &parent, int num)
    {
        if(parent[num] == num)
            return num;
        return (parent[num] = getParent(parent, parent[num]));
    }
    
    void unite(vector<int> &rank, vector<int> &parent, int a, int b)
    {
        int pa = getParent(parent, a);
        int pb = getParent(parent, b);
        if(rank[pa] > rank[pb])
        {
            parent[pb] = pa;
        }
        else if(rank[pa] < rank[pb])
        {
            parent[pa] = pb;
        }
        else
        {
            parent[pa] = pb;
            rank[pb]++;
        }
    }
    
    int kruskalsMST(int V, vector<vector<int>> &edges) {
        int W = 0;
        for(int i=0;i<edges.size();i++)
        {
            swap(edges[i][0], edges[i][2]);
        }
        sort(edges.begin(), edges.end());
        vector<int> parent(V);
        vector<int> rank(V, 0);
        for(int i=0;i<V;i++)    parent[i]=i;
        for(int i=0;i<edges.size();i++)
        {
            if(getParent(parent, edges[i][2]) != getParent(parent, edges[i][1]))
            {
                unite(rank, parent, edges[i][2], edges[i][1]);
                W += edges[i][0];
            }
        }
        return W;
    }
};
