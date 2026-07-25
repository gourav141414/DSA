class Solution {
public:
    int maxProduct(int n) {
        int largest = 0;
        int sLargest = 0;
        while (n > 0) {
            int digit = n % 10;
            if (digit > largest) {
                sLargest = largest;
                largest = digit;
            } else if (digit > sLargest) {
                sLargest = digit;
            }
            n /= 10;
        }
        return largest * sLargest;
    }
};