class Solution {
public:
    int missingInteger(vector<int>& nums) {
        unordered_set<int>st (nums.begin(), nums.end());
        int total = nums[0];
        for(int i=1; i<nums.size(); i++){
            if(nums[i] == nums[i-1] + 1){
                total += nums[i];
            }
            else{
                break;
            }
        }
        while(st.count(total)){
            total += 1;
        }
        return total;
    }
};