class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        int mini = INT_MAX, maxi = INT_MIN;
        unordered_set<int>st;
        for(int x: nums){
            mini = min(mini, x);
            maxi = max(maxi, x);
            st.insert(x);
        }
        vector<int>ans;
        for(int i =mini; i<maxi; i++){
            if(!st.count(i))
            ans.push_back(i);
        }
        return ans;
    }
};