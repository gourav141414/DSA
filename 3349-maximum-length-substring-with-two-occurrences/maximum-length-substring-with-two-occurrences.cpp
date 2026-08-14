class Solution {
public:
    int maximumLengthSubstring(string s) {
        int n = s.size();
        int left = 0, ans = 0;
        int freq[26] = {};
        for (int right = 0; right < n; right++) {
            freq[s[right] - 'a']++;
            while (freq[s[right] - 'a'] > 2) {
                freq[s[left] - 'a']--;
                left++;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};