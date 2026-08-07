class Solution {
public:

    // factors of each digit:
    // 2 -> 2
    // 3 -> 3
    // 4 -> 2^2
    // 5 -> 5
    // 6 -> 2 * 3
    // 7 -> 7
    // 8 -> 2^3
    // 9 -> 3^2

    int f[10][4] = {
        {0,0,0,0}, // 0
        {0,0,0,0}, // 1
        {1,0,0,0}, // 2
        {0,1,0,0}, // 3
        {2,0,0,0}, // 4
        {0,0,1,0}, // 5
        {1,1,0,0}, // 6
        {0,0,0,1}, // 7
        {3,0,0,0}, // 8
        {0,2,0,0}  // 9
    };

    int dp[47][31][21][18];

    int solve(int a, int b, int c, int d) {

        if (a <= 0 && b <= 0 && c <= 0 && d <= 0)
            return 0;

        a = max(a, 0);
        b = max(b, 0);
        c = max(c, 0);
        d = max(d, 0);

        int &res = dp[a][b][c][d];

        if (res != -1)
            return res;

        res = 1e9;

        for (int digit = 2; digit <= 9; digit++) {

            res = min(
                res,
                1 + solve(
                    a - f[digit][0],
                    b - f[digit][1],
                    c - f[digit][2],
                    d - f[digit][3]
                )
            );
        }

        return res;
    }

    string build(int a, int b, int c, int d, int len) {

        string ans;

        while (len > 0) {

            for (int digit = 1; digit <= 9; digit++) {

                int na = max(0, a - f[digit][0]);
                int nb = max(0, b - f[digit][1]);
                int nc = max(0, c - f[digit][2]);
                int nd = max(0, d - f[digit][3]);

                if (solve(na, nb, nc, nd) <= len - 1) {

                    ans += char('0' + digit);

                    a = na;
                    b = nb;
                    c = nc;
                    d = nd;

                    len--;

                    break;
                }
            }
        }

        return ans;
    }

    string smallestNumber(string num, long long t) {

        memset(dp, -1, sizeof(dp));

        // ------------------------------------------------
        // 1. Factorize t
        // ------------------------------------------------

        int need[4] = {0, 0, 0, 0};

        int primes[4] = {2, 3, 5, 7};

        for (int i = 0; i < 4; i++) {

            while (t % primes[i] == 0) {

                need[i]++;
                t /= primes[i];
            }
        }

        // t contains another prime factor
        if (t != 1)
            return "-1";


        // ------------------------------------------------
        // 2. Minimum number of digits required
        // ------------------------------------------------

        int minDigits = solve(
            need[0],
            need[1],
            need[2],
            need[3]
        );

        // If even the shortest possible answer
        // is longer than num, return it.
        if (minDigits > (int)num.size()) {

            return build(
                need[0],
                need[1],
                need[2],
                need[3],
                minDigits
            );
        }


        // ------------------------------------------------
        // 3. Check whether num itself works
        // ------------------------------------------------

        int have[4] = {0, 0, 0, 0};

        bool zero = false;

        for (char ch : num) {

            int digit = ch - '0';

            if (digit == 0) {
                zero = true;
                continue;
            }

            for (int j = 0; j < 4; j++)
                have[j] += f[digit][j];
        }

        if (!zero &&
            have[0] >= need[0] &&
            have[1] >= need[1] &&
            have[2] >= need[2] &&
            have[3] >= need[3]) {

            return num;
        }


        // ------------------------------------------------
        // 4. Try changing one digit
        //    from right to left
        // ------------------------------------------------

        int cur[4] = {0, 0, 0, 0};

        for (char ch : num) {

            int digit = ch - '0';

            for (int j = 0; j < 4; j++)
                cur[j] += f[digit][j];
        }

        int firstZero = num.find('0');

        if (firstZero == string::npos)
            firstZero = num.size();


        for (int i = num.size() - 1; i >= 0; i--) {

            int oldDigit = num[i] - '0';

            // Remove this digit from suffix/current count
            for (int j = 0; j < 4; j++)
                cur[j] -= f[oldDigit][j];

            // If there is a zero before this position,
            // we cannot keep this prefix unchanged.
            if (i > firstZero)
                continue;


            // Try every larger digit
            for (int digit = oldDigit + 1;
                 digit <= 9;
                 digit++) {

                int rem[4];

                for (int j = 0; j < 4; j++) {

                    rem[j] = max(
                        0,
                        need[j] - cur[j] - f[digit][j]
                    );
                }

                int positionsLeft = num.size() - i - 1;


                // Can remaining positions satisfy
                // all required prime factors?
                if (solve(
                        rem[0],
                        rem[1],
                        rem[2],
                        rem[3]
                    ) <= positionsLeft) {

                    string ans = num.substr(0, i);

                    ans += char('0' + digit);

                    ans += build(
                        rem[0],
                        rem[1],
                        rem[2],
                        rem[3],
                        positionsLeft
                    );

                    return ans;
                }
            }
        }


        // ------------------------------------------------
        // 5. No answer of same length
        // ------------------------------------------------

        // IMPORTANT FIX:
        // We need num.length() + 1 digits,
        // NOT minDigits digits.

        return build(
            need[0],
            need[1],
            need[2],
            need[3],
            num.size() + 1
        );
    }
};